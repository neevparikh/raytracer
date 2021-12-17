#!/usr/bin/env bash

./scripts/setup.sh
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make -j8
