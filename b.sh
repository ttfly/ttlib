#!/bin/sh
mkdir -i build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
cd -
