class Solution {
public:
    vector<vector<int> > res;

    void dfs(vector<int> &cand, int st, int ed, vector<int> &lr){
        if (lr.size()==ed){
            res.push_back(lr);
            return;
        }
        for (int i = st; i< cand.size();i++){
                lr.push_back(cand[i]);
                dfs(cand,i+1,ed,lr);
                lr.pop_back();
        }
    }

    vector<vector<int> > combine(int n, int k) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        res.clear();

        if ((k<1)||(n<1)||(k>n)){return res;}
        vector <int> cand;
        for (int i = 1; i<=n;i++){
            cand.push_back(i);
        }
        vector<int> lr;
        dfs(cand,0,k,lr);
        return res;
    }

};
