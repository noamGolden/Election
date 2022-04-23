#include "Str.h"
#include <iostream>
using namespace std;

Str::Str()
{
	size = 0;
	str = nullptr;
}


Str::Str(const char* _str) {
	int i = 0;
	while (_str[i] != '\0') {
		i++;
	}
	str = new char[i];
	size = i + 1;
	i = 0;
	while (_str[i] != '\0') {
		str[i] = _str[i];
		i++;
	}

}

Str::Str(const Str& _str)
{
	int i = 0;
	while (_str[i] != '\0' && _str[i] != -3) {
		i++;
	}
	str = new char[i + 1];
	size = i + 1;
	i = 0;
	for (int i = 0; i < size; i++)
	{
		str[i] = _str[i];
	}
	str[size - 1] = '\0';
}
Str::~Str()
{
	delete[] str;
}

bool Str::operator==(const char* origin)
{
	for (int i = 0; i < size; i++)
	{
		if (str[i] != origin[i])
			return false;
	}

	return true;
}

Str& Str::operator=(const char* origin)
{
	if (str != nullptr)
		delete[]str;
	int i = 0;
	while (origin[i] != '\0' && origin[i] != -3) {
		i++;
	}
	str = new char[i + 1];
	size = i;
	for (i = 0; i < size; i++)
	{
		str[i] = origin[i];
	}
	str[size] = '\0';
	return *this;
}

Str& Str::operator=(const Str origin)
{
	if (str != nullptr)
		delete[]str;
	size = origin.size;
	str = new char[size];
	for (int i = 0; i < size; i++)
	{
		str[i] = origin.str[i];
	}
	return *this;
}

int Str::getSize()
{
	return size;
}

int Str::toNumber()
{
	int res = 0;
	char c;
	for (int i = 0; i < size; i++)
	{
		c = str[i];
		if ('0' > c || c > '9')
			return -1;
		res *= 10;
		res += c - '0';
	}
	return res;
}
ostream& operator<<(ostream& os, const Str& str)
{
	os << str.str;
	return os;
}

istream& operator>>(istream& is, Str& s)
{
	char buffer[MAX_SIZE];
	is.getline(buffer, MAX_SIZE);
	s = buffer;
	return is;
}
void increaseSizeArr(char*& name, int realsize, int logsize)
{
	char* tmp = new char[realsize * 2];
	int i = 0;
	while (i <= logsize)
	{
		tmp[i] = name[i];
		i++;
	}
	delete[] name;
	name = tmp;
}