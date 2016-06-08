#pragma once

#include<vector>

template<typename T>
struct Node
{
	T value_;
	Node* left_;
	Node* right_;
	Node* parent_;

	Node() : value(0), left(nullptr), right(nullptr), parent_(nullptr) {}
	Node(T const value, Node* left, Node* right, Node* parent) : value_(value), left_(left), right_(right), parent_(parent) {}

};


template<typename T>
class BinnaryTree
{
private:
	void visit(Node<T>* node) const;
public:
	BinnaryTree();
	BinnaryTree(T value);
	~BinnaryTree();

	bool is_empty() const {
		return root_ == nullptr;
	}

	void insert(T const value);
	bool find(T const value) const;
	T remove(T const value);

	T successor(T const value) const;
	T predecessor(T const value) const;

	void display() const;
private:
	Node<T>* root_;
};


#include"bin_tree_impl.h"
