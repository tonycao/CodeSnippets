class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        /*
        Time ~ O(N^2), Space ~ O(1) 
        Rotate 90 clockwise: A -> B -> C -> D -> A
                         [i, j]
                     —  A  ————
                    |           |
                    |           B [j, n - 1 - i]
                    |           |
                    |           |
[n - j - 1, i]   D              |
                    | ———— C —  |
                       [n - i - 1, n - 1 - j]
        */
        int n = matrix.size();
        for (int i = 0; i < n / 2; i++) {
            for (int j = i; j < n - i - 1; j++) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = tmp;
            }
        }
    }
};