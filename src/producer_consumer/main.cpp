/*
* https://www.jianshu.com/p/c1dfa1d40f53
* producer_1 consumer_1 是简单的生产消费模型，有如下缺点
* 消费者的while循环很占用cpu，即使g_l为空时也占用100%的cpu
*
* producer_2 consumer_2 是改进的模型， 由于使用了list不需要考虑缓冲区的大小，所以能简化为一个信号
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <list>

std::list<int> g_l;
std::mutex g_m;

void producer_1();
void consumer_1();
void producer_2();
void consumer_2();

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
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
