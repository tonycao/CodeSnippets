//Write a program to swap odd and even bits in an integer with as few 
//instructions as possible (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, etc).

#include <iostream>
#include <string>
using namespace std;

void print_binary(int x){
    string s = "";
    for(int i=0; i<32 && x!=0; ++i, x >>= 1){
        if(x&1) s = "1" + s;
        else s = "0" + s;
    }
    cout<<s<<endl;
}
int swap_bits(int x){
    return ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
}
int swap_bits1(int x){
    return ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
}
int main(){
    int x = -7665543;
    print_binary(x);
    print_binary(swap_bits(x));
    print_binary(swap_bits1(x));
    return 0;
}