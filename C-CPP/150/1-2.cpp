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
    for(int i=0; i<n/2; ++i)
    {
        swap(s[i], s[n-i-1]);
    }
}

int main()
{
    char s[] = "12345678";
    char s2[] = "abcdefghi";
    reverse1(s);
    reverse1(s2);
    cout<<s<<endl;
    cout<<s2<<endl;
    return 0;

}
