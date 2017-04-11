#pragma once

#ifndef part_three_h
#define part_three_h

#include<iostream>
#include<vector>

#pragma region task_1
	
// ���������� 3.3.1 �������� ����� (���.40) 

template<typename T>
bool BinSearch(const std::vector<T> & ar, const T & key, int & keyId)
{
	int leftId = 0;
	int rightId = ar.size();
	int mediumId = 0;

	while (leftId < rightId)
	{
		mediumId = (leftId + rightId) / 2;
		if (ar.at(mediumId) == key)
		{
			keyId = mediumId;
			return true;
		}
		else if (ar.at(mediumId) > key)
			rightId = mediumId - 1;
		else
			leftId = mediumId + 1;
	}

	return false;
	
}



#pragma endregion

#pragma region task_2

// ������� 3.3.2 ������ ������������������ a1..an. a1 != an, ���������� �� log(n) ����� ���� ����� ��� a_{i} != a_{i+1} (���. 40)

#pragma endregion



#endif // !part_three_h
