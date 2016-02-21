#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


//http://www.careercup.com/question?id=5652784707796992
//write a multithreaded code with one thread printing all even numbers and the other all odd numbers. the output should always be in sequence i.e. 1,2,3,4,5
std::mutex mtx;
std::condition_variable cv;
bool first = true;
bool second= false;
bool third = false;
int nMax = 10;

void printfirst() {
	for (int i = 0; i < nMax; ++i) {
		std::unique_lock<std::mutex> lck(mtx);
		while (!first) cv.wait(lck);
		std::cout << 1 << std::endl;
		first = false;
		second = true;
		//third = false;
		cv.notify_one();
	}
}

void printsecond() {
	for (int i = 0; i < nMax; ++i) {
		std::unique_lock<std::mutex> lck(mtx);
		while (!second) cv.wait(lck);
		std::cout << 2 << std::endl;
		//first = false;
		second = false;
		third = true;
		cv.notify_one();
	}
}

void printthird() {
	for (int i = 0; i < nMax; ++i) {
		std::unique_lock<std::mutex> lck(mtx);
		while (!third) cv.wait(lck);
		std::cout << 3 << std::endl;
		first = true;
		//second = false;
		third = false;
		cv.notify_one();
	}
}

int main() {
	std::thread t1(printfirst);
	std::thread t2(printsecond);
	std::thread t3(printthird);

	t1.join();
	t2.join();
	t3.join();

	std::cout << "Press Enter to continue ..." << std::endl;
	std::cin.get();
	return 0;
}