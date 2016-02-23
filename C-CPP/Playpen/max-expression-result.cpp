#include <iostream>
#include <vector>

using namespace std;

//2维DP, O(N^3)
int maxExprResult(vector<int> A) {
	int n = A.size();
	vector<vector<int>> f(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		f[i][i] = A[i];
	}

	for (int w = 2; w <= n; w++) { // window size of the sliding window
		for (int i = 0, j = w - 1; j < n; i++, j++) {
			for (int k = i; k < j; k++) {
				f[i][j] = max(f[i][j], max(f[i][k] + f[k + 1][j], f[i][k] * f[k+1][j]));
			}
		}
	}
	return f[0][n - 1];
}

//1维DP，O(N)
int maxExprResult2(vector<int> A) {
	int n = A.size();
	vector<int> k(n);
	k[0] = A[0];

	for (int i = 1; i < n; i++) { 
		k[i] = max(k[i - 1]*A[i], (i >= 2 ? k[i - 2] : 1) * (A[i - 1] + A[i]));
		if (i >= 2) {
			k[i] = max(k[i], (i >= 3 ? k[i - 3] : 1) * (A[i - 2] + A[i - 1] + A[i]));
		}
	}
	return k[n - 1];
}

int main() {
	vector<int> A = {1, 2, 3, 4, 5};
	cout << maxExprResult(A) << endl;
	cout << maxExprResult2(A) << endl;
}