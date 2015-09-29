class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int>> res;
        if(numRows == 0) return res;
        vector<int> r;
        r.push_back(1);
        res.push_back(r);
        if(numRows == 1) return res;
        r.push_back(1);
        res.push_back(r);
        if(numRows == 2) return res;

        for(int i = 2; i<numRows; i++){
            vector<int> c(i+1,1);
            for(int j=1; j<i; j++){
                c[j] = res[i-1][j] + res[i-1][j-1];
            }
            res.push_back(c);
        }
        return res;
    }
};
