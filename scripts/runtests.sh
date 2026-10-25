#!/bin/zsh
# Run from project root dir, i.e., ./scripts/runtests.sh
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=true
cd build && make
ctest --test-dir tests
cd ..