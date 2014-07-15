#!/bin/bash
mkdir bin
mkdir plot
mkdir plot/gcc-o2
mkdir plot/gcc-o3
mkdir plot/gcc-of
mkdir plot/icc-o2
mkdir plot/icc-o3
mkdir plot/icc-of
mkdir plot/llvm-o2
mkdir plot/llvm-o3
mkdir plot/llvm-of

# Compile time measurement benchmark

make CC1=g++ CC2=gcc OPT=-O2
make CC1=g++ CC2=gcc OPT=-O3
make CC1=g++ CC2=gcc OPT=-Ofast
make CC1=icpc CC2=icc OPT=-O2
make CC1=icpc CC2=icc OPT=-O3
make CC1=icpc CC2=icc OPT=-Ofast
make CC1=clang++ CC2=clang OPT=-O2
make CC1=clang++ CC2=clang OPT=-O3
make CC1=clang++ CC2=clang OPT=-Ofast
