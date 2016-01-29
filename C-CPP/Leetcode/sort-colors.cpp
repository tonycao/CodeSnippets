class Solution {
public:
    void sortColors(vector<int>& nums) {
        //if (nums.size() <= 1) return;
        int left = 0, right = nums.size() - 1;
        int i = 0;
        while(i < right + 1) {
            if (nums[i] == 0) {
                swap(nums, i, left);
                left++;
                i++;
            }
            else if (nums[i] == 2) {
                swap(nums, i, right);
                right--;
            }
            else i++;
        }
        
    }
    
    
private:
    void swap(vector<int>& nums, int a, int b){
        int tmp = nums[a];
        nums[a] = nums[b];
        nums[b] = tmp;
    }
};