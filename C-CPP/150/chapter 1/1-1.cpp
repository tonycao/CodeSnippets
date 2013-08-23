#include <iostream>
#include <cstring>

using namespace std;

bool isUnique1(string s)
{
    bool allset[256];
    memset(allset, 0, sizeof(allset));
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        int v = (int)s[i];
        if(allset[v]) return false;
        allset[v] = true;
    }
    return true;
}

bool isUnique2(string s)
{
    int allset[8];
    memset(allset, 0, sizeof(allset));
    int len = s.length();
    for(int i = 0; i < len; ++i)
    {
        int v = (int)s[i];
        int idx = v/32, shift = v%32;
        if(allset[idx] & (1 << shift)) return false;
        allset[idx] |= (1 << shift);
    }
    return true;
}

bool isUnique3(string s)
{
    int check = 0;
    int len = s.length();
    for(int i=0; i < len; ++i)
    {
        int v = (int)(s[i]-'a');
        if(check & (1 << v)) return false;
        check |= (1 << v);
    }
    return true;
}

int main()
{
    string s1 = "i am tian.";
    string s2 = "abcdefghijklmnopqrstuvwxyzABCD1234567890";
    cout << isUnique1(s1) << " " << isUnique1(s2) << endl;
    cout << isUnique2(s1) << " " << isUnique2(s2) << endl;
    return 0;
}
