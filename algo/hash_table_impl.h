#pragma once

#include"hash_table.h"

// List methods

template<typename T>
List<T>::List() : size_(0), root_(nullptr) {}

template<typename T>
List<T>::~List() {}

template<typename T>
inline void List<T>::push_front(T key) {
	if (is_empty()) {
		root_ = std::make_shared<HashNode<T>>(HashNode<T>(key));
	}
	else {
		std::shared_ptr<HashNode<T>> node =
			std::make_shared<HashNode<T>>(HashNode<T>(key, root_->get_next()));
		root_->set_next(node);
	}
	++size_;
}

template<typename T>
inline bool List<T>::is_find(T key) const {
	if (is_empty())
		return false;
	else {
		std::shared_ptr<HashNode<T>> cur_ptr = root_;
		while (cur_ptr) {
			if (cur_ptr->get_key() == key)
				return true;
			else
				cur_ptr = cur_ptr->get_next();
		}
		return false;
	}	
}


// Hash table implementation

template<typename T>
HashTable<T>::HashTable(size_t size): hash_size_(size), body_(hash_size_) {}

template<typename T>
HashTable<T>::~HashTable() {}

template<typename T>
inline void HashTable<T>::insert(T key) {
	size_t id = hash(key, hash_size_);
	body_.at(id).push_front(key);
}

template<typename T>
inline bool HashTable<T>::is_find(T key) const {
	size_t id = hash(key, hash_size_);
	if (body_.at(id).is_find(key))
		return true;
	return false;
}
