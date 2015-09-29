class Solution {
public:
    vector<vector<string> > res;

    void printres(vector<int> A,int n){
        vector<string> r;
        for(int i=0;i<n;i++){
            string str(n,'.');
            str[A[i]]='Q';
            r.push_back(str);
        }
        res.push_back(r);
    }


    bool isValid(vector<int> A, int r){
        for (int i=0;i<r;i++){
            if ( (A[i]==A[r])||(abs(A[i]-A[r])==(r-i))){
                return false;
            }
        }
        return true;
    }

    void nqueens(vector<int> A, int cur, int n){
        if (cur==n){printres(A,n);}
        else{
            for (int i=0;i<n;i++){
                A[cur]=i;
                if (isValid(A,cur)){
                    nqueens(A,cur+1,n);
                }
            }
        }
    }
    vector<vector<string> > solveNQueens(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        res.clear();
        vector<int> A(n,-1);
        nqueens(A,0,n);
        return res;
    }
};
