using namespace std;

/*
*	leftֵΪĿ��ֵ��pos
*		�� ���û��Ŀ��ֵ left��posΪ����Ŀ��ֵ��pos
*		�� �������������С��Ŀ��ֵ left��posΪright+1
*	ǰ��ĸ����ж���Insert2���ϵ�����ʹ��Ƶ�ʷ������� ע�͵�
*/
inline bool search(int arr[], int len, int goal, int& left)
{
	left = 0;
	int right = len - 1;

	//if (arr[right] < goal)	// ������������ҲС��goal
	//{
	//	left = right + 1;
	//	return false;
	//}
	//else if (arr[right] == goal)
	//{
	//	left = right;
	//	return true;
	//}
	//else if (arr[left] >= goal)	// ��������С����Ҳ���ڵ���goal
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
* Insert �򵥲������� �˴�����memcpy ��ΪҪִ�����β�����������ƫ��, ʵ��Ч�ú�ʱ��ȴ˰汾����һ�����ʱ��
* Insert2 �Ż� ����ʹʹ�ö��ַ�
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
		for (j = i - 1; j >= 0 && curValue < arr[j]; --j)		// �˴�����memcpy����Ϊʵ������Ч������for
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
			* �˴�Ϊ����Insert���Ա� û����memcpy
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
