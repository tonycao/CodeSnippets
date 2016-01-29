#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        // http://algobox.org/count-of-range-sum/
        // merge sort
        int n = nums.size();
        vector<long> sums(n + 1);
        for (int i = 0; i < n; ++i) {
            sums[i + 1] = nums[i] + sums[i];
        }
        return countWithMergeSort(sums, 0, n + 1, lower, upper);
    }
    
private:
    int countWithMergeSort(vector<long>& sums, int start, int end, int lower, int upper) {
        if (end - start <= 1) {
            return 0;
        }
        
        int mid = start + (end - start) / 2;
        int count = countWithMergeSort(sums, start, mid, lower, upper) +
                    countWithMergeSort(sums, mid, end, lower, upper);
        int j = mid, k = mid, t = mid;
        vector<long> cache(end - start);
        for (int i = start, r = 0; i < mid; ++i, ++r) {
            while (k < end && sums[k] - sums[i] < lower) k++;
            while (j < end && sums[j] - sums[i] <= upper) j++;
            while (t < end && sums[t] < sums[i]) cache[r++] = sums[t++];
            cache[r] = sums[i];
            count += j - k;
        }
        for (int i = 0; i < t - start; ++i) sums[start + i] = cache[i];
        return count;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-2, 5, -1};
    cout << sol.countRangeSum(nums, -2, 2) << endl;
}