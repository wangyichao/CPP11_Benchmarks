#!/bin/bash
mkdir bin

# Compile loop benchmark

g++ -std=c++11 -O2 loop.cpp -o bin/gcc-o2
g++ -std=c++11 -O3 loop.cpp -o bin/gcc-o3
g++ -std=c++11 -Ofast loop.cpp -o bin/gcc-of

icpc -std=c++11 -O2 loop.cpp -o bin/icc-o2
icpc -std=c++11 -O3 loop.cpp -o bin/icc-o3
icpc -std=c++11 -Ofast loop.cpp -o bin/icc-of

clang++ -std=c++11 -O2 loop.cpp -o bin/llvm-o2
clang++ -std=c++11 -O3 loop.cpp -o bin/llvm-o3
clang++ -std=c++11 -Ofast loop.cpp -o bin/llvm-of
