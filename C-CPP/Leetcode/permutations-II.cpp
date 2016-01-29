class Solution {
public:
    bool noswap(int l, int k, const vector<int> num){
        for(int i = l; i < k; i++){
            if(num[i] == num[k]) return true;
        }
        return false;
    }
    //Backtracking: Time ~ O(N!), Extra Space ~ O(N) 
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int> > res;
        //sort(num.begin(), num.end());
        perm(num, 0, num.size()-1, res);
        return res;
    }
    
    void perm(vector<int> num, int l, int r, vector<vector<int> >& res) {
        if(l == r) {
            res.push_back(num);
            return;
        }
        
        for ( int i = l; i <= r; i++) {
            // swap i and l;
            //if (i > 0 && num[i-1] == num[i]) continue;
            if(noswap(l, i, num)) continue;
           
            int tmp = num[i];
            num[i] = num[l];
            num[l] = tmp;
            
            perm(num, l+1, r, res);
            
            // swap back
            tmp = num[i];
            num[i] = num[l];
            num[l] = tmp;
            
        }
    }
};