class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(n == 0) return 0;
        if(n == 1) return A[0];

        int start = 0;
        int key = A[0];
        int rep = 1;
        for(int i = 1; i < n; i++){
            if(A[i] == key ){
                if(rep < 2){
                    A[start++] = key;
                    rep++;
                }else{
                    rep++;
                }
            }else{
                A[start++] = key;
                key = A[i];
                rep = 1;
            }
        }
        A[start++] = key;
        return start;
    }
};
