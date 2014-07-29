#include <iostream>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <functional>

#include <vector>
#include <array>
#include <list>
#include <set>

#include <fstream>
#include <functional>

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
	
	void index() {
		init(10000);
		time_and_print(testfun(for_size), "std::vector for_index", 10000);
	}

	void iterator() {
		init(10000);
		time_and_print(testfun(for_iterator), "std::vector for_iterator", 10000);
	}

	void each() {
		init(10000);
		time_and_print(testfun(for_each), "std::vector for_each", 10000);
	}

	void range() {
		init(10000);
		time_and_print(testfun(for_range), "std::vector C++11_range", 10000)	;
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

	void index() {
		init();
		time_and_print(testfun(for_size), "std::array for_index", 10000);
	}

	void iterator() {
		init();
		time_and_print(testfun(for_iterator), "std::array for_iterator", 10000);
	}

	void each() {
		init();
		time_and_print(testfun(for_each), "std::array for_each", 10000);
	}

	void range() {
		init();
		time_and_print(testfun(for_range), "std::array C++11_range", 10000)	;
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
		time_and_print(testfun(for_range), "C_array C++11_range", size); 
	}

	void index() {
		init();
		time_and_print(testfun(for_size), "C_array for_index", 10000);
	}

	void iterator() {
		init();
		time_and_print(testfun(for_iterator), "C_array for_iterator", 10000);
	}

	void each() {
		init();
		time_and_print(testfun(for_each), "C_array for_each", 10000);
	}

	void range() {
		init();
		time_and_print(testfun(for_range), "C_array C++11_range", 10000)	;
	}
}

namespace SetTest {
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
	
	void iterator() {
		init(10000);
		time_and_print(testfun(for_iterator), "std::set for_iterator", 10000);
	}

	void each() {
		init(10000);
		time_and_print(testfun(for_each), "std::set for_each", 10000);
	}

	void range() {
		init(10000);
		time_and_print(testfun(for_range), "std::set C++11_range", 10000)	;
	}
}

namespace ListTest {
	std::list<int> v;
	int temp;

	void init(size_t size) {
		for (int j=1; j<=size; j++)
			v.push_back(j);
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
		time_and_print(testfun(for_iterator), "std::list for_iterator",size);
		time_and_print(testfun(for_each), "std::list for_each", size);
		time_and_print(testfun(for_range), "std::list C++11_range", size)	;
	}
	
	void iterator() {
		init(10000);
		time_and_print(testfun(for_iterator), "std::list for_iterator", 10000);
	}

	void each() {
		init(10000);
		time_and_print(testfun(for_each), "std::list for_each", 10000);
	}

	void range() {
		init(10000);
		time_and_print(testfun(for_range), "std::list C++11_range", 10000)	;
	}
}

int main(int argc, char* argv[]) {
	if(!strcmp(argv[1],"all")){
        VectorTest::test(100);
        VectorTest::test(10000);
	    StdArray100Test::test();
        StdArray10000Test::test();
        CArray100Test::test();
        CArray10000Test::test();
		SetTest::test(100);
        SetTest::test(10000);
        ListTest::test(100);
        ListTest::test(10000);
	}else if(argc==3){
		if(!strcmp(argv[1],"vector")){
			if(!strcmp(argv[2],"index")){
				VectorTest::index();
			}
			if(!strcmp(argv[2],"iterator")){
				VectorTest::iterator();
			}
			if(!strcmp(argv[2],"each")){
				VectorTest::each();
			}
			if(!strcmp(argv[2],"range")){
				VectorTest::range();
			}
		}
		if(!strcmp(argv[1],"stdarray")){
			if(!strcmp(argv[2],"index")){
				StdArray10000Test::index();
			}
			if(!strcmp(argv[2],"iterator")){
				StdArray10000Test::iterator();
			}
			if(!strcmp(argv[2],"each")){
				StdArray10000Test::each();
			}
			if(!strcmp(argv[2],"range")){
				StdArray10000Test::range();
			}
		}
		if(!strcmp(argv[1],"carray")){
			if(!strcmp(argv[2],"index")){
				CArray10000Test::index();
			}
			if(!strcmp(argv[2],"iterator")){
				CArray10000Test::iterator();
			}
			if(!strcmp(argv[2],"each")){
				CArray10000Test::each();
			}
			if(!strcmp(argv[2],"range")){
				CArray10000Test::range();
			}
		}
		if(!strcmp(argv[1],"set")){
			if(!strcmp(argv[2],"iterator")){
				SetTest::iterator();
			}
			if(!strcmp(argv[2],"each")){
				SetTest::each();
			}
			if(!strcmp(argv[2],"range")){
				SetTest::range();
			}
		}
		if(!strcmp(argv[1],"list")){
			if(!strcmp(argv[2],"iterator")){
				ListTest::iterator();
			}
			if(!strcmp(argv[2],"each")){
				ListTest::each();
			}
			if(!strcmp(argv[2],"range")){
				ListTest::range();
			}
		}
	}else{
		std::cout << "Incorrect input!\nCorrect example, ./gcc-o2 all or ./gcc-o2 vector 100\nIncluding containers: vector, stdarray, carray, set, list\nSize: 100 or 10000"<<std::endl;
	}
	return 0;
}

