#!/bin/bash
mkdir bin
mkdir bin/O2
mkdir bin/O3
mkdir bin/Of

g++ -std=c++11 -O2 benchmarks.cpp -o bin/O2/gcc-o2
g++ -std=c++11 -O3 benchmarks.cpp -o bin/O3/gcc-o3
g++ -std=c++11 -Ofast benchmarks.cpp -o bin/Of/gcc-of

icpc -std=c++11 -O2 benchmarks.cpp -o bin/O2/icc-o2
icpc -std=c++11 -O3 benchmarks.cpp -o bin/O3/icc-o3
icpc -std=c++11 -Ofast benchmarks.cpp -o bin/Of/icc-of

clang++ -std=c++11 -O2 benchmarks.cpp -o bin/O2/llvm-o2
clang++ -std=c++11 -O3 benchmarks.cpp -o bin/O3/llvm-o3
clang++ -std=c++11 -Ofast benchmarks.cpp -o bin/Of/llvm-of
