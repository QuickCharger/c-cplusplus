/*
* 所有排序从小到大
*/

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <time.h>
#include <set>

#include "others.h"

using namespace std;

#define MOUNT 100000		// 测试 10M 数据
int *arr;
int *arrTmp;
int *arrSort;

void init()
{
	srand((int)time(nullptr));
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

	testMemcpy();

	cout << endl << "test over. press any key to exit" << endl;

	getchar();

	return 0;
}
