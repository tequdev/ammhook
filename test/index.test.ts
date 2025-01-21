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
              // floatToLEXfl returns ""(empty string) if the fee is "0"
              // https://github.com/Transia-RnD/hooks-toolkit-ts/pull/51
              HookParameterValue: floatToLEXfl(fee).toUpperCase() || '0000000000000000',
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
    const namespaceStates = await StateUtility.getHookStateDir(testContext.client, testContext.hook1.address, hexNamespace(namespace))
    const getState = (key: string) => namespaceStates.find(state => state.HookStateKey === key)

    const currencyState = getState(padHexString(convertStringToHex('CUR')))
    const curA = currencyState!.HookStateData.substring(0, 40 * 2)
    const curB = currencyState!.HookStateData.substring(40 * 2, 80 * 2)
    const currencyA = {
      currency: hexToCurrency(curA.substring(0, 20 * 2)),
      issuer: encodeAccountID(Buffer.from(curA.substring(20 * 2, 40 * 2), 'hex'))
    }
    const currencyB = {
      currency: hexToCurrency(curB.substring(0, 20 * 2)),
      issuer: encodeAccountID(Buffer.from(curB.substring(20 * 2, 40 * 2), 'hex'))
    }

    const AState = getState(padHexString(convertStringToHex('A')))
    const balanceA = hexToXfl(AState!.HookStateData)
    const BState = getState(padHexString(convertStringToHex('B')))
    const balanceB = hexToXfl(BState!.HookStateData)
    const GState = getState(padHexString(convertStringToHex('G')))
    const gConstant = hexToXfl(GState!.HookStateData)
    const FACState = getState(padHexString(convertStringToHex('FAC')))
    const FAC = hexToXfl(FACState!.HookStateData)
    const ownerState = getState(padHexString(decodeAccountID(provider.address).toString('hex').toUpperCase()))
    const ownerLp = ownerState ? hexToXfl(ownerState!.HookStateData.substring(0, 8 * 2)) : undefined
    const ownerFeeSetting = ownerState ? hexToXfl(ownerState!.HookStateData.substring(8 * 2, 16 * 2)) : undefined
    const TOTState = getState(padHexString(convertStringToHex('TOT')))
    const TOT = hexToXfl(TOTState!.HookStateData)
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
      'Invalid AMM fee %s',
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
          { issuer: testContext.gw.address, currency: 'EUR', value: '100' },
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
        expect(currencyA.issuer).toBe(testContext.gw.address)
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
        await fundIOU(testContext.gw, testContext.alice, {
          issuer: testContext.gw.address,
          currency: 'EUR',
          value: '1000000000',
        })
        const response = await deposit(
          testContext.alice,
          {
            issuer: testContext.gw.address,
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
        expect(currencyA.issuer).toBe(testContext.gw.address)
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
        await fundIOU(testContext.gw, testContext.bob, {
          issuer: testContext.gw.address,
          currency: 'EUR',
          value: '1000',
        })
        await deposit(
          testContext.alice,
          { issuer: testContext.gw.address, currency: 'EUR', value: '100', },
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
            { issuer: testContext.gw.address, currency: 'EUR', value: a, },
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
          { issuer: testContext.gw.address, currency: 'EUR', value: a, },
          { issuer: testContext.gw.address, currency: 'USD', value: b, }
        )
      })
      it('deposit from another account', async () => {
        onTestFinished(async () => {
          await withdraw(testContext.bob)
        })
        await deposit(
          testContext.bob,
          { issuer: testContext.gw.address, currency: 'EUR', value: '100', },
          { issuer: testContext.gw.address, currency: 'USD', value: '100', }
        )
      })
    })
    describe('withdraw', () => {
      describe('errors', () => {
        beforeEach(async () => {
          await fundIOU(testContext.gw, testContext.alice, {
            issuer: testContext.gw.address,
            currency: 'EUR',
            value: '1000',
          })
          await deposit(
            testContext.alice,
            { issuer: testContext.gw.address, currency: 'EUR', value: '100', },
            { issuer: testContext.gw.address, currency: 'USD', value: '100', }
          )
        })
        afterEach(async () => {
          await withdraw(testContext.alice)
        })
        it.each([-1, -0.1, -0.01])("Invalid LPToken amount %s", async (amount) => {
          const response = withdraw(testContext.alice, amount.toString())
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
            { issuer: testContext.gw.address, currency: 'EUR', value: '100', },
            { issuer: testContext.gw.address, currency: 'USD', value: '100', }
          )
        })
        it.each([0, 100, 101])('withdraw All %s', async (amount) => {
          await withdraw(testContext.alice, amount.toString())
        })
        it.each([1, 50, 99])('withdraw partial A (%s) -> B', async (amount) => {
          onTestFinished(async () => {
            await withdraw(testContext.alice)
          })
          await withdraw(testContext.alice, amount.toString())
          const states = await getStates(testContext.alice)
          expect(states.balanceA).toBe(100 - amount)
          expect(states.balanceB).toBe(100 - amount)
          expect(states.ownerLp).toBe(100 - amount)
          expect(states.TOT).toBe(100 - amount)
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
        it.each([0, 100, 101])('withdraw All %s', async (amount) => {
          await withdraw(testContext.alice, amount.toString())
        })
        it.each([1, 50, 99])('withdraw A (%s) -> B', async (amount) => {
          onTestFinished(async () => {
            await withdraw(testContext.alice)
          })
          await withdraw(testContext.alice, amount.toString())
          const states = await getStates(testContext.alice)
          expect(states.balanceA).toBe(100 - amount)
          expect(states.balanceB).toBe(100 - amount)
          expect(states.ownerLp).toBe(100 - amount)
          expect(states.TOT).toBe(100 - amount)
        })
      })
    })
    describe('swap', () => {
      describe('without fee', () => {
        beforeEach(async () => {
          await fundIOU(testContext.gw, testContext.alice, {
            issuer: testContext.gw.address,
            currency: 'EUR',
            value: '100000',
          })
          await fundIOU(testContext.gw, testContext.bob, {
            issuer: testContext.gw.address,
            currency: 'EUR',
            value: '100000',
          })
          await deposit(
            testContext.alice,
            { issuer: testContext.gw.address, currency: 'EUR', value: '1000', },
            { issuer: testContext.gw.address, currency: 'USD', value: '1000', }
            , '0'
          )
        })
        afterEach(async () => {
          await withdraw(testContext.alice)
        })
        it.each([1, 10, 20, 50, 100, 250, 500, 1000, 2500,/*5000,*/ 10000])('swap A (%s) -> B', async (amount) => {
          // 5000 will cause `AMM: Invariant failure A*B<G.`
          await swap(testContext.alice, {
            issuer: testContext.gw.address,
            currency: 'EUR',
            value: amount.toString(),
          })
          const states = await getStates(testContext.alice)
          expect(states.balanceA).toBe(1000 + amount)
          expect(states.balanceB).toBeCloseTo((1000000 / (1000 + amount)))
        })
      })
      describe('with fee', () => {
        beforeEach(async () => {
          await fundIOU(testContext.gw, testContext.alice, {
            issuer: testContext.gw.address,
            currency: 'EUR',
            value: '1000',
          })
          await deposit(
            testContext.alice,
            { issuer: testContext.gw.address, currency: 'EUR', value: '100', },
            { issuer: testContext.gw.address, currency: 'USD', value: '100', }
          )
        })
        afterEach(async () => {
          await withdraw(testContext.alice, '')
        })
        describe('IOU/IOU', () => {
          it.each([10, 100, 200, 1000])('swap A (%s) -> B', async (amount) => {
            const response = await swap(testContext.alice, {
              issuer: testContext.gw.address,
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
            const states = await getStates(testContext.alice)
            const expectedA = 100 + amount
            const expectedConstant = 10000
            const expectedFAC = 0.1
            const expectedTotalLp = 100

            const afterB_calcFromConstant = expectedConstant / expectedA
            const changeB = 100 - afterB_calcFromConstant
            const changeB_appliedFee = changeB * (1 - (expectedFAC / expectedTotalLp))
            const expectedB = 100 - changeB_appliedFee

            expect(states.balanceA).toBe(expectedA)
            expect(states.gConstant).toBe(expectedConstant)
            expect(states.FAC).toBe(expectedFAC)
            expect(states.TOT).toBe(expectedTotalLp)
            expect(states.balanceB).toBeCloseTo(expectedB)
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
            const states = await getStates(testContext.alice)
            const expectedB = 100 + amount
            const expectedConstant = 10000
            const expectedFAC = 0.1
            const expectedTotalLp = 100
            const afterA_calcFromConstant = expectedConstant / expectedB
            const changeA = 100 - afterA_calcFromConstant
            const changeA_appliedFee = changeA * (1 - (expectedFAC / expectedTotalLp))
            const expectedA = 100 - changeA_appliedFee

            expect(states.balanceB).toBe(expectedB)
            expect(states.gConstant).toBe(expectedConstant)
            expect(states.balanceA * states.balanceB).toBeGreaterThanOrEqual(expectedConstant)
            expect(expectedA).toBeCloseTo(states.balanceA)
          })
        })
        describe('XAH/IOU', () => {
          it.todo('swap')
        })
      })
    })
    describe('lptoken calculation', () => {
      beforeEach(async () => {
        await fundIOU(testContext.gw, testContext.alice, {
          issuer: testContext.gw.address,
          currency: 'EUR',
          value: '2000',
        })
        await fundIOU(testContext.gw, testContext.bob, {
          issuer: testContext.gw.address,
          currency: 'EUR',
          value: '2000',
        })
        await deposit(
          testContext.alice,
          { issuer: testContext.gw.address, currency: 'EUR', value: '100', },
          { issuer: testContext.gw.address, currency: 'USD', value: '100', },
          '0'
        )
      })
      afterEach(async () => {
        await withdraw(testContext.alice)
      })
      it('Additional deposits made by the same account', async () => {
        const s = await getStates(testContext.alice)
        expect(s.ownerLp).toBe(100)
        expect(s.TOT).toBe(100)
        {
          await deposit(testContext.alice, { issuer: testContext.gw.address, currency: 'EUR', value: '100', }, { issuer: testContext.gw.address, currency: 'USD', value: '100', })
          const states = await getStates(testContext.alice)
          expect(states.ownerLp).toBe(200)
          expect(states.TOT).toBe(200)
        }
        {
          await withdraw(testContext.alice, '50')
          const states = await getStates(testContext.alice)
          expect(states.ownerLp).toBe(150)
          expect(states.TOT).toBe(150)
        }
        {
          await withdraw(testContext.alice, '100')
          const states = await getStates(testContext.alice)
          expect(states.ownerLp).toBe(50)
          expect(states.TOT).toBe(50)
        }
      })
      it('Additional deposits made by a different account', async () => {
        onTestFinished(async () => {
          await withdraw(testContext.bob)
        })
        const s = await getStates(testContext.alice)
        expect(s.ownerLp).toBe(100)
        expect(s.TOT).toBe(100)

        await fundIOU(testContext.gw, testContext.bob, { issuer: testContext.gw.address, currency: 'EUR', value: '1000', })
        {
          await deposit(testContext.bob, { issuer: testContext.gw.address, currency: 'EUR', value: '100', }, { issuer: testContext.gw.address, currency: 'USD', value: '100', })
          const states = await getStates(testContext.bob)
          expect(states.ownerLp).toBe(100)
          expect(states.TOT).toBe(200)
        }
        {
          await withdraw(testContext.alice, '50')
          const states = await getStates(testContext.alice)
          expect(states.ownerLp).toBe(50)
          expect(states.TOT).toBe(150)
        }
        {
          await withdraw(testContext.bob, '50')
          const states = await getStates(testContext.bob)
          expect(states.ownerLp).toBe(50)
          expect(states.TOT).toBe(100)
        }
      })
      it('deposit small amount', async () => {
        const s = await getStates(testContext.alice)
        expect(s.ownerLp).toBe(100)
        expect(s.TOT).toBe(100)
        expect(s.balanceA).toBe(100)
        expect(s.balanceB).toBe(100)

        await deposit(testContext.alice, { issuer: testContext.gw.address, currency: 'EUR', value: '10', }, { issuer: testContext.gw.address, currency: 'USD', value: '10', })
        const states = await getStates(testContext.alice)
        expect(states.ownerLp).toBe(110)
        expect(states.TOT).toBe(110)
        expect(states.gConstant).toBe(110 * 110)
        expect(states.balanceA).toBe(110)
        expect(states.balanceB).toBe(110)
      })
      it('deposit large amount', async () => {
        const s = await getStates(testContext.alice)
        expect(s.balanceA).toBe(100)
        expect(s.balanceB).toBe(100)
        expect(s.ownerLp).toBe(100)
        expect(s.TOT).toBe(100)

        await deposit(testContext.alice, { issuer: testContext.gw.address, currency: 'EUR', value: '1000', }, { issuer: testContext.gw.address, currency: 'USD', value: '1000', })
        {
          const states = await getStates(testContext.alice)
          expect(states.ownerLp).toBe(1100)
          expect(states.TOT).toBe(1100)
          expect(states.gConstant).toBe(1100 * 1100)
          expect(states.balanceA).toBe(1100)
          expect(states.balanceB).toBe(1100)
        }

        await withdraw(testContext.alice, '100')
        {
          const states = await getStates(testContext.alice)
          expect(states.ownerLp).toBe(1000)
          expect(states.TOT).toBe(1000)
          expect(states.balanceA).toBe(1000)
          expect(states.balanceB).toBe(1000)
        }
      })
    })
    describe('pool fee', () => {
      afterEach(async () => {
        await withdraw(testContext.alice)
      })
      it('same account', async () => {
        await deposit(testContext.alice, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0')
        const states = await getStates(testContext.alice)
        expect(states.FAC).toBe(0)
        expect(states.ownerFeeSetting).toBe(0)
        // update to zero
        await deposit(testContext.alice, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0')
        {
          const states = await getStates(testContext.alice)
          expect(states.FAC).toBe(0)
          expect(states.ownerFeeSetting).toBe(0)
        }
        // increase
        await deposit(testContext.alice, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0.03')
        {
          const states = await getStates(testContext.alice)
          expect(states.FAC).toBe(0.03 * 300)
          expect(states.ownerFeeSetting).toBe(0.03)
        }
        // decrease
        await deposit(testContext.alice, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0.01')
        {
          const states = await getStates(testContext.alice)
          expect(states.FAC).toBe(0.01 * 400)
          expect(states.ownerFeeSetting).toBe(0.01)
        }
        // partial withdraw
        await withdraw(testContext.alice, '200')
        {
          const states = await getStates(testContext.alice)
          expect(states.FAC).toBe(0.01 * 200)
          expect(states.ownerFeeSetting).toBe(0.01)
        }
      })
      it('different account', async () => {
        await deposit(testContext.alice, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0.01')
        const states = await getStates(testContext.bob)
        expect(states.FAC).toBe(0.01 * 100)
        expect(states.ownerFeeSetting).toBeUndefined()
        // vote to zero
        await deposit(testContext.bob, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0')
        {
          const states = await getStates(testContext.bob)
          expect(states.FAC).toBe(0.01 * 100)
          expect(states.ownerFeeSetting).toBe(0)
        }
        // increase
        await deposit(testContext.bob, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0.03')
        {
          const states = await getStates(testContext.bob)
          expect(states.FAC).toBe(0.01 * 100 + 0.03 * 200)
          expect(states.ownerFeeSetting).toBe(0.03)
        }
        // decrease
        await deposit(testContext.bob, '100', { issuer: testContext.gw.address, currency: 'USD', value: '100', }, '0.01')
        {
          const states = await getStates(testContext.bob)
          expect(states.FAC).toBe(0.01 * 100 + 0.01 * 300)
          expect(states.ownerFeeSetting).toBe(0.01)
        }
        // partial withdraw
        await withdraw(testContext.bob, '200')
        {
          const states = await getStates(testContext.bob)
          expect(states.FAC).toBe(0.01 * 100 + 0.01 * 100)
          expect(states.ownerFeeSetting).toBe(0.01)
        }
        // withdraw
        await withdraw(testContext.bob)
        {
          const states = await getStates(testContext.bob)
          expect(states.FAC).toBe(0.01 * 100)
          expect(states.ownerFeeSetting).toBeUndefined()
        }
      })
    })
  })
  describe.todo('edge cases', () => {
    it.todo('large amount trade to small pool')
    it.todo('small amount trade to large pool')
  })
  // TransferRate
})

