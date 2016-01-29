/*
class TrieNode {
public:
    // Initialize your data structure here.
    static const int C_NUM = 26;
    TrieNode *next[C_NUM];
    bool leave;
    TrieNode() {
        leave = false;
        for (int i = 0; i < C_NUM; i++) {
            next[i] = NULL; // nullptr
        }
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string s) {
        TrieNode *cur = root;
        int index = 0;
        while(s.length() > index) {
            int chr = s[index] - 'a';
            if (cur->next[chr] == NULL) {
                cur->next[chr] = new TrieNode();
            }
            index++;
            cur = cur->next[chr];
        }
        cur->leave = true;
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode *cur = root;
        int index = 0;
        while(key.length() > index) {
            int chr = key[index] - 'a';
            if (cur->next[chr] == NULL) return false;
            index++;
            cur = cur->next[chr];
        }
        if (cur->leave == true) return true;
        return false;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *cur = root;
        int index = 0;
        while (prefix.length() > index) {
            int chr = prefix[index] - 'a';
            if (cur->next[chr] == NULL) return false;
            index++;
            cur = cur->next[chr];
        }
        return true;
    }

private:
    TrieNode* root;
};*/

struct TrieNode {
//public:
    // Initialize your data structure here.
    TrieNode() :isword(false){}
    bool isword;
    unordered_map<char, TrieNode*> children;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string s) {
        TrieNode * node = root;
        for (int i=0; i<s.length(); i++) {
            if (node->children.find(s[i]) == node->children.end())
                node->children[s[i]] = new TrieNode();
                //node->children.insert(make_pair(s[i], new TrieNode()));
            node = node->children[s[i]];
            if (i == s.length()-1) node->isword = true;
        } 
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode * node = root;
        for (int i=0; i<key.length(); i++) {
            if (node->children.find(key[i]) == node->children.end())
                return false;
            node = node->children[key[i]];
            if (i == key.length()-1) return node->isword;
        } 
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode * node = root;
        for (int i=0; i<prefix.length(); i++) {
            if (node->children.find(prefix[i]) == node->children.end())
                return false;
            node = node->children[prefix[i]];
        } 
        return true;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");