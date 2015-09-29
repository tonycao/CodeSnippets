class Solution {
public:
    int numTrees(int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (n == 0) return 1;
        if (n == 1) return 1;
        int sum = 0;
        for(int i = 1; i <= n; i++){
            sum += numTrees(i-1)*numTrees(n-i);
        }
        return sum;
    }
};

// algorithm 2: DP
class Solution {
public:
    int numTrees(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> table(n+1,0);
        if (n==0){return 0;}
        table[0]=1;
        table[1]=1;
        table[2]=2;
        for (int i=3;i<=n;i++){
            int res=0;
            for (int j=0;j<=i-1;j++){
                res = res+ table[j]*table[i-1-j];
            }
            table[i]=res;
        }
        return table[n];
    }
};
