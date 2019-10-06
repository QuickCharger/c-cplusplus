/*
* 所有排序从小到大
* https://zh.wikipedia.org/wiki/Category:%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95
*/

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <time.h>
#include <set>

#include "sort.h"

using namespace std;

int getRandom()
{
	//static int ret = 0;
	int ret = 0;
#ifdef WIN32
	ret = rand();
	ret <<= 16;
	ret |= rand();
	//return ret++;
#else
	ret = rand();
#endif

	return ret;
}


#define MOUNT 1000000		// 测试 10M 数据
int *arr;
int *arrTmp;
int *arrSort;

void init()
{
	srand((int)time(nullptr));

	arr = new int[MOUNT];
	for (int i = 0; i < MOUNT; ++i)
	{
		arr[i] = getRandom();
	}

	arrTmp = new int[MOUNT];
	memcpy(arrTmp, arr, MOUNT * sizeof(int));

	arrSort = new int[MOUNT];

	multiset<int> sArr;
	for (int i = 0; i < MOUNT; ++i)
	{
		sArr.insert(arr[i]);
	}
	int i = 0;
	for (auto it = sArr.begin(); it != sArr.end(); ++it)
	{
		arrSort[i++] = *it;
		//cout << *it << endl;
	}
	cout << "arrSort size: " << sArr.size() << endl;
}

bool verify(int arr[], int s)
{
	for (int i = 0; i < MOUNT; ++i)
	{
		if (arr[i] != arrSort[i])
			return false;
	}
	return true;
}

int main()
{
	init();

	/*
	* 冒泡排序等待时间较长 此处可注释
	*/
	//Bubble(arrTmp, MOUNT);
	//cout << "verify bubble. result " << (verify(arrTmp, MOUNT) ? "OK" : "FLASE !!!") << endl << endl;

	//memcpy(arrTmp, arr, MOUNT * sizeof(int));
	//Bubble2(arrTmp, MOUNT);
	//cout << "verify bubble2. result " << (verify(arrTmp, MOUNT) ? "OK" : "FLASE !!!") << endl << endl;

	//memcpy(arrTmp, arr, MOUNT * sizeof(int));
	//Insert(arrTmp, MOUNT);
	//cout << "verify insert. result " << (verify(arrTmp, MOUNT) ? "OK" : "FLASE !!!") << endl << endl;

	//memcpy(arrTmp, arr, MOUNT * sizeof(int));
	//Insert2(arrTmp, MOUNT);
	//cout << "verify insert. result " << (verify(arrTmp, MOUNT) ? "OK" : "FLASE !!!") << endl << endl;

	//memcpy(arrTmp, arr, MOUNT * sizeof(int));
	//shell(arrTmp, MOUNT);
	//cout << "verify shell. result " << (verify(arrTmp, MOUNT) ? "OK" : "FLASE !!!") << endl << endl;

	memcpy(arrTmp, arr, MOUNT * sizeof(int));
	quick(arrTmp, MOUNT);
	cout << "verify quick. result " << (verify(arrTmp, MOUNT) ? "OK" : "FLASE !!!") << endl << endl;

	memcpy(arrTmp, arr, MOUNT * sizeof(int));
	//merge_sort(arrTmp, MOUNT);
	cout << "verify quick. result " << (verify(arrTmp, MOUNT) ? "OK" : "FLASE !!!") << endl << endl;


	//for (int i = 0; i < MOUNT; ++i)
	//	cout << arrTmp[i] << endl;

	cout << endl << "test over. press any key to exit" << endl;

	getchar();

	return 0;
}
