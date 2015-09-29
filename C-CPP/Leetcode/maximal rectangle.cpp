class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int row = matrix.size();
        if (row == 0) return 0;
        int col = matrix[0].size();
        int res = 0;
        vector<vector<int>> ones(row, vector<int>(col,0));

        for(int i=0; i<row; ++i){
            for (int j = 0; j < col; ++j){
                if(matrix[i][j] == '1'){
                    if(j==0) ones[i][j] = 1;
                    else ones[i][j] = ones[i][j-1]+1;
                }
            }
        }

        for(int i=0; i < row; ++i){
            for(int j=0; j<col; ++j){
                if(ones[i][j]!=0){
                    int h = i-1;
                    int tmp = ones[i][j];
                    int mini = ones[i][j];
                    while(h >= 0){
                        if(ones[h][j] == 0){
                            break;
                        }else{
                            if(ones[h][j]<mini){
                                mini = ones[h][j];
                            }
                            if(tmp<mini*(i-h+1)){
                                tmp = mini*(i-h+1);
                            }
                            h--;
                        }
                    }
                    if(res<tmp){
                        res = tmp;
                    }
                }
            }
        }
        return res;
    }
};
