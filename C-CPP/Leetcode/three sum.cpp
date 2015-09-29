set<vector<int> > find_triplets(vector<int> arr) {
  sort(arr.begin(), arr.end());
  set<vector<int> > triplets;
  vector<int> triplet(3);
  int n = arr.size();
  for (int i = 0;i < n; i++) {
    int j = i + 1;
    int k = n - 1;
    while (j < k) {
      int sum_two = arr[i] + arr[j];
      if (sum_two + arr[k] < 0) {
        j++;
      } else if (sum_two + arr[k] > 0) {
        k--;
      } else {
        triplet[0] = arr[i];
        triplet[1] = arr[j];
        triplet[2] = arr[k];
        triplets.insert(triplet);
        j++;
        k--;
      }
    }
  }
  return triplets;
}


algorithm2:

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
         sort(num.begin(), num.end());
        vector<vector<int> > triplets;
        vector<int> triplet(3);
        int n = num.size();
        for (int i = 0;i < n; i++) {
            int j = i + 1;
            int k = n - 1;
            while (j < k) {
                int sum_two = num[i] + num[j];
                if (sum_two + num[k] < 0) {
                    j++;
                } else if (sum_two + num[k] > 0) {
                    k--;
                } else {
                    triplet[0] = num[i];
                    triplet[1] = num[j];
                    triplet[2] = num[k];
                    triplets.push_back(triplet);
                    j++;
                    k--;
                }
            }
        }
        sort(triplets.begin(),triplets.end());
        triplets.erase(unique(triplets.begin(),triplets.end()),triplets.end());
        return triplets;
    }
};
