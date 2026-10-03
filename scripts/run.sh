#!/bin/bash
set -e

cmake -S . -B build
cmake --build build
cd build
ctest --test-dir . --output-on-failure
cd ..