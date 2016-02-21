#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


//http://www.careercup.com/question?id=5652784707796992
//write a multithreaded code with one thread printing all even numbers and the other all odd numbers. the output should always be in sequence i.e. 1,2,3,4,5
std::mutex mtx;
std::condition_variable cv;
bool doPrintOdd = false;
bool doPrintEven= true;
int nMax = 100;

void printOdd() {
	for (int i = 0; i < nMax; ++i) {
		std::unique_lock<std::mutex> lck(mtx);
		while (!doPrintOdd) cv.wait(lck);
		std::cout << 2 * i + 1 << std::endl;
		doPrintOdd = false;
		doPrintEven = true;
		cv.notify_one();
	}
}

void printEven() {
	for (int i = 0; i < nMax; ++i) {
		std::unique_lock<std::mutex> lck(mtx);
		while (!doPrintEven) cv.wait(lck);
		std::cout << 2 * i << std::endl;
		doPrintEven = false;
		doPrintOdd = true;
		cv.notify_one();
	}
}

int main() {
	std::thread t1(printOdd);
	std::thread t2(printEven);

	t1.join();
	t2.join();

	std::cout << "Press Enter to continue ..." << std::endl;
	std::cin.get();
	return 0;
}