#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //Time ~ O(2N), Space ~ O(1)
        // E.g.: 6 8 7 4 3 2 -> 7 2 3 4 6 8 (partition number: 6, swap with 7)
        // find longest descending tail and reverse it, num[curr - 1] is the partition number
        int curr = nums.size() - 1;
        while(curr > 0 && nums[curr-1] >= nums[curr]) curr--;
        
        reverse(nums, curr, nums.size() - 1);
        // swap num[curr - 1] and the first larger element on its right side
        if (curr > 0) {
            int next = curr; // curr is the violation number
            curr--; 
            while(nums[curr] >= nums[next] && next < nums.size() - 1) next++;
            swap(nums[curr], nums[next]);
        }
    }
    
private: 
    void reverse(vector<int>& nums, int start, int end) {
        while(start < end){
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
    }
};

int main() {
    vector<int> a = {1, 1};
    Solution sol;
    sol.nextPermutation(a);
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
}