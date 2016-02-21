//
//  TFRingBuffer.h
//
//  Created by Tom Fewster on 25/01/2013.
//

#ifndef TFRingBuffer_h
#define TFRingBuffer_h

#include <iostream>
#include <atomic>
#include <iterator>
#include <cstddef>

template <typename T>
class TFRingBuffer {
	T *buffer_;
	std::atomic<size_t> head_;
	std::atomic<size_t> tail_;
	std::atomic<size_t> content_size_;
	const size_t buffer_size_;

	size_t next(size_t current) {
		return (current + 1) % buffer_size_;
	}

	void increment_tail() {
		++tail_;
		++content_size_;
		if (tail_ == buffer_size_) tail_ = 0; // tail_ = tail % buffer_size_;
	}

	void increment_head() {
		++head_;
		--content_size_;
		if (head_ == buffer_size_) head_ = 0; // head_ = head % buffer_size_;
	}
public:
	//typedef TFRingBuffer_iterator self_type;
	//TFRingBuffer_iterator<self_type> iterator;
	typedef size_t size_type;
	typedef T value_type;
	class TFRingBuffer_iterator {
	public:

		typedef TFRingBuffer_iterator self_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef std::bidirectional_iterator_tag iterator_category; // forward_iterator_tag
		typedef int difference_type;
		//typedef TFRingBuffer_iterator<self_type> iterator;
		TFRingBuffer_iterator(pointer b, size_type p) : buffer_(b), pos_(p) {
			//std::cout << p << std::endl;
		}

		reference operator*(){ return (buffer_[pos_]); }
		pointer operator->() { return &(operator*()); }
		self_type operator++() { 
			++pos_; return *this; 
		}
		self_type operator++(int) {
			self_type tmp(*this);
			++(*this);
			return tmp;
		}
		self_type &operator--() {}
		self_type operator--(int) {}
		self_type operator+(difference_type n) {
			self_type tmp(*this);
			tmp.pos_ += n;
			return tmp;
		}
		self_type &operator+=(difference_type n) {
			pos_ += n;
			return *this;
		}
		self_type operator-(difference_type n) {}
		self_type &operator-=(difference_type n) {}
		bool operator==(const self_type &other) const { return pos_ == other.pos_; }
		bool operator!=(const self_type &other) const { 
			return pos_ != other.pos_;
		}



	private:
		pointer buffer_;
		size_type pos_;
	};

	class const_TFRingBuffer_iterator {
	public:

		typedef const_TFRingBuffer_iterator self_type;
		typedef T value_type;
		
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef std::bidirectional_iterator_tag iterator_category; // forward_iterator_tag
		typedef int difference_type;
		//typedef TFRingBuffer_iterator<self_type> iterator;
		const_TFRingBuffer_iterator(pointer b, size_type p) : buffer_(b), pos_(p) {}

		reference operator*(){ return (buffer_[pos_]);}
		pointer operator->() { return &(operator*());}
		self_type operator++() { 
			++pos_; return *this; 
		}
		self_type operator++(int) {
			self_type tmp(*this);
			++(*this);
			return tmp;
		}
		self_type &operator--() {}
		self_type operator--(int) {}
		self_type operator+(difference_type n) {
			self_type tmp(*this);
			tmp.pos_ += n;
			return tmp;
		}
		self_type &operator+=(difference_type n) {
			pos_ += n;
			return *this;
		}
		self_type operator-(difference_type n) {}
		self_type &operator-=(difference_type n) {}
		bool operator==(const self_type &other) const { return pos_ == other.pos_; }
		bool operator!=(const self_type &other) const { 
			std::cout << pos_ << std::endl;
			std::cout << other.pos_ << std::endl;
			return pos_ != other.pos_; 
		}



	private:
		pointer buffer_;
		size_type pos_;
	};




	TFRingBuffer_iterator begin() {
		//cout << head_ << endl;
		return TFRingBuffer_iterator(buffer_, 0);
	}

	TFRingBuffer_iterator end() {
		return TFRingBuffer_iterator(buffer_, size());
	}


	explicit TFRingBuffer(const size_t size) : buffer_size_(size), head_(0), tail_(0), content_size_(0) {
		buffer_ = new T[size];
	}

	~TFRingBuffer() {
		delete [] buffer_;
	}

	T& front() {
		return buffer_[head_];
	}

	const T& front() const {
		return buffer_[head_];
	}

	T& back() {
		return buffer_[tail_];
	}

	const T& back() const {
		return buffer_[tail_];
	}


	void push_back(const T &object) {
		if (!content_size_) {
			buffer_[head_] = object;
			size_t head = head_.load(std::memory_order_relaxed);
			tail_.store(head, std::memory_order_release);
			++content_size_;
		} else {
			increment_tail();
			if (content_size_ == buffer_size_ + 1)
				increment_head(); // buffer is full, write the oldest data

			buffer_[tail_] = object;
		}


		//size_t head = m_head.load(std::memory_order_relaxed);
		//size_t nextHead = next(head);
		//if (nextHead == m_tail.load(std::memory_order_acquire)) {
		//	return false;
		//}
		//m_buffer[head] = object;
		//m_head.store(nextHead, std::memory_order_release);

		//return true;
	}

	void pop_front() {
		increment_head();
	}

	size_t size() const {
		return content_size_;
	}

	size_t capacity() const {
		return buffer_size_;
	}

	bool empty() const {
		return content_size_ == 0;
	}

	void clear() {
		head_ =  tail_ = content_size_ = 0;
	}

	// random access
	T& operator[](size_t rhs) {
		return buffer_[(head_ + rhs) % buffer_size_];
	}

	const T& operator[](size_t rhs) const {
		return buffer_[(head_ + rhs) % buffer_size_];
	}

	T& at(size_t rhs) {
		return buffer_[(head_ + rhs) % buffer_size_];
	}

	const T& at(size_t rhs) const {
		return buffer_[(head_ + rhs) % buffer_size_];
	}

};

#endif