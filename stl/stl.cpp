#include <iostream>
#include <fstream>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <vector>
#include <array>
#include <list>
#include <set>
#include <parallel/numeric>
#include <parallel/algorithm>
using namespace std;

double r = 0;

namespace VectorTest{
  vector<double> input1, input2, result1, result2;

  void init() {
    string rand;
    ifstream file1 ("input1");
    ifstream file2 ("input2");

	if(file1.is_open()) {
      while(getline(file1, rand)) {
		input1.push_back(stod(rand));
	  }
	  file1.close();
    }
    if(file2.is_open()) {
      while(getline(file2, rand)) {
		input2.push_back(stod(rand));
	  }
	  file2.close();
    }
  }

  void serial_sort() {
	sort(input1.begin(), input1.end());
	sort(input2.begin(), input2.end());
  }
  
  void parallel_sort() {
    __gnu_parallel::sort(input1.begin(), input1.end());
	__gnu_parallel::sort(input2.begin(), input2.end());
  }

  void serial_merge() {
	merge(input1.begin(), input1.end(), input2.begin(), input2.end(), std::back_inserter(result1));
  }

  void parallel_merge() {
	__gnu_parallel::merge(input1.begin(), input1.end(), input2.begin(), input2.end(), std::back_inserter(result2));
  }

  /* void operation() { */
  /*   accumulate(input1.begin(), input1.end(), 0.0); */
  /* } */

  void serial_for_each() {
	int sum = 0;
	for_each(input1.begin(), input1.end(), [&](int n){sum += n;});
	r += sum;
  }

  void parallel_for_each() {
	int sum = 0;
	__gnu_parallel::for_each(input2.begin(), input2.end(), [&](int n){sum += n;});
	r += sum;
  }

  double serial_accumulate() {
    return accumulate(result1.begin(), result1.end(), 0.0);
  }

  double parallel_accumulate() {
	return __gnu_parallel::accumulate(result2.begin(), result2.end(), 0.0);
  }

  void serial_partial_sum() {
	partial_sum(result1.begin(), result1.end(), result1.begin());
  }
  
  void parallel_partial_sum() {
	__gnu_parallel::partial_sum(result2.begin(), result2.end(), result2.begin());
  }

  void test() {
    init();

    auto start = chrono::steady_clock::now();
	serial_sort();
    auto end = chrono::steady_clock::now();
    int elapsed1 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_sort();
    end = chrono::steady_clock::now();
    int elapsed2 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup1 = elapsed1 / elapsed2; */

    start = chrono::steady_clock::now();
	serial_merge();
    end = chrono::steady_clock::now();
    int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_merge();
    end = chrono::steady_clock::now();
    int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup2 = elapsed3 / elapsed4; */

	start = chrono::steady_clock::now();
	serial_for_each();
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_for_each();
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup3 = elapsed5 / elapsed6; */

    start = chrono::steady_clock::now();
	r += serial_accumulate();
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += parallel_accumulate();
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
   	/* float speedup4 = elapsed7 / elapsed8; */
	
    start = chrono::steady_clock::now();
    serial_partial_sum();
    end = chrono::steady_clock::now();
    int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    parallel_partial_sum();
    end = chrono::steady_clock::now();
    int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "std::vector Sort serial " << elapsed1 << endl;
	cout << "std::vector Sort parallel " << elapsed2 << endl;
	/* cout << "std::vectorSort speedup is " << speedup1 << "x" << endl; */
	cout << "std::vector Merge serial " << elapsed3 << endl;
	cout << "std::vector Merge parallel " << elapsed4 << endl;
	/* cout << "std::vectorMerge speedup is " << speedup2 << "x" << endl; */
    cout << "std::vector For_each serial " << elapsed5 << endl;
	cout << "std::vector For_each parallel " << elapsed6 << endl;
	/* cout << "std::vectorFor_each speedup is " << speedup3 << "x" << endl; */
    cout << "std::vector Accumulate serial " << elapsed7 << endl;
	cout << "std::vector Accumulate parallel " << elapsed8 << endl;
	/* cout << "std::vector Accumulate speedup is " << speedup4 << "x" << endl; */
    cout << "std::vector Partial_sum serial " << elapsed7 << endl;
	cout << "std::vector Partial_sum parallel " << elapsed8 << endl;
  }
}
	
namespace ArrayTest{
  array<double, 10000000> input1, input2, result1, result2;

  void init() {
    string rand;
    ifstream file1 ("input1");
    ifstream file2 ("input2");

	int i = 0;
	if(file1.is_open()) {
      while(getline(file1, rand)) {
		input1[i] = stod(rand);
		i++;
	  }
	  file1.close();
    }
	i = 0;
    if(file2.is_open()) {
      while(getline(file2, rand)) {
        input2[i] = stod(rand);
		i++;
	  }
	  file2.close();
    }
  }

  void serial_sort() {
	sort(input1.begin(), input1.end());
	sort(input2.begin(), input2.end());
  }
  
  void parallel_sort() {
    __gnu_parallel::sort(input1.begin(), input1.end());
	__gnu_parallel::sort(input2.begin(), input2.end());
  }

  void serial_for_each() {
	int sum = 0;
	for_each(input1.begin(), input1.end(), [&](int n){sum += n;});
	r += sum;
  }

  void parallel_for_each() {
	int sum = 0;
	__gnu_parallel::for_each(input2.begin(), input2.end(), [&](int n){sum += n;});
	r += sum;
  }

  double serial_accumulate() {
    return accumulate(result1.begin(), result1.end(), 0.0);
  }

  double parallel_accumulate() {
	return __gnu_parallel::accumulate(result2.begin(), result2.end(), 0.0);
  }

  void serial_partial_sum() {
	partial_sum(result1.begin(), result1.end(), result1.begin());
  }
  
  void parallel_partial_sum() {
	  __gnu_parallel::partial_sum(result2.begin(), result2.end(), result2.begin());
  }

  void test() {
    init();

    auto start = chrono::steady_clock::now();
	serial_sort();
    auto end = chrono::steady_clock::now();
    int elapsed1 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_sort();
    end = chrono::steady_clock::now();
    int elapsed2 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup1 = elapsed1 / elapsed2; */
    
	start = chrono::steady_clock::now();
	serial_for_each();
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_for_each();
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup3 = elapsed5 / elapsed6; */

    start = chrono::steady_clock::now();
	r += serial_accumulate();
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += parallel_accumulate();
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup4 = elapsed7 / elapsed8; */
	
    start = chrono::steady_clock::now();
    serial_partial_sum();
    end = chrono::steady_clock::now();
    int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    parallel_partial_sum();
    end = chrono::steady_clock::now();
    int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "std::array Sort serial " << elapsed1 << endl;
	cout << "std::array Sort parallel " << elapsed2 << endl;
	/* cout << "std::array Sort speedup is " << speedup1 << "x" << endl; */
	cout << "std::array For_each serial " << elapsed5 << endl;
	cout << "std::array For_each parallel " << elapsed6 << endl;
	/* cout << "std::array For_each speedup is " << speedup3 << "x" << endl; */
    cout << "std::array Accumulate serial " << elapsed7 << endl;
	cout << "std::array Accumulate parallel " << elapsed8 << endl;
    cout << "std::array Partial_sum serial " << elapsed9 << endl;
	cout << "std::array Partial_sum parallel " << elapsed10 << endl;
	/* cout << "std::array Accumulate speedup is " << speedup4 << "x" << endl; */
  }
}

namespace ListTest{
  list<double> input1, input2, result1, result2;

  void init() {
    string rand;
    ifstream file1 ("input1");
    ifstream file2 ("input2");

	if(file1.is_open()) {
      while(getline(file1, rand)) {
		input1.push_back(stod(rand));
	  }
	  file1.close();
    }
    if(file2.is_open()) {
      while(getline(file2, rand)) {
		input2.push_back(stod(rand));
	  }
	  file2.close();
    }
  }

  void serial_merge() {
	merge(input1.begin(), input1.end(), input2.begin(), input2.end(), std::back_inserter(result1));
  }

  void parallel_merge() {
	__gnu_parallel::merge(input1.begin(), input1.end(), input2.begin(), input2.end(), std::back_inserter(result2));
  }

  void serial_for_each() {
	int sum = 0;
	for_each(input1.begin(), input1.end(), [&](int n){sum += n;});
	r += sum;
  }

  void parallel_for_each() {
	int sum = 0;
	__gnu_parallel::for_each(input2.begin(), input2.end(), [&](int n){sum += n;});
	r += sum;
  }

  double serial_accumulate() {
    return accumulate(result1.begin(), result1.end(), 0.0);
  }

  double parallel_accumulate() {
	return __gnu_parallel::accumulate(result2.begin(), result2.end(), 0.0);
  }

  void serial_partial_sum() {
	partial_sum(result1.begin(), result1.end(), result1.begin());
  }
  
  void parallel_partial_sum() {
	  __gnu_parallel::partial_sum(result2.begin(), result2.end(), result2.begin());
  }

  void test() {
    init();

    auto start = chrono::steady_clock::now();
	serial_merge();
    auto end = chrono::steady_clock::now();
    int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_merge();
    end = chrono::steady_clock::now();
    int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup2 = elapsed3 / elapsed4; */

	start = chrono::steady_clock::now();
	serial_for_each();
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_for_each();
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup3 = elapsed5 / elapsed6; */

    start = chrono::steady_clock::now();
	r += serial_accumulate();
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += parallel_accumulate();
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    serial_partial_sum();
    end = chrono::steady_clock::now();
    int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    parallel_partial_sum();
    end = chrono::steady_clock::now();
    int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* float speedup4 = elapsed7 / elapsed8; */

	cout << "std::list Merge serial " << elapsed3 << endl;
	cout << "std::list Merge parallel " << elapsed4 << endl;
	/* cout << "std::list Merge speedup is " << speedup2 << "x" << endl; */
    cout << "std::list For_each serial " << elapsed5 << endl;
	cout << "std::list For_each parallel " << elapsed6 << endl;
	/* cout << "std::list For_each speedup is " << speedup3 << "x" << endl; */
    cout << "std::list Accumulate serial " << elapsed7 << endl;
	cout << "std::list Accumulate parallel " << elapsed8 << endl;
	cout << "std::list Partial_sum serial " << elapsed9 << endl;
	cout << "std::list Partial_sum parallel " << elapsed10 << endl;
/* cout << "std::list Accumulate speedup is " << speedup4 << "x" << endl; */
  }
}

namespace SetTest{
  set<double> input1, input2, result1, result2;

  void init() {
    string rand;
    ifstream file1 ("input1");
    ifstream file2 ("input2");

	if(file1.is_open()) {
      while(getline(file1, rand)) {
		input1.insert(stod(rand));
	  }
	  file1.close();
    }
    if(file2.is_open()) {
      while(getline(file2, rand)) {
		input2.insert(stod(rand));
	  }
	  file2.close();
    }
  }

  double serial_accumulate() {
    return accumulate(input1.begin(), input1.end(), 0.0);
  }

  double parallel_accumulate() {
	return __gnu_parallel::accumulate(input2.begin(), input2.end(), 0.0);
  }

  /* void serial_partial_sum() { */
	/* partial_sum(input1.begin(), input1.end(), input1.begin()); */
  /* } */
  
  /* void parallel_partial_sum() { */
	  /* __gnu_parallel::partial_sum(input2.begin(), input2.end(), input2.begin()); */
  /* } */

  void test() {
    init();

    auto start = chrono::steady_clock::now();
	r += serial_accumulate();
    auto end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += parallel_accumulate();
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
	/* float speedup4 = elapsed7 / elapsed8; */

    /* start = chrono::steady_clock::now(); */
    /* serial_partial_sum(); */
    /* end = chrono::steady_clock::now(); */
    /* int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

	/* start = chrono::steady_clock::now(); */
    /* parallel_partial_sum(); */
    /* end = chrono::steady_clock::now(); */
    /* int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

    cout << "std::set Accumulate serial " << elapsed7 << endl;
	cout << "std::set Accumulate parallel " << elapsed8 << endl;
	/* cout << "std::set Partial_sum serial " << elapsed9 << endl; */
	/* cout << "std::set Partial_sum parallel " << elapsed10 << endl; */
/* cout << "std::set Accumulate speedup is " << speedup4 << "x" << endl; */
  }
}

int main (int argc, char* argv[]) {

  VectorTest::test();
  ArrayTest::test();
  ListTest::test();
  SetTest::test();
  cout << r << endl;

  return 0;
}
