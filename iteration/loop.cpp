#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

/******* Function Performance Profiling ***********/
#include <chrono>

/* A function pointer to the code to time.  
   Probably templating the timing code would be more idiomatic. */
typedef int (*timeable_fn)(void);

/**
  Return the number of seconds this function takes to run.
  May run the function several times (to average out 
  timer granularity).
*/
double time_function_onepass(timeable_fn fn)
{
	unsigned long i,count=1;
	double timePer=0;
	for (count=1;count!=0;count*=2) {
		auto start=std::chrono::high_resolution_clock::now();
		for (i=0;i<count;i++) fn();
		auto end=std::chrono::high_resolution_clock::now();
		double elapsed=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()*1.0e-9;
		const double time_granularity=1.0e-3;
		timePer=elapsed/count;
		if (elapsed>time_granularity) /* That took long enough */
			return timePer;
	}
	/* woa-- if we got here, "count" reached integer wraparound before 
	  the timer ran long enough.  Return the last known time */
	return timePer;
}

/**
  Return the number of seconds this function takes to run.
  May run the function several times (to average out 
  timer granularity).
*/
double time_function(timeable_fn fn)
{
	enum { ntimes=5 }; /* number of performance tests to run (and take median) */
	double times[ntimes];
	for (int t=0;t<ntimes;t++)
		times[t]=time_function_onepass(fn);
	std::sort(&times[0],&times[ntimes]);
	return times[ntimes/2];
}

/**
  Print the time taken for some action, in our standard format.
*/
void print_ns(const std::string &what,double seconds,const std::string &per) {
	std::cout<<what<<"\t"<<std::setprecision(3)<<seconds*1.0e9<<"\tns/"<<per<<std::endl;
}

/**
  Time a function's execution, and print the time out in nanoseconds.
*/
void print_time(const std::string &fnName,timeable_fn fn)
{
	print_ns(fnName,time_function(fn),"call");
}


namespace chrono_test {
	int empty_fn() {return 0;}
	int highres_clock() {
		auto start=std::chrono::high_resolution_clock::now();
		auto end=std::chrono::high_resolution_clock::now();
		return (int)((end-start).count());
	}

	void time() {
		print_time("  empty function 1",empty_fn); /* first call: cold cache, SpeedStep hasn't kicked up. */
		print_time("  empty function 2",empty_fn);
		print_time("  empty function 3",empty_fn);
		print_time("  empty function 4",empty_fn);
		print_time("    clock overhead",highres_clock);
	}
};


/* for_each: */
namespace for_each_test {
	std::vector<int> v(1000);
	int for_size(void) {
		int sum=0;
		for (unsigned int i=0;i<v.size();i++) sum+=v[i];
		return sum;
	}
	int for_iterator(void) {
		int sum=0;
		for (auto i=v.begin();i!=v.end();++i) sum+=*i;
		return sum;
	}
	int for_each(void) {
		int sum=0;
		std::for_each(v.begin(),v.end(),[&](int n){sum+=n;});
		return sum;
	}
	int for_range(void) {
		int sum=0;
		for (auto i : v) { sum+=i; }
		return sum;
	}

	void time() {
		print_time("for int to size",for_size);
		print_time("for range (i v)",for_size);
		print_time("for iterator ++",for_iterator);
		print_time("for_each lambda",for_each);
	}
};

int main() {
        for_each_test::time();
        return 0;
}

