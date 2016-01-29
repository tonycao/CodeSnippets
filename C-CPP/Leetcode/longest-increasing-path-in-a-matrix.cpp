#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.size() == 0) {
            return 0;
        }
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
        int res = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                res = max(res, dfs(i, j, matrix, dp));
                //cout << res << endl;
            }
        }
        return res;
    }
    
private:
    vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int dfs(int i, int j, vector<vector<int>> matrix, vector<vector<int>> &dp) {
        if (dp[i][j] > 0) return dp[i][j]; // if current location has visited
        int maxstep = 0;
        for (int m = 0; m < dir.size(); ++m) {
            if (i + dir[m][0] >= 0 && i + dir[m][0] < matrix.size() && 
                j + dir[m][1] >= 0 && j + dir[m][1] < matrix[0].size() &&
                matrix[i][j] < matrix[i + dir[m][0]][j + dir[m][1]]) {
                maxstep = max(maxstep, dfs(i + dir[m][0], j + dir[m][1], matrix, dp));
                //cout << maxstep << endl;
            }
        }
        dp[i][j] = 1 + maxstep;
        return dp[i][j];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{9,9,4}, {6,6,8}, {2,1,1}};
    cout << sol.longestIncreasingPath(matrix) << endl;
}