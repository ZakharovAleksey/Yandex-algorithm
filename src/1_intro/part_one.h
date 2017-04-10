#pragma once

#ifndef part_one_h
#define part_one_h

#include<iostream>
#include<vector>
#include<cstring>
#include<string>


#pragma region task 1

// Задача 1.1. Правильная скобочная последовательность

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


#pragma endregion

#pragma region  task 2

#include"../2_sorting/part_two.h"

//	Задача 2. Время ожидания в очереди. (53 стр.)
// Не понял что за задача

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


#pragma endregion

#endif // !part_one_h
