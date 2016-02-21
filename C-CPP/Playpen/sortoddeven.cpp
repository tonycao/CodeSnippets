#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct cmp {
	bool operator()(int a, int b) {
		if (a % 2 == b % 2) {
		 	return a < b;
		} else if (a % 2 == 0 && b % 2 == 1){
			return true;
		} else {
			return false;
		}
	}
};

void sortoddeven(vector<int> &nums) {
	if (nums.empty()) return ;
	int low = 0, high = nums.size() - 1;
	while(low < high) {
		if (nums[low] % 2 == 0) {
			low += 1;
		} else if (nums[high] % 2 == 1) {
			high -= 1;
		} else {
			int tmp = nums[low];
			nums[low] = nums[high];
			nums[high] = tmp;
		}
	}

	//return nums;
}


int main() {
	vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
	//sort(a.begin(), a.end());
	sort(a.begin(), a.end(), cmp());
	//sortoddeven(a);
	for (auto iter : a) {
		cout << iter << " ";
	}
	cout << endl;
}