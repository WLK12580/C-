#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <vector>
#include <chrono>

#include <math.h>
 
 
double accumulate(int min, int max)
{
	double sum = 0;
	for (int i = min; i <= max; ++i)
	{
		sum += sqrt(i);
	}
	return sum;
}
 
double concurrent_async(int min, int max)
{
	std::vector<std::future<double>> results; 
	unsigned concurrent_count = std::thread::hardware_concurrency();
	double sum = 0;
	min = 0;
	for (int i = 0; i < concurrent_count; i++)
	{
		int range = max / concurrent_count * (i + 1);
		auto f = std::async(std::launch::async, accumulate, min, range);
		results.push_back(std::move(f));
		min = range + 1;
	}
	
	int size = results.size();
	for (int i = 0; i < size; ++i)
	{
		//如果选择异步执行策略，调用get时，如果异步执行没有结束，get会阻塞当前调用线程，
		//直到异步执行结束并获得结果，如果异步执行已经结束，不等待获取执行结果；
		//如果选择同步执行策略，只有当调用get函数时，同步调用才真正执行，这也被称为函数调用被延迟
		sum += results[i].get();
	}
	return sum;
}
 
int main()
{
	std::cout << "waiting for the result..." << std::endl;
 
	auto start_time = std::chrono::steady_clock::now();
 
	double r = concurrent_async(1, 10e8);
 
	auto end_time = std::chrono::steady_clock::now();
 
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
 
	std::cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << r << std::endl;
 
	return 0;
}