#pragma once

#include "../common.h"

void func(int* a, int size, std::promise<int> &promiseObj)
{
	int r = 0;
	for (int i = 0; i < size; ++i)
	{
		r += *(a + i);
	}
	promiseObj.set_value(r);
}

void do_future()
{
	int nMax = 100;
	int* arr = new int[nMax] {0};
	int nIndex = 0;
	std::for_each(arr, arr + nMax, [&nIndex](int & i) { i = nIndex++; });

	unsigned int nThreadSize = 4;
	std::vector<std::thread> vThread{ nThreadSize };
	std::vector<std::promise<int>> vPromise{ nThreadSize };
	std::vector<std::future<int>> vFuture{ nThreadSize };

	for (auto i = 0; i < nThreadSize; ++i)
	{
		vFuture[i] = vPromise[i].get_future();
	}

	for (auto i = 0; i < nThreadSize; ++i)
	{
		vThread[i] = thread(func, arr + i * (nMax / nThreadSize), nMax / nThreadSize, std::ref(vPromise[i]));
	}

	for_each(vThread.begin(), vThread.end(), [](std::thread& th) { th.join(); });

	int total = 0;
	for (auto i = 0; i < nThreadSize; ++i)
	{
		int n = vFuture[i].get();
		total += n;
		std::cout << "f " << i + 1 << ": " << n << std::endl;
	}

	std::cout << "total: " << total << std::endl;


	std::future<int> r1 = std::async(std::launch::async, []() -> int {std::this_thread::sleep_for(std::chrono::milliseconds(1000)); std::cout << "async1" << std::endl; return 10; });
	std::cout << "after async result " << r1.get() << endl;
	std::future<bool> r2 = std::async(std::launch::async, []() -> bool {std::this_thread::sleep_for(std::chrono::milliseconds(1000)); std::cout << "async2" << std::endl; return true; });
	std::cout << "after async result " << (r2.get() ? "true" : "false") << endl;
}
