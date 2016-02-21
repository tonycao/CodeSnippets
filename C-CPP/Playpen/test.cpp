#include <iostream>

using namespace std;
int main()

{
    unsigned int a = ~0;
    if( a>65536 )
    {
    cout<<"32 bit"<<endl;
    }
    else
    {
    cout<<"16 bit"<<endl;
    }
    return 0;
}
