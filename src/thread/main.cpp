/*
* 参考自 https://www.cnblogs.com/haippy/p/3284540.html
*
* mutex 是 mutual exclusive 的缩写
*/

#include "../common.h"

#include "lock.hpp"
#include "try_lock.hpp"
#include "recursive_mutex.hpp"
#include "try_lock_for.hpp"
#include "try_lock_until.hpp"
#include "lock_guard.hpp"
#include "unique_lock.hpp"
#include "future.hpp"
#include "condition_variable.hpp"
#include "atomic.hpp"
#include "future.hpp"

using namespace std;

int main()
{
	/*
	* 如下是有关和线程的各种测试
	* 互斥量
	*		mutex			基本互斥量
	*		recursive_mutex	互斥量可在一个线程内被多次上锁
	*		timed_mutex		和时间有关的锁，可以在给定的时间内等待上锁，超出时间如果依旧没得到锁，直接返回false
	*		recursive_timed_mutex	没看
	*/
	cout << "==== do_lock ====" << endl;
	do_lock();
	cout << "==== do_trylock ====" << endl;
	do_try_lock();
	cout << "==== do_recurisve_mutex ====" << endl;
	do_recursive_mutex();
	cout << "==== do_try_lock_for ====" << endl;
	do_try_lock_for();
	cout << "==== do_try_lock_until ====" << endl;
	do_try_lock_until();
	cout << "==== do_lock_guard ====" << endl;
	do_lock_guard();
	cout << "==== do_unique_lock ====" << endl;
	do_unique_lock();

	/*
	* 锁的条件变量，用于通知解锁，类似于信号。 可用于生产消费模型
	*/
	cout << "==== do_condition_variable ====" << endl;
	do_condition_variable();

	/*
	* 原子操作
	*/
	cout << "==== do_atomic ====" << endl;
	do_atomic();

	cout << "==== do_future ====" << endl;
	do_future();

	getchar();

	return 0;
}
