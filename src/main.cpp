#include<iostream>

#include<cstdlib>
#include<ctime>

//#include"3_search\part_three.h"


#include <iostream>

template<typename T>
struct Node
{
	T value;

	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;

	Node() : value(T()), left(NULL), right(NULL), parent(NULL) {}
	Node(const T value) : value(value), left(NULL), right(NULL), parent(NULL) {}
	Node(const T value, Node<T>* parent) : value(value), left(NULL), right(NULL), parent(parent) {}
};

template<typename T>
class MySplayTree
{
public:
	MySplayTree() : root_(NULL) {}

	void Insert(const T value)
	{
		if (root_ == NULL)
			root_ = new Node<T>(value);
		else
		{
			Node<T>* cur = root_;
			Node<T>* parent = NULL;
			while (cur)
			{
				parent = cur;
				if (value < cur->value)
					cur = cur->left;
				else if (value > cur->value)
					cur = cur->right;
				else
					return;
			}

			if (value < parent->value)
			{
				parent->left = new Node<T>(value, parent);
				Splay(parent->left);
			}
			else
			{
				parent->right = new Node<T>(value, parent);
				Splay(parent->right);
			}
		}
	}

	void Search(const T value)
	{
		if (root_ == nullptr)
			return;
		else
			Search(root_, value);
	}

	void Remove(const T value)
	{
		if (root_ == nullptr)
			return;
		Node<T>* desired = Search1(root_, value);
		if (desired == nullptr)
			return;
		Node<T>* left = desired->left;
		if (left == nullptr)
		{
			root_ = desired->right;
			root_->parent = nullptr;
			free(desired);
			return;
		}
		Node<T>* right = desired->right;
		right->parent = nullptr;
		left->parent = nullptr;
		free(desired);

		while (left->right)
			left = left->right;
		Splay(left);
		root_ = left;
		root_->right = right;
		root_->parent = nullptr;

	}


	void InorderTraverse()
	{
		InorderTraverse(root_);
		std::cout << std::endl;
	}
private:
	Node<T>* root_;

	void InorderTraverse(Node<T>* cur)
	{
		if (cur == NULL)
			return;
		InorderTraverse(cur->left);
		std::cout << cur->value << ' ';
		if (cur->parent == nullptr)
			std::cout << "<-r ";

		InorderTraverse(cur->right);
	}

	// Main additional function for splay tree: 
	// It rotates Splay tree in a way, where current node is 
	// coming closer and closer to the root, untill reach it.
	void Splay(Node<T>* cur)
	{
		while (true)
		{
			Node<T>* parent = cur->parent;
			// If current node nas no parent - than it is a root
			if (parent == nullptr)
				break;
			Node<T>* grand_parent = parent->parent;
			// If grandparent is nullptr - than parent is root and we need to do
			// only Zig or Zag step
			if (grand_parent == nullptr)
			{
				if (cur == parent->left)
					rightRotate(parent);
				else if (cur == parent->right)
					leftRotate(parent);
				else
					break;
			}
			else if (grand_parent->left == parent)
			{
				if (cur == parent->left)
				{
					rightRotate(grand_parent);
					rightRotate(parent);
				}
				else
				{
					leftRotate(parent);
					rightRotate(grand_parent);
				}
			}
			else
			{
				if (cur == parent->right)
				{
					leftRotate(grand_parent);
					leftRotate(parent);
				}
				else
				{
					rightRotate(parent);
					leftRotate(grand_parent);
				}
			}
		}
		root_ = cur;
	}

	void Search(Node<T>* cur, const T value)
	{
		Node<T>* cur_node = cur;
		bool isInTree = false;
		while (cur_node)
		{
			if (value < cur_node->value)
				cur_node = cur_node->left;
			else if (value > cur_node->value)
				cur_node = cur_node->right;
			else
			{
				isInTree = true;
				break;
			}
		}
		if(isInTree)
			Splay(cur_node);
	}

	Node<T>* Search1(Node<T>* cur, const T value)
	{
		Node<T>* cur_node = cur;
		bool isInTree = false;
		while (cur_node)
		{
			if (value < cur_node->value)
				cur_node = cur_node->left;
			else if (value > cur_node->value)
				cur_node = cur_node->right;
			else
			{
				isInTree = true;
				break;
			}
		}
		if (isInTree)
		{
			Splay(cur_node);
			return root_;
		}
		return nullptr;
	}


	void rightRotate(Node<T>* y)
	{
		Node<T>* x = y->left;
		Node<T>* betta = x->right;
		Node<T>* dad = y->parent;
		if (dad)
		{
			if (dad->right == y)
				dad->right = x;
			else
				dad->left = x;
		}
		if (betta)
			betta->parent = y;
		x->parent = dad;
		x->right = y;

		y->parent = x;
		y->left = betta;
	}

	void leftRotate(Node<T>* x)
	{
		Node<T>* y = x->right;
		Node<T>* betta = y->left;
		Node<T>* dad = x->parent;
		if (dad)
		{
			if (dad->right == x)
				dad->right = y;
			else
				dad->left = y;
		}
		if (betta)
			betta->parent = x;
		y->parent = dad;
		y->left = x;

		x->parent = y;
		x->right = betta;
	}
};

int main()
{
	MySplayTree<int> tree;
	tree.Insert(10);
	tree.InorderTraverse();
	tree.Insert(5);
	tree.InorderTraverse();
	tree.Insert(1);
	tree.InorderTraverse();
	tree.Insert(20);
	tree.InorderTraverse();
	tree.Insert(-1);
	tree.InorderTraverse();
	tree.Insert(25);
	tree.InorderTraverse();

	tree.Search(-5);
	tree.InorderTraverse();

	tree.Remove(-1);
	tree.InorderTraverse();

	tree.Insert(-1);
	tree.InorderTraverse();

	return 0;
}
