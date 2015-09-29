class Solution {
public:
    bool isPalindrome(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(s.size() == 0) return true;

        int st = 0;
        int end = s.size()-1;

        while(st<ed){
            if(isalnum(s[st]) == false) {st++; continue;}
            if(isalnum(s[ed]) == false) {ed--; continue;}

            if(tolower(s[ed]) != tolower(s[st])){
                return false;
            }else{
                st++；
                ed--;
            }
        }
        return true;
    }
};
