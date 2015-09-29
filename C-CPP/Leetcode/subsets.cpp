class Solution {
public:
    void generateSub(vector<int> &s, int step, vector<vector<int>> &result, vector<int> &output){
        for(int i = step; i < s.size(); ++i){
            output.push_back(s[i]);
            result.push_back(output);
            if(i < s.size() - 1) generateSub(s, i+1, result, output);
            output.pop_back();
        }
    }
    vector<vector<int> > subsets(vector<int> &S) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int>> result;
        vector<int> output;
        if(S.size() == 0) return result;
        result.push_back(output);
        sort(S.begin(), S.end());
        generateSub(S, 0, result, output);

        return result;
    }
};
