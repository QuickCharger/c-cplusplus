#pragma once

#include "../common.h"

volatile int counter_try_lock_for(0);
std::timed_mutex mtx_timed;

/*
* try_lock_for(t) ����tʱ�䷶Χ�ڵȴ����������ʱ����ڻ������ ���� ����true��������������ʱ������û�����������false��
*/
void attempt_10k_increases_try_lock_for()
{
	if (mtx_timed.try_lock_for(std::chrono::milliseconds(1000)))		// ����ʱ������󣬼���Ľ��Ҳ������Ϊ�ȴ�����ʱ��䳤��
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
