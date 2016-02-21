#include <cstdio>
#include <iostream>
using namespace std;

void Endianness()
{
    int a = 0x12345678;
    if( *((char*)&a) == 0x12)
        cout << "Big Endian" << endl;
    else
        cout << "Little Endian" << endl;
}

int main()
{   
    Endianness();

    union check
    {
        int a;
        char b[2];
    } s;
    s.a = 0x1234;
    //s.a = 0x12345678;
    printf("数据在内存中：\n");
    printf("变量： %12s\t %12s\t %12s\n", "s.b[0]", "s.b[1]", "s.a");
    printf("地址： %8p\t %8p\t %8p\n", &s.b[0], &s.b[1], &s.a);
    printf("数据： %12x\t %12x\t %12x\n", s.b[0], s.b[1], s.a);
    if (s.b[0] == 0x12)
        printf("大端模式\n");
    else
        printf("小端模式\n");
    return 0;
}