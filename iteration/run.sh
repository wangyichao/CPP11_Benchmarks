#!/bin/bash
echo O2 opt
echo 
g++ -std=c++11 -O2 loop.cpp -o O2/gcc-o2
echo GCC:
./O2/gcc-o2

icpc -std=c++11 -O2 loop.cpp -o O2/icc-o2
echo ICC:
./O2/icc-o2

clang++ -std=c++11 -O2 loop.cpp -o O2/clang-o2
echo LLVM:
./O2/clang-o2

echo ---------------------------------------
echo O3 opt
echo 
g++ -std=c++11 -O3 loop.cpp -o O3/gcc-o3
echo GCC:
./O3/gcc-o3

icpc -std=c++11 -O3 loop.cpp -o O3/icc-o3
echo ICC:
./O3/icc-o3

clang++ -std=c++11 -O3 loop.cpp -o O3/clang-o3
echo LLVM:
./O3/clang-o3
