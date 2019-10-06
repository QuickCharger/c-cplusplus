/*
* https://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F
*/

void shell(int arr[], int len)
{
	int clo = clock();
	cout << "sort " << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;

	int gap, i, j;
	int temp;
	for (gap = len >> 1; gap > 0; gap >>= 1)
		for (i = gap; i < len; i++) {
			temp = arr[i];
			for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
				arr[j + gap] = arr[j];
			arr[j + gap] = temp;
		}

	cout << "sort " << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
}
