class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        // find leftmost
        while(left < right) {
            int mid = left + (right - left ) / 2;
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        int start = left;
        if (nums[left] != target) return {-1,-1}; // no match is found
        
        // find rightmost
        right = nums.size() - 1;
        while(left < right) {
            int mid = left + ( right - left + 1) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }
        int end = left;
        if (nums[left] != target) end = left - 1; // if no match on left, need move backward one step
        
        return {start, end};
    }
};