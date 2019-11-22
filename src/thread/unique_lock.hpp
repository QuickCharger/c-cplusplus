#pragma once

#include "../common.h"

volatile int counter_unique_lock(0);
std::mutex mtx_unique_lock;

/*
* try_lock_until(t) ���lock_guard��˵��д�� lock try_lock try_lock_for try_lock_until unlock ���ܶ�Ĳ�д��
*/

void attempt_10k_increases_unique_lock()
{
	std::unique_lock<std::mutex> l(mtx_unique_lock, std::defer_lock);		// �˴��������defer_lock�򴴽�ʱ�Զ���������ϸ�ɲο�unique_lock��Դ��
	l.lock();		// ��Ϊ��������ʹ����defer_lock ���Դ˴����Խ����ֶ������� ����try_lock try_lock_for try_lock_until����ϸ�ɲο�unique_lock��Դ��
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
