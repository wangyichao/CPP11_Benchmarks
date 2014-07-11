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
	
int OVERHEAD_LOOP_SIZE = 1000000;
int CYCLES_LOOP_SIZE = 1000;

volatile int var;

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

		/* for (j=0; j<BOUND_OF_LOOP; j++) { */ 
		/* 	for (i =0; i<SIZE_OF_STAT; i++) { */ 
		for (i=0; i<OVERHEAD_LOOP_SIZE; i++) {
				gettimeofday(&start, NULL);
				gettimeofday(&end, NULL);
				double elapsed = 1000 * (end.tv_usec-start.tv_usec);

				if (elapsed < 0) {
					overhead.push_back(0);
				}
				else {
					overhead.push_back(elapsed);
				}
		}
		statics("GetTimeofDay", overhead);
	}
	
	void TestCycles(){
		std::map<int, int> cycles_elapsed; 
		std::map<int, int>::iterator iter;
		struct timeval start, end;

		/* for (j=0; j<BOUND_OF_LOOP; j++) { */ 
		/* 	for (i =0; i<SIZE_OF_STAT; i++) { */ 
		for (i=0; i<CYCLES_LOOP_SIZE; i++) {
				gettimeofday(&start, NULL);
				measured_loop(i);
				gettimeofday(&end, NULL);
				int elapsed = 1000 * (end.tv_usec-start.tv_usec);

				if (elapsed < 0) {
					cycles_elapsed.insert(std::pair<int, int>(i, 0));
				}
				else {
					cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
				}
		}
		std::ofstream file;
		file.open("plot/GetTimeofDay_results.csv");
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
	
		/* for (j=0; j<BOUND_OF_LOOP; j++) { */ 
		/* 	for (i =0; i<SIZE_OF_STAT; i++) { */ 
		for (i=0; i<OVERHEAD_LOOP_SIZE; i++) {
				start = omp_get_wtime( );
				end = omp_get_wtime( );
				int elapsed = 1000000000*(end - start);
	
				if (elapsed < 0) {
					overhead.push_back(0);
				}
				else {
					overhead.push_back(elapsed);
				}
		}
		statics("OmpGetWtime", overhead);
	}
	
	void TestCycles() {
		std::map<int, int> cycles_elapsed;
		std::map<int, int>::iterator iter;
		double start, end;
	
		/* for (j=0; j<BOUND_OF_LOOP; j++) { */ 
		/* 	for (i =0; i<SIZE_OF_STAT; i++) { */ 
		for (i=10; i<CYCLES_LOOP_SIZE; i++) {
				start = omp_get_wtime( );
				measured_loop(i);
				end = omp_get_wtime( );
				int elapsed = 1000000000*(end - start);
	
				if (elapsed < 0) {
					cycles_elapsed.insert(std::pair<int, int>(i, 0));
				}
				else {
					cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
				}
		}
		std::ofstream file;
		file.open("plot/OmpGetWtime_results.csv");
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
	 
		/* for (j=0; j<BOUND_OF_LOOP; j++) { */ 
		/* 	for (i =0; i<SIZE_OF_STAT; i++) { */ 
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
				int elapsed = end - start;

				if ( (end - start) < 0) { 
					overhead.push_back(0); 
				} 
				else 
				{ 
					overhead.push_back(elapsed); 
				} 
		} 
		statics("RDTSCP", overhead);
	}

	void inline TestCycles() { 
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
	 
		/* for (j=0; j<BOUND_OF_LOOP; j++) { */ 
		/* 	for (i =0; i<SIZE_OF_STAT; i++) { */ 
		for (i=10; i<CYCLES_LOOP_SIZE; i++) {
				asm volatile ("CPUID\n\t" 
						"RDTSC\n\t" 
						"mov %%edx, %0\n\t" 
						"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" 
						(cycles_low):: "%rax", "%rbx", "%rcx", "%rdx"); 
				measured_loop(i);
				asm volatile("CPUID\n\t" 
						"RDTSC\n\t" 
						"mov %%edx, %0\n\t"
						"mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" 
						(cycles_low1):: "%rax", "%rbx", "%rcx", "%rdx"); 

				start = ( ((uint64_t)cycles_high << 32) | cycles_low ); 
				end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 ); 
				uint64_t elapsed = end - start;

				if ( (end - start) < 0) { 
					cycles_elapsed.insert(std::pair<int, int>(i, 0));
				} 
				else 
				{ 
					cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
				} 
		} 
		std::ofstream file;
		file.open("plot/RDTSCP_results.csv");
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

	void TestCycles() {
		std::map<int, int> cycles_elapsed;
		std::map<int, int>::iterator iter;
		for (i=10; i<CYCLES_LOOP_SIZE; i++) {

			auto start = std::chrono::steady_clock::now();
			measured_loop(i);
			auto end = std::chrono::steady_clock::now();
			int elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
			cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
		}
		std::ofstream file;
		file.open("plot/StdChrono_results.csv");
		for (iter = cycles_elapsed.begin(); iter != cycles_elapsed.end(); iter++) {
			file << iter->first << " " << iter->second << std::endl;
		}
		file.close();
	}
}

int main() {

	GetTimeofDay::TestOverhead();
	GetTimeofDay::TestCycles();
	OmpGetWtime::TestOverhead();
	OmpGetWtime::TestCycles();
	RDTSCP::TestOverhead();
	RDTSCP::TestCycles();
	StdChrono::TestOverhead();
	StdChrono::TestCycles();
	
	return 0;
}
