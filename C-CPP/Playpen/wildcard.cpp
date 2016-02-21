#include <iostream>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int sind = 0, pind = 0, match = 0, starind = -1;
        
        while(sind < s.length()) {
            if (pind < p.length()  && p[pind] == '*') { // for cases we have "*" in source string
                starind = pind++; 
                match = sind;
            } else if (pind < p.length()  && (p[pind] == '?' || s[sind] == p[pind])) {
                sind++;
                pind++;
            } else if (starind != -1) {
                pind = starind + 1;
                sind = ++match;
            } else return false;
        }
        
        while (pind < p.length() && p[pind] == '*') pind++;
        return pind == p.length();
    }
};

int main() {
    Solution sol;
    cout << sol.isMatch("ab*cdec", "ab*c") << endl;
    cout << sol.isMatch("ba", "*a") << endl;
    return 0;
}