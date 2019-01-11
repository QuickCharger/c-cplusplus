#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include<utility>
#include<future>
#include<atomic>
#include <windows.h>
#include <vector>
#include <set>
#include <map>
#include <list>

using namespace std;

int *arr;
int r1 = 0;
int r2 = 0;
int r3 = 0;
int r4 = 0;

void func(int* a, int size, std::promise<int> &promiseObj)
{
	int r = 0;
	for (int i = 1; i <= size; ++i)
	{
		r += *(a + i);
	}
	promiseObj.set_value(r);
}

int main()
{
	int nMax = 100;
	int* arr = new int[nMax];
	memset(arr, 0, nMax);
	for (int i = 0; i <= nMax; ++i)
	{
		arr[i] = i;
	}

	std::promise<int> promiseObj1;
	std::future<int> futureObj1 = promiseObj1.get_future();

	std::promise<int> promiseObj2;
	std::future<int> futureObj2 = promiseObj2.get_future();

	std::promise<int> promiseObj3;
	std::future<int> futureObj3 = promiseObj3.get_future();

	std::promise<int> promiseObj4;
	std::future<int> futureObj4 = promiseObj4.get_future();

	{
		int nThreadSize = 4;

		std::thread f1(func, arr + 0 * (nMax / nThreadSize), nMax / nThreadSize, std::ref(promiseObj1));
		std::thread f2(func, arr + 1 * (nMax / nThreadSize), nMax / nThreadSize, std::ref(promiseObj2));
		std::thread f3(func, arr + 2 * (nMax / nThreadSize), nMax / nThreadSize, std::ref(promiseObj3));
		std::thread f4(func, arr + 3 * (nMax / nThreadSize), nMax / nThreadSize, std::ref(promiseObj4));

		f1.join();
		f2.join();
		f3.join();
		f4.join();

		int i1 = futureObj1.get();
		int i2 = futureObj2.get();
		int i3 = futureObj3.get();
		int i4 = futureObj4.get();

		std::cout << "f1: " << i1 << std::endl;
		std::cout << "f2: " << i2 << std::endl;
		std::cout << "f3: " << i3 << std::endl;
		std::cout << "f4: " << i4 << std::endl;

		std::cout << "total: " << i1 + i2 + i3 + i4 << std::endl;
	}

	getchar();

	return 0;
}
