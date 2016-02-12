#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include <map>
using namespace std;

int randMax(vector<int> &nums) {
	int maxval = nums[0];
	
	int maxCount = 1, maxind = 0;
	for (int i = 1; i < nums.size(); ++i) {
		if (maxval == nums[i]) {
			maxCount++;
			int tmpind = rand() % (maxCount);
			//cout << tmpind << " "; 
			if (tmpind < 1) {
				maxind = i;
			}
		} 
			if (maxval < nums[i]) {
				maxval = nums[i];
				maxCount = 1;
				maxind = i;
			}
		
	}
	//cout << endl;
	return maxind;
}

int main() {
	srand(time(NULL));
	vector<int> nums = {1,2,3,7,5,3,4,2,3,5,7,1,2,7,7,5,6,7,2,1,0,7};
	map<int, int> fmap;
	for (int i = 0; i < 1000000; ++i) {
		fmap[randMax(nums)]++;
		//cout << randMax(nums) << endl;
	}

	for (auto it : fmap) {
		cout << it.first <<":" << it.second << endl;
	}
}