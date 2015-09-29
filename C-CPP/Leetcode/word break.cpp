class Solution {
public:

    class Node {
    public:
        Node* next[26];
        bool end;
        Node(): end(false) { for (int i = 0; i < 26; i++) next[i] = NULL;}
        void insert(string a) {
            Node * cur = this;
            for (int i = 0; i < a.size(); i++) {
                if (cur->next[a[i]-'a'] == NULL) {
                    cur->next[a[i]-'a'] = new Node();
                }
                cur = cur->next[a[i]-'a'];
            }
            cur->end = true;
        }
        ~Node () {
            for (int i = 0;i < 26; i++) delete next[i];
        }
    };

    bool wordBreak(string s, unordered_set<string> &dict) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        Node root;
        for(auto it = dict.begin(); it != dict.end(); it++){
            root.insert(*it);
        }

        vector<bool> v(s.size(),false);
        findMatch(s, &root, 0, v);
        for(int i = 0; i< s.size(); i++){
            if(v[i]) findMatch(s, &root, i+1, v);
        }
        return v[s.size()-1];
    }

    void findMatch(const string &s, Node *cur, int start, vector<bool> &v){
        int i = start, n = s.size();
        while(i < n){
            if(cur->next[s[i] - 'a'] != NULL){
                if(cur->next[s[i] - 'a']->end) v[i] = true;
                cur = cur->next[s[i] - 'a'];
            }
            else break;
            i++;
        }
    }
};
