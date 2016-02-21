#include <iostream>
using namespace std;

class TrieNode {
public:
    static const int C_NUM = 26;
    TrieNode *next[C_NUM];
    bool leave;
    TrieNode() {
        leave = false;
        for (int i = 0; i < C_NUM; i++) {
            next[i] = NULL;
        }
    }
};

class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode();
    }
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode *cur = root;
        int index = 0;
        while(word.length() > index) {
            int chr = word[index] - 'a';
            if (cur->next[chr] == NULL) 
                cur->next[chr] = new TrieNode();
            index++;
            cur = cur->next[chr];
        }
        cur->leave = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        // dfs
        return search(word, root);
    }
    
    bool search(string word, TrieNode* root) {
        if(word.empty()) return root->leave;
        int chr = word[0] - 'a';
        
        if (word[0] == '.') {
            for (int i = 0; i < 26; i++) {
                if (root->next[i] == NULL) continue;
                if (word.size() == 1) return root->next[i]->leave;
                if (search(word.substr(1), root->next[i])) return true;
            }
            return false;
        } else if (root->next[chr]) {
            if (word.size() > 1)
                return search(word.substr(1), root->next[chr]);
            else 
                return root->next[chr]->leave;
        }
        return false;
    }
private:
    TrieNode *root;
};


int main() {

    WordDictionary wordDictionary;
    wordDictionary.addWord("word");
    cout << wordDictionary.search("pattern") << endl;
    return 0;

}
// Your WordDictionary object will be instantiated and called as such:
