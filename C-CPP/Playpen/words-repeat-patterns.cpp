#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMultiple (string s){
        int N = s.size();
        if(N < 4) return false;
        int len = 1;
        int start = 0;
        for(int i = 1;i < N; ++i){
            if(s[start] == s[i]){
                start++;
                if(start >= len) start = 0;
            }
            else{
                len++;
                i = len-1;
                start = 0;
            }
            if(len > N / 2) return false;            
        }
        return len != 1 && (N % len == 0);
    }
};

int main() {
    Solution sol;
    cout<<sol.isMultiple("abcabcabc")<<"     "<<"1"<<endl;
    cout<<sol.isMultiple("bcdbcdbcde")<<"     "<<"0"<<endl;
    cout<<sol.isMultiple("abcdabcd" )<<"     "<<"1"<<endl;
    cout<<sol.isMultiple("xyz")<<"     "<<"0"<<endl;
    cout<<sol.isMultiple("aaaaaaaaaa")<<"     "<<"0"<<endl;
    cout<<sol.isMultiple("abaaba")<<"     "<<"1"<<endl;
    cout<<sol.isMultiple("aaabaaaaba")<<"     "<<"1"<<endl;
    cout<<sol.isMultiple("abaabaaba")<<"     "<<"1"<<endl;
    cout<<sol.isMultiple("abaababaab")<<"     "<<"1"<<endl;
    //_getch();
}