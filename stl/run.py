#Python script for C++11 benchmark to generate CSV file.

import csv
import sys
import os

# Run loop iteration benchmarks
# loop_gcc_o2 = os.popen("./bin/gcc-o2").read()
# loop_gcc_o3 = os.popen("./bin/gcc-o3").read()
# loop_gcc_of = os.popen("./bin/gcc-of").read()
loop_icc_o2 = os.popen("./bin/icc-o2").read()
loop_icc_o3 = os.popen("./bin/icc-o3").read()
loop_icc_of = os.popen("./bin/icc-of").read()
# loop_llvm_o2 = os.popen("./bin/llvm-o2").read()
# loop_llvm_o3 = os.popen("./bin/llvm-o3").read()
# loop_llvm_of = os.popen("./bin/llvm-of").read()

attribute = [
	("Container","Algorithm","Version","ICC-O2(ms)","ICC-O3(ms)","ICC-Of(ms)")
]

# gcc_o2_line = loop_gcc_o2.split("\n")
# gcc_o3_line = loop_gcc_o3.split("\n")
# gcc_of_line = loop_gcc_of.split("\n")
icc_o2_line = loop_icc_o2.split("\n")
icc_o3_line = loop_icc_o3.split("\n")
icc_of_line = loop_icc_of.split("\n")
# llvm_o2_line = loop_llvm_o2.split("\n")
# llvm_o3_line = loop_llvm_o3.split("\n")
# llvm_of_line = loop_llvm_of.split("\n")

writer = csv.writer(file('STL_Results.csv', 'wb'),dialect='excel')

for item in attribute:
	writer.writerow(item)

for i in range(len(icc_o2_line)-2):
	result = [];
	# result.append(gcc_o2_line[i].split(" ")[0])
	# result.append(gcc_o2_line[i].split(" ")[1])
	# result.append(gcc_o2_line[i].split(" ")[2])
	# result.append(gcc_o2_line[i].split(" ")[3])
	# result.append(gcc_o3_line[i].split(" ")[3])
	# result.append(gcc_of_line[i].split(" ")[3])
	result.append(icc_o2_line[i].split(" ")[0])
	result.append(icc_o2_line[i].split(" ")[1])
	result.append(icc_o2_line[i].split(" ")[2])
	result.append(icc_o2_line[i].split(" ")[3])
	result.append(icc_o3_line[i].split(" ")[3])
	result.append(icc_of_line[i].split(" ")[3])
	# result.append(llvm_o2_line[i].split(" ")[3])
	# result.append(llvm_o3_line[i].split(" ")[3])
	# result.append(llvm_of_line[i].split(" ")[3])
	writer.writerow(result)
