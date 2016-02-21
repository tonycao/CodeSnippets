#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int random_pivot(int begin, int end) {
	return begin + (rand() % (end - begin + 1));
}

int Partition(vector<int>& a, int low, int high) {

	// random pivot
	int pivot = random_pivot(low, high);
	swap(a[pivot], a[high]);


	int pivotval = a[high]; // use last element as pivot
	
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (a[j] <= pivotval) {
			i++;
			swap(a[i], a[j]);
		}
	}

	swap(a[i + 1], a[high]);

	return i + 1;
}

void QuickSort(vector<int>& a, int low, int high) {
	if (low < high) {
		int pivot = Partition(a, low, high);
		QuickSort(a, low, pivot - 1);
		QuickSort(a, pivot + 1, high);
	}
}

void quickSort2(vector<int>& arr, int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quickSort2(arr, left, j);
      if (i < right)
            quickSort2(arr, i, right);
}


int main()
{
	int n, temp;
	srand(time(NULL));

	vector<int> a = {11, 22, 3, 6, 7, 9, 23, 12, 56, 34, 75, 34, 55, 39};
	n = 14;
	quickSort2(a, 0, n - 1);
	//QuickSort(a, 0, n - 1);
	cout << "the values after sort:" << endl;
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}