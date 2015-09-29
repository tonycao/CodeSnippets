class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0)
            return 0;

        int start = 0;
        int key = A[0];
        for(int i = 0; i < n; i++)
            if (A[i] != key)
            {
                A[start++] = key;
                key = A[i];
            }

        A[start++] = key;

        return start;
    }
};
