#Python script for C++11 benchmark to generate CSV file.

import csv
import sys
import os

# Run loop iteration benchmarks
loop_gcc_o2 = os.popen("./bin/gcc-o2 all").read()
loop_gcc_o3 = os.popen("./bin/gcc-o3 all").read()
loop_gcc_of = os.popen("./bin/gcc-of all").read()
loop_icc_o2 = os.popen("./bin/icc-o2 all").read()
loop_icc_o3 = os.popen("./bin/icc-o3 all").read()
loop_icc_of = os.popen("./bin/icc-of all").read()
loop_llvm_o2 = os.popen("./bin/llvm-o2 all").read()
loop_llvm_o3 = os.popen("./bin/llvm-o3 all").read()
loop_llvm_of = os.popen("./bin/llvm-of all").read()

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

perf_ins = "perf stat -B -e cache-references,cache-misses,cycles,instructions,branches --pfm-events LLC_MISSES"
os.popen(perf_ins + " ./bin/gcc-of vector index > perf_data/vector_index 2>&1")
os.popen(perf_ins + " ./bin/gcc-of vector interator > perf_data/vector_iterator 2>&1")
os.popen(perf_ins + " ./bin/gcc-of vector each > perf_data/vector_each 2>&1")
os.popen(perf_ins + " ./bin/gcc-of vector range > perf_data/vector_range 2>&1")
os.popen(perf_ins + " ./bin/gcc-of stdarray index > perf_data/stdarray_index 2>&1")
os.popen(perf_ins + " ./bin/gcc-of stdarray interator > perf_data/stdarray_iterator 2>&1")
os.popen(perf_ins + " ./bin/gcc-of stdarray each > perf_data/stdarray_each 2>&1")
os.popen(perf_ins + " ./bin/gcc-of stdarray range > perf_data/stdarray_range 2>&1")
os.popen(perf_ins + " ./bin/gcc-of carray index > perf_data/carray_index 2>&1")
os.popen(perf_ins + " ./bin/gcc-of carray interator > perf_data/carray_iterator 2>&1")
os.popen(perf_ins + " ./bin/gcc-of carray each > perf_data/carray_each 2>&1")
os.popen(perf_ins + " ./bin/gcc-of carray range > perf_data/carray_range 2>&1")
os.popen(perf_ins + " ./bin/gcc-of set interator > perf_data/set_iterator 2>&1")
os.popen(perf_ins + " ./bin/gcc-of set each > perf_data/set_each 2>&1")
os.popen(perf_ins + " ./bin/gcc-of set range > perf_data/set_range 2>&1")
os.popen(perf_ins + " ./bin/gcc-of list interator > perf_data/list_iterator 2>&1")
os.popen(perf_ins + " ./bin/gcc-of list each > perf_data/list_each 2>&1")
os.popen(perf_ins + " ./bin/gcc-of list range > perf_data/list_range 2>&1")
