/*
Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm 
that finds an element in the array. You may assume that the array was originally sorted in increasing order.

EXAMPLE:

Input: find 5 in array (15 16 19 20 25 1 3 4 5 7 10 14)

Output: 8 (the index of 5 in the array)
*/

#include <iostream>

using namespace std;

int search(int a[], int n, int key) {

	int low = 0, high = n - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (a[mid] == key) return mid;
		if (a[mid] >= a[low]) {
			if (key < a[mid] && key >= a[low])
				high = mid - 1;
			else
				low = mid + 1;
		} else {
			if (key > a[mid] && key < a[low])
				low = mid + 1;
			else 
				high = mid - 1;
		}
	}
	return -1;

}

int main() {
	int a[10] = { 11, 24, 42, 19, 22, 10, 89, 39, 32, 73};
	cout << search(a, 10, 11) << endl;
	cout << search(a, 10, 10) << endl;
	cout << search(a, 10, 14) << endl;
	return 0;
}