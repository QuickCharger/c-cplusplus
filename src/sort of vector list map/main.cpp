/*
* 测试STL对排序的效率
* 10M个结构体的排序
* 结果vector最佳
*     list最差
* ps: 由于 set 和 map 结构的特殊性, 数据量可能达不到10M个， 但也足以体现vector在排序上的优势
*/

#include <algorithm>
#include <iostream>
#include <time.h>

#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

struct stru {
	int v;

	bool operator < (const stru& s) const
	{
		return this->v > s.v;
	}
};

typedef struct stru SS;

bool comp(const SS& a, const SS& b) {
	return a.v > b.v;
}

int main()
{
	srand((int)time(nullptr));
	int mount = 100000;		// 测试 10M 数据

	// vector
	{
		vector<SS> vect;
		for (int i = 0; i < mount; ++i)
		{
			//vect.push_back(SS{i});
			vect.push_back(SS{ rand()/* % mount */});
		}

		int clo = clock();
		cout << "sort vector begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
		cout << "vector size: " << vect.size() << endl;
		sort(vect.begin(), vect.end(), comp);
		cout << "sort vector end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo<< endl << endl << endl;
	}


	// list
	{
		list<SS> l;
		for (int i = 0; i < mount; ++i)
		{
			//l.push_back(SS{ i });
			l.push_back(SS{ rand()/* % mount */});
		}

		int clo = clock();
		cout << "sort list begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
		cout << "list size: " << l.size() << endl;
		l.sort(comp);
		cout << "sort list end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl << endl << endl;
	}

	// set
	{
		int clo = clock();
		cout << "sort set begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
		set<SS, less<SS>> s;
		for (int i = 0; i < mount; ++i)
		{
			//s.insert(SS{ i });
			s.insert(SS{ rand()/* % mount */});
		}
		cout << "set size: " << s.size() << endl;
		cout << "sort set end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl << endl << endl;
	}


	// map
	{
		int clo = clock();
		cout << "sort map begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
		map<SS, SS, less<SS>> m;
		for (int i = 0; i < mount; ++i)
		{
			//m[SS{ i }] = SS{ i };
			int n = rand()/* % mount*/;
			m[SS{ n }] = SS{ n };
		}
		cout << "map size: " << m.size() << endl;
		cout << "sort map end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl << endl << endl;
	}

	cout << "test over. press any key to exit" << endl;

	getchar();

	return 0;
}
