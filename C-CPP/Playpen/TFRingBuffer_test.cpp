#include "TFRingBuffer.h"
#include <iostream>

using namespace std;

int main() {
	TFRingBuffer<int> ringbuffer(10);
	for (int i = 1; i <= 10; i++) {
		ringbuffer.push_back(i);
		cout << ringbuffer.back() << " ";
	}

	cout << endl;

	//cout << ringbuffer.size() << endl << endl;
	//cout << ringbuffer.capacity() << endl << endl;

	ringbuffer.push_back(11);
	ringbuffer.push_back(12);
	ringbuffer.pop_front();
	ringbuffer.pop_front();

	//cout << ringbuffer.size() << endl << endl;
	//cout << ringbuffer.capacity() << endl << endl;

	ringbuffer.push_back(13);
	ringbuffer.push_back(14);
	ringbuffer.push_back(15);

	//cout << ringbuffer.size() << endl << endl;
	//cout << ringbuffer.capacity() << endl << endl;
	for (TFRingBuffer<int>::TFRingBuffer_iterator it = ringbuffer.begin(); it != ringbuffer.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	while(!ringbuffer.empty()) { // ringbuffer.size() > 0) {
		//cout << ringbuffer.size() << endl;
		//cout << ringbuffer.front() << endl;
		cout << ringbuffer[0] << " "; 
		ringbuffer.pop_front();
	}
	cout << endl;
	//for (int i = 0; i < 10; i++) 
	//	ringbuffer.push_back(i);

	//ringbuffer.pop();
	//ringbuffer.pop();

	//for (int i = 0; i < ringbuffer.size(); i++) {
	//	cout << *ringbuffer.front() << endl;
	//	ringbuffer.pop();
	//}


}