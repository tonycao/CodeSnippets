#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <limits>
#include <utility>
#include <ctime>
#include <bitset>
using namespace std;

/*
只能用+,-和位运算实现正整数除法(/)和模除(%),注意：不能用log！
*/

//判断n是否是2的正整数冪
inline bool is_2exp(unsigned int n)
{
	return !(n&(n-1));
}

//保持高位取反
inline int negate_bits(unsigned int n)
{
	if(n==0) return 1;
	unsigned int r=0, m=~n;
	while(n)
	{
		r |= (n^(n-1))&m;
		n &= n-1;
	}

	return r;
}

//计算n的二进制表示中1的个数
inline int count1(unsigned int n)
{
	int r = 0;
	while(n)
	{
		n &= n-1;
		r++;
	}
	return r;
}

//计算n的二进制表示中0的个数
inline int count0( unsigned int n)
{
	int r = 0;
	n = negate_bits(n);
	while(n)
	{
		n &= n-1;
		r++;
	}
	return r;
}

//求给定整数的二进制表示的位数
int count_bit(unsigned int n)
{
	int r = 0;
	while(n)
	{
		n>>=1;
		r++;
	}
	return r;
}

//求大于等于n的最小的2的正整数冪，方法1
//时间复杂度O(n的二进制位长度)
unsigned int high_2exp_1(unsigned int n)
{
	if(n<=1) return 1;
	if(is_2exp(n)) return n;

	unsigned int r = 1;
	while(n)
	{
		n >>= 1;
		r <<= 1;
	}

	return r;
}

//求大于等于n的最小的2的正整数冪，方法2
//计算时间与n的二进制表示中1的个数和位置有关，比方法1效率高
//最坏情况下的时间复杂度与方法1相同
unsigned int high_2exp_2(unsigned int n)
{
	if(n<=1) return 1;

	while(!is_2exp(n))
	{
		n |= n-1;
		n++;
	}

	return n;
}

//判断n是否是4的整数次幂
bool is_4exp(unsigned int n)
{
	if(!is_2exp(n)) return false;

	int bit_len = count_bit(n)-1;//线性时间求二进制位数
	if((bit_len&0x1)!=1)
		return true;
	else
		return false;
}

int integer_div_0(int dividend, int divisor)
{
	if(divisor == 0)
	{
		cout<<"非法参数，除零错"<<endl;
		exit(1);
	}

	int res = 0;
	while((dividend-=divisor)>=0)
		++res;

	return res;
}

//递归整数除法
int integer_div_1(unsigned int dividend, unsigned int divisor)
{
	if(divisor == 0)
	{
		cout<<"非法参数，除零错"<<endl;
		exit(1);
	}

	if(dividend < divisor) return 0;
	unsigned int k=0,c=divisor, res=0;
	
	for(;dividend>=c;c<<=1,k++)
		if(dividend-c < divisor)
			return 1<<k;

	return integer_div_1(dividend-(c>>1), divisor)+(1<<(k-1));
}

//非递归整数除法
int integer_div_2(unsigned int dividend, unsigned int divisor)
{
	if(divisor == 0)
	{
		cout<<"非法参数，除零错"<<endl;
		exit(1);
	}

	if(dividend < divisor) return 0;
	unsigned int k, c, res=0;

	while(dividend > divisor)
	{
		for(k=0,c=divisor;dividend>=c;c<<=1,k++)
		{
			if(dividend-c < divisor)
			{
				res += 1<<k;
				break;
			}		
		}
		if(dividend-c < divisor)
			break;

		res += 1<<(k-1);
		dividend -= c>>1;
	}

	return res;
}

//整数除法and取模，返回商和余数
pair<int,int> integer_div_3(unsigned int dividend, unsigned int divisor)
{
	if(divisor == 0)
	{
		cout<<"非法参数，除零错"<<endl;
		exit(1);
	}

	if(dividend < divisor) 
		return make_pair(0, dividend);
	unsigned int k, c, quotient=0, remainder;

	while(dividend > divisor)
	{
		for(k=0,c=divisor;dividend>=c;c<<=1,k++)
		{
			if(dividend-c < divisor)
			{
				quotient += 1<<k;
				remainder = dividend-c;
				break;
			}		
		}
		if(dividend-c < divisor)
			break;

		quotient += 1<<(k-1);
		dividend -= c>>1;
	}

	return make_pair(quotient, remainder);
}

//打印n的二进制表示
void print_bits(unsigned int n)
{
	bitset<32> bs(n);
	for(int i=bs.size()-1;i>=0;i--)
		cout<<bs.at(i);
	cout<<endl;
}

int main()
{
	unsigned int n,m;
	while(cin>>n>>m)
	{
		cout<<integer_div_3(n,m).first<<" "<<integer_div_3(n,m).second<<endl;
	}
	
	return 0;
}

