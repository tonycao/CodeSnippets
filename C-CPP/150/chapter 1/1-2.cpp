#include <iostream>
#include <cstring>

using namespace std;

void swap(char &a, char &b)
{
    a = a^b;
    b = a^b;
    a = a^b;
}

void reverse1(char *s)
{
    int n = strlen(s);
    int i,j, tmp;
    for(i=0, j=n-1; i<j; i++, j--)
    {
        //swap(s[i], s[n-i-1]);
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void reverse2(char *s){
    if(!s) return;
    char *p = s, *q = s;
    while(*q) ++q;
    --q;
    while(p < q)
        swap(*p++, *q--);
}

void reverse3(char *str){ // cc150 solution
    char* end = str;
    char tmp;
    if (str) {
        while(*end) {
            ++end;
        }
        --end;

        while(str<end) {
            tmp = *str;
            *str++ = *end;
            *end-- = tmp;
        }
    }
} 

int main()
{
    char s[] = "12345671";
    char s2[] = "abcdefghi";
    char s3[] = "abcdefghi12345671";
    reverse1(s);
    reverse2(s2);
    reverse3(s3);
    cout<<s<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    return 0;

}
