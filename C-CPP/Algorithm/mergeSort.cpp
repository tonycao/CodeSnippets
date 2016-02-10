#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//#define MAX_VALUE = 100000

void Merge(vector<int> &a, int p, int q, int r) {
	//int num1, num2;
	//num1 = q - p + 1;
	//num2 = r - q;
	int i = p, j = q + 1;
	//vector<int> left(num1 + 1);
	//vector<int> right(num2 + 1);
	vector<int> tmp;
	/*for (int i = 0; i < num1; i++) {
		left[i] = a[p + i];
	}
	for (int i = 0; i < num2; i++) {
		right[i] = a[q + 1 + i];
	}
	left[num1] = INT_MAX;
	right[num2] = INT_MAX;
	*/

	while(i <= q && j <= r) {
		if (a[i] < a[j]) {
			tmp.push_back(a[i++]);
		} else {
			tmp.push_back(a[j++]);
		}
	}
	while (i <= q) {
		tmp.push_back(a[i++]);
	}
	while (j <= r) {
		tmp.push_back(a[j++]);
	}

	//copy tmp to original array
	for (int k = 0; k <= r - p; k++) {
		a[p + k] = tmp[k];
	}

	// sorting

	/*int index1 = 0, index2 = 0;

	for (int i = p; i <= r; i++) {
		if (left[index1] <= right[index2]) {
			a[i] = left[index1];
			index1++;
		} else {
			a[i] = right[index2];
			index2++;
		}
	}*/

}

void MergeSort(vector<int> &a, int p, int r) {
	if (p < r) {
		int q = p + (r - p) / 2;
		MergeSort(a, p, q);
		MergeSort(a, q + 1, r);
		Merge(a, p, q, r);
	}
}

int main() {
	int n, temp;
	vector<int> a = {12, 1, 2, 4, 6, 11, 20, 21, 22, 22, 56, 22, 86, 5, 9, 33};
	n = a.size();
	MergeSort(a, 0, n - 1);
    cout<<"the values after sort:"<<endl;  
    for(int i = 0;i < n;++i)  
        cout<<a[i]<<" ";  
    cout << endl;
    return 0;
}
