class Solution {
public:
    bool isValid(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<char> lefts;
        for(int i = 0 ; i < s.size() ;++i) {
            char c = s[i];
            if(c == '(' || c == '[' || c == '{') {
                lefts.push(c);
            } else {
                if (lefts.size() == 0) return false;
                char top = lefts.top();
                if (c == ')') {
                    if(top != '(') return false;
                } else if ( c == ']' ) {
                    if(top != '[') return false;
                } else if ( c == '}' ){
                    if(top != '{') return false;
                }
                lefts.pop();
            }
        }
        return lefts.size() == 0;
    }
};
