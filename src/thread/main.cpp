/*
* �ο��� https://www.cnblogs.com/haippy/p/3284540.html
*
* mutex �� mutual exclusive ����д
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
	* �������йغ��̵߳ĸ��ֲ���
	* ������
	*		mutex			����������
	*		recursive_mutex	����������һ���߳��ڱ��������
	*		timed_mutex		��ʱ���йص����������ڸ�����ʱ���ڵȴ�����������ʱ���������û�õ�����ֱ�ӷ���false
	*		recursive_timed_mutex	û��
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
	* ������������������֪ͨ�������������źš� ��������������ģ��
	*/
	cout << "==== do_condition_variable ====" << endl;
	do_condition_variable();

	/*
	* ԭ�Ӳ���
	*/
	cout << "==== do_atomic ====" << endl;
	do_atomic();

	cout << "==== do_future ====" << endl;
	do_future();

	getchar();

	return 0;
}
