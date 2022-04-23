#pragma once
#include <fstream>
#include <iostream>
using namespace std;

#define WRITE reinterpret_cast<const char*>
#define READ reinterpret_cast<char*>

struct date
{
	int _year;
	int _mounth;
	int _day;

	date(int day, int mounth, int year)
	{
		_year = year;

		_mounth = mounth;

		_day = day;
	}

	friend ostream& operator<<(ostream& os, const date& _date)
	{
		os << "date : " << _date._day << " / " << _date._mounth << " / " << _date._year;
		return os;
	}
};



int Truncate(float realNumber);



//return the index of the maximum 
template <class T>
int findMax(T arr[], int size)
{
	T max = arr[0];
	int res = 0;
	for (int i = 1; i < size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			res = i;
		}
	}
	return res;
}

template <class T>
void printList(T* head)
{
	auto* p = head;
	while (p)
	{
		cout << *(p->_data) << endl;
		p = p->_next;
	}
}






