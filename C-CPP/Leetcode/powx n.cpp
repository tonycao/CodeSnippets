class Solution {
public:
    double pow(double x, int n) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (x==0){
            if (n==0){return 1;}
            else {return 0;}
        }

        if (n==0){
            return 1;
        }

        bool pos=true;
        if (n<0){
            pos = false;
            n=abs(n);
        }

        double np=x;
        double res=1;
        while (n>0){
            if (n%2==1){
                res = res * np;
            }
            np=np*np;
            n=n/2;
        }

        return  pos? res:1/res;
    }
};
