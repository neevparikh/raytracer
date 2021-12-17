#!/usr/bin/env bash

./scripts/setup.sh
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make -j8
