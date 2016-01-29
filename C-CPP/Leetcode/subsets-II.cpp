class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
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
            if (i > step && nums[i - 1] == nums[i]) continue; // skip duplicate
            sub.push_back(nums[i]);
            dfs(nums, sub, i + 1, res); // do not confuse i with step here
            sub.pop_back();
        }
    }  
};


// iterative
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        sort(S.begin(), S.end());
        vector<vector<int>> res;
        vector<int> r;
        res.push_back(r);
        r.push_back(S[0]);
        res.push_back(r);
        int pre = S[0];
        int count = 1;
        for(int i=1; i<S.size(); i++){
            int st = 0;
            int sz = res.size();
            if(S[i]==pre){st = sz-count;}
            count = 0;
            for(int j = st; j< sz; j++){
                r = res[j];
                r.push_back(S[i]);
                res.push_back(r);
                count++;
            }
            pre = S[i];
        }
        return res;
    }
};

