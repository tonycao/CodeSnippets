#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int Partition(vector<int> &arr, int beg, int end)
{
	int sentinel = arr[end];
	int i = beg - 1;
	for(int j = beg; j <= end-1; ++j)
	{
		if(arr[j] <= sentinel)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[end]);

	return i+1;
}

int RandomPartition(vector<int> &arr, int beg, int end)
{
	int i = beg + rand() % (end - beg + 1);
	swap(arr[i], arr[end]);
	return Partition(arr, beg, end);
}


int RandomSelect(vector<int> &a, int p, int r, int i)
{
	if(p == r)
		return a[p];
	int q = RandomPartition(a, p, r);
	int k = q - p + 1;
	if(i == k)
		return a[q];
	else if(i < k)
		return RandomSelect(a, p, q - 1, i);
	else
		return RandomSelect(a, q + 1, r, i - k);
}

int main()  
{  
    vector<int> a = {0, 89, 100, 21, 5, 2, 8, 33, 27, 63, 77, 1, 2};  
    int size = a.size();
    int res;
	cout << "array: ";
    for(int i = 0; i < size; ++i)  
        cout << a[i] << " ";
	cout << endl;
	int k = 8;
    res = RandomSelect(a, 1, size, k);
	cout << "the " << k <<"th smallest number: " << res << endl;
	getchar();

    return 0;  
}