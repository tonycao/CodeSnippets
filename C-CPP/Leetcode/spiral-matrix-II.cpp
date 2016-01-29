class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        int begin = 0, end = n - 1;
        int count = 1;
        while(begin < end) {
            for (int j = begin; j < end; j++) matrix[begin][j] = count++;
            for (int i = begin; i < end; i++) matrix[i][end] = count++;
            for (int j = end; j > begin; j--) matrix[end][j] = count++;
            for (int i = end; i > begin; i--) matrix[i][begin] = count++;
            begin++;
            end--;
        }
        if (begin == end) matrix[begin][end] = count;
        return matrix;
    }
};