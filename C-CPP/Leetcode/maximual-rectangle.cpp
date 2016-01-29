class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        // Two pointers: Time ~ O(MN)
        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        
        
        
        vector<int> hist(n, 0);
        vector<int> leftInd(n, 0);
        vector<int> rightInd(n, n);
        
        int maxRect = 0;
        for (int i = 0; i < m; i++) {
            int left = 0, right = n;
            
            
            for (int j = 0; j < n; j++) {
                // calculate leftind in row i
                if (matrix[i][j] == '1'){
                    hist[j]++;
                    leftInd[j] = max(leftInd[j], left); // compare with previous row
                } else {
                    hist[j] = 0;
                    left = j + 1;
                    // edge case: when '0' appears, make L[j] = left and R[j] = right in next row
                    leftInd[j] = 0;
                    rightInd[j] = n;
                }
            }
            
            // calculate rightind
            for (int j = n - 1; j >= 0; j--) {
                                
                if (matrix[i][j] == '1') {
                    rightInd[j] = min(rightInd[j], right);  // compare with previous row
                    maxRect = max(maxRect, hist[j] * (rightInd[j] - leftInd[j]));
                } else {
                    right = j;
                }
            }
            
        }
        
        return maxRect;
        
        
    }
};