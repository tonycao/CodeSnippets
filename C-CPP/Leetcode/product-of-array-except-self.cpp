class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);
        
        for (int i = 1; i < nums.size(); i++) {
            res[i] *= nums[i - 1] * res[i - 1];
        }
        
        int rightprod = 1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            rightprod *= nums[i + 1];
            res[i] *= rightprod;
        }
        return res;
    }
};