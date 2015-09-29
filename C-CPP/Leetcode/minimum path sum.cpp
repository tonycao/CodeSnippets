class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> allsum(m, vector<int>(n,0));
        allsum[0][0] = grid[0][0];
        for (int i = 1; i < n; ++i) allsum[0][i] = allsum[0][i-1] + grid[0][i];
        for (int i = 1; i < m; ++i) allsum[i][0] = allsum[i-1][0] + grid[i][0];
        for (int i = 1; i < m; ++i){
            for (int j = 1; j < n; ++j)
            {
                allsum[i][j] = min(allsum[i][j-1]+grid[i][j], allsum[i-1][j]+grid[i][j]);
            }
        }
        return allsum[m-1][n-1];
    }
};
