#include <stdio.h>


bool queue[10001];           // 进程存在与否
bool reList[10001];            // 打印进程号
int i,maxCount,maxRemove; // 循环及输入
char cmd[2];                      //命令缓存
int arg;                                //命令参数
int curP;                              //当前状态
int remNo;                           // 删除个数

void init();
bool processCmd(char);
int findCurMax();
int findCurMin();

int main(){
    while(scanf("%d\n",&maxCount)==1){
		init();
		scanf("%d\n",&maxRemove);	
		for(i=0;i<maxRemove;i++){
                       int x;
                       scanf("%d",&x);
                       reList[x] = true;
                   }
		while(scanf("%s",cmd)==1 
                      &&processCmd(cmd[0]));
		printf("\n");
	}
	return 0;
}

void init(){
	for(i=0;i<10001;i++){
		reList[i]=false;
		queue[i]=false;
	}
	curP=1;
	remNo=0;
}

bool processCmd(char cmd){
    if(cmd == 'e') return false;
    if(cmd == 'p'){ scanf("%d",&arg); curP = curP % 2 +1; }
    else if(cmd == 'a'){ scanf("%d",&arg); queue[arg]=true; }
    else if(cmd == 'r'){ 
        remNo++;
        int tmp;
        if(curP==1)  tmp=findCurMin(); 
        else  tmp=findCurMax();
        queue[tmp] = false;
        if(reList[remNo]) printf("%d\n",tmp); 
    }
    return true;
}

int findCurMax(){
	for(i=10000;i>0;i--) 
                   if(queue[i]) return i;
	return -1;
}
int findCurMin(){
	for(i=0;i<10001;i++) 
                    if(queue[i]) return i;
	return -1;
}