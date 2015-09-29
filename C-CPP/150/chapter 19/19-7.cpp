/*
You are given an array of integers (both positive and negative). Find the continuous sequence with the largest sum. Return the sum.

EXAMPLE

Input: {2, -8, 3, -2, 4, -10}

Output: 5 (i.e., {3, -2, 4} )
*/
	
#include <iostream>
	
using namespace std;

int maxSum(int a[], int n) {
	
	if (a == NULL || n <= 0) return 0;
	//int result;
	int max_sum = INT_MIN;
	int cur_sum = 0;
	for (int i = 0; i < n; i++) {
		if (cur_sum <= 0) cur_sum = a[i];
		else cur_sum += a[i];
		
		if (cur_sum > max_sum)
			max_sum = cur_sum;
	}
	return max_sum;
}

int main() {
	int a[] = { 2, -8, 3, -2, 4, -10, 45, -99};
	cout << maxSum(a, 8) << endl;
}