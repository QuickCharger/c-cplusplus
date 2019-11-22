#pragma once

#include "../common.h"

volatile int counter_unique_lock(0);
std::mutex mtx_unique_lock;

/*
* try_lock_until(t) 相对lock_guard来说重写了 lock try_lock try_lock_for try_lock_until unlock 功能多的不写了
*/

void attempt_10k_increases_unique_lock()
{
	std::unique_lock<std::mutex> l(mtx_unique_lock, std::defer_lock);		// 此处如果不用defer_lock则创建时自动上锁。详细可参考unique_lock的源码
	l.lock();		// 因为该锁创建使用了defer_lock 所以此处可以进行手动上锁。 可以try_lock try_lock_for try_lock_until。详细可参考unique_lock的源码
	for (int i = 0; i < 100000; ++i)
	{
		++counter_unique_lock;
	}
}

int do_unique_lock()
{
	std::thread threads[THREAD_MAX];

	for (auto& it : threads) it = std::thread(attempt_10k_increases_unique_lock);
	for (auto& it : threads) it.join();

	std::cout << counter_unique_lock << " successful increases of the counter_unique_lock.\n";

	return 0;
}
