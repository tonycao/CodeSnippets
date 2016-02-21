#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> A, int target) {
	int left = 0, right = A.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (A[mid] == target) return mid;
		else if (A[mid] < target) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}
int main() {
	vector<int> num = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int target = 11;
	cout << binary_search(num, target) << endl;
}