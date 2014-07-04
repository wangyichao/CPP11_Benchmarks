#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>

#include <vector>
#include <array>
#include <list>
#include <set>

#include <fstream>
#include <functional>

#include <chrono>
#include <string>

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
	std::cout << name << " " << size << "," << time.count() << std::endl;
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
		time_and_print(testfun(for_size), "std::vector for index", size);
		time_and_print(testfun(for_iterator), "std::vector for iterator",size);
		time_and_print(testfun(for_each), "std::vector for_each", size);
		time_and_print(testfun(for_range), "std::vector C++11 range", size)	;
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
		time_and_print(testfun(for_size), "std::array for index", size);
		time_and_print(testfun(for_iterator), "std::array for iterator", size);
		time_and_print(testfun(for_each), "std::array for_each", size);
		time_and_print(testfun(for_range), "std::array C++11 range", size);
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
		time_and_print(testfun(for_size), "std::array for index", size);
		time_and_print(testfun(for_iterator), "std::array for iterator", size);
		time_and_print(testfun(for_each), "std::array for_each", size);
		time_and_print(testfun(for_range), "std::array C++11 range", size);
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
		time_and_print(testfun(for_size), "C array for index", size);
		time_and_print(testfun(for_iterator), "C array for iterator", size);
		time_and_print(testfun(for_each), "C array for_each", size);
		time_and_print(testfun(for_range), "C array C++11 range", size);
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
		time_and_print(testfun(for_size), "C array for index", size);
		time_and_print(testfun(for_iterator), "C array for iterator", size);
		time_and_print(testfun(for_each), "C array for_each", size);
		time_and_print(testfun(for_range), "C array C++11 range", size);
	}
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
		time_and_print(testfun(for_iterator), "std::set for iterator", size);
		time_and_print(testfun(for_each), "std::set for_each", size);
		time_and_print(testfun(for_range), "std::set C++11 range", size);
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
		time_and_print(testfun(for_size), "std::list for index", size);
		time_and_print(testfun(for_iterator), "std::list for iterator",size);
		time_and_print(testfun(for_each), "std::list for_each", size);
		time_and_print(testfun(for_range), "std::list C++11 range", size)	;
	}
}

int main() {
        VectorTest::test(100);
        VectorTest::test(10000);
        StdArray100Test::test();
        StdArray10000Test::test();
        StdSetTest::test(100);
        StdSetTest::test(10000);
        CArray100Test::test();
        CArray10000Test::test();
        ListTest::test(100);
        ListTest::test(10000);
        return 0;
}

