#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>
#include <inttypes.h>

#include <vector>
#include <array>
#include <list>
#include <set>
#include <map>

#include <fstream>
#include <functional>

#include <sys/time.h>
#include <unistd.h>
#include "omp.h"
#include <chrono>

using testfun = std::function<int(void)>;

std::chrono::nanoseconds timeit(testfun fn, unsigned int iterations=1000) {
	std::list<double> times;
	auto t1 = std::chrono::steady_clock::now();
	for(unsigned int idx=0; idx<iterations; ++idx) {
		fn();
	}
	auto t2 = std::chrono::steady_clock::now();
	std::chrono::nanoseconds time_span_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
	return time_span_nanoseconds/iterations;
}

void time_and_print(testfun fn, std::string name, size_t size) {
	auto time = timeit(fn);
	std::cout << name << " " << size << " " << time.count() << std::endl;
}

namespace VectorTest {
	std::vector<int> v;
	int temp;

	void init(size_t size) {
		for (int j=1; j<=size; j++)
			v.push_back(j);
	}
	int for_size(void) {
		int sum=0;
		for (unsigned int i=0;i<v.size();i++) sum+=v[i];
		temp = sum;
		return sum;
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v.begin();i!=v.end();++i) sum+=*i;
		temp = sum;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v.begin(),v.end(),[&](int n){sum+=n;});
		temp = sum;
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		temp = sum;
		return sum;
	}

	void test(int size) {
		init(size);
		time_and_print(testfun(for_size), "std::vector for_index", size);
		time_and_print(testfun(for_iterator), "std::vector for_iterator",size);
		time_and_print(testfun(for_each), "std::vector for_each", size);
		time_and_print(testfun(for_range), "std::vector C++11_range", size)	;
	}
}

namespace StdArray100Test {
	std::array<int,100> v;
	size_t size = 100;
	int temp;
	void init() {
		for (int j=1; j<=size; j++)
			v[j] = j+1;
	}
	int for_size(void) {
		int sum=0;
		for (unsigned int i=0;i<v.size();i++) sum+=v[i];
		temp = sum;
		return sum;
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v.begin();i!=v.end();++i) sum+=*i;
		temp = sum;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v.begin(),v.end(),[&](int n){sum+=n;});
		temp = sum;
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		temp = sum;
		return sum;
	}

	void test() {
		init();
		time_and_print(testfun(for_size), "std::array for_index", size);
		time_and_print(testfun(for_iterator), "std::array for_iterator", size);
		time_and_print(testfun(for_each), "std::array for_each", size);
		time_and_print(testfun(for_range), "std::array C++11_range", size);
	}
}

namespace StdArray10000Test {
	std::array<int,10000> v;
	size_t size = 10000;
	int temp;
	void init() {
		for (int j=1; j<=size; j++)
			v[j] = j+1;
	}
	int for_size(void) {
		int sum=0;
		for (unsigned int i=0;i<v.size();i++) sum+=v[i];
		temp = sum;
		return sum;
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v.begin();i!=v.end();++i) sum+=*i;
		temp = sum;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v.begin(),v.end(),[&](int n){sum+=n;});
		temp = sum;
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		temp = sum;
		return sum;
	}

	void test() {
		init();
		time_and_print(testfun(for_size), "std::array for_index", size);
		time_and_print(testfun(for_iterator), "std::array for_iterator", size);
		time_and_print(testfun(for_each), "std::array for_each", size);
		time_and_print(testfun(for_range), "std::array C++11_range", size);
	}
}

namespace CArray100Test {
 	int v[100];
 	size_t size = 100;
	int temp;
	void init() {
		for (int j=1; j<=100; j++)
			v[j] = j+1;
	}
	int for_size(void) {
		int sum=0;
		for (unsigned int i=0;i<100;++i) sum+=v[i];
		temp = sum;
		return sum;
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v;i!=v+100;++i) sum+=*i;
		temp = sum;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v,v+100,[&](int n){sum+=n;});
		temp = sum;
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		temp = sum;
		return sum;
	}

	void test() {
		init();
		time_and_print(testfun(for_size), "C_array for_index", size);
		time_and_print(testfun(for_iterator), "C_array for_iterator", size);
		time_and_print(testfun(for_each), "C_array for_each", size);
		time_and_print(testfun(for_range), "C_array C++11_range", size);
	}
}

namespace CArray10000Test {
 	int v[10000];
 	size_t size = 10000;
	int temp;
	void init() {
		for (int j=1; j<=size; j++)
			v[j] = j+1;
	}
	int for_size(void) {
		int sum=0;
		for (unsigned int i=0;i<size;++i) sum+=v[i];
		temp = sum;
		return sum;
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v;i!=v+size;++i) sum+=*i;
		temp = sum;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v,v+size,[&](int n){sum+=n;});
		temp = sum;
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		temp = sum;
		return sum;
	}

	void test() {
		init();
		time_and_print(testfun(for_size), "C_array for_index", size);
		time_and_print(testfun(for_iterator), "C_array for_iterator", size);
		time_and_print(testfun(for_each), "C_array for_each", size);
		time_and_print(testfun(for_range), "C_array C++11_range", size); }
}

namespace StdSetTest {
 	std::set<int> v;
	int temp;
	void init(size_t size) {
		for (int j=1; j<=size; j++)
			v.insert(j+1);
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v.begin();i!=v.end();++i) sum+=*i;
		temp = sum;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v.begin(),v.end(),[&](int n){sum+=n;});
		temp = sum;
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		temp = sum;
		return sum;
	}

	void test(int size) {
		init(size);
		time_and_print(testfun(for_iterator), "std::set for_iterator", size);
		time_and_print(testfun(for_each), "std::set for_each", size);
		time_and_print(testfun(for_range), "std::set C++11_range", size);
	}
}

namespace ListTest {
	std::vector<int> v;
	int temp;

	void init(size_t size) {
		for (int j=1; j<=size; j++)
			v.push_back(j);
	}
	int for_size(void) {
		int sum=0;
		for (unsigned int i=0;i<v.size();i++) sum+=v[i];
		temp = sum;
		return sum;
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v.begin();i!=v.end();++i) sum+=*i;
		temp = sum;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v.begin(),v.end(),[&](int n){sum+=n;});
		temp = sum;
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		temp = sum;
		return sum;
	}

	void test(int size) {
		init(size);
		time_and_print(testfun(for_size), "std::list for_index", size);
		time_and_print(testfun(for_iterator), "std::list for_iterator",size);
		time_and_print(testfun(for_each), "std::list for_each", size);
		time_and_print(testfun(for_range), "std::list C++11_range", size)	;
	}
}

namespace TimeMeasurement {
	
	int OVERHEAD_LOOP_SIZE = 1000000;
	int CYCLES_LOOP_SIZE = 1000;

	volatile int var;

void inline measured_loop(unsigned int cycles) { 
	int k; 
	for (k=0; k<cycles; k++) 
		var = 1; 
}

void statics(std::vector<int> var) {
	int max = *std::max_element(var.begin(), var.end());
	int min = *std::min_element(var.begin(), var.end());
	nth_element(var.begin(), var.begin()+var.size()/2, var.end());
	int median = var[var.size()/2];
	int average = std::accumulate(var.begin(), var.end(), 0) / var.size();
	long int variance = 0;
	for (auto v : var) { variance += (v - average) * (v - average); }
	variance /= var.size();
	std::cout << "Max: " << max << std::endl;
	std::cout << "Min: " << min << std::endl;
	std::cout << "Median: " << median << std::endl;
	std::cout << "Variance: " << variance << std::endl;
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
		std::cout << "----- GetTimeofDay -----" << std::endl;
		statics(overhead);
	}
	
	void TestCycles(){
		std::map<int, int> cycles_elapsed; 
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
		std::cout << "----- OmpGetWtime -----" << std::endl;
		statics(overhead);
	}
	
	void TestCycles() {
		std::map<int, int> cycles_elapsed;
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
		std::cout << "----- RDTSCP -----" << std::endl;
		statics(overhead);
	}

	void inline TestCycles() { 
		std::map<int, int> cycles_elapsed;
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
		std::cout << "----- StdChrono -----" << std::endl;
		statics(overhead);
	}

	void TestCycles() {
		std::map<int, int> cycles_elapsed;
		for (i=10; i<CYCLES_LOOP_SIZE; i++) {

			auto start = std::chrono::steady_clock::now();
			measured_loop(i);
			auto end = std::chrono::steady_clock::now();
			int elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
			cycles_elapsed.insert(std::pair<int, int>(i, elapsed));
		}
	}
}
}

int main() {

	/* VectorTest::test(100); */
	/* VectorTest::test(10000); */
	/* StdArray100Test::test(); */
    /* StdArray10000Test::test(); */
    /* StdSetTest::test(100); */
    /* StdSetTest::test(10000); */
    /* CArray100Test::test(); */
    /* CArray10000Test::test(); */
    /* ListTest::test(100); */
    /* ListTest::test(10000); */

	TimeMeasurement::GetTimeofDay::TestOverhead();
	TimeMeasurement::GetTimeofDay::TestCycles();
	TimeMeasurement::OmpGetWtime::TestOverhead();
	TimeMeasurement::OmpGetWtime::TestCycles();
	TimeMeasurement::RDTSCP::TestOverhead();
	TimeMeasurement::RDTSCP::TestCycles();
	TimeMeasurement::StdChrono::TestOverhead();
	TimeMeasurement::StdChrono::TestCycles();
	
	return 0;
}

