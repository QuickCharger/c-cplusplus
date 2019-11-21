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
	std::thread threads[10];
	for (int i = 0; i < 10; ++i)
	{
		threads[i] = std::thread(attempt_10k_increases_lock);
	}

	for (auto& th : threads)
	{
		th.join();
	}

	std::cout << counter_lock << " successful increases of the counter_lock.\n";

	return 0;
}
