#include<iostream>

#include<cstdlib>
#include<ctime>

#include"3_search\part_three.h"



int main() 
{
	srand(time(NULL));

	using std::cout;
	using std::endl;
	

	MyBinTree<int> tree;
	tree.Insert(5);
	tree.Insert(2);
	tree.Insert(1);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(10);
	tree.Insert(6);
	tree.Insert(7);
	tree.InorderTraverse();

	std::cout << "prer= " << tree.Successor(6) << std::endl;

	

	tree.InorderTraverse();
	

	return 0;
}