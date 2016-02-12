#include <iostream>
#include <assert.h>
using namespace std;

typedef unsigned int uint;
uint swapBits(uint x, uint i, uint j){
    uint lo = ((x>>i) & 1);
    uint hi = ((x>>j) & 1);
    if(lo^hi){
        x ^= ((1U << i) | (1U << j));
    }
    return x;
}

uint reverseMask(uint x) {
    assert(sizeof(x) == 4); // special case: only works for 4 bytes (32 bits).
    x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
    x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
    x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
    x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
    x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
    return x;
}

uint reverseXor(uint x){
    uint n = sizeof(x) * 8;
    for(uint i = 0; i < n/2; i++){
        x = swapBits(x, i, n-i-1);
    }
    return x;
}

int main(){
    uint a = 1<<30;
    cout << reverseXor(a)<<endl;
    cout << reverseMask(a)<<endl;
    return 0;
}
