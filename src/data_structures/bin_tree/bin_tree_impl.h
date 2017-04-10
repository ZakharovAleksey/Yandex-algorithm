#pragma once

#include<iostream>
#include"bin_tree.h"

template<typename T>
inline BinnaryTree<T>::BinnaryTree() : root_(nullptr) {}

template<typename T>
inline BinnaryTree<T>::BinnaryTree(T value) : root_(new Node<T>(value, nullptr, nullptr, nullptr)) {}

template<typename T>
BinnaryTree<T>::~BinnaryTree() {}

template<typename T>
inline void BinnaryTree<T>::insert(T const value){
	// Если вершина пустая то создаем вершину с данным значением аргумента
	if (root_ == nullptr) {
		root_ = new Node<T>(value, nullptr, nullptr, nullptr);
	}
	else {
		Node<T>* curr_node = root_;
		Node<T>* parent = curr_node;
		
		while (curr_node != nullptr)
		{
			parent = curr_node;
			if (value < curr_node->value_)
				curr_node = curr_node->left_;
			else
				curr_node = curr_node->right_;
		}

		if (parent->value_ > value)
			parent->left_ = new Node<T>(value, nullptr, nullptr, parent);
		else
			parent->right_ = new Node<T>(value, nullptr, nullptr, parent);
		std::cout << " insert " << value << " parent -> " << parent->value_ << '\n';
	}
}

template<typename T>
inline bool BinnaryTree<T>::find(T const value) const {
	Node<T>* curr_node = root_;

	if (is_empty()) {
		std::cout << "The tree is empty. \n";
		return false;
	}
	else {
		while (curr_node != nullptr) {
			if (value < curr_node->value_)
				curr_node = curr_node->left_;
			else if (value > curr_node->value_)
				curr_node = curr_node->right_;
			else if (value == curr_node->value_) {
				std::cout << "Find : " << value << " in tree.\n";
				return true;
			}
		}
		std::cout << "Not find : " << value << " in the tree.\n";
		return false;
	}
}

template<typename T>
inline T BinnaryTree<T>::remove(T const value)
{
	Node<T>* curr_node = root_;

	if (is_empty()) {
		std::cout << "The tree is empty. \n";
		return -1;
	}
	else {
		while (curr_node != nullptr) {
			if (value < curr_node->value_)
				curr_node = curr_node->left_;
			else if (value > curr_node->value_)
				curr_node = curr_node->right_;
			else if (value == curr_node->value_) {
				std::cout << "Find : " << value << " in tree.\n";

				// Если вершина лист
				if (curr_node->left_ == nullptr && curr_node->right_ == nullptr) {
					if (curr_node->parent_ != nullptr && curr_node->parent_->left_ == curr_node) {
						Node<T>* parent = curr_node->parent_;
						parent->left_ = nullptr;
					}
					else if (curr_node->parent_ != nullptr && curr_node->parent_->right_ == curr_node) {
						Node<T>* parent = curr_node->parent_;
						parent->right_ = nullptr;
					}
					else
						root_ = nullptr;
					return value;
				}
				// Если у вершины есть левое поддерево, но нет правого
				else if (curr_node->left_ != nullptr && curr_node->right_ == nullptr) {
					if (curr_node->parent_->right_ == curr_node) {
						Node<T>* parent = curr_node->parent_;
						parent->right_ = curr_node->left_;
						curr_node->left_->parent_ = parent;
						
						delete curr_node;
						return value;
					}
					else if (curr_node->parent_->left_ == curr_node) {
						Node<T>* parent = curr_node->parent_;
						parent->left_ = curr_node->left_;
						curr_node->left_->parent_ = parent;

						delete curr_node;
						return value;
					}
				}
				// Если у вершины есть правое поддерево, но нет левого
				else if (curr_node->right_ != nullptr && curr_node->left_ == nullptr) {
					if (curr_node->parent_->right_ == curr_node) {
						Node<T>* parent = curr_node->parent_;
						parent->right_ = curr_node->right_;
						curr_node->right_->parent_ = parent;

						delete curr_node;
						return value;
					}
					else if (curr_node->parent_->left_ == curr_node) {
						Node<T>* parent = curr_node->parent_;
						parent->left_ = curr_node->right_;
						curr_node->right_->parent_ = parent;

						delete curr_node;
						return value;
					}
				}
				// Если вершина имеет правое и левое поддерево
				else if(curr_node->left_ != nullptr, curr_node->right_ != nullptr){
					Node<T>* parent = curr_node->parent_;
					Node<T>* succesor;
					Node<T>* left_son_new;
					Node<T>* curr_node_new = curr_node;

					// Находим sucsessor - крайний левый элемент правого поддерева (к нему будем целять cur->left)
					if (curr_node_new->right_ != nullptr) {
						curr_node_new = curr_node_new->right_;
						while (curr_node_new->left_ != nullptr)
							curr_node_new = curr_node_new->left_;
					}
					succesor = curr_node_new;

					// Определяем левого сына, который будем цеплять к sucsessor (раньше был левым сыном cur)
					left_son_new = curr_node->left_;
					left_son_new->parent_ = curr_node->right_;

					// Определяем что правый сын удаляемого элемента встанет на его место
					if (curr_node->parent_->right_ == curr_node)
						parent->right_ = curr_node->right_;

					else if (curr_node->parent_->left_ == curr_node)
						parent->left_ = curr_node->right_;

					curr_node->right_->parent_ = parent;

					succesor->left_ = left_son_new;
					succesor->right_ = nullptr;

					return value;
				}
			}
		}
		std::cout << "Not find : " << value << " in the tree.\n";
		return -1;
	}
}

// Можно чтобы возвращал Node<T>* тогда будет легче переписываться remove()
template<typename T>
inline T BinnaryTree<T>::successor(T const value) const {
	Node<T>* curr_node = root_;

	if (is_empty()) {
		std::cout << "The tree is empty. \n";
		return -1;
	}
	else {
		while (curr_node != nullptr) {
			if (value < curr_node->value_)
				curr_node = curr_node->left_;
			else if (value > curr_node->value_)
				curr_node = curr_node->right_;
			else if (value == curr_node->value_) {

				// Если есть наследник справа
				if (curr_node->right_ != nullptr) {
					curr_node = curr_node->right_;
					while (curr_node->left_ != nullptr)
						curr_node = curr_node->left_;
					return curr_node->value_;
				}

				// Если его нет, то идем наверх
				else if (curr_node->parent_ != nullptr) {
					while (curr_node->parent_ != nullptr && curr_node->parent_->right_ == curr_node)
						curr_node = curr_node->parent_;
					if (curr_node->parent_ != nullptr && curr_node->parent_->left_ == curr_node) {
						curr_node = curr_node->parent_;
						return curr_node->value_;
					}
					else
						return -1;
				}
				else
					return -1;
			}
		}
		std::cout << "Not find : " << value << " in the tree.\n";
		return -1;
	}
}

template<typename T>
inline T BinnaryTree<T>::predecessor(T const value) const
{
	Node<T>* curr_node = root_;

	if (is_empty()) {
		std::cout << "The tree is empty. \n";
		return -1;
	}
	else {
		while (curr_node != nullptr) {
			if (value < curr_node->value_)
				curr_node = curr_node->left_;
			else if (value > curr_node->value_)
				curr_node = curr_node->right_;
			else if (value == curr_node->value_) {

				// Если есть наследник слева
				if (curr_node->left_ != nullptr) {
					curr_node = curr_node->left_;
					while (curr_node->right_ != nullptr)
						curr_node = curr_node->right_;
					return curr_node->value_;
				}

				// Если его нет, то идем наверх
				else if (curr_node->parent_ != nullptr) {
					while (curr_node->parent_ != nullptr && curr_node->parent_->left_ == curr_node)
						curr_node = curr_node->parent_;
					if (curr_node->parent_ != nullptr && curr_node->parent_->right_ == curr_node) {
						curr_node = curr_node->parent_;
						return curr_node->value_;
					}
					else
						return -1;
				}
				else
					return -1;
			}
		}
		std::cout << "Not find : " << value << " in the tree.\n";
		return -1;
	}
}

template<typename T>
inline void BinnaryTree<T>::visit(Node<T>* node) const {
	// pre-order 
	// std::cout << node->value_ << ' ';
	if (node->left_ != nullptr)
		visit(node->left_);
	// in-order обход (при нем все ключи должны быть выведены в неубывающем порядке)
	if(node->parent_ != nullptr)
		std::cout << node->value_  << "(" << node->parent_->value_ << ") " << ' ';
	if(node->parent_ == nullptr)
		std::cout << node->value_ << "( root ) " << ' ';
	if (node->right_ != nullptr)
		visit(node->right_);
	// post-order
	// std::cout << node->value_ << ' ';
}

template<typename T>
inline void BinnaryTree<T>::display() const {
	visit(root_);
	std::cout << std::endl;
}
