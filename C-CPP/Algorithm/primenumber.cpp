#include <cmath>
#include <list>
#include <iostream>
using namespace std;

// the number of prime numbers
unsigned int PrimeNum_1(unsigned int maxNum)
{
    list<int> primes;
    primes.push_back(2);
    for(unsigned int i = 3; i < maxNum; ++i)
    {
        int k = (int)sqrt((double)i);
        bool bPrime = true;
        for(list<int>::const_iterator iter = primes.begin(); (*iter) <= k && iter != primes.end(); ++iter)
        {
            if(i%(*iter) == 0)
            {
                bPrime = false;
                break;
            }
        }
        if(bPrime){
            primes.push_back(i);
            //cout << "prime " <<i <<endl;
        }

    }
    return primes.size();
}

// algorithm 2:
unsigned int PrimeNum_2(unsigned int maxNum)
{
    unsigned int count = 0;
    // 分配标记数组，浪费flag[0]
    char* flag = (char*)malloc(maxNum+1);
    unsigned int i, j;
    // 初始化标记
    flag[2] = 1;
    // 步长为2，maxNum为奇数时，没有初始化flag[maxNum]
    for(i = 3; i < maxNum; )
    {
        flag[i++] = 1;
        // 所有大于2的偶数，均是非素数
        flag[i++] = 0;
    }
    if(maxNum%2)
    {
        flag[maxNum] = 1;
    }
    for(i = 3; i < maxNum/2; ++i)
    {
        // 已经判定是和数的，不再判定
        if(!flag[i])
            continue;
        // 用加法代替乘法，加法运算更快
        for(j = i+i; j < maxNum; j += i)
        {
            flag[j] = 0;
        }
    }
    // 剩下的凡是flag标识为1的索引，即是输出
    std::list<unsigned int> primes;
    for(i = 2; i <= maxNum; i++)
    {
        if(flag[i])
            primes.push_back(i);
    }
    return primes.size();
}

int main(){
    unsigned int maxNum = 500;
    cout << PrimeNum_1(maxNum) <<endl;
    return 0;
}
