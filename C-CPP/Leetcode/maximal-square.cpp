class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        //2-d DP: Time ~ O(MN), Space ~ O(MN) 
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        if (n == 0) return 0;
        
        int maxA = 0;
        vector<vector<int>> area(m, vector<int>(n, 0)); // length of square ending at area[i][j]
        for (int i = 0; i < m; i++) {
            area[i][0] = matrix[i][0] == '1';
            maxA = max(maxA, area[i][0]);
            for (int j = 1; j < n; j++) {
                if (i == 0) {
                    area[i][j] = matrix[i][j] == '1' ? 1 : 0;
                } else {
                    area[i][j] = matrix[i][j] == '1' ? min(area[i - 1][j], min(area[i - 1][j - 1], area[i][j - 1]))+1 : 0;
                }
                maxA = max(maxA, area[i][j]);
            }
        }
        
        return maxA*maxA;
    }
};