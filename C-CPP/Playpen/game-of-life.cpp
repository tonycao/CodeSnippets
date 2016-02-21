#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        

        // States:
        //  0 : dead to dead
        //  1 : live to live
        //  2 : live to dead
        //  3 : dead to live
        
        int m = board.size(), n = m ? board[0].size() : 0;

        int shifty[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int shiftx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        //vector<vector<int>> tmpboard(board.size(), vector<int>(board[0].size()));
        
        for (int i = 0; i< m; i++) {
            for (int j = 0; j < n; j++) {
                //int cur = board[i][j];
                int count = 0;
                for (int k = 0; k < 8; k++) {
                    int ii = i + shiftx[k], jj = j + shifty[k];
                    if (ii < 0 || ii >= m || jj < 0 || jj >= n)  continue;
                    cout << count << endl;
                    cout << ii << " " << jj << endl;
                    count += board[ii][jj] & 1;

                }
                if (count == 3 || (count + board[i][j] == 3))
                    board[i][j] |= 2;
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] >>= 1;
            }
        }
        
    }
};

int main() {
    Solution sol;
    vector<vector<int>> A = {{0}};
    sol.gameOfLife(A);

    return 0;
}