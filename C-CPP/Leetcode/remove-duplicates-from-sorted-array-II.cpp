class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();
        int pos = 1;
        
        /*/ method 1

        for (int i = 2; i < nums.size(); i++) {
            if (nums[i] != nums[pos - 1]) 
                nums[++pos] = nums[i];
        }
        */
        
        // method 2
        pos = 0;
        int dup = 0;
        for(int i = 1; i < nums.size(); i++) {
            if (nums[pos] == nums[i]) {
                if (dup == 0) nums[++pos] = nums[i];
                dup++;
            } else {
                nums[++pos] = nums[i];
                dup = 0;
            }
        }
        
        return pos + 1;
    }
};