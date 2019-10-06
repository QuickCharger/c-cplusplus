using namespace std;

/*
*	left值为目标值的pos
*		或 如果没有目标值 left的pos为大于目标值的pos
*		或 数组的所有数都小于目标值 left的pos为right+1
*	前面的各种判断在Insert2不断调用中使用频率反倒不高 注释掉
*/
inline bool search(int arr[], int len, int goal, int& left)
{
	left = 0;
	int right = len - 1;

	//if (arr[right] < goal)	// 数组中最大的数也小于goal
	//{
	//	left = right + 1;
	//	return false;
	//}
	//else if (arr[right] == goal)
	//{
	//	left = right;
	//	return true;
	//}
	//else if (arr[left] >= goal)	// 数组中最小的数也大于等于goal
	//{
	//	return arr[left] == goal;
	//}
	//else
	//{
		while (left < right)
		{
			int mid = left + (right - left) / 2;
			if (arr[mid] > goal)
				right = mid - 1;
			else if (arr[mid] < goal)
				left = mid + 1;
			else
			{
				left = mid;
				break;
			}
		}
		if (arr[left] == goal)
		{
			return true;
		}
		else if (arr[left] > goal)
		{
			return false;
		}
		else
		{
			left++;
			return false;
		}
	//}
}

/*
* Insert 简单插入排序 此处不用memcpy 因为要执行两次才能完整整体偏移, 实际效用耗时会比此版本多用一倍多的时间
* Insert2 优化 查找使使用二分法
*/
void Insert(int arr[], int s)
{
	int clo = clock();
	cout << "sort " << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;

	int curValue = 0;
	for (int i = 1; i < s; ++i)
	{
		curValue = arr[i];
		int j = i;
		for (j = i - 1; j >= 0 && curValue < arr[j]; --j)		// 此处不用memcpy是因为实际运行效果不如for
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = curValue;
	}

	cout << "sort " << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
}

void Insert2(int arr[], int s)
{
	int clo = clock();
	int *arrTmp = new int[s];
	memset(arrTmp, 0, s * sizeof(int));
	cout << "sort " << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;

	int pos = 0;
	int tmp = 0;
	for (int i = 1; i < s; ++i)
	{
		tmp = arr[i];

		search(arr, i, tmp, pos);

		if (pos < i)
		{
			/*
			* 此处为了与Insert做对比 没有用memcpy
			*/
			//memcpy(arrTmp, arr + pos, (i - pos) * sizeof(int));
			//memcpy(arr + pos + 1, arrTmp, (i - pos) * sizeof(int));
			for (int i2 = i; i2 > pos; --i2)
				arr[i2] = arr[i2 - 1];
			arr[pos] = tmp;
		}
	}

	cout << "sort " << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
	delete arrTmp;
}
