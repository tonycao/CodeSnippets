class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        // time~O(MN), space~O(M+N)
        set<int> rowset;
        set<int> colset;
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j <  n; j++) {
                if (matrix[i][j] == 0) {
                    rowset.insert(i);
                    colset.insert(j);
                }
            }
        }
        
        for (auto it = rowset.begin(); it != rowset.end(); it++) {
            fill(&matrix[*it][0], &matrix[*it][0] + n, 0 );
            //for (int i = 0; i < matrix[0].size(); i++) {
            //    matrix[*it][i] = 0;
            //}
        }
        
        for (auto it = colset.begin(); it != colset.end(); it++) {
            for (int i = 0; i < m; i++) {
                matrix[i][*it] = 0;
            }
        }
    }
};