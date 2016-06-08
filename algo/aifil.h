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
	������ 1.
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



#ifndef third
#define third

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


#endif // !third


#ifndef forth
#define forth

void forth_task_solver() {
	std::string line;
	std::getline(std::cin, line);
	int i{ 0 };
	std::string temp;

	while (i != line.length()) {
		if (line[i] != ' ' && line[i] != '=') {
			temp.push_back(line[i++]);
		}
		else {
			std::cout << temp;
			if (temp == "--help") {
				std::cout << " yep \n";
			}
			temp.clear();
			++i;
		}
	}
}

#endif // !forth
