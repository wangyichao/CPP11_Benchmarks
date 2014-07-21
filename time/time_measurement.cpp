#include <iostream>
#include <algorithm>
#include <inttypes.h>
#include <string>
#include <fstream>

#include <vector>
#include <map>

#include <sys/time.h>
#include <unistd.h>
#include <omp.h>
#include <chrono>
#include <sched.h>
#include <errno.h>

extern "C"
{
#include "perf_util.h"
#include "syst_count.h"
}

#define CPU_NOMINAL_FREQ 2.394
#define OVERHEAD_LOOP_SIZE 1000000
#define CYCLES_LOOP_SIZE 1000

volatile int var;

void microseconds_sleep(unsigned long uSec){
    struct timeval tv;
    tv.tv_sec=uSec/1000000;
    tv.tv_usec=uSec%1000000;
    int err;
    do{
        err=select(0,NULL,NULL,NULL,&tv);
    }while(err<0 && errno==EINTR);
}

void inline measured_loop(unsigned int cycles) { 
	int k; 
	for (k=0; k<cycles; k++) 
		var = 1; 
}

void statics(std::string title, std::vector<int> var) {
	int max = *std::max_element(var.begin(), var.end());
	int min = *std::min_element(var.begin(), var.end());
	nth_element(var.begin(), var.begin()+var.size()/2, var.end());
	int median = var[var.size()/2];
	int average = std::accumulate(var.begin(), var.end(), 0) / var.size();
	long int variance = 0;
	for (auto v : var) { variance += (v - average) * (v - average); }
	variance /= var.size();
	std::cout << title << " Max " << max << std::endl;
	std::cout << title << " Min " << min << std::endl;
	std::cout << title << " Median " << median << std::endl;
	std::cout << title << " Variance " << variance << std::endl;
}

namespace GetTimeofDay {
	int i, j;

	void TestOverhead(){
		std::vector<int> overhead; 
		struct timeval start, end;

		for (i=0; i<OVERHEAD_LOOP_SIZE; i++) {
				gettimeofday(&start, NULL);
				gettimeofday(&end, NULL);
				double elapsed = 1000 * (end.tv_usec-start.tv_usec);

				overhead.push_back(elapsed);
		}
		statics("GetTimeofDay", overhead);
	}

void TestCycles(char* argv){
	std::map<int, int> cycles_elapsed; 
	std::map<int, int>::iterator iter;
	struct timeval start, end;

	for (i=10; i<CYCLES_LOOP_SIZE; i++) {
		gettimeofday(&start, NULL);
		microseconds_sleep(i);
		/* measured_loop(i); */
		gettimeofday(&end, NULL);
		int elapsed = 1000 * (end.tv_usec-start.tv_usec);
		cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
	}
	std::ofstream file;
	std::string path = "plot/";
	path += argv;
	path += "/GetTimeofDay_results.csv";
	file.open(path);
	for (iter = cycles_elapsed.begin(); iter != cycles_elapsed.end(); iter++) {
		file << iter->first << " " << iter->second << std::endl;
	}
	file.close();
}
}

namespace OmpGetWtime {
int i, j;

void TestOverhead() {
	std::vector<int> overhead;
	double start, end;

	for (i=0; i<OVERHEAD_LOOP_SIZE; i++) {
			start = omp_get_wtime( );
			end = omp_get_wtime( );
			int elapsed = 1000000000*(end - start);

				overhead.push_back(elapsed);
	}
	statics("OmpGetWtime", overhead);
}

void TestCycles(char* argv) {
	std::map<int, int> cycles_elapsed;
	std::map<int, int>::iterator iter;
	double start, end;

	for (i=10; i<CYCLES_LOOP_SIZE; i++) {
		start = omp_get_wtime( );
		microseconds_sleep(i);
		/* measured_loop(i); */
		end = omp_get_wtime( );
		int elapsed = 1000000000*(end - start);
		cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
	}
	std::ofstream file;
	std::string path = "plot/";
	path += argv;
	path += "/OmpGetWtime_results.csv";
	file.open(path);
	for (iter = cycles_elapsed.begin(); iter != cycles_elapsed.end(); iter++) {
		file << iter->first << " " << iter->second << std::endl;
	}
	file.close();
}
}

namespace RDTSCP{
int i, j; 

void inline TestOverhead() { 
	std::vector<int> overhead;
	uint64_t start, end; 
	unsigned cycles_low, cycles_high, cycles_low1, cycles_high1; 

	asm volatile ("CPUID\n\t" 
			"RDTSC\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
			"%rax", "%rbx", "%rcx", "%rdx"); 
	asm volatile ("CPUID\n\t" 
			"RDTSC\n\t" 
			"CPUID\n\t" 
			"RDTSC\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: 
			"%rax", "%rbx", "%rcx", "%rdx"); 
	asm volatile ("CPUID\n\t" 
			"RDTSC\n\t"::: "%rax", "%rbx", "%rcx", "%rdx"); 
 
	for (i=0; i<OVERHEAD_LOOP_SIZE; i++) {
			asm volatile ("CPUID\n\t" 
					"RDTSC\n\t" 
					"mov %%edx, %0\n\t" 
					"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" 
					(cycles_low):: "%rax", "%rbx", "%rcx", "%rdx"); 
			asm volatile("CPUID\n\t" 
					"RDTSC\n\t" 
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" 
					(cycles_low1):: "%rax", "%rbx", "%rcx", "%rdx"); 

			start = ( ((uint64_t)cycles_high << 32) | cycles_low ); 
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 ); 
			uint64_t elapsed = (end - start) / CPU_NOMINAL_FREQ;
			overhead.push_back(elapsed); 
	} 
	statics("RDTSCP", overhead);
}

void inline TestCycles(char* argv) { 
	std::map<int, int> cycles_elapsed;
	std::map<int, int>::iterator iter;
	uint64_t start, end; 
	unsigned cycles_low, cycles_high, cycles_low1, cycles_high1; 

	asm volatile ("CPUID\n\t" 
			"RDTSC\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
			"%rax", "%rbx", "%rcx", "%rdx"); 
	asm volatile ("CPUID\n\t" 
			"RDTSC\n\t" 
			"CPUID\n\t" 
			"RDTSC\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: 
			"%rax", "%rbx", "%rcx", "%rdx"); 
	asm volatile ("CPUID\n\t" 
			"RDTSC\n\t"::: "%rax", "%rbx", "%rcx", "%rdx"); 
 
	for (i=10; i<CYCLES_LOOP_SIZE; i++) {
		asm volatile ("CPUID\n\t" 
					"RDTSC\n\t" 
					"mov %%edx, %0\n\t" 
					"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" 
					(cycles_low):: "%rax", "%rbx", "%rcx", "%rdx"); 
		microseconds_sleep(i);
			/* measured_loop(i); */
		asm volatile("CPUID\n\t" 
					"RDTSC\n\t" 
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" 
					(cycles_low1):: "%rax", "%rbx", "%rcx", "%rdx"); 

		start = ( ((uint64_t)cycles_high << 32) | cycles_low ); 
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 ); 
		uint64_t elapsed = (end - start) / CPU_NOMINAL_FREQ;

		cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
	} 
	std::ofstream file;
	std::string path = "plot/";
	path += argv;
	path += "/RDTSCP_results.csv";
	file.open(path);
	for (iter = cycles_elapsed.begin(); iter != cycles_elapsed.end(); iter++) {
		file << iter->first << " " << iter->second << std::endl;
	}
	file.close();
}
}

namespace StdChrono	{
int i, j;

void TestOverhead() {
	std::vector<int> overhead;
	for (i=0; i<OVERHEAD_LOOP_SIZE; i++) {

		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		int elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		overhead.push_back(elapsed);
	}
	statics("StdChrono", overhead);
}

void TestCycles(char* argv) {
	std::map<int, int> cycles_elapsed;
	std::map<int, int>::iterator iter;
	for (i=10; i<CYCLES_LOOP_SIZE; i++) {

		auto start = std::chrono::steady_clock::now();
		microseconds_sleep(i);
		/* measured_loop(i); */
		auto end = std::chrono::steady_clock::now();
		int elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
	}
	std::ofstream file;
	std::string path = "plot/";
	path += argv;
	path += "/StdChrono_results.csv";
	file.open(path);
	for (iter = cycles_elapsed.begin(); iter != cycles_elapsed.end(); iter++) {
			file << iter->first << " " << iter->second << std::endl;
		}
		file.close();
	}
}

namespace PMU {
	int i, j;
	
	void TestOverhead() {
		std::vector<int> overhead;

		char *events[] = {"-e", "UNHALTED_REFERENCE_CYCLES"};
		set_options(2, events);
		init();

		for (i=0; i<OVERHEAD_LOOP_SIZE; i++) {
			
			microseconds_sleep(i);
			int c = sched_getcpu();
			start_cpu(c);
			stop_cpu(c);
		
			counter_struct * counts = read_cpu(c);
			double result = (counts[0].delta/CPU_NOMINAL_FREQ);
			int elapsed = result * 1000;
			overhead.push_back(elapsed);
		}

		terminate();
		statics("PMU", overhead);
	}

	void TestCycles(char* argv) {
		std::map<int, int> cycles_elapsed;
		std::map<int, int>::iterator iter;

		char *events[] = {"-e", "UNHALTED_REFERENCE_CYCLES"};
		set_options(2, events);
		init();

		for (i=10; i<CYCLES_LOOP_SIZE; i++) {

			microseconds_sleep(i);
			int c = sched_getcpu();
			start_cpu(c);
			/* measured_loop(i); */
			microseconds_sleep(1000);
			stop_cpu(c);
		
			counter_struct * counts = read_cpu(c);
			double result = (counts[0].delta/CPU_NOMINAL_FREQ);
			int elapsed = result;
			cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
		}
	
		terminate();
		std::ofstream file;
		std::string path = "plot/";
		path += argv;
		path += "/PMU_results.csv";
		file.open(path);
		for (iter = cycles_elapsed.begin(); iter != cycles_elapsed.end(); iter++) {
			file << iter->first << " " << iter->second << std::endl;
		}
		file.close();
	}
}

int main(int argc, char* argv[]) {

	GetTimeofDay::TestOverhead();
	GetTimeofDay::TestCycles(argv[1]);
	OmpGetWtime::TestOverhead();
	OmpGetWtime::TestCycles(argv[1]);
	RDTSCP::TestOverhead();
	RDTSCP::TestCycles(argv[1]);
	StdChrono::TestOverhead();
	StdChrono::TestCycles(argv[1]);
	PMU::TestOverhead();
	PMU::TestCycles(argv[1]);
	
	return 0;
}
