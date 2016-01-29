class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int prev = 0;
        
        for (int i = 1; i <= nums.size(); i++) {
            // i == nums.size() should before the other condition
            if ( i == nums.size() || nums[i - 1] + 1 !=  nums[i] ) { 
                if (prev == i - 1) {
                    res.push_back(to_string(nums[prev]));
                } else {
                    res.push_back(to_string(nums[prev]) + "->" + to_string(nums[i - 1]));
                }
                prev = i;
            }  
        }


        return res;
    }
};