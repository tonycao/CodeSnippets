#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::cin;


/*
Given a matrix, each cell having only 0's or 1's, 
find the largest sub-matrix with equal number of 0's and 1's in it.
*/
class maxSubMatrixwithEqualZerosandOnes {
	
public:
	int getSubMatrix(vector<vector<int>> &matrix) {
		int m = matrix.size();
		if (m == 0) {
			return 0;
		}
		int n = matrix[0].size();

		int overallMax = 0;
		for (int i = 0; i < m; ++i) {
			vector<int> rowSum(n, 0);
			for (int j = i; j < m; ++j) {
				for (int k = 0; k < n; ++k) {
					rowSum[k] += matrix[j][k] == 0 ? -1 : 1;
				}
				
				int maxSofar = (j - i + 1) * maxSubarray(rowSum);
				if (maxSofar > overallMax) {
					overallMax = maxSofar;
				}
			}
		}
		return overallMax;
	}

private:
	// max subarry sum to 0
	// 
	int maxSubarray(vector<int> &arr) {
		vector<int> cumsum(arr.size(), 0);
		cumsum[0] = arr[0];
		for (int i = 1; i < arr.size(); ++i ) {
			cumsum[i] = cumsum[i - 1] + arr[i];
		}

		map<int, int> umap;
		int maxsize = 0;
		for (int i = 0; i < arr.size(); ++i) {
			if (cumsum[i] == 0) {
				maxsize = i + 1;
			}

			if (umap.find(cumsum[i]) == umap.end()) {
				umap[cumsum[i]] = i;
			} else {
				if (maxsize < i - umap[cumsum[i]]) {
					maxsize = i - umap[cumsum[i]];
				}
			}
		}

		return maxsize;
	}
};

int main() {
	vector<vector<int>> matrix = {
		{1, 0, 0, 1, 1}, 
		{0, 1, 1, 0, 0},
		{1, 1, 1, 1, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1}
	};



	maxSubMatrixwithEqualZerosandOnes sol;
	cout << sol.getSubMatrix(matrix) << endl;

	matrix = {{1, 0}, {0, 0}};
	cout << sol.getSubMatrix(matrix) << endl;

}