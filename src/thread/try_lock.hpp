#pragma once

#include "../common.h"

volatile int counter_try_lock(0);
std::mutex mtx_try_lock;

/*
* try_lock�ڵ�ǰ��������ʱ����������Ҳ����ȴ���ֱ�ӷ���false
* ���ս��С�� 10000*10
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
	std::thread threads[THREAD_MAX];

	for (auto& it : threads) it = std::thread(attempt_10k_increases_try_lock);
	for (auto& it : threads) it.join();

	std::cout << counter_try_lock << " successful increases of the counter_try_lock.\n";

	return 0;
}
