#!/bin/bash
mkdir bin

python generator.py 10000000

# Compile STL benchmark
g++ -std=c++11 -fopenmp -O2 stl.cpp -o bin/gcc-o2
g++ -std=c++11 -fopenmp -O3 stl.cpp -o bin/gcc-o3
g++ -std=c++11 -fopenmp -Ofast stl.cpp -o bin/gcc-of

icpc -std=c++11 -fopenmp -O2 stl.cpp -o bin/icc-o2
icpc -std=c++11 -fopenmp -O3 stl.cpp -o bin/icc-o3
icpc -std=c++11 -fopenmp -Ofast stl.cpp -o bin/icc-of

# clang++ -std=c++11 -fopenmp -O2 stl.cpp -o bin/llvm-o2
# clang++ -std=c++11 -fopenmp -O3 stl.cpp -o bin/llvm-o3
# clang++ -std=c++11 -fopenmp -Ofast stl.cpp -o bin/llvm-of
