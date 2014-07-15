#Python script for C++11 benchmark to generate CSV file.

import csv
import sys
import os
 
# os.popen("sh compile.sh")

# Run loop iteration benchmarks
loop_gcc_o2 = os.popen("./bin/loop/gcc-o2").read()
loop_gcc_o3 = os.popen("./bin/loop/gcc-o3").read()
loop_gcc_of = os.popen("./bin/loop/gcc-of").read()
loop_icc_o2 = os.popen("./bin/loop/icc-o2").read()
loop_icc_o3 = os.popen("./bin/loop/icc-o3").read()
loop_icc_of = os.popen("./bin/loop/icc-of").read()
loop_llvm_o2 = os.popen("./bin/loop/llvm-o2").read()
loop_llvm_o3 = os.popen("./bin/loop/llvm-o3").read()
loop_llvm_of = os.popen("./bin/loop/llvm-of").read()

attribute = [
	("Container","Size","Syntax","GCC-O2","GCC-O3","GCC-Of","ICC-O2","ICC-O3","ICC-Of","LLVM-O2","LLVM-O3","LLVM-Of")
]

gcc_o2_line = loop_gcc_o2.split("\n")
gcc_o3_line = loop_gcc_o3.split("\n")
gcc_of_line = loop_gcc_of.split("\n")
icc_o2_line = loop_icc_o2.split("\n")
icc_o3_line = loop_icc_o3.split("\n")
icc_of_line = loop_icc_of.split("\n")
llvm_o2_line = loop_llvm_o2.split("\n")
llvm_o3_line = loop_llvm_o3.split("\n")
llvm_of_line = loop_llvm_of.split("\n")

writer = csv.writer(file('Iteration_Results.csv', 'wb'),dialect='excel')

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
