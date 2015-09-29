class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // find the last x where (nums[x] <= target) is false
        // use template from topcoder
        int left = 0, right = nums.size() - 1;
        while(left < right) {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] < target) {
                left = mid;
            } else if (nums[mid] > target){
                right = mid - 1;
            } else {
                return mid;
            }
        }
        return (nums[left] >= target) ? left : left + 1;
    }
};