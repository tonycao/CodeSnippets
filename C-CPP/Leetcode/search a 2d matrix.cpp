class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int row = matrix.size();
        if (row == 0) return false;
        int col = matrix[0].size();
        if (col == 0) return false;
        int tol = row*col;

        int start = 0, end = row*col-1;

        while(start <= end){
            int mid = (start+end)/2;
            int r = mid/col;
            int c = mid%col;

            if (matrix[r][c] == target) return true;
            if (matrix[r][c] < target) start = mid + 1;
            else end = mid - 1;
        }
        return false;
    }
};


// dichotomy search

// algorithm 1: two dichotomy search, one in row and one in colomn
// algorithm 2: one dichotomy search
