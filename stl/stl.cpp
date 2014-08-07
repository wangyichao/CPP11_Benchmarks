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

  void operation() {
    accumulate(input1.begin(), input1.end(), 0.0);
  }

  void serial_for_each() {
	for_each(input1.begin(), input1.end(), operation);
  }

  /* void parallel_for_each() { */
	/* __gnu_parallel::for_each(input1.begin(), input1.end(), operation); */
  /* } */

  void serial_accumulate() {
    accumulate(input1.begin(), input1.end(), 0.0);
  }

  void parallel_accumulate() {
	__gnu_parallel::accumulate(input1.begin(), input1.end(), 0.0);
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

	float speedup1 = elapsed1 / elapsed2;

    start = chrono::steady_clock::now();
	serial_merge();
    end = chrono::steady_clock::now();
    int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_merge();
    end = chrono::steady_clock::now();
    int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	float speedup2 = elapsed3 / elapsed4;

	start = chrono::steady_clock::now();
	serial_for_each();
    end = chrono::steady_clock::now();
    int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    /* start = chrono::steady_clock::now(); */
	/* parallel_for_each(); */
    /* end = chrono::steady_clock::now(); */
    /* int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

	/* float speedup3 = elapsed5 / elapsed6; */

    start = chrono::steady_clock::now();
	serial_accumulate();
    end = chrono::steady_clock::now();
    int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::steady_clock::now();
	parallel_accumulate();
    end = chrono::steady_clock::now();
    int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count();

	float speedup4 = elapsed7 / elapsed8;

	cout << "Vector" << endl;
	cout << "Sort serial time is " << elapsed1 << "ms" << endl;
	cout << "Sort parallel time is " << elapsed2 << "ms" << endl;
	cout << "Sort speedup is " << speedup1 << "x" << endl;
	cout << "Merge serial time is " << elapsed3 << "ms" << endl;
	cout << "Merge parallel time is " << elapsed4 << "ms" << endl;
	cout << "Merge speedup is " << speedup2 << "x" << endl;
    cout << "For_each serial time is " << elapsed5 << "ms" << endl;
	/* cout << "For_each parallel time is " << elapsed6 << "ms" << endl; */
	/* cout << "For_each speedup is " << speedup3 << "x" << endl; */
    cout << "Accumulate serial time is " << elapsed7 << "ms" << endl;
	cout << "Accumulate parallel time is " << elapsed8 << "ms" << endl;
	cout << "Accumulate speedup is " << speedup4 << "x" << endl;
  }
}
	
/* namespace ArrayTest{ */
/*   array<double, 10000000> input1, input2, result1, result2; */

/*   void init() { */
/*     string rand; */
/*     ifstream file1 ("input1"); */
/*     ifstream file2 ("input2"); */

/* 	int i = 0; */
/* 	if(file1.is_open()) { */
/*       while(getline(file1, rand)) { */
/* 		input1[i] = stod(rand); */
/* 		i++; */
/* 	  } */
/* 	  file1.close(); */
/*     } */
/* 	i = 0; */
/*     if(file2.is_open()) { */
/*       while(getline(file2, rand)) { */
/*         input2[i] = stod(rand); */
/* 		i++; */
/* 	  } */
/* 	  file2.close(); */
/*     } */
/*   } */

/*   void serial_sort() { */
/* 	sort(input1.begin(), input1.end()); */
/* 	sort(input2.begin(), input2.end()); */
/*   } */
  
/*   void parallel_sort() { */
/*     __gnu_parallel::sort(input1.begin(), input1.end()); */
/* 	__gnu_parallel::sort(input2.begin(), input2.end()); */
/*   } */

/*   void serial_merge() { */
/* 	merge(input1.begin(), input1.end(), input2.begin(), input2.end(), result1.begin()); */
/*   } */

/*   void parallel_merge() { */
/* 	__gnu_parallel::merge(input1.begin(), input1.end(), input2.begin(), input2.end(), result2.begin()); */
/*   } */

/*   void operation() { */
/*     accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void serial_for_each() { */
/* 	for_each(input1.begin(), input1.end(), operation); */
/*   } */

/*   void parallel_for_each() { */
/* 	__gnu_parallel::for_each(input1.begin(), input1.end(), operation); */
/*   } */

/*   void serial_accumulate() { */
/*     accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void parallel_accumulate() { */
/* 	__gnu_parallel::accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void test() { */
/*     init(); */

/*     auto start = chrono::steady_clock::now(); */
/* 	serial_sort(); */
/*     auto end = chrono::steady_clock::now(); */
/*     int elapsed1 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_sort(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed2 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup1 = elapsed1 / elapsed2; */

/*     /1* start = chrono::steady_clock::now(); *1/ */
/* 	/1* serial_merge(); *1/ */
/*     /1* end = chrono::steady_clock::now(); *1/ */
/*     /1* int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count(); *1/ */

/*     /1* start = chrono::steady_clock::now(); *1/ */
/* 	/1* parallel_merge(); *1/ */
/*     /1* end = chrono::steady_clock::now(); *1/ */
/*     /1* int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count(); *1/ */

/* 	/1* float speedup2 = elapsed3 / elapsed4; *1/ */

/* 	start = chrono::steady_clock::now(); */
/* 	serial_for_each(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_for_each(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup3 = elapsed5 / elapsed6; */

/*     start = chrono::steady_clock::now(); */
/* 	serial_accumulate(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_accumulate(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup4 = elapsed7 / elapsed8; */

/* 	cout << "Array" << endl; */
/* 	cout << "Sort serial time is " << elapsed1 << "ms" << endl; */
/* 	cout << "Sort parallel time is " << elapsed2 << "ms" << endl; */
/* 	cout << "Sort speedup is " << speedup1 << "x" << endl; */
/* 	/1* cout << "Merge serial time is " << elapsed3 << "ms" << endl; *1/ */
/* 	/1* cout << "Merge parallel time is " << elapsed4 << "ms" << endl; *1/ */
/* 	/1* cout << "Merge speedup is " << speedup2 << "x" << endl; *1/ */
/*     cout << "For_each serial time is " << elapsed5 << "ms" << endl; */
/* 	cout << "For_each parallel time is " << elapsed6 << "ms" << endl; */
/* 	cout << "For_each speedup is " << speedup3 << "x" << endl; */
/*     cout << "Accumulate serial time is " << elapsed7 << "ms" << endl; */
/* 	cout << "Accumulate parallel time is " << elapsed8 << "ms" << endl; */
/* 	cout << "Accumulate speedup is " << speedup4 << "x" << endl; */
/*   } */
/* } */

/* namespace ListTest{ */
/*   list<double> input1, input2, result1, result2; */

/*   void init() { */
/*     string rand; */
/*     ifstream file1 ("input1"); */
/*     ifstream file2 ("input2"); */

/* 	if(file1.is_open()) { */
/*       while(getline(file1, rand)) { */
/* 		input1.push_back(stod(rand)); */
/* 	  } */
/* 	  file1.close(); */
/*     } */
/*     if(file2.is_open()) { */
/*       while(getline(file2, rand)) { */
/* 		input2.push_back(stod(rand)); */
/* 	  } */
/* 	  file2.close(); */
/*     } */
/*   } */

/*   /1* void serial_sort() { *1/ */
/* 	/1* input1.sort(); *1/ */
/* 	/1* input2.sort(); *1/ */
/*   /1* } *1/ */
  
/*   /1* void parallel_sort() { *1/ */
/*   /1*   input1.__gnu_parallel::sort(); *1/ */
/* 	/1* input2.__gnu_parallel::sort(); *1/ */
/*   /1* } *1/ */

/*   void serial_merge() { */
/* 	merge(input1.begin(), input1.end(), input2.begin(), input2.end(), std::back_inserter(result1)); */
/*   } */

/*   void parallel_merge() { */
/* 	__gnu_parallel::merge(input1.begin(), input1.end(), input2.begin(), input2.end(), std::back_inserter(result2)); */
/*   } */

/*   void operation() { */
/*     accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void serial_for_each() { */
/* 	for_each(input1.begin(), input1.end(), operation); */
/*   } */

/*   void parallel_for_each() { */
/* 	__gnu_parallel::for_each(input1.begin(), input1.end(), operation); */
/*   } */

/*   void serial_accumulate() { */
/*     accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void parallel_accumulate() { */
/* 	__gnu_parallel::accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void test() { */
/*     init(); */

/*     /1* auto start = chrono::steady_clock::now(); *1/ */
/* 	/1* serial_sort(); *1/ */
/*     /1* auto end = chrono::steady_clock::now(); *1/ */
/*     /1* int elapsed1 = chrono::duration_cast<chrono::microseconds>(end - start).count(); *1/ */

/*     /1* start = chrono::steady_clock::now(); *1/ */
/* 	/1* parallel_sort(); *1/ */
/*     /1* end = chrono::steady_clock::now(); *1/ */
/*     /1* int elapsed2 = chrono::duration_cast<chrono::microseconds>(end - start).count(); *1/ */

/* 	/1* float speedup1 = elapsed1 / elapsed2; *1/ */

/*     auto start = chrono::steady_clock::now(); */
/* 	serial_merge(); */
/*     auto end = chrono::steady_clock::now(); */
/*     int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_merge(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup2 = elapsed3 / elapsed4; */

/* 	start = chrono::steady_clock::now(); */
/* 	serial_for_each(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_for_each(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup3 = elapsed5 / elapsed6; */

/*     start = chrono::steady_clock::now(); */
/* 	serial_accumulate(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_accumulate(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	/1* float speedup4 = elapsed7 / elapsed8; *1/ */

/* 	/1* cout << "Sort serial time is " << elapsed1 << "ms" << endl; *1/ */
/* 	/1* cout << "Sort parallel time is " << elapsed2 << "ms" << endl; *1/ */
/* 	/1* cout << "Sort speedup is " << speedup1 << "x" << endl; *1/ */
/* 	cout << "List" << endl; */
/* 	cout << "Merge serial time is " << elapsed3 << "ms" << endl; */
/* 	cout << "Merge parallel time is " << elapsed4 << "ms" << endl; */
/* 	cout << "Merge speedup is " << speedup2 << "x" << endl; */
/*     cout << "For_each serial time is " << elapsed5 << "ms" << endl; */
/* 	cout << "For_each parallel time is " << elapsed6 << "ms" << endl; */
/* 	cout << "For_each speedup is " << speedup3 << "x" << endl; */
/*     cout << "Accumulate serial time is " << elapsed7 << "ms" << endl; */
/* 	cout << "Accumulate parallel time is " << elapsed8 << "ms" << endl; */
/* 	/1* cout << "Accumulate speedup is " << speedup4 << "x" << endl; *1/ */
/*   } */
/* } */

/* namespace SetTest{ */
/*   set<double> input1, input2, result1, result2; */

/*   void init() { */
/*     string rand; */
/*     ifstream file1 ("input1"); */
/*     ifstream file2 ("input2"); */

/* 	if(file1.is_open()) { */
/*       while(getline(file1, rand)) { */
/* 		input1.insert(stod(rand)); */
/* 	  } */
/* 	  file1.close(); */
/*     } */
/*     if(file2.is_open()) { */
/*       while(getline(file2, rand)) { */
/* 		input2.insert(stod(rand)); */
/* 	  } */
/* 	  file2.close(); */
/*     } */
/*   } */

/*   void serial_merge() { */
/* 	merge(input1.begin(), input1.end(), input2.begin(), input2.end(), result1.begin()); */
/*   } */

/*   void parallel_merge() { */
/* 	__gnu_parallel::merge(input1.begin(), input1.end(), input2.begin(), input2.end(), result2.begin()); */
/*   } */

/*   void operation() { */
/*     accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void serial_for_each() { */
/* 	for_each(input1.begin(), input1.end(), operation); */
/*   } */

/*   void parallel_for_each() { */
/* 	__gnu_parallel::for_each(input1.begin(), input1.end(), operation); */
/*   } */

/*   void serial_accumulate() { */
/*     accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void parallel_accumulate() { */
/* 	__gnu_parallel::accumulate(input1.begin(), input1.end(), 0.0); */
/*   } */

/*   void test() { */
/*     init(); */

/*     auto start = chrono::steady_clock::now(); */
/* 	serial_merge(); */
/*     auto end = chrono::steady_clock::now(); */
/*     int elapsed3 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_merge(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed4 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup2 = elapsed3 / elapsed4; */

/* 	start = chrono::steady_clock::now(); */
/* 	serial_for_each(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed5 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_for_each(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed6 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup3 = elapsed5 / elapsed6; */

/*     start = chrono::steady_clock::now(); */
/* 	serial_accumulate(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed7 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/*     start = chrono::steady_clock::now(); */
/* 	parallel_accumulate(); */
/*     end = chrono::steady_clock::now(); */
/*     int elapsed8 = chrono::duration_cast<chrono::microseconds>(end - start).count(); */

/* 	float speedup4 = elapsed7 / elapsed8; */

/* 	cout << "Set" << endl; */
/* 	cout << "Merge serial time is " << elapsed3 << "ms" << endl; */
/* 	cout << "Merge parallel time is " << elapsed4 << "ms" << endl; */
/* 	cout << "Merge speedup is " << speedup2 << "x" << endl; */
/*     cout << "For_each serial time is " << elapsed5 << "ms" << endl; */
/* 	cout << "For_each parallel time is " << elapsed6 << "ms" << endl; */
/* 	cout << "For_each speedup is " << speedup3 << "x" << endl; */
/*     cout << "Accumulate serial time is " << elapsed7 << "ms" << endl; */
/* 	cout << "Accumulate parallel time is " << elapsed8 << "ms" << endl; */
/* 	cout << "Accumulate speedup is " << speedup4 << "x" << endl; */
/*   } */
/* } */

int main (int argc, char* argv[]) {

  VectorTest::test();
  /* ArrayTest::test(); */
  /* ListTest::test(); */
  /* SetTest::test(); */

  return 0;
}
