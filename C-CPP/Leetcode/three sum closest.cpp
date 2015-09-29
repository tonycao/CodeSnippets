class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int closest = num[1] + num[2] + num[3];
        sort(num.begin(), num.end());
        vector<vector<int> > triplets;
        vector<int> triplet(3);
        int n = num.size();
        for (int i = 0;i < n; i++) {
            int j = i + 1;
            int k = n - 1;
            while (j < k) {
                int sum_two = num[i] + num[j];
                if (sum_two + num[k] < target) {
                    if (abs(closest-target) > abs(sum_two+num[k]-target)){
                        closest = sum_two+num[k];
                    }
                    j++;
                } else if (sum_two + num[k] > target) {
                    if (abs(closest-target) > abs(sum_two+num[k]-target)){
                        closest = sum_two+num[k];
                    }
                    k--;
                } else {
                    closest = sum_two+num[k];
                    return closest;
                    //j++;
                    //k--;
                }
            }
        }
        return closest;
    }
};
