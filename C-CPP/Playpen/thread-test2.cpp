#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

struct Counter {
	//std::mutex mutex;
    int value;

    Counter() : value(0){}

    void increment(){
    	//mutex.lock();
        ++value;
        //mutex.unlock();
    }

    void decrement(){
        if(value == 0){
            throw "Value cannot be less than 0";
        }

        --value;
    }
};

struct ConcurrentCounter {
    std::mutex mutex;
    Counter counter;

    void increment(){
        mutex.lock();
        counter.increment();
        mutex.unlock();
    }

    void decrement(){
        mutex.lock();
        //counter.decrement();        
        try {
        	counter.decrement();
    	} catch (std::string e){
        	mutex.unlock();
        	throw e;
    	}
        mutex.unlock();
    }
};

struct ConcurrentSafeCounter {
    std::mutex mutex;
    Counter counter;

    void increment(){
        std::lock_guard<std::mutex> guard(mutex);
        counter.increment();
    }

    void decrement(){
        std::lock_guard<std::mutex> guard(mutex);
        counter.decrement();
    }
};


int main(){
    ConcurrentCounter counter;

    std::vector<std::thread> threads;

    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread([&](){
            for(int i = 0; i < 100; ++i){
                counter.increment();
            }
        }));
    }

    for(auto& thread : threads){
        thread.join();
    }

    std::cout << counter.counter.value << std::endl;

    return 0;
}