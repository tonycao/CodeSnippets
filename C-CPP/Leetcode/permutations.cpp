class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int> > res;
        perm(num,0,(num.size()-1),res);
        return res;
    }

    void perm(vector<int> num,int k,int n, vector<vector<int> > &res){
        if (k==n){
            res.push_back(num);
        }else{
            for (int i=k;i<=n;i++){
                int tmp = num[k];
                num[k]=num[i];
                num[i]=tmp;

                perm(num,k+1,n,res);

                tmp = num[k];
                num[k]=num[i];
                num[i]=tmp;
            }
        }
    }
};
