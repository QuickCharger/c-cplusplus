
void swap(int *x, int *y) {
	int t = *x;
	*x = *y;
	*y = t;
}

void quick_sort_recursive(int arr[], int start, int end) {
	if (start >= end)
		return;
	int mid = arr[end];
	int left = start, right = end - 1;
	while (left < right) {
		while (arr[left] < mid && left < right)
			left++;
		while (arr[right] >= mid && left < right)
			right--;
		swap(&arr[left], &arr[right]);
	}
	if (arr[left] >= arr[end])
		swap(&arr[left], &arr[end]);
	else
		left++;
	if (left)
		quick_sort_recursive(arr, start, left - 1);
	quick_sort_recursive(arr, left + 1, end);
}

void quick(int arr[], int len)
{
	int clo = clock();
	cout << "sort " << __FUNCTION__ << " begin. time: " << time(nullptr) << ". clock: " << clock() << endl;

	quick_sort_recursive(arr, 0, len - 1);

	cout << "sort " << __FUNCTION__ << " end.   time: " << time(nullptr) << ". clock: " << clock() << ". use clock: " << clock() - clo << endl;
}
