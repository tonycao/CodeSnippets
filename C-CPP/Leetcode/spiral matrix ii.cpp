class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int>> matrix(n, vector<int>(n,0));
        if( n==0) {return matrix;}
        int lvl = 0, curr = 1;
        while(curr <= n*n){
            for(int i = lvl; i< n-lvl; i++)
                matrix[lvl][i] = curr++;
            for(int i = lvl+1; i < n-lvl; i++)
                matrix[i][n - lvl - 1] = curr++;
            for(int i = n-lvl-2; i>=lvl; i--)
                matrix[n-lvl-1][i] = curr++;
            for(int i = n-lvl-2; i>=lvl+1; i--)
                matrix[i][lvl] = curr++;
            lvl++;
        }
        return matrix;
    }
};
