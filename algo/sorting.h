#pragma once

#include<cmath>

template<typename T>
void display(std::vector<T> const & v) {
	for (auto i : v)
		std::cout << i << ' ';
	std::cout << std::endl;
}


//	Сортровка выбором
template <typename T>
void select_sort(std::vector<T> & v) {
	for (size_t i = 0; i != v.size(); ++i) {
		auto min_id = std::min_element(v.begin() + i, v.end());
		std::swap(*(v.begin() + i), *(v.begin() + std::distance(v.begin(), min_id)));
	}
	display(v);
}


//	Сортировка вставками 
template<typename T>
void insert_sort(std::vector<T> & v) {
	for (size_t i = 1; i != v.size(); ++i)
		for (size_t j = i; j > 0 && v[j] < v[j - 1]; --j)
			std::swap(v[j], v[j - 1]);

	display(v);
}

//	Сортировка пузырьком (существуют улучшения)
template <typename T>
void bubble_sort(std::vector<T> & v) {
	for (size_t i = 0; i != v.size() - 1; ++i)
		for (size_t j = i + 1; j != v.size(); ++j) {
			if (v[i] > v[j])
				std::swap(v[i], v[j]);
		}
	display(v);
}

// Эффективные методы сортировки

// Сортировка Шелла (с уменьшающимися расстояниями)
template<typename T>
void shell_sort_step(std::vector<T> & v, size_t h) {
	for (size_t i = h; i <= v.size() - h; i += h)
		for (size_t j = i; j > 0 && v[j] < v[j - h]; j -= h)
			std::swap(v[j], v[j - h]);
}

template<typename T>
void shell_sort(std::vector<T> & v) {
	size_t h = 4;
	while (h >= 1)
	{
		shell_sort_step(v, h);
		h /= 2;
	}
	display(v);
}

// Пирамидальная сортировка
template <typename T>
void down_heap(std::vector<T> & v, size_t id, size_t size) {
	
	while (id < size / 2)
	{
		size_t left_id = 2 * id + 1;
		size_t max_id = left_id;
		if (2 * id + 2 < size && v[left_id] < v[left_id + 1])
			++max_id;
		std::swap(v[id], v[max_id]);
		id = max_id;
	}
}

template<typename T>
void heap_sort(std::vector<T> & v) {
	// Сначала строим пирамиду из данного массива
	for (size_t i = v.size() / 2 - 1; i != -1; --i)
		down_heap(v, i, v.size());
	display(v);

	// Вершину в правый угол, а оттуда в вершину и просеиваем без учета последнего
	for (size_t i = 0; i != v.size(); ++i) {
		std::swap(v[0], v[v.size() - 1 - i]);
		down_heap(v, 0, v.size() - 1 - i);
	}
	display(v);
}

// Быстрая сортировка
template<typename T>
size_t partition(std::vector<T> & v, size_t left, size_t right) {
	size_t id = ( right + left ) >> 1;
	while (left <= right){
		while (v[left] < v[id])
			++left;
		while (v[right] > v[id])
			--right;
		if (left <= right) {
			std::swap(v[left++], v[right--]);
		}
	}
	return id;
}

// Алгоритм partition описанный в книге яндекса (стр. 24)
template<typename T>
size_t partition_sec(std::vector<T> & v, size_t left, size_t right) {
	// Чтобы убрать рандомизированный доступ надо просто оставить privot_id = (right + left) >> 1;
	size_t privot_id{ 0 };
	if (left != right)
		privot_id = (rand() % (right - left)) + left;
	// Для устранения проблемм q_sort(equal, equal) - там rand() % 0 - ERROR!!!
	else
		privot_id = (right + left) >> 1;
	T privot = v.at(privot_id);
	std::swap(v.at(right), v.at(privot_id));

	size_t l = left, r = left;
	while (r != right) {
		if (v.at(r) > privot)
			++r;
		else if (v.at(r) <= privot)
			std::swap(v.at(r++), v.at(l++));
	}
	std::swap(v.at(l), v.at(right));
	return l;
}

template<typename T>
void q_sort(std::vector<T> & v, size_t left, size_t right) {
	size_t separater = partition_sec(v, left, right);
	if (left < separater)
		q_sort(v, left, separater - 1);
	if(separater < right)
		q_sort(v, separater + 1, right);
}

// Выбираем отрезок [для уменьшения глубины рекурсии + еще можно убрать хвостовую рекурсию goto]
template<typename T>
void quick_sort(std::vector<T> & v, size_t left, size_t right) {
	size_t separater = partition_sec(v, left, right);
	if (separater >= 2 * (left + right)) {
		if (left < separater)
			q_sort(v, left, separater - 1);
		if (separater < right)
			q_sort(v, separater + 1, right);
	}	
	else {
		if (separater < right)
			q_sort(v, separater + 1, right);
		if (left < separater)
			q_sort(v, left, separater - 1);
	}
}

// Задача поиска k-ой порядковой статистики
template<typename T>
T k_statistic(std::vector<T> & v, size_t left, size_t right, size_t const k) {
	size_t privot = partition_sec(v, left, right);
	if (k <= privot && left < privot) {
		k_statistic(v, left, privot - 1, k);
	}
	if (k > privot && privot < right) {
		k_statistic(v, privot + 1, right, k);
	}
	return v.at(k);
}

// Для того чтобы решать задачу поиска k-ой порядковой статистики в худшем случае за линейное время
// необходимо выбирать медиану почти точно, алгоритм lineral-select как раз ищет эту медиану
// Необходимо добавлять максивмально возможные значения MAX
template<typename T>
T lineral_select(std::vector<T> v, T max) {
	// input your code here
	display(v);
}

// Сортировка Подсчетом
template< typename T>
void counting_sort(std::vector<T> & v) {
	auto max = std::max_element(v.begin(), v.end());
	std::vector<T> temp(*max + 1);
	for (auto i : v)
		++temp[i];
	v.clear();

	for (size_t i = 0; i != temp.size(); ++i) {
		if (temp[i] == 0)
			continue;
		for (size_t j = 0; j != temp[i]; ++j)
			v.push_back(i);
	}
}

// Сортировка слиянием (работет правильно только для массивов размеров степени двойки)
template<typename T>
void merge(std::vector<T> & v, size_t left_id_begin, size_t left_id_end, size_t right_id_end) {
	auto left_iter = v.begin() + left_id_begin;
	auto right_iter = v.begin() + left_id_end + 1;
	
	std::vector<T> temp;

	for (size_t i = 0; i != right_id_end - left_id_begin + 1; ++i) {
		if (*left_iter < * right_iter)
			temp.push_back(*left_iter++);
		else
			temp.push_back(*right_iter++);

		if (std::distance(v.begin(), right_iter) == right_id_end + 1) {
			while (left_iter != v.begin() + left_id_end + 1)
				temp.push_back(*left_iter++);
			for (size_t i = 0; i != temp.size(); ++i)
				v[i + left_id_begin] = temp[i];
			return;
		}

		if (std::distance(v.begin(), left_iter) == left_id_end + 1) {
			while (right_iter != v.begin() + right_id_end + 1)
				temp.push_back(*right_iter++);
			for (size_t i = 0; i != temp.size(); ++i)
				v[i + left_id_begin] = temp[i];
			return;
		}
	}
}

template<typename T>
void merge_sort(std::vector<T> & v, size_t k) {
	size_t iter_numb = floor(log2(v.size()));

	for (size_t i = 0; i != iter_numb; ++i) {
		float left_begin{ 0 }, left_end{ powf(2, i) - 1 }, right_end{ powf(2, i + 1) - 1 };
		while (right_end < v.size()){
			if (right_end + k == v.size())
				merge(v, left_begin, left_end, right_end + 1);
			else
				merge(v, left_begin, left_end, right_end);
			left_begin += k;	left_end += k;		right_end += k;
		}
		k *= 2;
	}
}