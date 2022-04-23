#pragma once
#include <iostream>
using namespace std;
#define MAX_SIZE 100
class Str {
public:
	Str(const char* _str);
	Str(const Str& _str);
	Str();
	~Str();
	int getSize();
	int toNumber();

	friend ostream& operator<<(ostream& os, const Str& str);
	friend istream& operator>>(istream& os, Str& str);
	bool operator==(const char* origin);
	Str& operator=(const char* origin);
	Str& operator=(const Str origin);
	char& operator[](int i) { return str[i]; }
	const char& operator[](int i) const { return str[i]; }
	friend bool operator==(const Str& s1, const Str& s2) { return memcmp(s1.str, s2.str, s1.size) == 0; }
	char* str;
private:
	int size;
};