CPP11_Benchmarks
================

Benchmarks on C++11 based on GCC, ICC and LLVM

Introduction:

Iteration loop benchmark is to test the time consuming fof four different loop syntax combined with different STL containers.

Time measurement benchmark is to test the accuracy and stablility. Max, Min, Median and Variance are used to give out statics results.

Guide:

1. Compile the whole project.

$sh compile.sh

2. Run benchmarks and generate the results to CSV file.

$python run.py
