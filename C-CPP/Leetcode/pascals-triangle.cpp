class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        //Time ~ O(k), Space ~ O(k^2 = 1+2+...+k) 
        vector<vector<int> > res;
        for (int i = 0; i < numRows; i++) {
            vector<int> ilevel;
            
            for(int j = 0; j <= i; j++) {
                if (i == 0 || j == i) ilevel.push_back(1);
                else ilevel.push_back(res[i-1][j] + res[i-1][j-1]);
            }

            res.push_back(ilevel);
        }
        return res;
    }
};