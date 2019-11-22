#pragma once

#include "../common.h"

volatile int counter_recursive_mutex(0);
static std::recursive_mutex  mtx_recursive_mutex;
thread_local int recursive_counter = 10000;

/*
* std::recursive_mutex ����ͬһ���̶߳Ի�����������������ݹ��������� ͬһ���߳������������� ��ͬ�߳�ֱ�ӱ���
* �˺������õ��˵ݹ�͵ݹ�����������ʾ�ݹ�����ʹ�������
*/
void attempt_10k_increases_recursive_mutex()
{
	if (recursive_counter-- == 0)
	{
		return;
	}
	mtx_recursive_mutex.lock();			// �ݹ�����ͬһ�߳��������������
	++counter_recursive_mutex;
	attempt_10k_increases_recursive_mutex();
	mtx_recursive_mutex.unlock();
}

int do_recursive_mutex()
{
	std::thread threads[THREAD_MAX];

	for (auto& it : threads) it = std::thread(attempt_10k_increases_recursive_mutex);
	for (auto& it : threads) it.join();

	std::cout << counter_recursive_mutex << " successful increases of the counter_recursive_mutex.\n";

	return 0;
}
