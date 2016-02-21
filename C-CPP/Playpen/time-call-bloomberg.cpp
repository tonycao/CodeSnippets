#include <iostream>
#include <queue>
#include <ctime>
#include <thread>
#include <chrono>

//写一个函数，10秒内如果该函数被调用了至少十次就返回true，否则false 
/*
80.有一个函数，如果这个函数一分钟之内被call了大于5次，输入一个warning~~；

写一个函数，10秒内如果该函数被调用了至少十次就返回true，否则false 假如已经有了timestamp的函数，
那么就是建一个长度为5的queue，里面存每次call的时间，每call一次，把queue的第一次call的时间相比较，
看是不是在60秒以内，是的话就输出warning。然后把queue top() pop出去，把最近call的push进去，
就可以了~~还要注意初始时候queue小于5的处理~~ 
时间boundary为T，次数为>K
que.push(currTime)
while (que.front() + T < currTime) que.pop();
if(que.size() > k) "warning"
*/

using namespace std;

queue<time_t> fooqueue;

bool foo() {
	time_t currtime;
	time(&currtime);
	fooqueue.push(currtime);
	
	while (difftime(currtime, fooqueue.front()) > 1) {
		//cout << "difftime " << difftime(currtime, fooqueue.front()) << endl;
		fooqueue.pop();
	}
	if (fooqueue.size() > 10) return true;
	else return false;
}

int main() {
	for (int i = 0; i < 100; i++) {
		this_thread::sleep_for(std::chrono::milliseconds(i*10));
		cout << i << " " << foo()<< endl;
	}
	return 0;
}