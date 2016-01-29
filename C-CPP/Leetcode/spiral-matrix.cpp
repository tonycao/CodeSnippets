class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        //Time ~ O(MN), Space ~ O(1) 
        vector<int> result;
        if (matrix.empty()) return result;
        
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = -1;
        while(true) {
            // top row
            for (int k = 0; k < n; k++) {
                result.push_back(matrix[i][++j]);
            }
            if (--m == 0) break;
            // right col
            for (int k = 0; k < m; k++) {
                result.push_back(matrix[++i][j]);
            }
            if (--n == 0) break;
            // bottom row
            for (int k = 0; k < n; k++) {
                result.push_back(matrix[i][--j]);
            }
            if (--m == 0) break;
            // left col
            for (int k = 0; k < m; k++) {
                result.push_back(matrix[--i][j]);
            }
            if (--n == 0) break;
        }
        return result;
    }
};