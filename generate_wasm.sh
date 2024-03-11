#! /bin/bash

#    -lembind \
#    --bind \
#    -flto \

emcc \
    --no-entry \
    -s IGNORE_MISSING_MAIN=1 \
    -s ERROR_ON_UNDEFINED_SYMBOLS=1 -s LLD_REPORT_UNDEFINED \
    -s EXIT_RUNTIME=0 \
    -s MALLOC=emmalloc \
    -o src/wasmJsMain/kotlin/lib.js src/nativeSources/lib.c \

ls -hal src/wasmJsMain/kotlin/lib.js src/wasmJsMain/kotlin/lib.wasm
