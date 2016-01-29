class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        //DFS: Time ~ O(N!), Space ~ O(N)
        vector<vector<int>> res;
        if (nums.empty()) return res;
        sort(nums.begin(), nums.end());
        vector<int> sub;
        dfs(nums, sub, 0, res);
        return res;
    }
    
private:
    void dfs(vector<int>& nums, vector<int>& sub, int step, vector<vector<int>>& res) {
        res.push_back(sub);
        for (int i = step; i < nums.size(); i++) {
            sub.push_back(nums[i]);
            dfs(nums, sub, i + 1, res);
            sub.pop_back();
        }
    }    
};