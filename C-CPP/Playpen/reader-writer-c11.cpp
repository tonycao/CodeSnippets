#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx-reader;
std::mutex mtx-writer;
//bool wrt = true;
int readercount = 0;
std::condition_variable cv;

void writer() {
	std::unique_lock<std::mutex> lck(mtx-writer);
	while (readercount) cv.wait(lck);
	//wrt = false;
	cout << " writing ... " << endl;
	cv.notify_one();
}

void reader() {
	mtx-reader.lock();
	readercount++;
	std::unique_lock<std::mutex> lck(mtx-writer);
	if (readercount == 5) cv.wait(lck);
	mtx-reader.unlock();

	cout << " reading ... " << endl;

	mtx-reader.lock();
	readercount--;
	if (readercount == 0) {
		//wrt = true;
		cv.notefy_one();
	}
	mtx-reader.unlock();
}
//

semaphore mutex = 1;
semaphore wrt = 1;
int readcount = 0;

writer() {
	P(wrt);
	do_write();
	V(wrt);
}


Reader(){ 
	P(mutex);
	readcount++;
	if (readcount == 5) {
		P(wrt);
	}
	V(mutex);
	do_read();
	P(mutex);
	readcount--;
	if(readcount == 0) {
		V(wrt);
	}
	V(mutex);

}
 //
std::atomic<int> readers;
std::mutex write;

// One write, no reads.
void write_fun()
{
    write.lock();// We lock the resource
    while(readers > 0){}// We wait till everyone finishes read.
    // DO WRITE
    write.unlock();// Release
}

// Multiple reads, no write
void read_fun()
{
    // We wait if it is being written.
    write.lock();
    readers++;
    write.unlock();

    // do read
    readers--;
}