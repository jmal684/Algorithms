#pragma once

#include<sstream>
struct Digit
{
	int value;

	Digit() = default;
	Digit(const int& val) :value(val) {};
	bool operator == (Digit& dg);
	bool operator < (Digit& dg);
	bool operator > (Digit& dg);
	int operator  - (Digit& dg);
};

std::ostream& operator<<(std::ostream& output, const Digit& dg);





