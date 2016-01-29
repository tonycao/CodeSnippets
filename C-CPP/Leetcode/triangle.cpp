class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        //1-d DP: Time ~ O(N^2), Space ~ O(N) 
        vector<int> sum(triangle.size(), 0);
        for (int i = triangle.size() - 1; i >= 0; i--) {
            for (int j = 0; j <= i ; j++) {
                if (i == triangle.size() - 1) sum[j] = triangle[i][j];
                else sum[j] = min(sum[j], sum[j + 1]) + triangle[i][j];
            }
        }
        return sum[0];
    }
};