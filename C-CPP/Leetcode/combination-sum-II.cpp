class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        //Time ~ O(N!), Space ~ O(N)
        vector<vector<int>> result;
        if (candidates.empty()) return result;
        sort(candidates.begin(), candidates.end());
        
        vector<int> path;
        dfs(candidates, target, 0, path, result);
        return result;
    }
    
private:
    void dfs(vector<int>& candidates, int target, int step, vector<int>& path, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(path);
            return ;
        }
        for (int i = step; i < candidates.size(); i++) {
            if (i > step && candidates[i] == candidates[i-1]) continue;
            if (target >= candidates[i]) {
                path.push_back(candidates[i]);
                dfs(candidates, target-candidates[i], i + 1, path, result);
                path.pop_back();
            }
        }
    }    
};