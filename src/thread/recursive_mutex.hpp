#pragma once

#include "../common.h"

volatile int counter_recursive_mutex(0);
static std::recursive_mutex  mtx_recursive_mutex;
thread_local int recursive_counter = 10000;

/*
* std::recursive_mutex 允许同一个线程对互斥量多次上锁（即递归上锁）。 同一个线程允许多次上锁， 不同线程直接被锁
* 此函数中用到了递归和递归锁，用以演示递归锁的使用情况。
*/
void attempt_10k_increases_recursive_mutex()
{
	if (recursive_counter-- == 0)
	{
		return;
	}
	mtx_recursive_mutex.lock();			// 递归锁在同一线程中允许被多次上锁
	++counter_recursive_mutex;
	attempt_10k_increases_recursive_mutex();
	mtx_recursive_mutex.unlock();
}

int do_recursive_mutex()
{
	std::thread threads[THREAD_MAX];

	for (auto& it : threads) it = std::thread(attempt_10k_increases_recursive_mutex);
	for (auto& it : threads) it.join();

	std::cout << counter_recursive_mutex << " successful increases of the counter_recursive_mutex.\n";

	return 0;
}
