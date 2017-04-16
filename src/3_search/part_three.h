#pragma once

#ifndef part_three_h
#define part_three_h

#include<iostream>
#include<vector>

#pragma region task_1
	
// Task 3.3.1 (p.40) Binary search algorithm implementation.

template<typename T>
bool BinSearch(const std::vector<T> & ar, const T & key, int & keyId)
{
	int leftId = 0;
	int rightId = ar.size();
	int mediumId = 0;

	while (leftId < rightId)
	{
		mediumId = (leftId + rightId) / 2;
		if (ar.at(mediumId) == key)
		{
			keyId = mediumId;
			return true;
		}
		else if (ar.at(mediumId) > key)
			rightId = mediumId - 1;
		else
			leftId = mediumId + 1;
	}

	return false;
	
}

#pragma endregion

#pragma region task_2

// Task 3.3.2 (p.40) One has sequence a1..an, a1 != an which consist from 0 and 1 only. 
// We need to find the pair a_{i} != a_{i+1} in time log(n).

// Main Idea is simple, like in binnary search. Consider an bit array: 00 10 00 00 11
// Choose left = 0, right = size, middle = (right + left) / 2.
// - If middle = 0, then choose rigth half of an array : because it's wiev: (middle) 0 ... 1 (right) 
// and between them 0 and 1, so in worst case we find pair 01 in last arrys elements. So the change MUST BE.
// - If middle = 1, then choose left  half of an array : because it's wiev: (left ) 1 ... 0 (middle)
// and between them 0 and 1, so in worst case we find pair 10 in first arrys elements. So the change MUST BE.

int FindOneZeroSequaence(const int size)
{
	// Initilize an array in accordance with task
	std::vector<bool> vec(size);
	for (auto & i : vec)
		i = ((rand() % 100) % 2 == 0) ? true : false;

	vec.at(0) = ((rand() % 100) % 2 == 0) ? true : false;
	vec.at(size - 1) = (vec.at(0) == true) ? false : true;

	for (auto i : vec)
		std::cout << i << ' ';
	std::cout << std::endl;


	// Solution algorithm
	int leftId = 0;
	int rigthId = vec.size() - 1;
	int middleId = 0;

	while (leftId + 1 < rigthId)
	{
		middleId = (rigthId + leftId) / 2;

		if (vec.at(middleId) == false)
		{
			// Two cases: 0 ... middle ... 1 and 1 ... middle ... 0
			if (vec.at(0) == 0)
				leftId = middleId;
			else
				rigthId = middleId;
		}
		else
		{
			// Two cases: 0 ... middle ... 1 and 1 ... middle ... 0
			if (vec.at(0) == 0)
				rigthId = middleId;
			else
				leftId = middleId;
		}
	}

	std::cout << "V[" << leftId << "] = " << vec.at(leftId) << " ; V[" << rigthId << "] = " << vec.at(rigthId) << std::endl;

	return leftId;
}

#pragma endregion

#pragma region task_3

// Task 3.3.3 (p.40) Obtain whether the point belogs to the poligon. Execution time log(n).

// Main idea is thery simple (one could find more information here: https://habrahabr.ru/post/144571/) 
// - Start from angle formed by p[0], p[1], p[n-1]
// - Then divide this angle in two: and if to obtain the point we need to turn left - choose upper angle,
// bootom angle otherwise
// - At last, when we obtain the last angle, check whenether it intersect main segment: p[up]p[down] 
// intersect p[0]Point. 
// - If intersect - then the point is outside of the poligon, inside otherwise.

struct Point
{
	int x_;
	int y_;

	Point() : x_(0), y_(0) {}
	Point(int x, int y) : x_(x), y_(y) {}

	void SetRandomPosition(int min, int max)
	{
		x_ = min + rand() % (max - min);
		y_ = min + rand() % (max - min);
	}
};

// Obtain the Z-component of Vector product [ABxBC] [Node] if > 0 turn left, 
// turn right otherwise.
int VectorProductZ(const Point & A, const Point & B, const Point & C)
{
	return (B.x_ - A.x_) * (C.y_ - B.y_) - (B.y_ - A.y_) * (C.x_ - B.x_);
}

// Checks if the segment AB intersect segment CD.
bool IsIntersects(const Point & A, const Point & B, const Point & C, const Point & D)
{
	return (VectorProductZ(A, B, C) * VectorProductZ(A, B, D) <= 0 && VectorProductZ(C, D, B) * VectorProductZ(C, D, A) < 0) ? true : false;
}

// Checks whenether the 'point' is in the angle.
bool IsInAngle(const Point & vertexUp, const Point & vertexMiddle, const Point & vertexBottom, const Point & point)
{
	int up = VectorProductZ(vertexMiddle, vertexUp, point);
	int bottom = VectorProductZ(vertexMiddle, vertexBottom, point);

	// If point in left rotation relative to up and in right rotation relative to 
	// down segments - then in the angle.
	return (up < 0 && bottom > 0) ? true : false;
}

bool Solver(const int & n, const Point & point)
{
	srand(time(NULL));

	std::vector<Point> poligon(n);
	for (auto iter = poligon.begin(); iter != poligon.end(); ++iter)
		iter->SetRandomPosition(0, 10);

	for (auto i : poligon)
		std::cout << "A(" << i.x_ << " , " << i.y_ << ")\n";
	
	// Check if point in first big angle
	if (IsInAngle(poligon.at(n - 1), poligon.at(0), poligon.at(1), point))
	{
		int down = 1;
		int up = n - 1;
		int middle = 0;

		// Choose half-angle in which point takes place
		while (down + 1 < up)
		{
			middle = (down + up) / 2;
			if (VectorProductZ(poligon.at(0), poligon.at(middle), point) > 0)
				down = middle;
			else
				up = middle;
		}

		// Check on ontersection
		return !IsIntersects(poligon.at(0), point, poligon.at(down), poligon.at(up));
	}
	else
	{
		std::cout << "Point A(" << point.x_ << " , " << point.y_ << ") is not in the poligon!\n";
		return false;
	}

	return true;
}

#pragma endregion

#pragma region task_4

// Task 3.4.1 (p.42) Inorder-traverse procedure implementation in Binnary tree.

#include<memory>


template<typename T>
struct Node
{
	std::shared_ptr<Node<T>> left_;
	std::shared_ptr<Node<T>> rigth_;
	std::shared_ptr<Node<T>> parent_;

	T key_;

	Node() : left_(nullptr), rigth_(nullptr), parent_(nullptr), key_(T()) {}
	Node(T key) : left_(nullptr), rigth_(nullptr), parent_(nullptr), key_(key) {}
};

template<typename T>
class MyBinTree
{
public:
	MyBinTree();
	~MyBinTree();

	void Insert(const T & value);

	void InorderTraverse();

private:

	std::shared_ptr<Node<T>> root_;

	// Here we need to pass a constant ref, because unique_ptr could not have a COPY!!!
	void InorderTraverse(const std::shared_ptr<Node<T>> & curNode);
};



#pragma region methods implementation

template<typename T>
MyBinTree<T>::MyBinTree() : root_(nullptr) {}

template<typename T>
MyBinTree<T>::~MyBinTree() {}

template<typename T>
inline void MyBinTree<T>::Insert(const T & value)
{
	std::shared_ptr<Node<T>> insNode = std::make_shared<Node<T>>(value);

	if (root_ == nullptr)
	{
		root_ = insNode;
	}
	else
	{
		std::shared_ptr<Node<T>> curNode = root_;
		std::shared_ptr<Node<T>> parent;

		while (curNode)
		{
			parent = curNode;

			if (curNode->key_ > value)
				curNode = curNode->left_;
			else
				curNode = curNode->rigth_;
		}

		insNode->parent_ = parent;
		if (value < parent->key_)
		{
			parent->left_ = std::move(insNode);
		}
		else
			parent->rigth_ = std::move(insNode);


	}
}

template<typename T>
inline void MyBinTree<T>::InorderTraverse()
{
	InorderTraverse(root_);
}


template<typename T>
inline void MyBinTree<T>::InorderTraverse(const std::shared_ptr<Node<T>> & curNode)
{
	if (curNode->left_ != nullptr)
	{
		InorderTraverse(curNode->left_);
	}
		
	std::cout << curNode->key_ << " ";
	if(curNode->parent_ != nullptr)
		std::cout << "(" << curNode->parent_->key_ << ") ";

	if (curNode->rigth_ != nullptr)
	{
		InorderTraverse(curNode->rigth_);
	}
}


#pragma endregion



#pragma endregion


#endif // !part_three_h
