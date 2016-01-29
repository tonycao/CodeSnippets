#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> array(26, 0);
        if (s.size() == 0) return "";
        
        for (int i = 0; i < s.size(); i++) {
            array[s[i]-'a']++;
        }
        
        cout << array.size() << endl;
        stringstream res;
        for (int i = 0; i < array.size(); i++) {
            cout << array[i] << endl;
            if (array[i] == 1) {
                res << (char)(i + 'a');
            } 
        }
        return res.str();
    }
};

int main() {
    Solution sol;
    cout << sol.removeDuplicateLetters("bcabc");

}