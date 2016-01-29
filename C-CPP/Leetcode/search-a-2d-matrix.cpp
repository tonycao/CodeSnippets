class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // method 1: time~ O(log(m + n))
        /*int m = matrix.size();
        int n = matrix[0].size();
        int left = 0, right = m * n - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            int row = mid / n;
            int col = mid % n;
            if (matrix[row][col] == target) return true;
            else if (matrix[row][col] < target) left = mid + 1;
            else right = mid - 1;
        }
        return false;
        */
        // method 2 : time ~ O(log(m) + log(m))
        int n = matrix.size() - 1, m = matrix[0].size() - 1;
        int l = 0, r = n;
        // Let's find a row where may be our target
        while (l < r){
            int mid = l + (r - l) / 2;
            if (matrix[mid][m] == target) return true;
            if (matrix[mid][m] > target) r = mid; else l = mid + 1;
        }
        int row = r;            
        l = 0, r = m;
        while (l <= r){
            int mid = l + (r - l) / 2;
            if (matrix[row][mid] == target) return true;
            if (matrix[row][mid] > target) r = mid - 1; else l = mid + 1;
        }
        return false;
    }
};