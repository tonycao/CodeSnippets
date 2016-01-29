class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        // time~O(MN), space~O(N)
        int m = grid.size();
        int n = grid[0].size();
        int minval = min(m, n), maxval = max(m, n);
        vector<int> tmpsum(minval, INT_MAX);
        int val;
        for (int i = 0; i < maxval; i++) {
            for (int j = 0; j < minval; j++) {
                if (n == minval) val = grid[i][j];
                else             val = grid[j][i]; // rotate matrix
        
                if (i == 0 && j == 0) tmpsum[j] = val;
                else tmpsum[j] = min((i > 0) ? tmpsum[j] : INT_MAX, 
                                     (j > 0) ? tmpsum[j - 1] : INT_MAX) + val;
            }
        }
        return tmpsum[minval - 1];
    }
};