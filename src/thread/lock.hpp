#pragma once

#include "../common.h"

static volatile int counter_lock(0);
static std::mutex mtx_lock;

void attempt_10k_increases_lock()
{
	for (int i = 0; i < 10000; ++i)
	{	
		mtx_lock.lock();
		++counter_lock;
		mtx_lock.unlock();
	}
}

int do_lock()
{
	std::thread threads[THREAD_MAX];

	for (auto& it : threads) it = std::thread(attempt_10k_increases_lock);
	for (auto& it : threads) it.join();

	std::cout << counter_lock << " successful increases of the counter_lock.\n";

	return 0;
}
