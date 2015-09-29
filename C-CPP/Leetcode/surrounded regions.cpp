class Solution {
public:
    void solve(vector<vector<char>> &board) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int m = board.size();
        if (m==0){return;}
        int n = board[0].size();
        vector<int> sti;
        vector<int> stj;
        for(int i=0;i<m;i++){
            if (board[i][0]=='O'){
                sti.push_back(i);
                stj.push_back(0);
            }
            if (board[i][n-1]=='O'){
                sti.push_back(i);
                stj.push_back(n-1);

            }
        }
        for(int j=0;j<n;j++){
            if (board[0][j]=='O'){
                sti.push_back(0);
                stj.push_back(j);
            }
            if (board[m-1][j]=='O'){
                sti.push_back(m-1);
                stj.push_back(j);

            }
        }

        int i=0;
        while (i<sti.size()){
            int x= sti[i];
            int y= stj[i];
            board[x][y]='P';

            if (x-1>=0 && board[x-1][y]=='O'){
                sti.push_back(x-1);
                stj.push_back(y);
            }
            if (x+1<m && board[x+1][y]=='O'){
                sti.push_back(x+1);
                stj.push_back(y);
            }
            if (y-1>=0 && board[x][y-1]=='O'){
                sti.push_back(x);
                stj.push_back(y-1);
            }
            if (y+1<n && board[x][y+1]=='O'){
                sti.push_back(x);
                stj.push_back(y+1);
            }
            i++;
        }


        for(int i=0; i<m; i++){
            for(int j=0;j<n;j++){
                if (board[i][j]=='O'){
                    board[i][j]='X';
                }
                if (board[i][j]=='P'){
                    board[i][j]='O';
                }
            }
        }
    }
};
