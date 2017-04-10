#pragma once

#include"list.h"
#include<iostream>


template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() : size_(0), root_(nullptr), tail_(nullptr) {}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {}

template<typename T>
inline void DoubleLinkedList<T>::push_back(T key) {
	++size_;
	if (is_empty())
		root_ = std::make_shared<ListNode<T>>(ListNode<T>(key));
	else {
		std::shared_ptr<ListNode<T>> cur_ptr;
		if (tail_ == nullptr) {
			cur_ptr = root_;
			while (cur_ptr->next_)
				cur_ptr = cur_ptr->next_;
		}
		else
			cur_ptr = tail_;
		std::shared_ptr<ListNode<T>> temp_node = 
			std::make_shared<ListNode<T>>(ListNode<T>(nullptr, cur_ptr, key));
		cur_ptr->next_ = temp_node;
		tail_ = temp_node;
	}
}

template<typename T>
inline void DoubleLinkedList<T>::push_front(T key) {
	++size_;
	if (is_empty())
		root_ = std::make_shared<ListNode<T>>(ListNode<T>(key));
	else {
		std::shared_ptr<ListNode<T>> temp_ptr
			= std::make_shared<ListNode<T>>(ListNode<T>(root_,root_->next_,root_->key_));
		temp_ptr.swap(root_);
		root_->next_ = temp_ptr;
		root_->key_ = key;
	}
}

template<typename T>
inline T DoubleLinkedList<T>::pop_back() {
	if (is_empty()) {
		std::cout << "List is empty. There is nothing to delete. \n";
		return -1;
	}
	else if (tail_ == nullptr) {
		--size_;
		T result_to_return = root_->key_;
		root_ = nullptr;
		return result_to_return;
	}
	else {
		--size_;
		T result_to_return = tail_->key_;
		T value = tail_->prew_->key_;
		tail_->prew_ = tail_->prew_->prew_;
		tail_->prew_->next_ = tail_;
		tail_->key_ = value;
		return result_to_return;
	}
}

template<typename T>
inline T DoubleLinkedList<T>::pop_front() {
	if (is_empty()) {
		std::cout << "List is emplty. There is nothing to delete. \n";
		return -1; 
	}
	else if(tail_ == nullptr) {
		--size_;
		T result_to_return = root_->key_;
		root_ = nullptr;
		return result_to_return;
	}
	else {
		--size_;
		T result_to_return = root_->key_;
		T value = root_->next_->key_;
		root_->next_ = root_->next_->next_;
		root_->next_->prew_ = root_;
		root_->key_ = value;
		return result_to_return;
	}

}


template<typename T>
inline void DoubleLinkedList<T>::merge(DoubleLinkedList<T> & right) {
	if (is_empty()) {
		root_ = right.root_;
	}
	else if (!is_empty() && !right.is_empty()) {
		// place code here
		return;
	}
}

template<typename T>
inline void DoubleLinkedList<T>::display() const {
	std::shared_ptr<ListNode<T>> cur_ptr = root_;
	while (cur_ptr)	{
		std::cout << cur_ptr->key_ << ' ';
		cur_ptr = cur_ptr->next_;
	}
	std::cout << std::endl;
}
