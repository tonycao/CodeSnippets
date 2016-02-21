#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int> > result;
        if (num.size() < 3) return result;
        vector<int> triplet(3);
        sort(num.begin(), num.end());
        int n = num.size();
        for (int i = 0; i < n - 2; i++) {
            // remove duplicate i
            if (i > 0 && i < n && num[i] == num[i-1]) continue;
            int left = i + 1, right = num.size() - 1;
            while(left < right) {
                int sum = num[left] + num[right] + num[i];
                cout << sum << endl;
                cout << i << " " << left <<" "<< right << endl;
                cout << num[i] << " " << num[left] <<" "<< num[right] << endl;
                if (sum < 0 ) {
                    left++;
                    while(left < right && num[left] == num[left - 1]) left++;
                } else  if (sum > 0) {
                    right--;
                    while(left < right && num[right] == num[right + 1]) right--;
                } else {
                    triplet[0] = num[i];
                    triplet[1] = num[left];
                    triplet[2] = num[right];
                    result.push_back(triplet);
                    cout << i << " " << left <<" "<< right << endl;
                    left++;
                    right--;
                    while(num[left] == num[left - 1] && num[right] == num[right + 1] && left < right) left++;
                }
            }
            
        }
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> input(5, 0);
    input[0] = -2;
    input[1] = 0;
    input[2] = 1;
    input[3] = 1;
    input[4] = 2;
    sol.threeSum(input);

    return 0;
}