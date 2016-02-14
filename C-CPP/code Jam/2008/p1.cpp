#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE(X) ((int)(X.size()))//NOTES:SIZE(
#define LENGTH(X) ((int)(X.length()))//NOTES:LENGTH(
#define MP(X,Y) make_pair(X,Y)//NOTES:MP(
typedef long long int64;//NOTES:int64
typedef unsigned long long uint64;//NOTES:uint64
#define two(X) (1<<(X))//NOTES:two(
#define twoL(X) (((int64)(1))<<(X))//NOTES:twoL(
#define contain(S,X) (((S)&two(X))!=0)//NOTES:contain(
#define containL(S,X) (((S)&twoL(X))!=0)//NOTES:containL(
const double pi=acos(-1.0);//NOTES:pi
const double eps=1e-11;//NOTES:eps
template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}//NOTES:checkmin(
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}//NOTES:checkmax(

const int maxsize=2000+5;

int n,m;
map<string,int> M;
int f0[maxsize],f1[maxsize];

int main()
{
	freopen("..\\A-small-attempt3.in","r",stdin);
	freopen("..\\A-small-attempt3.out","w",stdout);
	int testcase;
	scanf("%d",&testcase);
	for (int caseId=1;caseId<=testcase;caseId++)
	{
		M.clear();
		scanf("%d",&n);
		char buf[1024];
		gets(buf);
		for (int i=0;i<n;i++)
		{
			gets(buf);
			M[buf]=i;
		}
		scanf("%d",&m);
		gets(buf);
		for (int i=0;i<n;i++) f0[i]=0;
		for (int T=0;T<m;T++)
		{
			gets(buf);
			int key=M[buf];
			for (int i=0;i<n;i++) 
			{
				f1[i]=10000000;
				if (i==key) continue;
				for (int j=0;j<n;j++) checkmin(f1[i],f0[j]+(int)(i!=j));
			}
			for (int i=0;i<n;i++) f0[i]=f1[i];
		}
		int result=10000000;
		for (int i=0;i<n;i++) checkmin(result,f0[i]);
		printf("Case #%d: %d\n",caseId,result);
	}
	return 0;
}