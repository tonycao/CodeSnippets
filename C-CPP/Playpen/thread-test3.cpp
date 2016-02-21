#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

std::timed_mutex mutex;

struct Complex {
	//std::mutex mutex;
	std::recursive_mutex mutex;
	int i;

	Complex() : i(0) {}

	void mul(int x) {
		std::lock_guard<std::recursive_mutex> lock(mutex);
		i *= x;
	}

	void div(int x) {
		std::lock_guard<std::recursive_mutex> lock(mutex);
		i /= x;
	}

	void both(int x, int y) {
		std::lock_guard<std::recursive_mutex> lock(mutex);
		mul(x);
		div(y);
	}

};

void work(){
    std::chrono::milliseconds timeout(100);

    while(true){
        if(mutex.try_lock_for(timeout)){
            std::cout << std::this_thread::get_id() << ": do work with the mutex" << std::endl;

            std::chrono::milliseconds sleepDuration(250);
            std::this_thread::sleep_for(sleepDuration);

            mutex.unlock();

            std::this_thread::sleep_for(sleepDuration);
        } else {
            std::cout << std::this_thread::get_id() << ": do work without mutex" << std::endl;

            std::chrono::milliseconds sleepDuration(100);
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}

std::once_flag flag;
std::mutex mutex2;

void do_something(){
    std::call_once(flag, [](){std::cout << "Called once" << std::endl;});
    mutex2.lock();
    std::cout << "Called each time" << std::endl;
    mutex2.unlock();
}



int main(){
    //Complex complex;
    //complex.both(32, 23);

    //qreturn 0;

    //std::thread t1(work);
    //std::thread t2(work);

    //t1.join();
    //t2.join();

    std::thread t1(do_something);
    std::thread t2(do_something);
    std::thread t3(do_something);
    std::thread t4(do_something);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;

    return 0;
}
