#pragma once

/*
	Тут будут решены задачи из книжки яндекса.
*/

#include<iostream>
#include<vector>
#include<cstring>
#include<string>



#ifdef task_1
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

#ifdef task_2
#define task_2

#include"sorting.h"

//	Задача 1. Время ожидания в очереди. (53 стр.)


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


#ifdef task_3
#define task_3


//	Задача 2. Пары в последовательности a_i + a_j = sum, i < j (стр. 34)


template<typename T>
size_t mid_sum_count(std::vector<T> & v, size_t const l, size_t r, size_t const sum) {
	if (l > r) {
		return 0;
	}
	else {
		size_t count{ 0 };
		while (l < r)
		{
			if (v.at(l) + v.at(r) > sum)
				--r;
			else if (v.at(l) + v.at(r) == sum) {
				--r;	 ++count;
			}
			else
				break;
		}
		return count;
	}
}

template<typename T>
size_t pair_count(std::vector<T> & v, T sum) {
	q_sort(v, 0, v.size() - 1);
	display(v);

	size_t l{ 0 }, r{ v.size() - 1 };
	size_t count{ 0 };

	while (l < r)
	{
		count += mid_sum_count(v, l, r, sum);
		++l;
	}
	
	return count;
}


#endif // !task_3


#ifndef task_4
#define task_4

// Задача 3. Число пересекающихся отрезков (стр 36)

template<typename T>
struct Jog
{

	Jog(T begin, T end) : begin_(begin), end_(end) {}
	~Jog() {}

	bool operator <(Jog const & right) { return end_ < right.end_; }

	bool operator>(Jog const & right) { return end_ > right.end_; }

	bool operator<=(Jog const & right) { return !(*this > right); }

	bool operator>=(Jog const & right) { return !(*this < right); }

	template<typename T1>
	friend std::ostream & operator<<(std::ostream & os, Jog<T1> const & jog) {
		os << "[ " << jog.begin_ << " , " << jog.end_ << " ] \n";
		return os;
	}

	T begin_;
	T end_;
};


template<typename T>
size_t max_jog_count(std::vector<Jog<T>> & v) {
	q_sort(v, 0, v.size() - 1);
	size_t max_count{ 0 };

	for (auto iter = v.rbegin(); iter != v.rend() - 1; ++iter) {
		auto in_iter = iter + 1;
		size_t count{ 1 };

		while (iter->begin_ <= in_iter->end_) {
			++count;
			if (in_iter + 1 != v.rend())
				++in_iter;
			else
				break;
		}

		if (count > max_count)
			max_count = count;
	}
	return max_count;
}

#endif // !task_4
