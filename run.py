#Python script for C++11 benchmark to generate CSV file.

import csv
import sys
import os
 
# os.popen("sh compile.sh")

#run benchmarks
gcc_o2 = os.popen("./bin/O2/gcc-o2").read()
gcc_o3 = os.popen("./bin/O3/gcc-o3").read()
gcc_of = os.popen("./bin/Of/gcc-of").read()
icc_o2 = os.popen("./bin/O2/icc-o2").read()
icc_o3 = os.popen("./bin/O3/icc-o3").read()
icc_of = os.popen("./bin/Of/icc-of").read()
llvm_o2 = os.popen("./bin/O2/llvm-o2").read()
llvm_o3 = os.popen("./bin/O3/llvm-o3").read()
llvm_of = os.popen("./bin/Of/llvm-of").read()

attribute = [
	("Container","Size","Syntax","GCC-O2","GCC-O3","GCC-Of","ICC-O2","ICC-O3","ICC-Of","LLVM-O2","LLVM-O3","LLVM-Of")
]

gcc_o2_line = gcc_o2.split("\n")
gcc_o3_line = gcc_o3.split("\n")
gcc_of_line = gcc_of.split("\n")
icc_o2_line = icc_o2.split("\n")
icc_o3_line = icc_o3.split("\n")
icc_of_line = icc_of.split("\n")
llvm_o2_line = llvm_o2.split("\n")
llvm_o3_line = llvm_o3.split("\n")
llvm_of_line = llvm_of.split("\n")

writer = csv.writer(file('C++11_Benchmark_Results.csv', 'wb'),dialect='excel')

for item in attribute:
	writer.writerow(item)

for i in range(len(gcc_o2_line)-1):
	result = [];
	result.append(gcc_o2_line[i].split(" ")[0])
	result.append(gcc_o2_line[i].split(" ")[1])
	result.append(gcc_o2_line[i].split(" ")[2])
	result.append(gcc_o2_line[i].split(" ")[3])
	result.append(gcc_o3_line[i].split(" ")[3])
	result.append(gcc_of_line[i].split(" ")[3])
	result.append(icc_o2_line[i].split(" ")[3])
	result.append(icc_o3_line[i].split(" ")[3])
	result.append(icc_of_line[i].split(" ")[3])
	result.append(llvm_o2_line[i].split(" ")[3])
	result.append(llvm_o3_line[i].split(" ")[3])
	result.append(llvm_of_line[i].split(" ")[3])
	writer.writerow(result)
