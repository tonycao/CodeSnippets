class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // 2 cases to swap:
        // A[i] is within [1..N]
        // A[i] and A[A[i] - 1] are different (equal will result in dead loop)
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != nums[nums[i]-1]) {
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        
        // find nums[i] in wrong position
        int i = 0;
        for (; i < nums.size(); i++) {
            if (nums[i] != i + 1) break;
        }
        return i + 1;
    }
};