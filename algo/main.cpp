#include<iostream>

#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>

#include"part_one.h"


#include"sorting.h"
//#include"bin_tree.h"
//#include"bin_heap.h"
//#include"list.h"
#include"hash_table.h"

#include"aifil.h"

int main() {
	srand(time(NULL));

	using std::cout;
	using std::endl;

	std::vector<Jog<int>> v;
	v.push_back(Jog<int>(0, 1));
	v.push_back(Jog<int>(1, 3));
	v.push_back(Jog<int>(-100, -99));

	display(v);
	cout << max_jog_count(v) << endl;

	

	return 0;
}