#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;


class TrieNode {
public:
    // Initialize your data structure here.
    static const int C_NUM = 26;
    TrieNode *next[C_NUM];
    bool leave;
    TrieNode() {
        leave = false;
        memset(next, 0, sizeof(next));
    }
};

class Trie {
public:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string s) {
        TrieNode *cur = root;
        int index = 0;
        for(int i = 0; i < s.size(); i++) {
        //while(s.length() > index) {
            int chr = s[i] - 'a';
            if (cur->next[chr] == NULL) {
                cur->next[chr] = new TrieNode();
            }
            //index++;
            cur = cur->next[chr];
        }
        cur->leave = true;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        vector<string> res;
        if (board.size() == 0 || board[0].size() == 0 || words.size() == 0) return res;
        
        int m = board.size();
        int n = board[0].size();
        int wordcount = words.size();
        //cout << wordcount << endl;
        
        Trie *trie = new Trie();
        for (int i = 0; i < wordcount; i++) {
            trie->insert(words[i]);
        }
        
        vector<vector<bool> > visit(m, vector<bool>(n, false));
        
        string s = "";
        for (int i = 0; i < m; i++) {
            //cout << res.size() << endl;
            for (int j = 0; j< n && wordcount > res.size(); j++) {

                DFS(trie->root, i, j, board, visit, res, s);
            }
        }
        return res;
    }
    
    void DFS(TrieNode* root, int i, int j, vector<vector<char> >& board, vector<vector<bool> > &visit, vector<string> &res, string &s) {
        //if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return;
        //cout << i << " " << j << " " << visit[i][j] << " " << root->next[board[i][j] - 'a'] << endl;
        if (!visit[i][j] && NULL != root->next[board[i][j] - 'a']) {
            //cout << 1 << endl;
            visit[i][j] = true;
            s.push_back(board[i][j]);
            //cout << s << endl;
            if (root->next[board[i][j] - 'a']->leave ) {
                cout << s << endl;
                res.push_back(s);
                root->next[board[i][j] - 'a']->leave = false;
            }
            
            DFS(root->next[board[i][j] - 'a'], i + 1, j, board, visit, res, s);
            DFS(root->next[board[i][j] - 'a'], i - 1, j, board, visit, res, s);
            DFS(root->next[board[i][j] - 'a'], i, j + 1, board, visit, res, s);
            DFS(root->next[board[i][j] - 'a'], i, j - 1, board, visit, res, s);
            
            s.pop_back();
            visit[i][j] == false;
        }
    }
};

int main() {
    Solution sol;
    vector<vector<char> > board(1, vector<char>(1, 'a'));
    vector<string> words(1, "a");
    //cout << board.size() << board[0].size() << words.size() << endl;
    vector<string> res = sol.findWords(board, words);
    //cout << res.size() << endl;
    return 0;
}