#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int k1 = nums1.size();
        int k2 = nums2.size();
        if ((k1 + k2) % 2 == 1) {
            return findkth(nums1, 0, k1 - 1, nums2, 0, k2 - 1, (k1 + k2) / 2 + 1);
        } else {
            int a = findkth(nums1, 0, k1 - 1, nums2, 0, k2 - 1, (k1 + k2) / 2);
            int b = findkth(nums1, 0, k1 - 1, nums2, 0, k2 - 1, (k1 + k2) / 2 + 1) ;
            cout << a << " " << b << endl; 
            return ( a + b )/ 2.0;
        }
    }
    
private:
    double findkth(vector<int>& nums1, int start1, int end1, vector<int>& nums2, int start2, int end2, int k) {
        if (end1 - start1 > end2 - start2) {
            return findkth(nums2, start2, end2, nums1, start1, end1, k);
        }
        if (start1 > end1) return nums2[start2 + k - 1];
        if (k == 1) return min(nums1[start1], nums2[start2]);
        
        int index1 = min(end1 - start1 + 1, k / 2);
        int index2 = k - index1;
        
        if (nums1[start1 + index1 - 1] <= nums2[start2 + index2 - 1]) {
            return findkth(nums1, start1 + index1, end1, nums2, start2, end2, k - index1);
        } else {
            return findkth(nums1, start1, end1, nums2, start2 + index2, end2, k - index2);
        }
    }
};

int main() {
    vector<int> A = {1, 2, 4}, B = {3};
    Solution sol;
    cout << sol.findMedianSortedArrays(A, B) << endl;

}