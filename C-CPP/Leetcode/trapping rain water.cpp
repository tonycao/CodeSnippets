class Solution {
public:
    int trap(int A[], int n) {
        //no way to contain any water
        if(n <= 2) return 0;

        //1. first run to calculate the heiest bar on the left of each bar
        int *lmh = new int[n];//for the most height on the left
        lmh[0] = 0;
        int maxh = A[0];
        for(int i = 1; i < n; ++i) {
            lmh[i] = maxh;
            if(maxh < A[i]) maxh = A[i];
        }
        int trapped = 0;

        //2. second run from right to left,
        // caculate the highest bar on the right of each bar
        // and calculate the trapped water simutaniously
        maxh = A[n-1];
        for(int i = n - 2; i > 0; --i) {
            int left = lmh[i];
            int right = maxh;
            int container = min(left,right);
            if(container > A[i]) {
                trapped += container - A[i];
            }
            if(maxh < A[i]) maxh = A[i];
        }
        delete lmh;
        return trapped;
    }
};
