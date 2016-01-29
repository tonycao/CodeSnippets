class TrieNode {
public:
    TrieNode* next[26];
    bool leave;

    TrieNode() {
        //for (int i = 0; i < 26; i++) {
        //    next[i] == nullptr;
        //}
        fill(next, next+26, nullptr);
        leave = false;
    }
};

class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode();
    }
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode* p = root;
        
        for (int i = 0; i < word.size(); i++) {
            int chr = word[i] - 'a';
            if (p->next[chr] == NULL) {
                p->next[chr] = new TrieNode();
                //p = p->next[word[i] - 'a'];
            }
            p = p->next[chr];
        }
    
        p->leave = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        // dfs
        return search(word, root);
    }
    
    bool search(string word, TrieNode* p) {
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == '.') {
                for (int j = 0; j < 26; j++)
                    if (p->next[j] && search(word.substr(i + 1), p->next[j]))   return true;
                return false;
            }
            else {
                if (p->next[word[i] - 'a'])
                    p = p->next[word[i] - 'a'];
                else
                    return false;
            }
        }
    
        return p->leave;
    }

private:
    TrieNode *root;
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");