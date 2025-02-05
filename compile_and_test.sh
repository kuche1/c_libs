#! /usr/bin/env bash

{
    # https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index

    set -euo pipefail

    ME=$(readlink -f -- "${BASH_SOURCE[0]}")
    HERE=$(dirname -- "$ME")

    IN="$HERE"
    OUT="$HERE/out"

    COMPILER='gcc'
    COMPILER_FLAGS='-std=c99' # standard
    COMPILER_FLAGS+=" -Werror -Wextra -Wall -pedantic" # strict
    COMPILER_FLAGS+=" -Wfatal-errors" # stop on first encountered error
    COMPILER_FLAGS+=" -Wshadow" # shadow variables
    COMPILER_FLAGS+=" -fwrapv" # make signed integer operations defined

    COMP="$COMPILER $COMPILER_FLAGS"
    COMP_LIB_SHARED="$COMP -c -fPIC"

    CHECK="$COMP -fsyntax-only"

    function compile_and_test()
    {
        set -euo pipefail

        test $# = 1
        local name="$1"

        local in="$IN/$name"
        local out="$OUT/$name"

        local additional_deps='err.h' # not really needed since it's only a header file

        $CHECK "$in.c" "$in.h" $additional_deps
        $COMP_LIB_SHARED -o "$out.so" "$in.c"

        $COMP -o "${out}_test" "${in}_test.c" "$in.h" "$out.so"
        "${out}_test"
    }

    shellcheck "$ME"
    mkdir -p "$OUT"
    compile_and_test buf
    # compile_and_test net # unfinished
    # compile_and_test com # unfinished
}
