# Example: v8_wasm_compile_fuzzer
The `v8_wasm_compile_fuzzer` within the Chromium project is highly productive. Therefore, it may be a good idea to reuse its WebAssembly sample generator in AFL++ for fuzzing WebAssembly compilers.
## Note (Not Steps!)
- [Replace](https://chromium.googlesource.com/chromium/src/+/main/docs/clang.md#using-a-custom-clang-binary) the default `clang/clang++` compiler with modified `afl-cc` for chromium building.
- Copy the `snapshot_blob.bin` to your working dir if needed.