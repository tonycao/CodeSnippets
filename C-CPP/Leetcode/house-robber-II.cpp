class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) return nums.empty()? 0 : nums[0];
        if (len == 2) return max(nums[0], nums[1]);
        vector<int> res1(len), res2(len);
        
        res1[0] = nums[0];
        res1[1] = max(nums[0], nums[1]);
        res2[0] = 0;
        res2[1] = nums[1];
        
        for (int i = 2; i < len; i++) {
            res1[i] = max(nums[i] + res1[i - 2], res1[i - 1]);
            res2[i] = max(nums[i] + res2[i - 2], res2[i - 1]);
        }
        
        //res1[len - 1] = res1[len - 2];
        //res2[len - 1] = max(res2[i - 2], res[i - 3] + nums[len - 1]);
        
        return max(res1[len - 2], res2[len - 1]); // for res1 cannot use the last two, res2 can use the last one
        
    }
};