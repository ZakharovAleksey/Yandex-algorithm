#pragma once

#include<vector>
#include<iostream>
#include<cmath>

#include<list>
#include<algorithm>

#include<map>
#include<string>

#ifndef first
#define first
/*
	������ 1


	�������� �������, ������� ���������� ����������� ����� �� 1 �� N ������������ � ������������ ������ ����� �� �������
	���������. ��������� ����� �������� �� ����� ���� ������ � ����� ��������� ������.
*/

// ������ ������� - ��� �������� �� ������ (�� �� ���������� ����� ������������)
template<typename T>
void first_task_solver(T n) {
	for (int numb = 1; numb != n + 1; ++numb) {
		size_t cur_numb = numb;
		std::cout << cur_numb << " = 1 * ";
		size_t divisor = 2;

		while (cur_numb != 1) {
			if (cur_numb % divisor == 0) {
				cur_numb /= divisor;
				if (cur_numb != 1)
					std::cout << divisor << " * ";
				else
					std::cout << divisor;
			}
			else
				++divisor;
		}
		std::cout << std::endl;
	}
}

// ������ ������� - ������� �� ������ (�� �������� �� ���������� ������� �������� �����)
template<typename T>
void first_task_solver_mem(T n) {
	std::vector< std::vector<size_t> > v;
	v.resize(n + 1);
	v.at(1).push_back(1);
	for (int numb = 2; numb != n + 1; ++numb) {
		size_t cur_numb = numb;
		size_t divisor = 2;
		bool div_on = false;
		while (!div_on) {
			if (cur_numb % divisor == 0) {
				v[numb].push_back(divisor);
				cur_numb /= divisor;
				for (auto i : v[cur_numb])
					v[numb].push_back(i);
				div_on = true;
			}
			else
				++divisor;
		}

		std::cout << numb << " = ";
		for (auto j : v[numb])
			std::cout << j << ' ';
		std::cout << std::endl;
	}
}


#endif // !first

#ifndef second
#define second

/*
	������ 2 

	�������� ���, ������� ������ ��������� ������:
	������� ������ ������� N. ���������� ��������� ��� �� M < N ������ ������ (�� ���� ����� ���������� ��������� � ������ �����
	���� ����������). ����� �� ������ ������������ � ������ ��������� ���� ������ (���������� - ����������� ���������� �� 
	������ ������� �� ������ ������ ����� � �� ����� ��������� ����� �� ����� �������, �� � ���� ������ ���������� 
	��������, ����� ������� � �������� ���� ����������� ���� �����������).

	����������� ������ �������� ������� ������ � ����� ������ ����� (���� ����� �� �����, ���� ���������� � ����� ��������� ������).


*/

template<typename T>
void solv(std::vector<T> & v, size_t m) {
	if (m > v.size()) {
		std::cout << "Error! m = " << m << " is bigger then n = " << v.size() << std::endl;
		return;
	}
	// ������ ������ �����
	size_t each_part_size = v.size() / m;
	// ���������� ����������� �����
	size_t diff = v.size() - m * each_part_size;
	size_t i{ 0 };

	if (!diff)
		i = 0;
	else if (!(diff % 2))
		i = diff >> 1;
	else if (diff % 2)
		i =  (diff >> 1) + 1;

	std::cout << "[" << i << " , " << i + each_part_size - 1 << "] ";
	i += each_part_size;
	while (i + each_part_size <= v.size() - (diff >> 1)) {
		std::cout << "[" << i << " , " << i + each_part_size - 1 << "] ";
		i += each_part_size;
	}
	std::cout << std::endl;
}

#endif // !second



#ifndef forth
#define forth

/*
	������ 4 

	������� ������� ����������� ������ ������� N. ���������� ����������� ��������, ������� �������������� ������ ���, 
	����� �� ������ �������� �������� ���������, ����� ������, ����� ������������� � �. �. ������ ������ ���������:
	 �������� ������: 1-2-3-4-5-6-7-8
	 �������������� ������: 1-8-2-7-3-6-4-5.

	������� ��������� ������������� ���������.

*/


void third_task_solver(std::list<int> & l) {
	std::cout << "list before: ";
	for (auto i : l)
		std::cout << i << ' ';
	std::cout << std::endl;

	std::list<int> temp;
	while (!l.empty()) {
		temp.push_back(*l.begin());
		l.pop_front();
		if (!l.empty()) {
			temp.push_back(*l.rbegin());
			l.pop_back();
		}
		else
			break;
	}

	l.swap(temp);
	
	std::cout << "list after: ";
	for (auto i : l)
		std::cout << i << ' ';
	std::cout << std::endl;
}


#endif // !forth


#ifndef third
#define third

/*
	������ 3 

	�������� ������� ���������� ������� ��� ������� ���������� ��������� ������ (getopt).

	��������, ��� ��� ��������� ��������� ������, ���������� ������� ��������� ���������� ����� ���������� ����������
	���� - ������, �����, ����� � ��������� ������ � �. �., � ����� �������, �������� �� ���� �������� ������������.
	��������, ��� ��������� ����� ������������ ������ � "�������" ������� � ������������ "--" ����� ������ ���������
	(�� ���� "--my-option-name my-option-val", "--my-option-name=my-option-val", "--my-boolean-option").
	
	������� ������ ����������� ����� ������������ �������� "--help" (���� �� ������ � ������ ���������� ��� ������ �������), ��������� ������ ������������� (�������������� ��������� ������ ���������� � ���������� �������).


*/

enum ArgumentStatus
{
	no_argument = 0,
	require_argument = 1
};

struct Option
{
	std::string option_name_;
	int argument_status_;
	int* on_value_ptr_;
	int set_value_;

	Option() : option_name_(), argument_status_(), on_value_ptr_(nullptr), set_value_(0) {}

	Option(std::string name, int is_arg, int* on_value_ptr, int set_value) :
		option_name_(name), argument_status_(is_arg), on_value_ptr_(on_value_ptr), set_value_(set_value) {}

	void set(std::string name, int is_arg, int* on_value_ptr, int set_value) {
		option_name_ = name;
		argument_status_ = is_arg;
		on_value_ptr_ = on_value_ptr;
		set_value_ = set_value;
	}
};


int get_top_(std::string & line, Option opt_mas[], size_t size, size_t cur_mas_id) {
	int i{ 0 };
	std::string opt_name;
	std::string arg_value;

	while (i != line.length())
	{
		// ���� ������ --
		if (line[i] == '-' && line[i + 1] == '-') {
			i += 2;
			// �������� ��� ��������
			while (i != line.length() && line[i] != ' ' && line[i] != '=')
				opt_name.push_back(line[i++]);

			// ���� ��� ���� ��
			if (opt_name == "help") {
				std::cout << "HELP init\n";
				std::cout << "Current " << cur_mas_id << " param demo: " << opt_mas[cur_mas_id].option_name_;
				if (opt_mas[cur_mas_id].argument_status_ == ArgumentStatus::require_argument) {
					std::cout << "=[]\n";
				}
				else {
					std::cout << "=() ORE nothing \n";
				}
				line.erase(0, i);
				get_top_(line, opt_mas, size, cur_mas_id);
			}

			// ���� ����� ��������� � ���, ��� � �������, ��
			if (opt_mas[cur_mas_id].option_name_ == opt_name) {
				// ���� ��������� ��������
				if (opt_mas[cur_mas_id].argument_status_ == ArgumentStatus::require_argument) {
					// ����� ������ ���� ����� �� ��������� ��������
					if (line[i] == '=') {
						++i; // ��� ��� ���� � �����, � ������ ������� � ���������
						while (i != line.length() && line[i] != ' ')
							arg_value.push_back(line[i++]);
						int value = std::stoi(arg_value);
						*opt_mas[cur_mas_id].on_value_ptr_ = value;
						// ������, ����� �� ��������� �������� ��������� ������ ��������� �������
						line.erase(0, i);
						get_top_(line, opt_mas, size, ++cur_mas_id);

					}
					// ���� ����� ����� ����� ��� =, �� ������� ��� �������� ������ ����� �������� � ��������� �� ����������
					else {
						line.erase(0, i);
						// ��� ��������
						get_top_(line, opt_mas, size, ++cur_mas_id);
					}
				}
				// ���� �� ��������� ��������
				else {
					line.erase(0, i);
					get_top_(line, opt_mas, size, ++cur_mas_id);
				}
			}
			// ���� ����� �� ��������� � ��� ��� � ������� �� ����� ��������� �� ���������� --
			else {
				line.erase(0, i);
				// ��� ��������
				get_top_(line, opt_mas, size, ++cur_mas_id);
			}
			return -1;
		}
		// ���� �� ������ ���� �� �������� --
		else {
			++i;
			continue;
		}
	}
	return -1;
}

// ����������� main() ��� ��� ��� ������ ������� main() ����������
/*
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
*/

#endif // !third
