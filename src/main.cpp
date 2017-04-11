#include<iostream>

#include<cstdlib>
#include<ctime>

#include"3_search\part_three.h"



int main() 
{
	srand(time(NULL));

	using std::cout;
	using std::endl;

	std::vector<int> v(10);
	int i = 0;
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		*it = i++;

	cout << BinSearch(v, -1) << endl;
	

	cout << "Calculations complete!\n";

	return 0;
}