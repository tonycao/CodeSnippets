class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for (auto c : s) {
            if (stk.empty() || p.find(c) != p.end()) {
                stk.push(c);
            } else {
                if (stk.empty() || c != p[stk.top()]) {
                    return false;
                } else stk.pop();
            }
        }
        return stk.empty();
    }
private:
    map<char, char> p = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
};