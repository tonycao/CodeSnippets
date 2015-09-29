class Solution {
public:
    int maxSubArray(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int sum = 0;
        int max = A[0];
        for (int i = 0; i < n; ++i){
            sum += A[i];
            if (max < sum) max = sum;
            if (sum < 0) sum = 0;
        }
        return max;
    }
};


// algorithm 2 divide and conquer
1:    int maxSubArray(int A[], int n) {
2:      // Start typing your C/C++ solution below
3:      // DO NOT write int main() function
4:      int maxV = INT_MIN;
5:      return maxArray(A, 0, n-1, maxV);
6:    }
7:    int maxArray(int A[], int left, int right, int& maxV)
8:    {
9:      if(left>right)
10:        return INT_MIN;
11:      int mid = (left+right)/2;
12:      int lmax = maxArray(A, left, mid -1, maxV);
13:      int rmax = maxArray(A, mid + 1, right, maxV);
14:      maxV = max(maxV, lmax);
15:      maxV = max(maxV, rmax);
16:      int sum = 0, mlmax = 0;
17:      for(int i= mid -1; i>=left; i--)
18:      {
19:        sum += A[i];
20:        if(sum > mlmax)
21:          mlmax = sum;
22:      }
23:      sum = 0; int mrmax = 0;
24:      for(int i = mid +1; i<=right; i++)
25:      {
26:        sum += A[i];
27:        if(sum > mrmax)
28:          mrmax = sum;
29:      }
30:      maxV = max(maxV, mlmax + mrmax + A[mid]);
31:      return maxV;
32:    }
