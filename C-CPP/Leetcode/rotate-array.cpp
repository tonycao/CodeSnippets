class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n; // when k > n
        //if (n == 0 || k == 0) return ;
        reverse(nums, 0, n-1);
        reverse(nums, 0, k-1);
        reverse(nums, k, n-1);
    }
    
    void reverse(vector<int> &nums, int start, int end) {
        /*
        int n = end - start;
        for (int i = 0; i < n / 2; i++) {
            int lhs = start + i;
            int rhs = start + n - 1 - i;
            int tmp = nums[lhs];
            nums[lhs] = nums[rhs];
            nums[rhs] = tmp;
            
        }*/
        while (start < end) {
            int tmp = nums[start];
            nums[start] = nums[end];
            nums[end] = tmp;
            start++;
            end--;
        }
    }
};