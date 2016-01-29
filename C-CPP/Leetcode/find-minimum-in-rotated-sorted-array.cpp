class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        //int res = nums[0];
        while(left < right && nums[left] >= nums[right]) { // if rotated, otherwise directly return left
            int mid = left + (right - left) / 2;
            if (nums[right] < nums[mid]) {
                left = mid + 1;
            } else {
                right = mid;
            }
            //res = min(nums[mid], res);
        }
        
        return nums[left];
    }
};