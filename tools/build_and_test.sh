#!/bin/bash

cd $(dirname "$(readlink -f "$BASH_SOURCE")")/..

[[ -z "${WITHIN_DEV}" ]] && echo "Run this in the development environment!" && exit 1

mkdir -p build

cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/x86-linux-gcc-11.cmake
make all && ctest --verbose
