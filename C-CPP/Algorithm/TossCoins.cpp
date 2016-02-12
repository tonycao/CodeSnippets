// 主文件main
/*
* Author: Tanky woo
* Blog:   www.WuTianQi.com
* Date:   2010.12.7
* 代码来至王晓东《计算机算法设计与分析》
*/
#include "RandomNumber.h"
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
 
int TossCoins(int numberCoins)
{
	// 随机抛硬币
	static RandomNumber coinToss;
	int i, tosses = 0;
	for(i = 0; i < numberCoins; ++i)
		tosses += coinToss.Random(2);
	return tosses;
}
 
int main()
{
	// 模拟随机抛硬币事件
	const int NCOINS = 10;
	const long NTOSSES = 50000L;
	// heads[i]得到的i次正面的次数
	long i, heads[NCOINS+1];
	int j, position;
	// 初始化数组heads
	for(j = 0; j < NCOINS+1; ++j)
		heads[j] = 0;
	// 重复50,000次模拟事件
	for(i = 0; i < NTOSSES; ++i)
		heads[TossCoins(NCOINS)] ++;
	// 输出频率图
	for(i = 0; i <= NCOINS; ++i)
	{
		position = int (float(heads[i]) / NTOSSES*72);
		cout << setw(6) << i << " ";
		for(j = 0; j<position-1; ++j)
			cout << " ";
		cout << "*" << endl;
	}
	return 0;
}