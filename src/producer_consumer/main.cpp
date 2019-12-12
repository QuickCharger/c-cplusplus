/*
* https://www.jianshu.com/p/c1dfa1d40f53
* producer_1 consumer_1 是简单的生产消费模型，有如下缺点
* 消费者的while循环很占用cpu，即使g_l为空时也占用100%的cpu
*
* producer_2 consumer_2 是改进的模型， 由于使用了list不需要考虑缓冲区的大小，所以能简化为一个信号
*/

#include <atomic>
#include <iostream>
#include <list>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include "TConsumerProducer.h"

std::list<int> g_l;
std::mutex g_m;

void producer_1();
void consumer_1();
void producer_2();
void consumer_2();
void testConsumerProducerQueue();

int main()
{
	std::thread t1(producer_1);
	std::thread t2(consumer_1);

	t1.join();
	t2.join();

	std::thread t3(producer_2);
	std::thread t4(consumer_2);

	t3.join();
	t4.join();

	testConsumerProducerQueue();

	std::cout << "over" << std::endl;
	std::cin.get();

	return 0;
}

void producer_1()
{
	for (auto it : { 1,2,3,4,5,6,7,8,9,10 })
	{
		std::unique_lock<std::mutex> locker(g_m);
		g_l.push_front(it);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void consumer_1()
{
	int data = 0;
	while(data != 10)
	{
		std::unique_lock<std::mutex> locker(g_m);
		if (g_l.size() != 0)
		{
			data = g_l.back();
			g_l.pop_back();
			std::cout << "consumer_1 got " << data << std::endl;
		}
	}
}

std::condition_variable g_cond;

void producer_2()
{
	for (auto it : { 1,2,3,4,5,6,7,8,9,10 })
	{
		std::unique_lock<std::mutex> locker(g_m);
		g_l.push_front(it);
		locker.unlock();
		g_cond.notify_all();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void consumer_2()
{
	int data = 0;
	while (data != 10)
	{
		std::unique_lock<std::mutex> locker(g_m);
		if (g_l.size() == 0)
		{
			g_cond.wait(locker);
		}
		data = g_l.back();
		g_l.pop_back();
		std::cout << "consumer_2 got " << data << std::endl;
	}
}

void testConsumerProducerQueue()
{
#define MAX_QUEUE 1
#define MAX_FOR 10000
	std::atomic_flag g_atomic_flag = ATOMIC_FLAG_INIT;
	TConsumerProducer<int> q(MAX_FOR);
	TConsumerProducer<std::string> qstr(MAX_FOR);

	std::thread producer1([&q]() {for (int i = 0; i < MAX_FOR; ++i) { q.Add(i); }});
	std::thread producer2([&q]() {for (int i = 0; i < MAX_FOR; ++i) { q.Add(i); }});
	std::thread producer3([&q]() {for (int i = 0; i < MAX_FOR; ++i) { q.Add(i); }});
	std::thread producer4([&q]() {for (int i = 0; i < MAX_FOR; ++i) { q.Add(i); }});

	std::thread consumer1([&q, &g_atomic_flag, &qstr]() {for (;;) { while (g_atomic_flag.test_and_set()) { int i = q.Consume(); std::stringstream ss; ss << "consumer1: " << i;  qstr.Add(ss.str()); g_atomic_flag.clear(); }}});
	std::thread consumer2([&q, &g_atomic_flag, &qstr]() {for (;;) { while (g_atomic_flag.test_and_set()) { int i = q.Consume(); std::stringstream ss; ss << "consumer2: " << i;  qstr.Add(ss.str()); g_atomic_flag.clear(); }}});
	std::thread consumer3([&q, &g_atomic_flag, &qstr]() {for (;;) { while (g_atomic_flag.test_and_set()) { int i = q.Consume(); std::stringstream ss; ss << "consumer3: " << i;  qstr.Add(ss.str()); g_atomic_flag.clear(); }}});
	std::thread consumer4([&q, &g_atomic_flag, &qstr]() {for (;;) { while (g_atomic_flag.test_and_set()) { int i = q.Consume(); std::stringstream ss; ss << "consumer4: " << i;  qstr.Add(ss.str()); g_atomic_flag.clear(); }}});

	std::thread consumer_str([&qstr]() {for (;;) { std::string &&str = qstr.Consume(); std::cout << str.c_str() << std::endl; }});

	producer1.join();
	producer2.join();
	producer3.join();
	producer4.join();
	consumer1.join();
	consumer2.join();
	consumer3.join();
	consumer4.join();
	consumer_str.join();

#undef MAX_QUEUE
#undef MAX_FOR
}
