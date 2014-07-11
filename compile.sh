#!/bin/bash
mkdir bin
mkdir bin/loop
mkdir bin/time
mkdir plot

# Compile loop benchmark

g++ -std=c++11 -O2 loop.cpp -o bin/loop/gcc-o2
g++ -std=c++11 -O3 loop.cpp -o bin/loop/gcc-o3
g++ -std=c++11 -Ofast loop.cpp -o bin/loop/gcc-of

icpc -std=c++11 -O2 loop.cpp -o bin/loop/icc-o2
icpc -std=c++11 -O3 loop.cpp -o bin/loop/icc-o3
icpc -std=c++11 -Ofast loop.cpp -o bin/loop/icc-of

clang++ -std=c++11 -O2 loop.cpp -o bin/loop/llvm-o2
clang++ -std=c++11 -O3 loop.cpp -o bin/loop/llvm-o3
clang++ -std=c++11 -Ofast loop.cpp -o bin/loop/llvm-of

# Compile time measurement benchmark

g++ -fopenmp -std=c++11 -O2 time_measurement.cpp -o bin/time/gcc-o2
g++ -fopenmp -std=c++11 -O3 time_measurement.cpp -o bin/time/gcc-o3
g++ -fopenmp -std=c++11 -Ofast time_measurement.cpp -o bin/time/gcc-of

icpc -openmp -std=c++11 -O2 time_measurement.cpp -o bin/time/icc-o2
icpc -openmp -std=c++11 -O3 time_measurement.cpp -o bin/time/icc-o3
icpc -openmp -std=c++11 -Ofast time_measurement.cpp -o bin/time/icc-of
