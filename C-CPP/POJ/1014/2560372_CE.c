#include <iostream>
#include <fstream>
using namespace std;

int n[10];
int allnum[10000];
int mark[100];
int an;

bool findn(int cur){
	if(cur==0)return true;
	else{
		for(int i=2;i<an;i++){
			if(mark[i]==0&&allnum[i]<=cur){
				mark[i]=1;
				int sum=cur-allnum[i];
				if(findn(sum))return true;
				mark[i]=0;
			}
		}
	}
	return false;
}

bool compute(){
	memset(allnum,0,sizeof(allnum));
	an=1;

	int sum=0;
	for(int j=1;j<=6;j++){
		for(int k=1;k<=n[j];k++){
			allnum[an++]=j;
			sum+=j;
		}
	}
	if(sum%2==1)return false;
	int half=sum/2;
	memset(mark,0,sizeof(mark));
	mark[1]=1;
	return findn(half-allnum[1]);
}
//判断结束 
bool bk(){
	for(int i=1;i<=6;i++){
		if(n[i]!=0)return false;
	}
	return true;
}

int main(){
	int testcase=1;
	while(1){
		for(int i=1;i<=6;i++){
			cin>>n[i];
		}
		n[1]=n[1]%12;//数学公式.
		if(n[2]>4)n[2]=4-n[2]%2;
		if(n[3]>5)n[3]=4+n[3]%2;
		if(n[4]>5)n[4]=4+n[4]%2;
		if(n[5]>6)n[5]=6-n[5]%2;
		if(n[6]>5)n[6]=4+n[6]%2;


		if(bk())break;
		cout<<"Collection #"<<testcase++<<":"<<endl;
		if(compute())cout<<"Can be divided."<<endl;
		else cout<<"Can't be divided."<<endl;
		cout<<endl;
	}
	return 0;
}