class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        map<char, bool> row;
        map<char, bool> col;
        map<char, bool> block;

        for(int i = 0; i<9; i++){
            col.clear();
            row.clear();
            for(int j=0; j < 9; j++){
                if(board[i][j]!='.'){
                    if(col[board[i][j]]){
                        return false;
                    }else{
                        col[board[i][j]] = true;
                    }
                }
                if(board[j][i]!='.'){
                    if(row[board[j][i]]){
                        return false;
                    }else{
                        row[board[j][i]] = true;
                    }
                }
            }
        }

        for(int ib = 0; ib < 9; ib+=3){
            for(int jb = 0; jb < 9; jb+=3){
                block.clear();
                for(int i = ib; i<ib+3; i++){
                    for(int j = jb; j < jb+3; j++){
                        if(board[i][j]!='.'){
                            if(block[board[i][j]]){
                                return false;
                            }else{
                                block[board[i][j]] = true;
                            }
                        }
                    }
                }
            }
        }
    }
};
