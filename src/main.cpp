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
	tree.Insert(10);
	tree.Insert(4);
	tree.Insert(11);
	tree.Insert(2);
	tree.Insert(15);
	tree.Insert(5);
	tree.InorderTraverse();

	return 0;
}