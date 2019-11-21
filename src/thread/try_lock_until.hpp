#include "../common.h"
#include <time.h>

volatile int counter_try_lock_until(0);
std::timed_mutex mtx_timed_until;

/*
* try_lock_until(t) 等待t时间戳前获得锁。如果等到了锁 上锁 返回true。如果到达时间戳依旧没上锁，返回false。
*/
void attempt_10k_increases_try_lock_until(int i)
{
	auto timestamp = std::chrono::system_clock::now();
	if (i == 2)
	{
		timestamp = std::chrono::system_clock::time_point(std::chrono::system_clock::duration(_Xtime_get_ticks() + 10000000));		// 当前时间戳的下一秒, _Xtime_get_ticks()返回的是纳秒
	}
	if (mtx_timed_until.try_lock_until(timestamp))		// 此处传入的是当前时间戳，为了演示进行了特殊处理，只有两个个线程获得了锁。其余的线程都因为等待超时而结束。
	{
		for (int i = 0; i < 10000; ++i)
		{
			++counter_try_lock_until;
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));		// 此处需要加上一定延迟，否则所有线程都会获得锁。
		}
		mtx_timed_until.unlock();
	}
}

int do_try_lock_until()
{
	std::thread threads[THREAD_MAX];
	for (int i = 0; i < THREAD_MAX; ++i)
	{
		threads[i] = std::thread(attempt_10k_increases_try_lock_until, i);
	}

	std::for_each(threads, threads + THREAD_MAX, [](std::thread& t) { t.join(); });

	std::cout << counter_try_lock_until << " successful increases of the counter_try_lock_until.\n";

	return 0;
}
