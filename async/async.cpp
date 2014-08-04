#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <chrono>
#include <unistd.h>
/* #include <pthread.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */

double iteration_sum(std::vector<double>::iterator beg, std::vector<double>::iterator end)
{
  /* pid_t pid; */
  /* pthread_t tid; */
  /* pid = getpid(); */
  /* tid = pthread_self(); */
  auto len = std::distance(beg, end);
  if(len < 1000)
  {
    return std::accumulate(beg, end, 0.0);
  }

  std::vector<double>::iterator mid = beg + len/2;
  auto handle = std::async(std::launch::async, iteration_sum, mid, end);
  double sum = iteration_sum(beg, mid);
  return sum + handle.get();
}

double fsum(std::vector<double>::iterator beg, std::vector<double>::iterator end)
{
	return std::accumulate(beg, end, 0.0);
}

double fork_sum(std::vector<double> v, int thread_num)
{
  int len = std::distance(v.begin(), v.end());
  int distance = len / thread_num;
  int i;
  double sum = 0;
  auto handle1 = std::async(std::launch::async, fsum, v.begin(), v.begin()+distance);
  auto handle2 = std::async(std::launch::async, fsum, v.begin()+distance, v.begin()+2*distance);
  auto handle3 = std::async(std::launch::async, fsum, v.begin()+2*distance, v.begin()+3*distance);
  auto handle4 = std::async(std::launch::async, fsum, v.begin()+3*distance, v.end());
  sum = handle1.get()+handle2.get()+handle3.get()+handle4.get();
  return sum;
}

double serial_sum(std::vector<double> v)
{
  return std::accumulate(v.begin(), v.end(), 0.0);  
}
 
int main()
{
  std::vector<double> v(100000, 3.1415);

  auto start = std::chrono::steady_clock::now();
  std::cout << "Parallel: The sum is " << iteration_sum(v.begin(), v.end()) << '\n';
  auto end = std::chrono::steady_clock::now();
  int elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << "Parallel: Time is " << elapsed << '\n';

  start = std::chrono::steady_clock::now();
  std::cout << "Fork: The sum is " << fork_sum(v, 4) << '\n';
  end = std::chrono::steady_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << "Fork: Time is " << elapsed << '\n';

  start = std::chrono::steady_clock::now();
  std::cout << "Serial: The sum is " << serial_sum(v) << '\n';
  end = std::chrono::steady_clock::now();
  elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << "Serial: Time is " << elapsed << std::endl;
}
