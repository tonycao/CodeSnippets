#include <iostream>
#include <cstdlib>
using namespace std;

int Partition(int *arr, int beg, int end)
{
	int sentinel = arr[end];
	int i = beg-1;
	for(int j=beg; j<=end-1; ++j)
	{
		if(arr[j] <= sentinel)
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


int RandomSelect(int *a, int p, int r, int i)
{
	if(p == r)
		return a[p];
	int q = Partition(a, p, r);
	int k = q-p+1;
	if(i == k)
		return a[q];
	else if(i < k)
		return RandomSelect(a, p, q-1, i);
	else
		return RandomSelect(a, q+1, r, i-k);
}

int main()  
{  
    int a[] = {0, 89, 100, 21, 5, 2, 8, 33, 27, 63};  
    int num = 9;
    int ith;
	cout << "序列为: ";
    for(int i=1; i<=num; ++i)  
        cout << a[i] << " ";
	cout << endl;
    ith = RandomSelect(a, 1, num, 2);
	cout << "序列中第2小的数字是: " << ith << endl;
	getchar();

    return 0;  
}