#pragma once

#include "../common.h"

volatile int counter_try_lock_for(0);
std::timed_mutex mtx_timed;

/*
* try_lock_for(t) ，在t时间范围内等待上锁。如果时间段内获得了锁 上锁 返回true。如果超过了这段时间依旧没获得锁，返回false。
*/
void attempt_10k_increases_try_lock_for()
{
	if (mtx_timed.try_lock_for(std::chrono::milliseconds(1000)))		// 随着时间的增大，计算的结果也会变大。因为等待锁的时间变长了
	{
		for (int i = 0; i < 10000; ++i)
		{
			++counter_try_lock_for;
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));
		}
		mtx_timed.unlock();
	}
}

int do_try_lock_for()
{
	std::thread threads[THREAD_MAX];

	for (auto& it : threads) it = std::thread(attempt_10k_increases_try_lock_for);
	for (auto& it : threads) it.join();

	std::cout << counter_try_lock_for << " successful increases of the counter_try_lock_for.\n";

	return 0;
}
