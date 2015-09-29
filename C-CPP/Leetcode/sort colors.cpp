class Solution {
public:
    void swap(int A[], int i, int j){
        int tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
    }
    void sortColors(int A[], int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int red = 0;
        int blue = n-1;

        while(A[red] == 0) red++;
        while(A[blue] == 2) blue--;

        int i = red;
        while(i<=blue){
            if(A[i] == 0 && i > red){
                swap(A, i, red);
                red++;
                continue;
            }
            if(A[i] == 2){
                swap(A, i, blue);
                blue--;
                continue;
            }
            i++;
        }
    }
};
