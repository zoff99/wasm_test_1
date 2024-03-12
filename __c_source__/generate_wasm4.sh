#! /bin/sh

emcc \
    --no-entry \
    -s IGNORE_MISSING_MAIN=1 \
    -s MODULARIZE=1 \
    -flto \
    -s ERROR_ON_UNDEFINED_SYMBOLS=1 -s LLD_REPORT_UNDEFINED \
    -s ENVIRONMENT=web \
    -s EXIT_RUNTIME=0 \
    -s MALLOC=emmalloc \
    libsodium/libsodium-js/lib/libsodium.a \
    -I. \
    -I ./toxcore/ \
    -I ./libsodium/src/libsodium/include/ \
    -I ./libsodium/src/libsodium/include/sodium/ \
    ./toxcore/toxcore_amalgamation_no_toxav.c \
    -o lib.emcc.js lib.c \


cp -v ./lib.emcc.wasm ./lib.emcc.js \
    ../src/nativeSources/
