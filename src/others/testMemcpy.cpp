/*
* ���Խ��
	vs2015
		debug
			�򵥸��ƺ�������λ�������memcpy�죬ʱ������Լ��for��1/3
		release
			�򵥸��� memcpy��for�죬ʱ������Լ��for��1/5
			������λ for��memcpy�Կ죬 ʱ������Լ��memcpy��1/1.3
	g++5.4.0
		g++ testMemcpy.cpp -std=c++11
			�򵥸��� memcpy��for�죬ʱ������Լ��for��1/5
			������λ memcpy��for�죬ʱ������Լ��for��1/2
		g++ testMemcpy.cpp -std=c++11 -O2
			�򵥸��� memcpy��for�죬ʱ������Լ��for��1/10
			������λ for��memcpy�죬ʱ������Լ��memcpy��1/2
*/

using namespace std;

void testMemcpy()
{
	/*
	* ���Լ򵥸���
	* ����times�Σ� �����СarrCount
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
	* ������λ, arrCount��С�����飬��������ƶ�times�Σ� �Ƴ��Ĳ��������� ÿ�ν��ƶ�һ����
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
