class Solution {
public:
    bool canJump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int maxx=0;
        for(int i=0;i<n;++i)
        {
            if(i<=maxx)
            {
                maxx=max(maxx,i+A[i]);
            }
        }
        return maxx>=n-1;

    }
};
