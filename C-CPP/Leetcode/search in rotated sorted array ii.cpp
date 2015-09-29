class Solution {
public:
    bool search(int A[], int n, int target) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int start = 0;
        int end = n-1;
        while(start <= end){
            int mid = (start + end)/2;
            if(A[mid] == target) return true;
            if(A[start] < A[mid]){
                if(target>=A[start] && target < A[mid]) end = mid-1;
                else start = mid +1;
            }else if(A[start] > A[mid]){
                if(target>A[mid] && target <= A[end]) start = mid +1;
                else end = mid -1;
            }
            else start++; //skip duplicate one, A[start] == A[mid]
        }
        return false;
    }
};
