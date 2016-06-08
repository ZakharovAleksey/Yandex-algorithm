#pragma once

/*
	Тут будут решены задачи из книжки яндекса.
*/

#include<iostream>
#include<vector>
#include<cstring>
#include<string>



#ifndef task_1
#define task_1
/*
Задача1. Про определение корректной последовательности скобок :
- создаем стэк, если первая скобка закрывающая, то ничего не сделаешь
- в противном случае если скобка открывающаяся то кидаем в верх стека, если закрывающаяся то смотрим
если на вершине стека соответствующая открывающаяся скобка то снимаем, если нет то заканчиваем
*/

void bracket_solver() {
	char bracket_ = ' ';
	size_t id{ 0 };
	std::vector<char> body_;
	std::string line;

	std::cout << "Input bracket sequence: ";

	std::getline(std::cin, line);
	while (id != line.length()) {
		bracket_ = line[id];
		if (id == 0 && (bracket_ == ')' || bracket_ == ']' || bracket_ == '}')) {
			std::cout << "heer 0 \n";
			return;
		}
		else if (bracket_ == '(' || bracket_ == '[' || bracket_ == '{') {
			body_.push_back(bracket_);
		}
		else if (bracket_ == ')' || bracket_ == ']' || bracket_ == '}') {
			char bracket_open = ' ';
			switch (bracket_)
			{
			case ')':
				bracket_open = '(';
				break;
			case ']':
				bracket_open = '[';
				break;
			case '}':
				bracket_open = '{';
				break;
			default:
				break;
			}

			if (body_.at(body_.size() - 1) == bracket_open)
				body_.pop_back();
			else {
				std::cout << body_.size() << '\n';
				return;
			}

		}
		++id;
	}
	if (body_.size() == 0)
		std::cout << "correct\n";
	else
		std::cout << body_.size() << '\n';
}


#endif // !task_1

#ifndef task_2
#define task_2

#include"sorting.h"
/*
	Задача 2. Время ожидания в очереди. (53 стр.)
*/

template<typename T>
T time_calculate(std::vector<T> & v) {
	q_sort(v, 0, v.size() - 1);
	display(v);
	
	T addition{ 0 };
	T sum_time{ 0 };
	if (v.size() == 1)
		return sum_time;
	else {
		for (size_t i = 1; i != v.size(); ++i) {
			addition += v.at(i - 1);
			sum_time += addition;
			std::cout << sum_time << '\n';
		}
	}

	return sum_time;
}

#endif // !task_2


#ifndef task_3
#define task_3

template<typename T>
size_t pair_count(std::vector<T> & v, T sum) {
	q_sort(v, 0, v.size() - 1);
	display(v);

	size_t l = 0, r = v.size() - 1;
	size_t count{ 0 };
	while (l < r) {
		std::cout << "v[" << l << "] = " << v.at(l) << " V  v[" << r << "] = " << v.at(r) << std::endl;
		if (v.at(l) + v.at(r) > sum)
			--r;
		else if (v.at(l) + v.at(r) == sum) {
			std::cout << v.at(l) << " + " << v.at(r) << std::endl;
			while(v.at(l) == v.at(r))
			--r;
			++count;
		}
		else if (v.at(l) + v.at(r) < sum) {
			++l;
			r = v.size() - 1;
		}
	}
	return count;
}

#endif // !task_3