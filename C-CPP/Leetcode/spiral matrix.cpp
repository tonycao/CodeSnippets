class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
                vector<int> res;
        if (matrix.empty()){return res;}
        if (matrix.size()==1){return matrix[0];}
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<bool> > mask(m,vector<bool>(n,false));
        int i=0;
        int j=0;
        int k=0;
        res.push_back(matrix[i][j]);
        mask[0][0]=true;
        while (k<m*n-1){
            while ((j+1<n)&&(mask[i][j+1]==false)){
                j++;
                k++;
                res.push_back(matrix[i][j]);
                mask[i][j]=true;
            }

            while ((i+1<m)&&(mask[i+1][j]==false)){
                i++;
                k++;
                res.push_back(matrix[i][j]);
                mask[i][j]=true;
            }

            while ((j>0)&&(mask[i][j-1]==false)){
                j--;
                k++;
                res.push_back(matrix[i][j]);
                mask[i][j]=true;
            }

            while ((i>0)&&(mask[i-1][j]==false)){
                i--;
                k++;
                res.push_back(matrix[i][j]);
                mask[i][j]=true;
            }
        }
        return res;
    }
};
