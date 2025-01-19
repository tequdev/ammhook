import {
  SetHookFlags,
  type TransactionMetadata,
  Wallet,
  calculateHookOn,
  convertStringToHex,
  decodeAccountID,
  encodeAccountID,
  getBalanceChanges,
  xrpToDrops,
} from '@transia/xrpl'

import {
  // serverUrl,
  type XrplIntegrationTestContext,
  ledgerAccept,
  serverUrl,
  setupClient,
  teardownClient,
} from '@transia/hooks-toolkit/dist/npm/src/libs/xrpl-helpers'

import {
  type SetHookParams,
  setHooksV3,
  hexNamespace,
  type iHook,
  readHookBinaryHexFromNS,
  clearAllHooksV3,
  clearHookStateV3,
  Xrpld,
  floatToLEXfl,
  ExecutionUtility,
  StateUtility,
  padHexString,
} from '@transia/hooks-toolkit'

import {
  hexToCurrency,
  hexToXfl,
} from '@transia/hooks-toolkit/dist/npm/src/libs/binary-models'
import { hashURIToken } from '@transia/xrpl/dist/npm/utils/hashes'
import type { Amount } from '@transia/xrpl/dist/npm/models/common'

import Big from 'big.js'

const namespace = 'namespace'

const mergeBalanceChanges = (
  changes1: ReturnType<typeof getBalanceChanges>,
  changes2: ReturnType<typeof getBalanceChanges>
) => {
  const mergedChanges = [...changes2]

  for (const change1 of changes1) {
    const existingAccount = mergedChanges.find(
      (c) => c.account === change1.account
    )
    if (existingAccount) {
      for (const balance1 of change1.balances) {
        const existingBalance = existingAccount.balances.find(
          (b) => b.issuer === balance1.issuer && b.currency === balance1.currency
        )
        if (existingBalance) {
          existingBalance.value = Big(existingBalance.value)
            .plus(Big(balance1.value))
            .toString()
        } else {
          existingAccount.balances.push({ ...balance1 })
        }
      }
    } else {
      mergedChanges.push({ ...change1 })
    }
  }
  return mergedChanges;
}

describe('test', () => {
  let testContext: XrplIntegrationTestContext

  const newAccount = async (amount?: string) => {
    const wallet = Wallet.generate()
    const response = await testContext.client.request({
      command: 'server_info',
    })
    const ledger = response.result.info.validated_ledger
    if (!ledger) throw new Error('No ledger found')
    const { reserve_base_xrp, reserve_inc_xrp } = ledger

    let Amount = Number(xrpToDrops(reserve_base_xrp + reserve_inc_xrp * 3))
    Amount += Number(amount ? amount : 0)
    await Xrpld.submit(testContext.client, {
      tx: {
        TransactionType: 'Payment',
        Account: testContext.alice.address,
        Destination: wallet.address,
        Amount: Amount.toString(),
      },
      wallet: testContext.alice,
    })
    return wallet
  }

  const fundIOU = async (from: Wallet, to: Wallet, amount: Amount) => {
    await Xrpld.submit(testContext.client, {
      tx: {
        TransactionType: 'Remit',
        Account: from.address,
        Destination: to.address,
        Amounts: [
          { AmountEntry: { Amount: amount } },
        ] as any,
      },
      wallet: from
    })
    await ledgerAccept(testContext.client)
  }

  const deposit = (wallet: Wallet, amount1: Amount, amount2: Amount, fee?: string) => {
    return Xrpld.submit(testContext.client, {
      tx: {
        TransactionType: 'Remit',
        Account: wallet.address,
        Destination: testContext.hook1.address,
        Amounts: [
          { AmountEntry: { Amount: amount1 } },
          { AmountEntry: { Amount: amount2 } },
        ] as any,
        HookParameters: fee ? [
          {
            HookParameter: {
              HookParameterName: convertStringToHex('FEE'),
              HookParameterValue: floatToLEXfl(fee).toUpperCase(),
            },
          },
        ] : undefined,
      },
      wallet,
    })
  }

  const withdraw = (wallet: Wallet, amount?: string) => {
    return Xrpld.submit(testContext.client, {
      tx: {
        TransactionType: 'Remit',
        Account: wallet.address,
        Destination: testContext.hook1.address,
        HookParameters: amount ? [
          {
            HookParameter: {
              HookParameterName: convertStringToHex('WDR'),
              HookParameterValue: floatToLEXfl(amount).toUpperCase(),
            },
          },
        ] : undefined,
      },
      wallet,
    })
  }

  const swap = async (wallet: Wallet, amount: Amount) => {
    return Xrpld.submit(testContext.client, {
      tx: {
        TransactionType: 'Remit',
        Account: wallet.address,
        Destination: testContext.hook1.address,
        Amounts: [
          { AmountEntry: { Amount: amount, }, },
        ] as any,
      },
      wallet: wallet,
    })
  }

  const getBalanceChangesThroughHook = async (meta: TransactionMetadata) => {
    const changes1 = getBalanceChanges(meta)
    if (!meta.HookEmissions) throw new Error('HookEmissions not found')
    const emittedTxId = meta.HookEmissions[0].HookEmission.EmittedTxnID
    const emittedTxResponse = await testContext.client.request({
      command: 'tx',
      transaction: emittedTxId,
    })
    const changes2 = getBalanceChanges(emittedTxResponse.result.meta as TransactionMetadata)
    return mergeBalanceChanges(changes1, changes2)
  }

  const getStates = async (provider: Wallet) => {
    const getState = async (key: string) => StateUtility.getHookState(testContext.client, testContext.hook1.address, key, hexNamespace(namespace))
    const currencyState = await getState(padHexString(convertStringToHex('CUR')))
    const curA = currencyState.HookStateData.substring(0, 40 * 2)
    const curB = currencyState.HookStateData.substring(40 * 2, 80 * 2)
    const currencyA = {
      currency: hexToCurrency(curA.substring(0, 20 * 2)),
      issuer: encodeAccountID(Buffer.from(curA.substring(20 * 2, 40 * 2), 'hex'))
    }
    const currencyB = {
      currency: hexToCurrency(curB.substring(0, 20 * 2)),
      issuer: encodeAccountID(Buffer.from(curB.substring(20 * 2, 40 * 2), 'hex'))
    }

    const AState = await getState(padHexString(convertStringToHex('A')))
    const balanceA = hexToXfl(AState.HookStateData)
    const BState = await getState(padHexString(convertStringToHex('B')))
    const balanceB = hexToXfl(BState.HookStateData)
    const GState = await getState(padHexString(convertStringToHex('G')))
    const gConstant = hexToXfl(GState.HookStateData)
    const FACState = await getState(padHexString(convertStringToHex('FAC')))
    const FAC = hexToXfl(FACState.HookStateData)
    const ownerState = await getState(padHexString(decodeAccountID(provider.address).toString('hex').toUpperCase()))
    const ownerLp = hexToXfl(ownerState.HookStateData.substring(0, 8 * 2))
    const ownerFeeSetting = hexToXfl(ownerState.HookStateData.substring(8 * 2, 16 * 2))
    const TOTState = await getState(padHexString(convertStringToHex('TOT')))
    const TOT = hexToXfl(TOTState.HookStateData)
    return {
      currencyA,
      currencyB,
      balanceA,
      balanceB,
      gConstant,
      FAC,
      ownerLp,
      ownerFeeSetting,
      TOT,
    }
  }

  beforeAll(async () => {
    testContext = await setupClient(serverUrl)
    const hook = {
      CreateCode: readHookBinaryHexFromNS('../build/amm'),
      Flags: SetHookFlags.hsfOverride,
      HookOn: calculateHookOn(['Invoke', 'Remit']),
      HookNamespace: hexNamespace(namespace),
      HookApiVersion: 0,
    } as iHook
    await setHooksV3({
      client: testContext.client,
      seed: testContext.hook1.seed,
      hooks: [{ Hook: hook }],
    } as SetHookParams)
  })

  afterAll(async () => {
    const clearHook = {
      Flags: SetHookFlags.hsfNSDelete,
      HookNamespace: hexNamespace(namespace),
    } as iHook
    await clearHookStateV3({
      client: testContext.client,
      seed: testContext.hook1.seed,
      hooks: [{ Hook: clearHook }],
    } as SetHookParams)
    await clearAllHooksV3({
      client: testContext.client,
      seed: testContext.hook1.seed,
    } as SetHookParams)
    await teardownClient(testContext)
  })

  describe('errors', () => {
    it('outgoing txn / non-remit', async () => {
      {
        const response = await Xrpld.submit(testContext.client, {
          tx: {
            TransactionType: 'Invoke',
            Account: testContext.hook1.address,
          },
          wallet: testContext.hook1,
        })
        const hookExecutions = await ExecutionUtility.getHookExecutionsFromMeta(
          testContext.client,
          response.meta as TransactionMetadata,
        )
        expect(hookExecutions.executions[0].HookReturnString).toBe(
          'AMM: Passing outgoing txn.',
        )
      }
      {
        const response = await Xrpld.submit(testContext.client, {
          tx: {
            TransactionType: 'Invoke',
            Account: testContext.alice.address,
            Destination: testContext.hook1.address,
          },
          wallet: testContext.alice,
        })
        const hookExecutions = await ExecutionUtility.getHookExecutionsFromMeta(
          testContext.client,
          response.meta as TransactionMetadata,
        )
        expect(hookExecutions.executions[0].HookReturnString).toBe(
          'AMM: Passing non-REMIT txn.',
        )
      }
    })

    it.each(['0.06', '0.050001', '-1', '-0.000001'])(
      'Invalid AMM fee',
      async (fee) => {
        const response = Xrpld.submit(testContext.client, {
          tx: {
            TransactionType: 'Remit',
            Account: testContext.alice.address,
            Destination: testContext.hook1.address,
            Amounts: [
              { AmountEntry: { Amount: '100', }, },
            ] as any,
            HookParameters: [
              {
                HookParameter: {
                  HookParameterName: convertStringToHex('FEE'),
                  HookParameterValue: floatToLEXfl(fee).toUpperCase(),
                },
              },
            ],
          },
          wallet: testContext.alice,
        })
        await expect(response).rejects.toThrow(
          'AMM: Invalid proposed FEE, must be between 0 and 0.05 (5%) as XFL LE',
        )
      },
    )

    it('Block URITokens', async () => {
      const url = 'https://example.com'
      {
        const response = Xrpld.submit(testContext.client, {
          tx: {
            TransactionType: 'Remit',
            Account: testContext.alice.address,
            Destination: testContext.hook1.address,
            MintURIToken: {
              URI: convertStringToHex(url),
            },
          },
          wallet: testContext.alice,
        })
        await expect(response).rejects.toThrow(
          'AMM: Cannot accept REMIT with URITokens.',
        )
      }
      {
        await Xrpld.submit(testContext.client, {
          tx: {
            TransactionType: 'URITokenMint',
            Account: testContext.alice.address,
            URI: convertStringToHex(url),
          },
          wallet: testContext.alice,
        })
        onTestFinished(async () => {
          await Xrpld.submit(testContext.client, {
            tx: {
              TransactionType: 'URITokenBurn',
              Account: testContext.alice.address,
              URITokenID: hashURIToken(testContext.alice.address, url),
            },
            wallet: testContext.alice,
          })
        })

        const response = Xrpld.submit(testContext.client, {
          tx: {
            TransactionType: 'Remit',
            Account: testContext.alice.address,
            Destination: testContext.hook1.address,
            URITokenIDs: [hashURIToken(testContext.alice.address, url)],
          },
          wallet: testContext.alice,
        })
        await expect(response).rejects.toThrow(
          'AMM: Cannot accept REMIT with URITokens.',
        )
      }
    })

    it('Amounts.length > 2', async () => {
      {
        const response = Xrpld.submit(testContext.client, {
          tx: {
            TransactionType: 'Remit',
            Account: testContext.alice.address,
            Destination: testContext.hook1.address,
            Amounts: [
              { AmountEntry: { Amount: '100', }, },
              { AmountEntry: { Amount: { issuer: testContext.alice.address, currency: 'ABC', value: '100', }, }, },
              { AmountEntry: { Amount: { issuer: testContext.alice.address, currency: 'XYZ', value: '100', }, }, },
            ] as any,
          },
          wallet: testContext.alice,
        })
        await expect(response).rejects.toThrow(
          'AMM: Send either 0, 1 or 2 currencies to use AMM.',
        )
      }
    })

    it('Insufficient funds', async () => {
      const hook = {
        CreateCode: readHookBinaryHexFromNS('../amm'),
        Flags: SetHookFlags.hsfOverride,
        HookOn: calculateHookOn(['Invoke', 'Remit']),
        HookNamespace: hexNamespace(namespace),
        HookApiVersion: 0,
      } as iHook
      const newAcc = await newAccount(`${hook.CreateCode!.length * 500 / 2}`)
      await setHooksV3({
        client: testContext.client,
        seed: newAcc.seed,
        hooks: [{ Hook: hook }],
      } as SetHookParams)
      const response = Xrpld.submit(testContext.client, {
        tx: {
          TransactionType: 'Remit',
          Account: testContext.alice.address,
          Destination: newAcc.address,
          Amounts: [
            { AmountEntry: { Amount: '100', }, },
            { AmountEntry: { Amount: { issuer: testContext.alice.address, currency: 'EUR', value: '100', }, }, },
          ] as any,
        },
        wallet: testContext.alice,
      })
      await expect(response).rejects.toThrow(
        'AMM: Error setting initial state (reserves?',
      )
    })

    describe('before setup', () => {
      it('0 currency, Withdraw', async () => {
        const response = withdraw(testContext.alice)
        await expect(response).rejects.toThrow(
          'AMM: Setup the AMM by remitting two currencies.',
        )
      })
      it('1 currency, Swap', async () => {
        const response = swap(testContext.alice, '100')
        await expect(response).rejects.toThrow(
          'AMM: Cannot setup new AMM without two currencies. Send two.',
        )
      })
      it.skip('2 currency, Deposit: this is setup')
    })
  })
  describe('success', () => {
    describe('setup', () => {
      afterEach(async () => {
        await withdraw(testContext.alice)
      })
      it('setup - 100EUR/100USD', async () => {
        const response = await deposit(
          testContext.alice,
          { issuer: testContext.alice.address, currency: 'EUR', value: '100' },
          { issuer: testContext.gw.address, currency: 'USD', value: '100' },
        )
        const { executions } = await ExecutionUtility.getHookExecutionsFromMeta(
          testContext.client,
          response.meta as TransactionMetadata,
        )
        expect(executions[0].HookReturnString).toBe('AMM: Created.')
        const {
          currencyA,
          currencyB,
          balanceA,
          balanceB,
          gConstant,
          FAC,
          ownerLp,
          ownerFeeSetting,
          TOT,
        } = await getStates(testContext.alice)
        expect(currencyA.currency).toBe('EUR')
        expect(currencyA.issuer).toBe(testContext.alice.address)
        expect(currencyB.currency).toBe('USD')
        expect(currencyB.issuer).toBe(testContext.gw.address)
        expect(balanceA).toBe(100)
        expect(balanceB).toBe(100)
        expect(gConstant).toBe(10000)
        expect(FAC).toBe(100 * 0.001)
        expect(ownerLp).toBe(100)
        expect(ownerFeeSetting).toBe(0.001)
        expect(TOT).toBe(100)
      })
      it('setup2 - 1000000000EUR/0.1USD with FEE', async () => {
        const response = await deposit(
          testContext.alice,
          {
            issuer: testContext.alice.address,
            currency: 'EUR',
            value: '1000000000',
          },
          { issuer: testContext.gw.address, currency: 'USD', value: '0.1' },
          '0.02',
        )
        const { executions } = await ExecutionUtility.getHookExecutionsFromMeta(
          testContext.client,
          response.meta as TransactionMetadata,
        )
        expect(executions[0].HookReturnString).toBe('AMM: Created.')
        const {
          currencyA,
          currencyB,
          balanceA,
          balanceB,
          gConstant,
          FAC,
          ownerLp,
          ownerFeeSetting,
          TOT,
        } = await getStates(testContext.alice)
        expect(currencyA.currency).toBe('EUR')
        expect(currencyA.issuer).toBe(testContext.alice.address)
        expect(currencyB.currency).toBe('USD')
        expect(currencyB.issuer).toBe(testContext.gw.address)
        expect(balanceA).toBe(1000000000)
        expect(balanceB).toBe(0.1)
        expect(gConstant).toBe(100000000)
        expect(FAC).toBe(100 * 0.02)
        expect(ownerLp).toBe(100)
        expect(ownerFeeSetting).toBe(0.02)
        expect(TOT).toBe(100)
      })
      it('setup4 - 0.000100XAH/100USD', async () => {
        await deposit(
          testContext.alice,
          '100',
          {
            issuer: testContext.gw.address,
            currency: 'USD',
            value: '0.1',
          }
        )
        const states = await getStates(testContext.alice)
        expect(states.balanceA).toBe(0.0001)
        expect(states.balanceB).toBe(0.1)
      })
      it('setup5 - 100XAH/1000USD', async () => {
        await deposit(testContext.alice, xrpToDrops('100'), {
          issuer: testContext.gw.address,
          currency: 'USD',
          value: '1000',
        })
        const states = await getStates(testContext.alice)
        expect(states.balanceA).toBe(100)
        expect(states.balanceB).toBe(1000)
      })
      it('setup6 - 1000XAH/0.000001USD', async () => {
        await deposit(testContext.alice, xrpToDrops('1000'), {
          issuer: testContext.gw.address,
          currency: 'USD',
          value: '0.000001',
        })
        const states = await getStates(testContext.alice)
        expect(states.balanceA).toBe(1000)
        expect(states.balanceB).toBe(0.000001)
      })
    })
    describe('deposit', async () => {
      beforeEach(async () => {
        await deposit(
          testContext.alice,
          { issuer: testContext.alice.address, currency: 'EUR', value: '100', },
          { issuer: testContext.gw.address, currency: 'USD', value: '100', }
        )
      })
      afterEach(async () => {
        await withdraw(testContext.alice)
      })
      it.each([['101.1', '100'], ['100', '101.1']])('ratio error', async (a, b) => {
        {
          const response = deposit(
            testContext.alice,
            { issuer: testContext.alice.address, currency: 'EUR', value: a, },
            { issuer: testContext.gw.address, currency: 'USD', value: b, }
          )
          await expect(response).rejects.toThrow(
            'AMM: Divergence too great. Send amounts at the correct ratio',
          )
        }
      })
      it.each([['101', '100'], ['100', '101']])('additional deposit', async (a, b) => {
        await deposit(
          testContext.alice,
          { issuer: testContext.alice.address, currency: 'EUR', value: a, },
          { issuer: testContext.gw.address, currency: 'USD', value: b, }
        )
      })
      it.todo('deposit from another account', async () => {
        onTestFinished(async () => {
          await withdraw(testContext.bob)
        })
        await fundIOU(testContext.alice, testContext.bob, {
          issuer: testContext.alice.address,
          currency: 'EUR',
          value: '1000',
        })
        await deposit(
          testContext.bob,
          { issuer: testContext.alice.address, currency: 'EUR', value: '100', },
          { issuer: testContext.gw.address, currency: 'USD', value: '100', }
        )
      })
    })
    describe('withdraw', () => {
      describe('errors', () => {
        beforeEach(async () => {
          await deposit(
            testContext.alice,
            { issuer: testContext.alice.address, currency: 'EUR', value: '100', },
            { issuer: testContext.gw.address, currency: 'USD', value: '100', }
          )
        })
        afterEach(async () => {
          await withdraw(testContext.alice)
        })
        it.todo("Invalid value", async () => {
          const response = await withdraw(testContext.alice, '0')
          await expect(response).rejects.toThrow(
            'AMM: Minimum withdrawal amount is 1% of holdings.',
          )
        })
        it.each([0.1, 0.9])('Very small partial withdraw %s', async (amount) => {
          const response = withdraw(testContext.alice, amount.toString())
          await expect(response).rejects.toThrow(
            'AMM: Minimum withdrawal amount is 1% of holdings.',
          )
        })
        it.each([99.1, 99.9])('Very large partial withdraw %s', async (amount) => {
          const response = withdraw(testContext.alice, amount.toString())
          await expect(response).rejects.toThrow(
            'AMM: To withdraw all omit the WDR param on the REMIT txn.',
          )
        })
      })
      describe('IOU/IOU', () => {
        beforeEach(async () => {
          await deposit(
            testContext.alice,
            { issuer: testContext.alice.address, currency: 'EUR', value: '100', },
            { issuer: testContext.gw.address, currency: 'USD', value: '100', }
          )
        })
        it.each([0, 100, 101])('withdraw All', async (amount) => {
          await withdraw(testContext.alice, amount.toString())
        })
        it.each([1, 50, 99])('withdraw partial A (%s) -> B', async (amount) => {
          onTestFinished(async () => {
            await withdraw(testContext.alice)
          })
          const response = await withdraw(testContext.alice, amount.toString())
        })
      })
      describe('XAH/IOU', () => {
        beforeEach(async () => {
          await deposit(
            testContext.alice,
            xrpToDrops(100),
            { issuer: testContext.gw.address, currency: 'USD', value: '100', }
          )
        })
        it.each([0, 100, 101])('withdraw All', async (amount) => {
          await withdraw(testContext.alice, amount.toString())
        })
        it.each([1, 50, 99])('withdraw A (%s) -> B', async (amount) => {
          onTestFinished(async () => {
            await withdraw(testContext.alice)
          })
          const response = await withdraw(testContext.alice, amount.toString())
        })
      })
    })
    describe('swap', () => {
      beforeEach(async () => {
        await deposit(
          testContext.alice,
          { issuer: testContext.alice.address, currency: 'EUR', value: '100', },
          { issuer: testContext.gw.address, currency: 'USD', value: '100', }
        )
      })
      afterEach(async () => {
        await withdraw(testContext.alice, '')
      })
      describe('IOU/IOU', () => {
        it.each([10, 100, 200, 1000])('swap A (%s) -> B', async (amount) => {
          const response = await swap(testContext.alice, {
            issuer: testContext.alice.address,
            currency: 'EUR',
            value: amount.toString(),
          })
          const meta = response.meta as TransactionMetadata
          const { executions } =
            await ExecutionUtility.getHookExecutionsFromMeta(
              testContext.client,
              meta,
            )
          expect(executions[0].HookReturnString).toBe(
            'AMM: Emitted remit currency B.',
          ) // should be fixed

          await ledgerAccept(testContext.client)
          // const balanceChanges = await getBalanceChangesThroughHook(meta)
          const states = await getStates(testContext.alice)
          const expectedA = 100 + amount
          const expectedConstant = 10000
          const expectedFAC = 0.1
          const expectedTotalLp = 100
          const expectedB = Big(expectedConstant)
            .div(expectedA)
            .times(Big(1).minus(Big(expectedFAC).div(expectedTotalLp)))
            .toNumber()

          expect(states.balanceA).toBe(expectedA)
          // expect(states.balanceB).toBe(expectedB)
          expect(states.gConstant).toBe(expectedConstant)
          expect(
            Big(states.balanceA).times(states.balanceB).toNumber(),
          ).greaterThanOrEqual(expectedConstant)
        })
        it.each([10, 100, 200, 1000])('swap B (%s) -> A', async (amount) => {
          const response = await swap(testContext.alice, {
            issuer: testContext.gw.address,
            currency: 'USD',
            value: amount.toString(),
          })
          const meta = response.meta as TransactionMetadata
          const { executions } =
            await ExecutionUtility.getHookExecutionsFromMeta(
              testContext.client,
              meta,
            )
          expect(executions[0].HookReturnString).toBe(
            'AMM: Emitted remit currency B.',
          ) // should be fixed

          await ledgerAccept(testContext.client)
          // const balanceChanges = await getBalanceChangesThroughHook(meta)
          const states = await getStates(testContext.alice)
          const expectedB = 100 + amount
          const expectedConstant = 10000
          const expectedFAC = 0.1
          const expectedTotalLp = 100
          const expectedA =
            100 -
            (expectedConstant / expectedB) * (1 - expectedFAC / expectedTotalLp)
          expect(expectedB).toBe(states.balanceB)
          // expect(expectedA).toBe(states.balanceA)
          expect(expectedConstant).toBe(states.gConstant)
          expect(
            Big(states.balanceA).times(states.balanceB).toNumber(),
          ).greaterThanOrEqual(expectedConstant)
        })
      })
      describe('XAH/IOU', () => {
        it.todo('swap')
      })
    })
    describe('pool fee', () => {
      it.todo('new vote')
      it.todo('update vote')
      it.todo('delete vote')
    })
    describe.todo('edge cases', () => {
      it.todo('large amount trade to small pool')
      it.todo('small amount trade to large pool')
    })
    // TransferRate
  })
})

