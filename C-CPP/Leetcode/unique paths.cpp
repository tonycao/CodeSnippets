class Solution {
public:
    int uniquePaths(int m, int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> maxV(n,0);
        maxV[0] = 1;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                maxV[j] = maxV[j-1] + maxV[j];
            }
        }
        return maxV[n-1];
    }
};
