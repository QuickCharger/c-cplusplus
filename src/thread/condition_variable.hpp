#pragma once
/*
* 当 std::condition_variable 对象的某个 wait 函数被调用的时候，它使用 std::unique_lock(通过 std::mutex) 来锁住当前线程。
* 当前线程会一直被阻塞，直到另外一个线程在相同的 std::condition_variable 对象上调用了 notification 函数来唤醒当前线程。
*
* wait(lock) 的说明在 https://zh.cppreference.com/w/cpp/thread/condition_variable/wait 里有说明，会解锁lock
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
