#pragma once

#include<memory>

template<typename T>
struct ListNode
{
	ListNode() : next_(nullptr), prew_(nullptr), key_(0) {}
	ListNode(T key) : next_(nullptr), prew_(nullptr), key_(key) {}
	ListNode(std::shared_ptr<ListNode> next, std::shared_ptr<ListNode> prew, T key) : next_(next), prew_(prew), key_(key) {}

	std::shared_ptr<ListNode> next_;
	std::shared_ptr<ListNode> prew_;
	T key_;
};

template<typename T>
class DoubleLinkedList
{
public:
	DoubleLinkedList();
	~DoubleLinkedList();

	bool is_empty() const { return root_ == nullptr; }

	void push_back(T key);
	void push_front(T key);

	T pop_back();
	T pop_front();

	size_t size() const { return size_; }

	void merge(DoubleLinkedList<T> & right);
	void display() const;
private:
	size_t size_;
	std::shared_ptr<ListNode<T>> root_;
	std::shared_ptr<ListNode<T>> tail_;
};

#include"list_impl.h"
