#include <cstdio>
#include <list>
#include <iostream>
using namespace std;
//#include "conio.h"
int main()
{
  int n=12345;

  //printf("\nplease input a number:\n");
  //scanf("%d",&n);
  printf("%d=",n);
  for(int i=2;i*i<=n;i++)
    while(n!=i)
    {
      if(n%i==0)
      {
        printf("%d*",i);
        n=n/i;
      }
      else
        break;
    }
  printf("%d",n);
  return 0;
  //getch();
}

//返回质因数数组
list<int> decPrime(int n) {
    list<int> mylist;
    for (int i=2;i <= n;i++){
        while(n != i){
            if(n%i != 0){
                break;//不能整除肯定不是因数，能够整除在这里一定是质数。因为所有的2，3,5,7
                      //都被除完之后。剩下的因数只能是奇数，且是质数。
            }
            mylist.push_back(i);
            n = n/i;
        }
    }
    mylist.push_back(n);
    return mylist;
}

//Sieve of Eratosthenes (筛法)
void trial_divisio_fac(int n)
{
    int a=2;
    while(a*a<=n)
    {
        while(n%a==0)
        {
            cout<<a<<ends;
            n=n/a;
        }
        a++;
    }
    if(n>1) cout<<n;//n没有因数
}
