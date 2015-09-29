class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        map<string, int> words;
        map<string, int> curStr;
        for(int i = 0; i < L.size(); ++i)
            ++words[L.at(i)];
        int N = L.size();
        vector<int> ret;
        if(N <= 0)   return ret;
        int M = L.at(0).size();
        for(int i = 0; i <= (int)S.size()-N*M; ++i)
        {
            curStr.clear();
            int j = 0;
            for(j = 0; j < N; ++j)
            {
                string w = S.substr(i+j*M, M);
                if(words.find(w) == words.end())
                    break;
                ++curStr[w];
                if(curStr[w] > words[w])
                    break;
            }
            if(j == N)  ret.push_back(i);
        }
        return ret;
    }
};
