#include <iostream>
#include <cstdio>

using namespace std;

unsigned char reverse_char(unsigned char in) {
    unsigned char high = 0x80; // keep the top bit in original char
    unsigned char res = 0x0, tmp = 0x0;
    for (int i=7; i>=0; i--) {
        tmp = (in&0x1)<<i;
        in = in>>1;
        res = (res&~high)|tmp;
        high = high>>1;
    }
    return res;
}

int main(int argc, char *argv[]) {
    unsigned char high = 0x4c;
    unsigned char test = 0xbc;
    unsigned char reversed = reverse_char(high);
    //unsigned char test = 'a';
    printf("%u\n", (unsigned int)high);
    printf("%x\n", high);
    printf("%u\n", 0x80);
    printf("%c\n", reversed);
    printf("%x\n", reversed);
    printf("%u\n", reversed);
}

//01001101
//10110010