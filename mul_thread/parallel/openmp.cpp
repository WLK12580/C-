#include <iostream>
#include <chrono>
#include<math.h>
#include <thread>
#include<omp.h>
 
using namespace std;
 
double calculate(int min, int max) {
	double sum = 0.0;
omp_set_num_threads(std::thread::hardware_concurrency());
#pragma omp parallel for reduction(+:sum)
	for (int i = min; i <= max; ++i)
	{
		sum += sqrt(i);
        int id=omp_get_thread_num();
        printf("thread id=%d loop=%d sum=%f\n",id,i,sum);
	}
	return sum;
}
 
int main() 
{
	std::cout << "waiting for the result..." << std::endl;
 
	auto time1 = chrono::steady_clock::now();
	auto sum = calculate(1, 10);
	auto time2 = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1).count();
	cout << "Concurrent task finish, " << duration  << "ms consumed, Result: " << sum << endl;
}