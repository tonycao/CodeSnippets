class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // 1-d DP（滚动数组）: Time ~ O(M*N), Space ~ O(min{M, N}) 
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        //vector<vector<int>> steps(m, vector<int>(n,0));
        vector<int> steps(n, 0);
        steps[0] = obstacleGrid[0][0] ? 0 : 1;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                steps[j] = obstacleGrid[i][j] ? 0 : ((j > 0) ? (steps[j - 1]) : 0) + steps[j];
            }
        }
        return steps[n - 1];
    }
};