class Solution {
public:
    string getPermutation(int n, int k) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> nums(n);
        int permCount = 1;
        for (int i = 0; i < n ; ++i)
        {
            nums[i] = i+1;
            permCount *= (i+1);
        }

        k--;
        string targetNum;
        for (int i = 0; i < n; ++i)
        {
            permCount = permCount / (n-i);
            int choosed = k / permCount;
            targetNum.push_back(nums[choosed] + '0');
            for(int j = choosed; j < n-i; ++j){
                nums[j] = nums[j+1];
            }
            k = k%permCount;

        }
        return targetNum;
    }
};
