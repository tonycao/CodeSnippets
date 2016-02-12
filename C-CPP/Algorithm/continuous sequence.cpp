#include <iostream>
using namespace std;


void printcontinuousSequence(int small, int big){
    for(int i = small; i <= big; i++){
        cout<< i << " ";
    }
    cout << endl;
}

void FindContinuousSequence(int n){
    if(n < 3) return;
    int small = 1;
    int big = 2;
    int middle = (1+n)/2;
    int sum = small + big;

    while(small < middle){
        if(sum == n) printcontinuousSequence(small, big);

        while(sum > n) {
            sum -= small;
            small++;

            if(sum == n) printcontinuousSequence(small, big);
        }

        big++;
        sum += big;
    }
}


int main(){
    FindContinuousSequence(15);
    return 0;
}
