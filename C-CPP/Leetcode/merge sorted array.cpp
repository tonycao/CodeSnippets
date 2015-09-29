class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int k = m+n-1;
        int i = m-1;
        int j = n-1;
        while(i>=0 && j>=0){
            A[k--] = A[i] > B[j] ? A[i--] : B[j--];
        }
        while(j>=0){
            A[k--] = B[j--];
        }
    }
};
