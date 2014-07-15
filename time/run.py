#Python script for C++11 benchmark to generate CSV file.

import csv
import sys
import os

writer = csv.writer(file('Time_Measurement_Results.csv', 'wb'),dialect='excel')

# Run time measurement benchmarks

time_gcc_o2 = os.popen("taskset -c 0 ./bin/gcc-O2 gcc-o2").read()
time_gcc_o3 = os.popen("taskset -c 1 ./bin/gcc-O3 gcc-o3").read()
time_gcc_of = os.popen("taskset -c 2 ./bin/gcc-Ofast gcc-of").read()
time_icc_o2 = os.popen("taskset -c 3 ./bin/icc-O2 icc-o2").read()
time_icc_o3 = os.popen("taskset -c 4 ./bin/icc-O3 icc-o3").read()
time_icc_of = os.popen("taskset -c 5 ./bin/icc-Ofast icc-of").read()
time_llvm_o2 = os.popen("taskset -c 6 ./bin/clang-O2 llvm-o2").read()
time_llvm_o3 = os.popen("taskset -c 7 ./bin/clang-O3 llvm-o3").read()
time_llvm_of = os.popen("taskset -c 8 ./bin/clang-Ofast llvm-of").read()

attribute = [
	("Method","Statics","GCC-O2","GCC-O3","GCC-Of","ICC-O2","ICC-O3","ICC-Of","LLVM-O2","LLVM-O3","LLVM-Of")
]

gcc_o2_line = time_gcc_o2.split("\n")
gcc_o3_line = time_gcc_o3.split("\n")
gcc_of_line = time_gcc_of.split("\n")
icc_o2_line = time_icc_o2.split("\n")
icc_o3_line = time_icc_o3.split("\n")
icc_of_line = time_icc_of.split("\n")
llvm_o2_line = time_llvm_o2.split("\n")
llvm_o3_line = time_llvm_o3.split("\n")
llvm_of_line = time_llvm_of.split("\n")

for item in attribute:
	writer.writerow(item)

for i in range(len(gcc_o2_line)-1):
	result = [];
	result.append(gcc_o2_line[i].split(" ")[0])
	result.append(gcc_o2_line[i].split(" ")[1])
	result.append(gcc_o2_line[i].split(" ")[2])
	result.append(gcc_o3_line[i].split(" ")[2])
	result.append(gcc_of_line[i].split(" ")[2])
	result.append(icc_o2_line[i].split(" ")[2])
	result.append(icc_o3_line[i].split(" ")[2])
	result.append(icc_of_line[i].split(" ")[2])
	result.append(llvm_o2_line[i].split(" ")[2])
	result.append(llvm_o3_line[i].split(" ")[2])
	result.append(llvm_of_line[i].split(" ")[2])
	writer.writerow(result)
