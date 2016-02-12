// RandomNumber.h
 
const unsigned long maxshort = 65535L;
const unsigned long multiplier = 1194211693L;
const unsigned long adder = 12345L;
 
#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H
 
class RandomNumber{
private:
    // 当前种子
    unsigned long randSeed;
public:
    // 构造函数,默认值0表示由系统自动产生种子
    RandomNumber(unsigned long s = 0);
    // 产生0 ~ n-1之间的随机整数
    unsigned short Random(unsigned long n);
    // 产生[0, 1) 之间的随机实数
    double fRandom();
};
 
#endif