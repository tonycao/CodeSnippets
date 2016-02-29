#include <stdio.h>
#include <iostream>

#define n 6

int rock[n];
bool opt[60000];
bool print;
int mid;
int r;

void init()
{
	int i;
	mid = 0;
	print = true;
	//printf("%d", mid);
	for( i = 1; i <= n; i++)
	{
		scanf("%d",&rock[i]);
		mid = mid + rock[i] * i;
		//printf("%d\n", mid);
		if(!(mid % 2))
			print = false;		
	}
	
}

bool bk(){
	for(int i=1;i<=6;i++){
		if(rock[i]!=0)return false;
	}
	return true;
}
/*int min(int a, int b)
{
	if( a < b)
		return a;
	else
		return b;		
}*/

bool dp()
{
	int max;
	int i;
	int j, k;
	memset( opt, false, sizeof(opt));
	opt[0] = true;
	max = 0;
	print = true;
	for( i = 1; i <= n; i++)
	{
		if(rock[i])
		{
			for( j = max; j >= 0; j--)
			{
				if(opt[j])
				{
					if(opt[mid])
					{
						//printf("Can be divided./n");
						//print = true;
						return true;
					}
					for( k = 1; k <= rock[i]; k++)
					{
						if((j + k * i) > mid || opt[j + k * i] )
							break;
						opt[j + k * i] = true;
						
					}
				}
			}
		}
		max = max + i * rock[i];
		if( max > mid) max = mid;
	}
	return false;
}

int main()
{
	init();
	r = 0;
	while(1)
	{	
		if(bk()) break;
		++r;
		printf("Collection #%d:\n", r, ':');
		if((!(mid%2)) && (!print))
		{
			mid = mid / 2;
			print = dp();
			if(!print)
				printf("Can't be divided.\n");	
			else
				printf("Can be divided.\n");
		}
		else
		{
			if(print)
				printf("Can be divided.\n");
			else
				printf("Can't be divided.\n");
		}
		init();
	}
	return 0;
}
