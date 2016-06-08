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

	forth_task_solver();

	cout << "done\n";

	return 0;
}