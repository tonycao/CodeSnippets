#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    /**
     * @param buildings: A list of lists of integers
     * @return: Find the outline of those buildings
     */
    vector<vector<int> > buildingOutline(vector<vector<int> > &buildings) {
        // write your code here
        vector<pair<int, int>> height;
        for (auto b : buildings) {
            height.push_back(make_pair(b[0], -b[2]));
            height.push_back(make_pair(b[1],  b[2]));
        }
        
        sort(height.begin(), height.end());
        multiset<int> heap;
        heap.insert(0);
        vector<vector<int>> res;
        int pre = 0, cur = 0, start = 0;
        
        for (auto h : height) {
            if (h.second < 0) {
                heap.insert(-h.second);
            } else {
                heap.erase(heap.find(h.second));
            }
            cur = *heap.rbegin();
            if (cur != pre && pre != 0) {
                res.push_back({start, h.first, pre});    
                
            }
            if (cur != pre)
                start = h.first;  
            pre = cur;
              
        }
        return res;
    }

};

int main() {
    vector<vector<int>> buildings = {{1, 3, 3}, {2, 4, 4}, {5, 6, 1}};
    Solution sol;
    vector<vector<int>> res = sol.buildingOutline(buildings);
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    
}