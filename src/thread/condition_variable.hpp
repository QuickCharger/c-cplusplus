#pragma once
/*
* 当 std::condition_variable 对象的某个 wait 函数被调用的时候，它使用 std::unique_lock(通过 std::mutex) 来锁住当前线程。
* 当前线程会一直被阻塞，直到另外一个线程在相同的 std::condition_variable 对象上调用了 notification 函数来唤醒当前线程，一旦线程被唤醒，wait()会再次自动调用lck.lock()。
*
* https://zh.cppreference.com/w/cpp/thread/condition_variable/wait
* https://www.cnblogs.com/GuoXinxin/p/11675053.html 这个文章里有condition_variable的各种使用场景，而且介绍的详细。
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
		cv.wait(lck);		// 此处用while循环，不用if，是因为可能会被虚假唤醒，所以每次被唤醒时都要检测是否是被真实唤醒。 详情搜索 "condition_variable 虚假唤醒"
	}
	//cv.wait(lck, []() -> bool { return ready_condition_lock; });		// 此语句等同上面语句
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
