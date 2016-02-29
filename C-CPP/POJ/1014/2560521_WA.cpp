#include<iostream>
void print(int id,int isOK){
	if(isOK==1)
		printf("Collection #%d:\nCan be divided.\n\n",id);
	else printf("Collection #%d:\nCan't be divided.\n\n",id);
}
int main(){
	int sum,i,j,k,a[7],time,temp;
	char f[7][10001];
	
	sum=0;
	memset(a,0,sizeof(a));
	for(i=1;i<=6;i++){
		scanf("%d",&a[i]);
		sum+=i*a[i]/30;
	}
	time=1;
	while(sum>0){
		if(sum&1) print(time,0);
		else {
			sum=sum/2;
			memset(f,0,sizeof(f));
			for(i=0;i<=6;i++) f[i][0]=1;
			for(i=1;i<=6;i++)
				for(j=1;j<=sum;j++)
					if(f[i-1][j]==1) f[i][j]=1;
					else for(k=1;k<=a[i];k++)
						if(f[i-1][j-k*i]==1&&j-i*k>=0)
							f[i][j]=1;
			temp=0;
			for(i=1;i<=6;i++)
				if(f[i][sum]==1){
					temp=1;
					break;
				}
			print(time,temp);
		}
		sum=0;
		memset(a,0,sizeof(a));
		for(i=1;i<=6;i++){
			scanf("%d",&a[i]);
			sum+=i*a[i];
		}
		time++;
		
	}
	return 0;
}