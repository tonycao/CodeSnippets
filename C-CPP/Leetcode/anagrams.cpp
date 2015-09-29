class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        map<string,int> mp; //store the occurrence of strings, keys are sorted string
        map<string,string> pre; //store the first-time string
        vector<string> res; //result vector
        for (int i=0;i<strs.size();i++){
            string s = strs[i]; //current string
            sort(s.begin(),s.end()); // get the key (sorted string)
            if (mp.find(s)==mp.end()){ // if this is the 1st time meet this string
                mp[s]=1; // set occurence to 1
                pre[s] = strs[i]; // save the original string
            }else{ // if anagrams found
                mp[s]++;
                if (mp[s]==2){res.push_back(pre[s]);} // need to push the 1st string into result only once
                res.push_back(strs[i]); // push the current string
            }
        }
        return res;
    }
};
