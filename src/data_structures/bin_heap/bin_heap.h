#pragma once

#include<vector>

template<typename T>
class BinHeap
{
private:
	size_t sift_up();
	size_t sift_down();
public:
	BinHeap();
	BinHeap(T value);
	BinHeap(std::vector<T> & body);
	~BinHeap();

	size_t insert(T value);
	T extract_min();

	bool is_empty() const {
		return size_ == 0;
	}
	size_t get_heap_size() const {
		return size_;
	}

	void display() const;

private:
	size_t size_;
	std::vector<T> body_;	
};

#include"bin_heap_impl.h"
