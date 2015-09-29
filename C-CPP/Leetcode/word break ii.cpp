#include <vector>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <set>

using namespace std;
using namespace std::tr1;

class Solution {
public:

    void DFS(vector<string> &ret, unordered_map<int, vector<int>> &hashmap, int cur, string s){
        if(cur==0){
            ret.push_back(s);
            return;
        }
        if(cur<s.size()) s.insert(cur, " ");
        for(auto it = hashmap[cur].begin(); it != hashmap[cur].end(); it++){
            DFS(ret, hashmap, *it, s);
        }
    }
    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int n = s.size();
        vector<string> ret;
        if(n == 0) return ret;
        vector<int> wb(n+1,0);
        wb[0] = 1;
        unordered_map<int, vector<int>> hashmap;
        for(int i = 1; i <= n; i++){
            for(auto it = dict.begin(); it!=dict.end(); it++){
                string ele = *it;
                int length = ele.size();
                if(i-length>=0){
                    if(wb[i-length] == 1 && s.substr(i-length, length).compare(ele) == 0){
                        wb[i] = 1;
                        hashmap[i].push_back(i-length);
                    }
                }
            }
        }
        if(wb[n] == 0) return ret;
        DFS(ret, hashmap, n, s);
        return ret;
    }
};
