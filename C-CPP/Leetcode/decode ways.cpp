class Solution {
public:
    int numDecodings(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(s.size()==0) return 0;
        vector<int> c(s.size()+1,1);
        for(int i = s.size()-1; i>=0; i--){
            if(s[i]=='0') c[i] = 0;
            else c[i] = c[i+1];
            if(i+1<s.size() && (s[i] == '1' || (s[i]=='2' && s[i+1] <= '6')))
                c[i] += c[i+2];
        }
        return c[0];
    }
};

// 1D dp
