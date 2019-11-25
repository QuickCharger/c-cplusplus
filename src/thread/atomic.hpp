#pragma once

/*
* c++11������������ԭ�Ӷ���atomic_flag �� atomic
* atomic_flag����򵥵�ԭ��bool�ͣ�ֻ֧�����ֲ��� test_and_set �� clear
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
* �����������Ի�ȡ�������õ���ռ�С����������������ֱ����ȡ��
* �ŵ㣺����Ҫ�̵߳��л����ܼ�ʱ�������������ںܶ�ʱ��ᱻ�ͷ����ܿ��ȡ������
* ȱ�㣺�˷�cpu��������ڶ�ʱ���ڲ��ܱ��ͷţ�����ռ��cpu��
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
	* �򵥲��� atomic_flag
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
	* �򵥵�spin-lock����
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
