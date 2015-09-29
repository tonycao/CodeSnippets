class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0) return 0;
        int l = 0, r = n-1;
        while(l<=r){
            int mid = (l+r)/2;
            int mv = A[mid];
            if(mv == target)
                return mid;
            if(mv < target)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }
};
