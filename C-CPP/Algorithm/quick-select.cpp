#include <iostream>
#include <cstdlib>
using namespace std;

int Partition(int *arr, int beg, int end)
{
	int key = arr[end];
	int i = beg-1;
	for(int j=beg; j<=end-1; ++j)
	{
		if(arr[j] <= key)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i+1], arr[end]);

	return i+1;
}

int RandomPartition(int *arr, int beg, int end)
{
	int i = beg + rand() % (end-beg+1);
	swap(arr[i], arr[end]);
	return Partition(arr, beg, end);
}


int RandomSelect(int *a, int left, int right, int i)
{
	if(left == right)
		return a[left];
	int q = Partition(a, left, right);
	int k = q - left + 1;
	if(i == k)
		return a[q];
	else if(i < k)
		return RandomSelect(a, left, q - 1, i);
	else
		return RandomSelect(a, q + 1, right, i - k);
}

int main()  
{  
    int a[] = {0, 89, 100, 21, 5, 2, 8, 33, 27, 63};  
    int num = sizeof(a) / sizeof(a[0]);
    int ith;
	cout << "numbers: ";
    for(int i = 1; i < num; ++i)  
        cout << a[i] << " ";
	cout << endl;
	int k = 4;
    ith = RandomSelect(a, 1, num, k);
	cout << k << "th smallest: " << ith << endl;
	getchar();

    return 0;  
}