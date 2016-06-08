#pragma once

#include<memory>
#include<vector>


template<typename T>
struct HashNode
{
private:
	T key_;
	std::shared_ptr<HashNode<T>> next_;

public:
	HashNode() : key_(-1), next_(nullptr) {}
	HashNode(T key) : key_(key), next_(nullptr) {}
	HashNode(T key, std::shared_ptr<HashNode<T>> next_ptr) : key_(key), next_(next_ptr) {}

	std::shared_ptr<HashNode<T>> get_next() const { return next_; }
	T get_key() const { return key_; }

	void set_next(std::shared_ptr<HashNode<T>> next) {
		next_ = next;
	}

	void set_key(T key) {
		key_ = key;
	}

	template<typename T1>
	friend std::ostream & operator<<(std::ostream & os, HashNode<T1> const & node) {
		os << node.get_key() << ' ';
		return os;
	}
};


template<typename T>
class List
{
public:
	List();
	~List();

	bool is_empty() const { return root_ == nullptr; }

	void push_front(T key);
	bool is_find(T key) const;


	template<typename T1>
	friend std::ostream & operator<<(std::ostream & os, List<T1> const & list) {
		if (list.is_empty())
			os << '\n';
		else {
			std::shared_ptr<HashNode<T1>> cur_node = list.root_;
			std::cout << cur_node->get_key();
			cur_node = cur_node->get_next();
			while (cur_node) {
				os << " -> " << cur_node->get_key();
				cur_node = cur_node->get_next();
			}
			os << std::endl;
		}
		return os;
	}

private:
	size_t size_;
	std::shared_ptr<HashNode<T>> root_;
};


template<typename T>
size_t hash(T value, size_t hash_size) {
	return value % hash_size;
}


template<typename T>
class HashTable
{
public:
	HashTable(size_t size);
	~HashTable();

	size_t get_hash_size() const { return hash_size_; }

	void insert(T key);
	bool is_find(T key) const;

	template<typename T1>
	friend std::ostream & operator<<(std::ostream & os, HashTable<T1> const & hash) {
		for (auto id : hash.body_)
			os << id;
		return os;
	}
	
private:
	size_t hash_size_;
	std::vector<List<T>> body_;
};

#include"hash_table_impl.h"
