class Solution {
public:
    int climbStairs(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> d(n+1, 0);
        d[1] = 1;
        d[2] = 2;
        for (int i = 3; i <=n; ++i)
        {
            d[i] = d[i-1] + d[i-2];
        }
        return d[n];
    }
};
