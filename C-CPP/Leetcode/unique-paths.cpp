class Solution {
public:
    int uniquePaths(int m, int n) {
        // 1d DP: time ~ O(mn), space~O(n)
        vector<int> path(n, 1);
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                path[j] = path[j - 1] + path[j];
            }
        }
        return path[n - 1];
    }
};