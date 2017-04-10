#pragma once

#include"bin_heap.h"

#include<iostream>
#include<cmath>

template<typename T>
BinHeap<T>::BinHeap() : size_(0), body_(0) {}

template<typename T>
inline BinHeap<T>::BinHeap(T value) : size_(1) {
	body_.push_back(value);
}

template<typename T>
inline BinHeap<T>::BinHeap(std::vector<T> & body) : size_(body.size()), body_(body) {
	for (size_t i = body_.size() / 2 - 1; i != -1; --i) {
		size_t id = i;
		while (id < size_ / 2)
		{
			size_t left_id = 2 * id + 1;
			size_t min_id = left_id;
			if (2 * id + 2 < size_ && body_.at(left_id) > body_.at(left_id + 1))
				++min_id;
			std::swap(body_.at(id), body_.at(min_id));
			id = min_id;
		}
	}
}

template<typename T>
BinHeap<T>::~BinHeap() {}


template<typename T>
inline size_t BinHeap<T>::sift_up() {	
	size_t cur_id = size_ - 1;
	size_t parent_id = floor((cur_id - 1) / 2);
	while (parent_id >= 0 && body_.at(parent_id) > body_.at(cur_id)) {
		std::swap(body_.at(parent_id),body_.at(cur_id));
		cur_id = parent_id;
		parent_id = (cur_id == 0) ? 0 : floor((cur_id - 1) / 2);
	}
	return cur_id;
}

template<typename T>
inline size_t BinHeap<T>::sift_down() {
	size_t cur_id = 0;
	if (size_ == 1)
		return cur_id;
	else if (size_ == 2) {
		if (body_.at(1) < body_.at(0)) {
			std::swap(body_.at(1), body_.at(0));
			return cur_id + 1;
		}
		return cur_id;
	}
	else if (size_ >= 3) {
		size_t child_id = (body_.at(2 * cur_id + 1) < body_.at(2 * cur_id + 2)) ? 2 * cur_id + 1 : 2 * cur_id + 2;
		while (child_id < body_.size() - 1 && body_.at(cur_id) > body_.at(child_id)) {
			std::swap(body_.at(cur_id), body_.at(child_id));
			cur_id = child_id;
			if (2 * cur_id + 2 < body_.size() - 1)
				child_id = (body_.at(2 * cur_id + 1) < body_.at(2 * cur_id + 2)) ? 2 * cur_id + 1 : 2 * cur_id + 2;
			else
				return cur_id;
		}
		return cur_id;
	}
}



template<typename T>
inline size_t BinHeap<T>::insert(T value)
{
	body_.push_back(value);
	++size_;
	size_t result_id = sift_up();
	//return result_id;
	return sift_up();
}

//template<typename T>
//inline T BinHeap<T>::remove(size_t index)
//{
//	
//}


template<typename T>
inline T BinHeap<T>::extract_min()
{
	std::swap(body_.at(0), body_.at(--size_));
	sift_down();
	T res = body_.at(size_);
	body_.pop_back();
	return res;
}

template<typename T>
inline void BinHeap<T>::display() const {
	for (auto i : body_)
		std::cout << i << ' ';
	std::cout << std::endl;
}
