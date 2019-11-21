#include "../common.h"

volatile int counter_try_lock(0);
std::mutex mtx_try_lock;

/*
* try_lock在当前锁被锁上时不会再上锁也不会等待，直接返回false
* 最终结果小于 10000*10
*/
void attempt_10k_increases_try_lock()
{
	for (int i = 0; i < 10000; ++i)
	{
		if (mtx_try_lock.try_lock())
		{
			++counter_try_lock;
			mtx_try_lock.unlock();
		}
	}
}

int do_try_lock()
{
	std::thread threads[10];
	for (int i = 0; i < 10; ++i)
	{
		threads[i] = std::thread(attempt_10k_increases_try_lock);
	}

	for (auto& th : threads)
	{
		th.join();
	}

	std::cout << counter_try_lock << " successful increases of the counter_try_lock.\n";

	return 0;
}
