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
	for (int i = 0; i < THREAD_MAX; ++i)
	{
		threads[i] = std::thread(attempt_10k_increases_lock);
	}

	std::for_each(threads, threads + THREAD_MAX, [](std::thread& t) { t.join(); });

	std::cout << counter_lock << " successful increases of the counter_lock.\n";

	return 0;
}
