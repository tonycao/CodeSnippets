class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        // DFS: Time ~ O(N!), Space ~ O(N)
        vector<vector<int>> result;
        vector<int> path;
        dfs(k, n, result, path, 1);
        return result;
    }
    
private:
    void dfs(int k, int n, vector<vector<int>>& result, vector<int>& path, int step) {
        if (k < 0 || n < 0) return;
        if (k == 0 && n == 0) {
            result.push_back(path);
        }
        
        for (int i = step; i <= 9; i++) {
            path.push_back(i);
            dfs(k - 1, n - i, result, path, i + 1);
            path.pop_back();
        }
    }    
};