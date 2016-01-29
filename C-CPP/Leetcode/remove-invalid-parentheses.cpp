class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        // DFS
        /*
        unordered_set<string> result;
        if (s.empty()) {
            return vector<string>({""});
        }
        
        int left_remove = 0, right_remove = 0;
        for (auto c : s) {
            if (c == '(') {
                ++left_remove;
            } else if (c == ')') {
                if (left_remove != 0) {
                    --left_remove;
                } else {
                    ++right_remove;
                }
            }
        }
        
        dfs(s, 0, left_remove, right_remove, 0, "", result);
        return vector<string>(result.begin(), result.end());
        */
        
        // BFS:
        // T(n) = n x C(n, n) + (n-1) x C(n, n-1) + ... + 1 x C(n, 1) = n x 2^(n-1).
    
        // sanity check
        if (s.empty()) {
            return vector<string>({""});
        }
        
        vector<string>res;
        set<string> visited;
        queue<string> q;
        
        // initialize
        q.push(s);
        visited.insert(s);
        
        bool found = false;
        
        while(!q.empty()) {
            s = q.front();
            q.pop();
            
            if (isValid(s)) {
                // found answer, add to the result
                res.push_back(s);
                found = true;
            }
            
            if (found) continue;
            
            // generate all possible states
            for (int i = 0; i < s.size(); i++) {
                // only try to remove left or right paren
                if (s[i] != '(' && s[i] != ')') continue;
                
                string t = s.substr(0, i) + s.substr(i + 1);
                
                if (visited.count(t) == 0) {
                    // for each state, if its' not visited , add to the queue
                    q.push(t);
                    visited.insert(t);
                }
            }
        }
        return res;
    }
    
    bool isValid(string s) {
        int count = 0;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') count++;
            if (s[i] == ')' && count-- == 0) {
                //count--;
                return false;
            }
        }
        return count == 0;
    }
    
    void dfs(string s, int index, int left_remove, int right_remove, int pair, string path, unordered_set<string>& result) {
        if (index == s.size()) {
            if (left_remove == 0 && right_remove == 0 && pair == 0) {
                result.insert(path);
            }
            return;
        }
        
        if (s[index] == '(') {
            if (left_remove > 0) {
                dfs(s, index + 1, left_remove - 1, right_remove, pair, path, result);
            } 
            dfs(s, index + 1, left_remove, right_remove, pair + 1, path + s[index], result);
        } else if (s[index] == ')'){ // s[index] == ')'
            if (right_remove > 0) {
                dfs(s, index + 1, left_remove, right_remove - 1 ,pair, path, result);
            }
            if (pair > 0) {
                dfs(s, index + 1, left_remove, right_remove, pair - 1, path + s[index], result);
            }
        } else { //if (s[index] != '(' && s[index] != ')') 
            dfs(s, index + 1, left_remove, right_remove, pair, path + s[index], result);
        }
    }
};