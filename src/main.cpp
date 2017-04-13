#include<iostream>

#include<cstdlib>
#include<ctime>

#include"3_search\part_three.h"



int main() 
{
	srand(time(NULL));

	using std::cout;
	using std::endl;

	Point A(3, 1);
	if (Solver(6, A))
		cout << "Point inside!\n";
	else
		cout << "Point outside!\n";

	cout << "Calculations complete!\n";

	return 0;
}