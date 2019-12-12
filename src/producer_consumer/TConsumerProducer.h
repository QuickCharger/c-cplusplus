/*
* https://gist.github.com/dpressel/de9ea7603fa3f20b55bf
*
* 默认使用队列
*
*	producer			consumer
*	wait(可写)			wait(可读)
*	lock()				lock()
*	write()				read()
*	unlock()			unlock()
*	signal(可读)			signal(可写)
*/

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

/*
 * Some references in order
 *
 * Some code I wrote a long time before C++ 11 to do consumer producer buffers, using 2 condition variables
 * https://github.com/mdaus/coda-oss/blob/master/modules/c%2B%2B/mt/include/mt/RequestQueue.h
 *
 * A great article explaining both 2 condition variable and 1 condition variable buffers
 * https://en.wikipedia.org/wiki/Monitor_%28synchronization%29#Condition_variables
 *
 * C++ 11 thread reference:
 * http://en.cppreference.com/w/cpp/thread
 */

template<typename T, typename _Container = std::queue<T>>
class TConsumerProducer
{
	using size_type = typename _Container::size_type;

public:
	TConsumerProducer(int mxsz) : maxSize(mxsz)
	{ }

	template<typename T>
	void Add(T&& a)
	{
		std::unique_lock<std::mutex> lock(mutex);
		while(isFull())
			cond_able_write.wait(lock);
		cpq.push(std::forward<T>(a));
		lock.unlock();
		cond_able_read.notify_all();
	}

	T Consume()
	{
		std::unique_lock<std::mutex> lock(mutex);
		while (isEmpty())
			cond_able_read.wait(lock);
		T ret= std::move(cpq.front());
		cpq.pop();
		lock.unlock();
		cond_able_write.notify_all();
		return std::move(ret);
	}

private:
	inline bool isFull() const
	{
		return cpq.size() >= maxSize;
	}

	inline bool isEmpty() const
	{
		return cpq.size() == 0;
	}

private:
	size_type maxSize;
	_Container cpq;

	std::mutex mutex;
	std::condition_variable cond_able_write;
	std::condition_variable cond_able_read;

};
