class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<string> rslt;
        if(0 == words.size()) return rslt;
        int si = 0, ei = si;
        int len = 0;
        while(true) {
            for(ei = si; ei < words.size(); ++ei) {
                if(len + (ei - si) + words[ei].size() > L) {
                    break;
                }
                len += words[ei].size();
            }
            --ei;
            if(ei < si) ei = si;
            //form the string
            if(si >= ei) {
                //only one word on this line
                string line = words[si];
                line.append(L - line.size(), ' ');
                rslt.push_back(line);
            } else {
                //multiple words on this line
                bool lastline = (ei == (words.size() - 1));
                int spaceBase = (L - len) / (ei - si);
                int bonus = (L - len) - spaceBase * (ei - si);
                if(lastline) {
                    //lastline
                    spaceBase = 1;
                    bonus = 0;
                }
                string line = words[si];
                for(int i = si + 1; i <= ei; ++i) {
                    int space = spaceBase;
                    if(bonus > 0) {
                        ++space;
                        --bonus;
                    }
                    line.append(space,' ');
                    line.append(words[i]);
                }
                if(lastline) {
                    line.append(L - len - ei + si,' ');
                }
                rslt.push_back(line);
            }
            //progress
            si = ei + 1;
            len = 0;
            if(si >= words.size()) break;
        }//end while
        return rslt;
    }
};
