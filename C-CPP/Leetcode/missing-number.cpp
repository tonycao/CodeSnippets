class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // method 1
        /*long sum = 0;
        int n = nums.size();
        //for (int i = 0;  i < n; i++) {
        //    sum += nums[i];
        //}
        sum = accumulate(nums.begin(), nums.end(), 0);
        return (0 + n) * (n + 1) / 2 - sum; 
        */
        // method 2
        /*
        int i = 0, res = nums.size();
        for (auto num : nums) {
            res ^= num;
            res ^= i;
            i++;
        }
        return res;
        */
        // method 3
        // O(NlogN)
        sort(nums.begin(), nums.end());
        int left = 0, right = nums.size();
        while(left < right) {
            int mid = left + (right - left) / 2;
            if (mid >= nums[mid]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};