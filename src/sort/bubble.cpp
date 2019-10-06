using namespace std;

/*
* Bubble 简单冒泡排序 无任何优化
* Bubble2 优化 第二层循环只定位最小值位置 循环结束后或交换数值
*/
void Bubble(int arr[], int s)
{
	int clo = clock();
	cout << "sort " << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
	int j = 0;
	int tmpSwap = 0;
	for (int i = 0; i < s; ++i)
		for (j = i + 1; j < s; ++j)
			if (arr[i] > arr[j])
			{
				tmpSwap = arr[i];
				arr[i] = arr[j];
				arr[j] = tmpSwap;
			}
	cout << "sort " << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
}

void Bubble2(int arr[], int s)
{
	int clo = clock();
	cout << "sort " << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;
	int j = 0;
	int tmpSwap = 0;
	int minPos = 0;
	for (int i = 0; i < s; ++i)
	{
		minPos = i;
		for (j = i + 1; j < s; ++j)
		{
			if (arr[minPos] > arr[j])
				minPos = j;
		}
		if (minPos != i)
		{
			tmpSwap = arr[i];
			arr[i] = arr[minPos];
			arr[minPos] = tmpSwap;
		}
	}
	cout << "sort " << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
}
