class TrieNode {
public:
    static const int C_NUM = 26;
    TrieNode *children[C_NUM];
    bool leave;
    TrieNode() {
        leave = false;
        fill_n(children, C_NUM, nullptr);
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string s) {
        TrieNode* cur = root;
        int index = 0;
        for (int i = 0; i < s.size(); i++) {
            int chr = s[i] - 'a';
            if (cur->children[chr] == nullptr) {
                cur->children[chr] = new TrieNode();
            }
            cur = cur->children[chr];
        }
        cur->leave = true;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        if (board.size() == 0 ||board[0].size() == 0 || words.size() == 0) return res;
        
        int m = board.size();
        int n = board[0].size();
        int wordcount = words.size();
        
        Trie *trie = new Trie();
        
        for (int i = 0; i < words.size(); i++) {
            trie->insert(words[i]);
        }
        
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        
        string s = "";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n && wordcount > res.size(); j++) {
                DFS(trie->root, i, j, board, visit, res, s);
            }
        }
        
        return res;
    }
    
    void DFS(TrieNode* root, int i, int j, vector<vector<char>> &board, vector<vector<bool>> &visit, vector<string> &res, string &s) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return;
        
        if (!visit[i][j] && (root->children[board[i][j] - 'a'] != nullptr)) {
            visit[i][j] = true;
            s.push_back(board[i][j]);
            
            if (root->children[board[i][j] - 'a']->leave) {
                res.push_back(s);
                root->children[board[i][j] - 'a']->leave = false; // find this word
            }
            
            DFS(root->children[board[i][j] - 'a'], i + 1, j, board, visit, res, s);
            DFS(root->children[board[i][j] - 'a'], i - 1, j, board, visit, res, s);
            DFS(root->children[board[i][j] - 'a'], i, j + 1, board, visit, res, s);
            DFS(root->children[board[i][j] - 'a'], i, j - 1, board, visit, res, s);
            
            s.pop_back();
            visit[i][j] = false;
        }
    }
};