class Solution {
public:
    // Time: O(N^2) deleteCharAt() takes linear time, Space: O(N)
    string getPermutation(int n, int k) {
        string nums(n, '0');
        int factorial = 1;
        for (int i = 0; i < n; i++) {
            nums[i] += i + 1;
            factorial *= (i + 1);
        }
        
        k--;
        string targetNum;
        for (int i = 0; i < n; i++) {
            factorial = factorial / (n - i);
            int choosed = k / factorial;
            targetNum.push_back(nums[choosed]);
            nums.erase(choosed, 1); // remove chosen digit
            k = k % factorial;
        }
        return targetNum;
    }
};