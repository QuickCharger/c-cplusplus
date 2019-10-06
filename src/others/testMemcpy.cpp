/*
* 测试结果
	vs2015
		debug
			简单复制和数组移位结果均是memcpy快，时间消耗约是for的1/3
		release
			简单复制 memcpy比for快，时间消耗约是for的1/5
			数组移位 for比memcpy略快， 时间消耗约是memcpy的1/1.3
	g++5.4.0
		g++ testMemcpy.cpp -std=c++11
			简单复制 memcpy比for快，时间消耗约是for的1/5
			数组移位 memcpy比for快，时间消耗约是for的1/2
		g++ testMemcpy.cpp -std=c++11 -O2
			简单复制 memcpy比for快，时间消耗约是for的1/10
			数组移位 for比memcpy快，时间消耗约是memcpy的1/2
*/

using namespace std;

void testMemcpy()
{
	/*
	* 测试简单复制
	* 复制times次， 数组大小arrCount
	* src: arr	dst: arrTmp
	*/
	{
		int clo = 0;
		int times = 10000000;
		//int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int arrCount = 10000000;
		int *arr = new int[arrCount];

		for (int i = 0; i < arrCount; ++i)
		{
			arr[i] = i;
		}

		cout << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
		{
			int *arrTmp = new int[arrCount];
			clo = clock();
			for (int t = 0; t < times; ++t)
				for (int i = 0; i < 10; ++i)
				{
					arrTmp[i] = arr[i];
				}
			cout << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
			delete arrTmp;
		}

		{
			int *arrTmp = new int[arrCount];
			clo = clock();
			for (int t = 0; t < times; ++t)
				memcpy(arrTmp, arr, 10 * sizeof(int));
			cout << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
			delete arrTmp;
		}
	}


	/*
	* 数组移位, arrCount大小的数组，整体向后移动times次， 移除的部分舍弃， 每次仅移动一个数
	*/
	{
		int clo = 0;
		int times = 1000;
		//int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int arrCount = 1000000;
		int *arr = new int[arrCount];

		for (int i = 0; i < arrCount; ++i)
		{
			arr[i] = i;
		}

		cout << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
		{
			int *arrTmp = new int[arrCount];
			memcpy(arrTmp, arr, arrCount * sizeof(int));
			clo = clock();
			for (int t = 0; t < times; ++t)
				for (int i = arrCount - 1; i > 0; --i)
				{
					arrTmp[i] = arrTmp[i - 1];
				}
			cout << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
			delete arrTmp;
		}

		{
			int *arrTmp = new int[arrCount];
			memcpy(arrTmp, arr, arrCount * sizeof(int));
			int *arrSwap = new int[arrCount];
			clo = clock();
			for (int t = 0; t < times; ++t)
			{
				memcpy(arrSwap, arrTmp, (arrCount - 1) * sizeof(int));
				memcpy(arrTmp + 1, arrSwap, (arrCount -1) * sizeof(int));
			}
			cout << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
			delete arrTmp;
			delete arrSwap;
		}
	}
}
