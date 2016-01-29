class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //Time ~ O(N), Space ~ O(N) 
        set<int> numset;
        int maxval = 0;
        for (auto i : nums) numset.insert(i); // use set 
        for (auto i : nums) {
            int len = 1;
            // find in two directions
            for (int j = i + 1; numset.find(j) != numset.end(); j++) {
                len++;
                numset.erase(j);
            }
            for (int j = i - 1; numset.find(j) != numset.end(); j--) {
                len++;
                numset.erase(j);
            }
            numset.erase(i);
            maxval = max(maxval, len);
        }
        return maxval;
    }
    
private:
    int mergeCluster(unordered_map<int, int> &map, int left, int right) {
        int upper = right + map[right] - 1;
        int lower = left - map[left] + 1;
        int length = upper - lower + 1;
        map[upper] = length;
        map[lower] = length;
        return length;
    }
};