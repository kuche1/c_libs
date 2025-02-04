#! /usr/bin/env bash

{
    set -euo pipefail

    # https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index

    COMPILER='gcc'
    COMPILER_FLAGS='-std=c99' # standard
    COMPILER_FLAGS="$COMPILER_FLAGS -Werror -Wextra -Wall -pedantic" # strict
    COMPILER_FLAGS="$COMPILER_FLAGS -Wfatal-errors" # stop on first encountered error
    COMPILER_FLAGS="$COMPILER_FLAGS -Wshadow" # shadow variables
    COMPILER_FLAGS="$COMPILER_FLAGS -fwrapv" # make signed integer operations defined

    COMP="$COMPILER $COMPILER_FLAGS"
    COMP_LIB_SHARED="$COMP -c -fPIC"

    CHECK="$COMP -fsyntax-only"

    function compile_and_test()
    {
        test $# = 1
        local name=$1

        $CHECK $name.c $name.h
        $COMP_LIB_SHARED -o $name.so $name.c
        $COMP -o ${name}_test ${name}_test.c $name.h $name.so
        ./buf_test
    }

    compile_and_test buf
}