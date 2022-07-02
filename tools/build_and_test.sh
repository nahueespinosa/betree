#!/bin/bash

cd $(dirname "$(readlink -f "$BASH_SOURCE")")/..

[[ -z "${WITHIN_DEV}" ]] && echo "Run this in the development environment!" && exit 1

mkdir -p build

cd build
cmake ..
make all
ctest
