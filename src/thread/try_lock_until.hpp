#include "../common.h"
#include <time.h>

volatile int counter_try_lock_until(0);
std::timed_mutex mtx_timed_until;

/*
* try_lock_until(t) �ȴ�tʱ���ǰ�����������ȵ����� ���� ����true���������ʱ�������û����������false��
*/
void attempt_10k_increases_try_lock_until(int i)
{
	auto timestamp = std::chrono::system_clock::now();
	if (i == 2)
	{
		timestamp = std::chrono::system_clock::time_point(std::chrono::system_clock::duration(_Xtime_get_ticks() + 10000000));		// ��ǰʱ�������һ��, _Xtime_get_ticks()���ص�������
	}
	if (mtx_timed_until.try_lock_until(timestamp))		// �˴�������ǵ�ǰʱ�����Ϊ����ʾ���������⴦��ֻ���������̻߳��������������̶߳���Ϊ�ȴ���ʱ��������
	{
		for (int i = 0; i < 10000; ++i)
		{
			++counter_try_lock_until;
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));		// �˴���Ҫ����һ���ӳ٣����������̶߳���������
		}
		mtx_timed_until.unlock();
	}
}

int do_try_lock_until()
{
	std::thread threads[THREAD_MAX];
	for (int i = 0; i < THREAD_MAX; ++i)
	{
		threads[i] = std::thread(attempt_10k_increases_try_lock_until, i);
	}

	std::for_each(threads, threads + THREAD_MAX, [](std::thread& t) { t.join(); });

	std::cout << counter_try_lock_until << " successful increases of the counter_try_lock_until.\n";

	return 0;
}
