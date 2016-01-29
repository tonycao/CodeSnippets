class Solution {
public:
    bool search(vector<int>& nums, int target) {
        //Binary Search: Time ~ O(logN) worst case ~ O(N), Space ~ O(1) 
        int left = 0, right = nums.size() - 1;
        while(left < right) {
            int mid = left + (right - left ) / 2;
            if (nums[mid] == target) return true;
            else if (nums[mid] > nums[right]) {
                if (nums[left] <= target && nums[mid] > target) right = mid;
                else left = mid + 1;
            } else if (nums[mid] < nums[right]){
                if (nums[mid] < target && nums[right] >= target) left = mid + 1;
                else right = mid;
            } else {  // for nums[mid] == nums[right]
                //left++;
                right--;  // for duplicated cases
            }
        }
        return (nums[left] == target) ? true : false;
    }
};