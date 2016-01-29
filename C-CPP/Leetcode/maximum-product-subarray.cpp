class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxprod = 1, maxval = INT_MIN, minprod = 1; // minval = INT_MAX;
        // keep both maxprod and minprod
        for (int i = 0; i < nums.size(); i++) {
            int tmp = maxprod;
            maxprod = max(max(maxprod * nums[i], nums[i]), minprod * nums[i]);
            minprod = min(min(minprod * nums[i], nums[i]), tmp * nums[i]);
            maxval = max(maxprod, maxval);
            //min = min(minprod, min);
        }
        return maxval;
    }
};