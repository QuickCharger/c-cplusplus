#pragma once
/*
* �� std::condition_variable �����ĳ�� wait ���������õ�ʱ����ʹ�� std::unique_lock(ͨ�� std::mutex) ����ס��ǰ�̡߳�
* ��ǰ�̻߳�һֱ��������ֱ������һ���߳�����ͬ�� std::condition_variable �����ϵ����� notification ���������ѵ�ǰ�̡߳�
*
* wait(lock) ��˵���� https://zh.cppreference.com/w/cpp/thread/condition_variable/wait ����˵���������lock
*/
#include "../common.h"

std::mutex mtx_condition_lock;
std::condition_variable cv;
bool ready_condition_lock = false;

void attempt_do_condition_variable(int id)
{
	std::unique_lock<std::mutex> lck(mtx_condition_lock);
	while (!ready_condition_lock)
	{
		cv.wait(lck);
	}
	std::cout << "thread " << id << endl;
}

void go()
{
	std::unique_lock<std::mutex> lck(mtx_condition_lock);
	ready_condition_lock = true;
	cv.notify_all();
}

int do_condition_variable()
{
	std::thread threads[THREAD_MAX];

	for (int i = 0; i < 10; ++i)
	{
		threads[i] = std::thread(attempt_do_condition_variable, i);
	}

	std::cout << THREAD_MAX << " threads ready to race ..." << std::endl;
	go();

	for (auto& it : threads) it.join();

	std::cout << "successful do attempt_do_condition_variable.\n";

	return 0;
}
