class Solution {
     void find_subset(vector<int>::iterator first,vector<int>::iterator last,
                      vector<int> &comb, int target, vector<vector<int>> &ret){
         if(target == 0)
             ret.push_back(comb);
         if(target < 0)
             return;
         vector<int>::iterator it;
         for(it = first; it != last && *it <= target; it++){
             comb.push_back(*it);
             find_subset(it, last, comb, target - *it, ret);
             comb.pop_back();
         }
     }
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> ret;
        unique(candidates.begin(), candidates.end());
        sort(candidates.begin(), candidates.end());
        vector<int> a;

        find_subset(candidates.begin(), candidates.end(), a, target, ret);
        return ret;
    }
};
