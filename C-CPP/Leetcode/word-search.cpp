#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        // DFS: Time ~ O(M^2*N^2), Space ~ O(M*N)
        // Time: DFS ~ O(MN = number of edges), loop ~ O(MN)
        int m = board.size();
        int n = board[0].size();
        
        vector<vector<bool> > visited(m , vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, 0, i, j, visited)) return true;
            }
        }
        return false;
    }
    
    bool dfs(const vector<vector<char> > &board, const string &word, int index, int x, int y, vector<vector<bool> > &visited) {
        if (index == word.size()) return true;
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size()) 
            return false;
        if (visited[x][y]) return false;
        if (board[x][y] != word[index]) return false;
        
        visited[x][y] = true;
        bool ret = dfs(board, word, index + 1, x - 1, y, visited) ||
                   dfs(board, word, index + 1, x + 1, y, visited) ||
                   dfs(board, word, index + 1, x, y - 1, visited) ||
                   dfs(board, word, index + 1, x, y + 1, visited);
        visited[x][y] = false;
        return ret;
        
    }
};

int main() {
    vector<vector<char>> board = {{'a', 'b', 'c','d'}};
    string word = "ab";

    Solution sol;
    cout << sol.exist(board, word) <<endl;
}