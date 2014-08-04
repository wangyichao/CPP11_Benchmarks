#!/bin/bash
mkdir bin

# Compile loop benchmark

g++ -std=c++11 -pthread -O2 async.cpp -o bin/gcc-o2
g++ -std=c++11 -pthread -O3 async.cpp -o bin/gcc-o3
g++ -std=c++11 -pthread -Ofast async.cpp -o bin/gcc-of

icpc -std=c++11 -pthread -O2 async.cpp -o bin/icc-o2
icpc -std=c++11 -pthread -O3 async.cpp -o bin/icc-o3
icpc -std=c++11 -pthread -Ofast async.cpp -o bin/icc-of

clang++ -std=c++11 -pthread -O2 async.cpp -o bin/llvm-o2
clang++ -std=c++11 -pthread -O3 async.cpp -o bin/llvm-o3
clang++ -std=c++11 -pthread -Ofast async.cpp -o bin/llvm-of
