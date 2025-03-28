all:
	wasmcc amm.cpp -o amm.wasm -O3 -Wno-int-conversion -Wno-incompatible-pointer-types  -Wl,--allow-undefined -std=c++17 -I./ -mllvm -inline-threshold=10000
	wasm-opt amm.wasm -o amm.wasm -O3 
	hook-cleaner amm.wasm
	guard_checker amm.wasm
	
