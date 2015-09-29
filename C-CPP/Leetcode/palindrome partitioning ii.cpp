class Solution {
public:
    int minCut(string s) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> res(s.size(),0);
        bool mp[s.size()][s.size()];

        for(int i = s.size()-1; i>=0; i--){
            for(int j = i; j<s.size(); j++){
                if(s[i]==s[j] && (j-i<2 || mp[i+1][j-1])){
                    mp[i][j] = true;
                }else{
                    mp[i][j] = false;
                }
            }
        }

        for(int i = 0; i<s.size(); i++){
            int ms = s.size();
            if(mp[0][i]){
                res[i] = 0;
            }else{
                for(int j=0; j<i; j++){
                    if(mp[j+1][i] && ms>res[j]+1){
                        ms = res[j]+1;
                    }
                }
                res[i] = ms;
            }
        }
        return res[s.size()-1];
    }
};
