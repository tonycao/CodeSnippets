class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> hashmap;
        int start = 0, maxlen = 0;
        for (int i = 0; i < s.length(); i++) {
            auto iter = hashmap.find(s[i]);
            if ( iter != hashmap.end() && start <= iter->second) {
                maxlen = max(maxlen, i - start);
                start = iter->second + 1; // update start
            }
            hashmap[s[i]] = i;
        } 
        return max(maxlen, (int)s.length() - start); // check the last max length
    }
};