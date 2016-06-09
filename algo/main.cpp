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

	int a_ptr = 0;
	int b_ptr = 0;
	int c_ptr = 0;

	std::string line;
	std::getline(std::cin, line);

	size_t const size = 3;
	Option comand_list[size];

	comand_list[0].set("int", ArgumentStatus::require_argument, &a_ptr, 1);
	comand_list[1].set("float", ArgumentStatus::no_argument, &b_ptr, 10);
	comand_list[2].set("int", ArgumentStatus::require_argument, &c_ptr, 1);

	while (get_top_(line, comand_list, size, 0) != -1);
	std::cout << "PARAMETRES\n";

	cout << "a = " << a_ptr << '\n';
	cout << "b = " << b_ptr << '\n';
	cout << "c = " << c_ptr << '\n';

	cout << "done\n";

	return 0;
}