class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxsum = nums[0], cursum = nums[0]; 
        for (int i = 1; i < nums.size(); i++) {
            cursum += nums[i];
            cursum = max(cursum, nums[i]);
            maxsum = max(maxsum, cursum);
        }
        return maxsum;
    }
};