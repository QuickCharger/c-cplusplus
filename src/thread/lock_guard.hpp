#pragma once

#include "../common.h"

std::mutex mtx_lock_guard;

void print_even(int x)
{
	if (x % 2 == 0)
	{
		std::cout << x << " is even" << endl;
	}
	else
	{
		throw (std::logic_error("not even"));
	}
}

void attempt_lock_guard(int id)
{
	try {
		std::lock_guard<std::mutex> l(mtx_lock_guard);
		print_even(id);
	}
	catch (std::logic_error& e) {
		std::cout << "[exception caught]. reason: " << e.what() << endl;
	}
}

int do_lock_guard()
{
	std::thread threads[THREAD_MAX];
	for (int i = 0; i < THREAD_MAX; ++i)
	{
		threads[i] = std::thread(attempt_lock_guard, i);
	}

	for (auto& it : threads) it.join();

	return 0;
}
