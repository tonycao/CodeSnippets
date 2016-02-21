// longest increasing subsequence

#include <iostream>
#include <vector>

using namespace std;

int lis(int A[], int n) {
	vector<int> d(n, 0);
	int len = 1;
	for (int i = 0; i < n; i++) {
		d[i] = 1;
		for (int j = 0; j < i; j++) {
			if (A[i] >= A[j] && d[j] + 1 > d[i]) {
				d[i] = d[j] + 1;
			}
			if (d[i] > len) len = d[i];
		}
	}
	return len;
}

int main() {
	int A[] = {4, 3, 5, 8 ,6, 7, 9};

	cout << lis(A, 7) << endl;
}
