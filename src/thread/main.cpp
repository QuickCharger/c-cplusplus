/*
* ²Î¿¼×Ô https://www.cnblogs.com/haippy/p/3284540.html
*/

#include "../common.h"

#include "lock.hpp"
#include "try_lock.hpp"
#include "recursive_mutex.hpp"
#include "try_lock_for.hpp"
#include "try_lock_until.hpp"

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
	int* arr = new int[nMax] {0};
	int nIndex = 0;
	std::for_each(arr, arr + nMax, [&nIndex](int & i) { i = nIndex++; });

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

	cout << "==== do_lock ====" << endl;
	do_lock();
	cout << "==== do_trylock ====" << endl;
	do_try_lock();
	cout << "==== do_recurisve_mutex ====" << endl;
	do_recursive_mutex();
	cout << "==== do_try_lock_for ====" << endl;
	do_try_lock_for();
	cout << "==== do_try_lock_until ====" << endl;
	do_try_lock_until();

	getchar();

	return 0;
}
