// RandomNumber.cpp
#include "RandomNumber.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
 
using namespace std;
 
// 产生种子
RandomNumber::RandomNumber(unsigned long s)
{
	if(s == 0)
		randSeed = time(0);    //用系统时间产生种子
	else
		randSeed = s;
}
 
// 产生0 ~ n-1 之间的随机整数
unsigned short RandomNumber::Random(unsigned long n)
{
	randSeed = multiplier * randSeed + adder;
	return (unsigned short)((randSeed >> 16) % n);
}
 
// 产生[0, 1)之间的随机实数
double RandomNumber::fRandom()
{
	return Random(maxshort) / double(maxshort);
}