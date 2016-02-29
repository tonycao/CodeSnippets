#include<iostream>
using namespace std;

int main(){
	long int m;
	cin>>m;
	long int a[100000][8];  //a[][7]表示该号码出现的次数
	char b;
	for(long int i=0; i<100000; i++)
		a[i][7]=1;
	for(long int j=0; j<m; j++){      //数据录入
		for(int k=0; k<7; k++){
				cin>>b;
				switch(b){
					case'0':a[j][k]=0;break;
					case'1':a[j][k]=1;break;
					case'2':
					case'A':
					case'B':
					case'C':a[j][k]=2;break;
					case'3':
					case'D':
					case'E':
					case'F':a[j][k]=3;break;
					case'4':
					case'G':
					case'H':
					case'I':a[j][k]=4;break;
					case'5':
					case'J':
					case'K':
					case'L':a[j][k]=5;break;
					case'6':
					case'M':
					case'N':
					case'O':a[j][k]=6;break;
					case'7':
					case'P':
					case'R':
					case'S':a[j][k]=7;break;
					case'8':
					case'T':
					case'U':
					case'V':a[j][k]=8;break;
					case'9':
					case'W':
					case'X':
					case'Y':a[j][k]=9;break;
					default:k--;break;
			}
		}
	}
	for(long int i1=0; i1<m-1; i1++){     //一对相等号码：前一个a[][7]++,后一个全部置0
		if(a[i1][7]==0)
			continue;
		for(long int j=i1+1; j<m; j++){
			if(a[j][7]==0)
				continue;
			for(int k=0; k<7; k++){
				if(a[i1][k]!=a[j][k])
					break;
				if(k==6){
					a[i1][7]++;
					for(int l=0; l<=7; l++)
						a[j][l]=0;
				}
			}
		}
	}
	for(long int i4=0; i4<m-1; i4++)                  //对数组冒泡排序
		for(long int j=0; j<m-1-i4; j++)
			for(int k=0; k<7; k++){
				if(a[j][k]==a[j+1][k])
					continue;
				else if(a[j][k]<a[j+1][k])
					break;
				else{
					for(int l=0, c; l<=7; l++){
						c=a[j][l];
						a[j][l]=a[j+1][l];
					    a[j+1][l]=c;
					}
					break;
				}
			}
	int x=0;
	for(long int i3=0; i3<m; i3++)             //输出
		if(a[i3][7]<2)
			continue;
		else{
			for(int j=0; j<3; j++)
				cout<<a[i3][j];
			cout<<"-";
			for(int k=3; k<7; k++)
				cout<<a[i3][k];
			cout<<ends;
			cout<<a[i3][7];
			cout<<endl;
			x++;
		}
	if(x==0)
		cout<<"No duplicates."<<endl;
	return 0;

}
