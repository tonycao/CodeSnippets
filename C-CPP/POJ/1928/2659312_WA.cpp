#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct pea
{
	int x,y;
	int amount;
	pea(int i,int j,int t):x(i),y(j),amount(t){}
};
bool cmp(pea a,pea b)
{
	return a.amount>b.amount;
}
int k;
vector<pea> vp;
void input()
{
	int i,j,m,n,t;
	cin>>m>>n>>k;
	for (i=0;i<m;i++)
	{
		for (j=0;j<n;j++)
		{
			cin>>t;
			if (t!=0)	
			{
				vp.push_back(pea(j,i,t));
			}
		}
	}
	sort(vp.begin(),vp.end(),cmp);
}	
 int MTdist(int a,int b,int c,int d)
{	
	return (a>b?(a-b):(b-a))+(c>d?(c-d):(d-c));
}
int solve()
{
	int tmCost=0;
	vector<pea>::iterator pos=vp.begin();
	int currX=pos->x,currY=-1;
	int nuts=0;	
	for (;pos!=vp.end();++pos)
	{
		int t;
		t=MTdist(int(currX),int(currY),int(pos->x),int(pos->y));
		if ((tmCost+t+1+pos->y+1)<=k)
		{
			tmCost=tmCost+t+1;
			currX=pos->x;
			currY=pos->y;
			nuts+=pos->amount;
		}
		else
			break;
	}
	return nuts;
}



int main()
{
	int testCase;
	cin>>testCase;
	while (testCase--)
	{         
		input();
		cout<<solve()<<endl;
        vp.erase(vp.begin(),vp.end());	
	}
	return 0;
}

