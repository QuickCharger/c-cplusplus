#pragma once

/*
* c++11定义了两大类原子对象。atomic_flag 和 atomic
* atomic_flag是最简单的原子bool型，只支持两种操作 test_and_set 和 clear
*/

#include "../common.h"

std::atomic<bool> atomic_ready{ false };
std::atomic_flag g_atomic_flag = ATOMIC_FLAG_INIT;
static int counter_spin_lock(0);

void attempt_do_count1m(int id)
{
	while (!atomic_ready) {
		std::this_thread::yield();
	}

	for (int i = 0; i < 1000000; ++i)
		;

	if (!g_atomic_flag.test_and_set())
	{
		std::cout << "thread #" << id << " first finish"<< std::endl;
	}
}

/*
* 自旋锁：尝试获取锁，若得到就占有。若不能则持续尝试直到获取。
* 优点：不需要线程的切换就能及时获得锁。如果锁在很短时间会被释放则会很快获取到锁。
* 缺点：浪费cpu。如果锁在短时间内不能被释放，则会很占用cpu。
*/
void attempt_do_spin_lock()
{
	for (int i = 0; i < 10000; ++i)
	{
		while (g_atomic_flag.test_and_set())
			;
		++counter_spin_lock;
		g_atomic_flag.clear();
	}
}

int do_atomic()
{
	std::thread threads[THREAD_MAX];

	/*
	* 简单测试 atomic_flag
	*/
	for (int j = 0; j < 10; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			threads[i] = std::thread(attempt_do_count1m, i);
		}

		atomic_ready = true;

		for (auto& it : threads) it.join();

		atomic_ready = false;
		g_atomic_flag.clear();
	}
	std::cout << "successful do attempt_do_count1m.\n";

	/*
	* 简单的spin-lock测试
	*/
	{
		g_atomic_flag.clear();
		for (int i = 0; i < 10; ++i)
		{
			threads[i] = std::thread(attempt_do_spin_lock);
		}
		for (auto& it : threads) it.join();

		std::cout << counter_spin_lock << " successful increases of the spin-lock.\n";
	}

	return 0;
}
