#include <iostream>
#include <fstream>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <vector>
#include <array>
#include <list>
#include <set>
#include <unordered_set>
#include <parallel/numeric>
#include <parallel/algorithm>
using namespace std;

double r = 0;

namespace Algorithm {
  template <typename Container>
  void serial_sort(Container &v1) {
    sort(v1.begin(), v1.end());
  }
  
  template <typename Container>
  void parallel_sort(Container &v1) {
	__gnu_parallel::sort(v1.begin(), v1.end());
  }

  template <typename Container>
  void serial_merge(Container &v1, Container &v2, Container v3) {
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));
  }
  
  template <typename Container>
  void parallel_merge(Container &v1, Container &v2, Container &v3) {
	  __gnu_parallel::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));
  }
  
  template <typename Container>
  void serial_for_each(Container &v1) {
    double sum = 0.0;
	auto n = v1.begin();
	for_each(v1.begin(), v1.end(), [&](double const& n){sum += n;});
	r += sum;
  }
  
  template <typename Container>
  void parallel_for_each(Container &v1) {
    double sum = 0.0;
	auto n = v1.begin();
	__gnu_parallel::for_each(v1.begin(), v1.end(), [&](double const& n){sum += n;});
	r += sum;
  }

  template <typename Container>
  double serial_accumulate(Container &v1) {
    return accumulate(v1.begin(), v1.end(), 0.0);
  }
  
  template <typename Container>
  double parallel_accumulate(Container &v1) {
	return __gnu_parallel::accumulate(v1.begin(), v1.end(), 0.0);
  }

  template <typename Container>
  void serial_partial_sum(Container &v1) {
    partial_sum(v1.begin(), v1.end(), v1.begin());
  }
  
  template <typename Container>
  void parallel_partial_sum(Container &v1) {
    __gnu_parallel::partial_sum(v1.begin(), v1.end(), v1.begin());
  }

  template <typename Container>
  void serial_min_element(Container &v1) {
    auto m = min_element(v1.begin(), v1.end());
	r += *m;
  }

  template <typename Container>
  void parallel_min_element(Container &v1) {
	auto m = __gnu_parallel::min_element(v1.begin(), v1.end());
	r += *m;
  }

  template <typename Container>
  void serial_copy(Container &v1, Container &v2) {
	unique_copy(v1.begin(), v1.end(), back_inserter(v2));
  }

  template <typename Container>
  void parallel_copy(Container &v1, Container &v2) {
	__gnu_parallel::unique_copy(v1.begin(), v1.end(), back_inserter(v2));
  }

  template <typename Container>
  void serial_transform(Container &v1) {
	transform(v1.begin(), v1.end(), v1.begin(), [&](double & v){return v*v;});
  }

  template <typename Container>
  void parallel_transform(Container &v1) {
	__gnu_parallel::transform(v1.begin(), v1.end(), v1.begin(), [&](double & v){return v*v;});
  }

  template <typename Container>
  void serial_partition(Container &v1) {
	partition(v1.begin(), v1.end(), [&](double & v){return v<0.5;});
  }

  template <typename Container>
  void parallel_partition(Container &v1) {
	__gnu_parallel::partition(v1.begin(), v1.end(), [&](double & v){return v<0.5;});
  }

  template <typename Container>
  void serial_find_if(Container &v1) {
	find_if(v1.begin(), v1.end(), [&](double & v){return v<0.5;});
  }

  template <typename Container>
  void parallel_find_if(Container &v1) {
	__gnu_parallel::find_if(v1.begin(), v1.end(), [&](double & v){return v<0.5;});
  }

}

namespace VectorTest {
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
  
  void test() {
    init();

    auto start = chrono::steady_clock::now();
	Algorithm::serial_sort(input1);
    auto end = chrono::steady_clock::now();
    int elapsed1 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_sort(input2);
    end = chrono::steady_clock::now();
    int elapsed2 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::serial_merge(input1, input2, result1);
    end = chrono::steady_clock::now();
    int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_merge(input1, input2, result2);
    end = chrono::steady_clock::now();
    int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
	Algorithm::serial_for_each(input1);
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_for_each(input2);
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::serial_accumulate(input1);
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::parallel_accumulate(input2);
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_partial_sum(input1);
    end = chrono::steady_clock::now();
    int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_partial_sum(input2);
    end = chrono::steady_clock::now();
    int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_min_element(input1);
    end = chrono::steady_clock::now();
    int elapsed11 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_min_element(input2);
    end = chrono::steady_clock::now();
    int elapsed12 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_copy(input1, input2);
    end = chrono::steady_clock::now();
    int elapsed13 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_copy(input2, input1);
    end = chrono::steady_clock::now();
    int elapsed14 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_transform(input1);
    end = chrono::steady_clock::now();
    int elapsed15 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_transform(input2);
    end = chrono::steady_clock::now();
    int elapsed16 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_partition(input1);
    end = chrono::steady_clock::now();
    int elapsed17 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_partition(input2);
    end = chrono::steady_clock::now();
    int elapsed18 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_find_if(input1);
    end = chrono::steady_clock::now();
    int elapsed19 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_find_if(input2);
    end = chrono::steady_clock::now();
    int elapsed20 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "std::vector Sort serial " << elapsed1 << endl;
	cout << "std::vector Sort parallel " << elapsed2 << endl;

	cout << "std::vector Merge serial " << elapsed3 << endl;
	cout << "std::vector Merge parallel " << elapsed4 << endl;

    cout << "std::vector For_each serial " << elapsed5 << endl;
	cout << "std::vector For_each parallel " << elapsed6 << endl;
	
    cout << "std::vector Accumulate serial " << elapsed7 << endl;
	cout << "std::vector Accumulate parallel " << elapsed8 << endl;

    cout << "std::vector Partial_sum serial " << elapsed9 << endl;
	cout << "std::vector Partial_sum parallel " << elapsed10 << endl;

    cout << "std::vector Min_element serial " << elapsed11 << endl;
	cout << "std::vector Min_element parallel " << elapsed12 << endl;

	cout << "std::vector Copy serial " << elapsed13 << endl;
	cout << "std::vector Copy parallel " << elapsed14 << endl;

	cout << "std::vector Transform serial " << elapsed15 << endl;
	cout << "std::vector Transform parallel " << elapsed16 << endl;

	cout << "std::vector Partition serial " << elapsed17 << endl;
	cout << "std::vector Partition parallel " << elapsed18 << endl;

	cout << "std::vector Find_if serial " << elapsed19 << endl;
	cout << "std::vector Find_if parallel " << elapsed20 << endl;

  }
}
	
namespace ArrayTest{
  array<double, 10000000> input1, input2;
  array<double, 20000000> result1, result2;

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

  void test() {
    init();

    auto start = chrono::steady_clock::now();
	Algorithm::serial_sort(input1);
    auto end = chrono::steady_clock::now();
    int elapsed1 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_sort(input2);
    end = chrono::steady_clock::now();
    int elapsed2 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	merge(input1.begin(), input1.end(), input2.begin(), input2.end(),  result1.begin());
    end = chrono::steady_clock::now();
    int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	__gnu_parallel::merge(input1.begin(), input1.end(), input2.begin(), input2.end(), result2.begin());
    end = chrono::steady_clock::now();
    int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
	Algorithm::serial_for_each(input1);
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_for_each(input2);
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::serial_accumulate(input1);
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::parallel_accumulate(input2);
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_partial_sum(input1);
    end = chrono::steady_clock::now();
    int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_partial_sum(input2);
    end = chrono::steady_clock::now();
    int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
    Algorithm::serial_min_element(input1);
    end = chrono::steady_clock::now();
    int elapsed11 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_min_element(input2);
    end = chrono::steady_clock::now();
    int elapsed12 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    unique_copy(input1.begin(), input1.end(), input2.begin());
    end = chrono::steady_clock::now();
    int elapsed13 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
	__gnu_parallel::unique_copy(input1.begin(), input1.end(), input2.begin());
    end = chrono::steady_clock::now();
    int elapsed14 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_transform(input1);
    end = chrono::steady_clock::now();
    int elapsed15 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_transform(input2);
    end = chrono::steady_clock::now();
    int elapsed16 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_partition(input1);
    end = chrono::steady_clock::now();
    int elapsed17 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_partition(input2);
    end = chrono::steady_clock::now();
    int elapsed18 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_find_if(input1);
    end = chrono::steady_clock::now();
    int elapsed19 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_find_if(input2);
    end = chrono::steady_clock::now();
    int elapsed20 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "std::array Sort serial " << elapsed1 << endl;
	cout << "std::array Sort parallel " << elapsed2 << endl;

	cout << "std::array Merge serial " << elapsed3 << endl;
	cout << "std::array Merge parallel " << elapsed4 << endl;

	cout << "std::array For_each serial " << elapsed5 << endl;
	cout << "std::array For_each parallel " << elapsed6 << endl;

    cout << "std::array Accumulate serial " << elapsed7 << endl;
	cout << "std::array Accumulate parallel " << elapsed8 << endl;

    cout << "std::array Partial_sum serial " << elapsed9 << endl;
	cout << "std::array Partial_sum parallel " << elapsed10 << endl;

    cout << "std::array Min_element serial " << elapsed11 << endl;
	cout << "std::array Min_element parallel " << elapsed12 << endl;

	cout << "std::array Copy serial " << elapsed13 << endl;
	cout << "std::array Copy parallel " << elapsed14 << endl;

	cout << "std::array Transform serial " << elapsed15 << endl;
	cout << "std::array Transform parallel " << elapsed16 << endl;

	cout << "std::array Partition serial " << elapsed17 << endl;
	cout << "std::array Partition parallel " << elapsed18 << endl;

	cout << "std::array Find_if serial " << elapsed19 << endl;
	cout << "std::array Find_if parallel " << elapsed20 << endl;

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

  void test() {
    init();

    auto start = chrono::steady_clock::now();
	Algorithm::serial_merge(input1, input2, result1);
    auto end = chrono::steady_clock::now();
    int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_merge(input1, input2, result2);
    end = chrono::steady_clock::now();
    int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
	Algorithm::serial_for_each(input1);
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_for_each(input2);
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::serial_accumulate(input1);
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::parallel_accumulate(input2);
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_partial_sum(input1);
    end = chrono::steady_clock::now();
    int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_partial_sum(input2);
    end = chrono::steady_clock::now();
    int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
    Algorithm::serial_min_element(input1);
    end = chrono::steady_clock::now();
    int elapsed11 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_min_element(input2);
    end = chrono::steady_clock::now();
    int elapsed12 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_copy(input1, input2);
    end = chrono::steady_clock::now();
    int elapsed13 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_copy(input2, input1);
    end = chrono::steady_clock::now();
    int elapsed14 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_transform(input1);
    end = chrono::steady_clock::now();
    int elapsed15 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_transform(input2);
    end = chrono::steady_clock::now();
    int elapsed16 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_partition(input1);
    end = chrono::steady_clock::now();
    int elapsed17 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_partition(input2);
    end = chrono::steady_clock::now();
    int elapsed18 = chrono::duration_cast<chrono::microseconds>(end - start).count();
	
    start = chrono::steady_clock::now();
    Algorithm::serial_find_if(input1);
    end = chrono::steady_clock::now();
    int elapsed19 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_find_if(input2);
    end = chrono::steady_clock::now();
    int elapsed20 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "std::list Merge serial " << elapsed3 << endl;
	cout << "std::list Merge parallel " << elapsed4 << endl;

    cout << "std::list For_each serial " << elapsed5 << endl;
	cout << "std::list For_each parallel " << elapsed6 << endl;

    cout << "std::list Accumulate serial " << elapsed7 << endl;
	cout << "std::list Accumulate parallel " << elapsed8 << endl;

	cout << "std::list Partial_sum serial " << elapsed9 << endl;
	cout << "std::list Partial_sum parallel " << elapsed10 << endl;

    cout << "std::list Min_element serial " << elapsed11 << endl;
	cout << "std::list Min_element parallel " << elapsed12 << endl;

	cout << "std::list Copy serial " << elapsed13 << endl;
	cout << "std::list Copy parallel " << elapsed14 << endl;

	cout << "std::list Transform serial " << elapsed15 << endl;
	cout << "std::list Transform parallel " << elapsed16 << endl;

	cout << "std::list Partition serial " << elapsed17 << endl;
	cout << "std::list Partition parallel " << elapsed18 << endl;

	cout << "std::list Find_if serial " << elapsed19 << endl;
	cout << "std::list Find_if parallel " << elapsed20 << endl;

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

  void test() {
    init();

    auto start = chrono::steady_clock::now();
	r += Algorithm::serial_accumulate(input1);
    auto end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::parallel_accumulate(input2);
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
	Algorithm::serial_for_each(input1);
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_for_each(input2);
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
    Algorithm::serial_min_element(input1);
    end = chrono::steady_clock::now();
    int elapsed11 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_min_element(input2);
    end = chrono::steady_clock::now();
    int elapsed12 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	/* vector<double> v2; */
    /* start = chrono::steady_clock::now(); */
    /* partial_sum(input1.begin(), input1.end(), v2.begin()); */
    /* end = chrono::steady_clock::now(); */
    /* int elapsed9 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

	/* start = chrono::steady_clock::now(); */
	/* __gnu_parallel::partial_sum(input1.begin(), input1.end(), v2.begin()); */
    /* end = chrono::steady_clock::now(); */
    /* int elapsed10 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */
	
    cout << "std::set For_each serial " << elapsed5 << endl;
	cout << "std::set For_each parallel " << elapsed6 << endl;

    cout << "std::set Accumulate serial " << elapsed7 << endl;
	cout << "std::set Accumulate parallel " << elapsed8 << endl;

	/* cout << "std::set Partial_sum serial " << elapsed9 << endl; */
	/* cout << "std::set Partial_sum parallel " << elapsed10 << endl; */

    cout << "std::set Min_element serial " << elapsed11 << endl;
	cout << "std::set Min_element parallel " << elapsed12 << endl;

  }
}

namespace Unordered_setTest {
  unordered_set<double> input1, input2, result1, result2;

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

  void test() {
    init();

	auto start = chrono::steady_clock::now();
	Algorithm::serial_for_each(input1);
    auto end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	Algorithm::parallel_for_each(input2);
    end = chrono::steady_clock::now();
    int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::serial_accumulate(input1);
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	r += Algorithm::parallel_accumulate(input2);
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
    Algorithm::serial_min_element(input1);
    end = chrono::steady_clock::now();
    int elapsed11 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::steady_clock::now();
    Algorithm::parallel_min_element(input2);
    end = chrono::steady_clock::now();
    int elapsed12 = chrono::duration_cast<chrono::microseconds>(end - start).count();
		
    cout << "std::unordered_set For_each serial " << elapsed5 << endl;
	cout << "std::unordered_set For_each parallel " << elapsed6 << endl;

	cout << "std::unordered_set Accumulate serial " << elapsed7 << endl;
	cout << "std::unordered_set Accumulate parallel " << elapsed8 << endl;

    cout << "std::unordered_set Min_element serial " << elapsed11 << endl;
	cout << "std::unordered_set Min_element parallel " << elapsed12 << endl;

  }

}

int main (int argc, char* argv[]) {

  VectorTest::test();
  ArrayTest::test();
  ListTest::test();
  SetTest::test();
  Unordered_setTest::test();
  cout << r << endl;

  return 0;
}
