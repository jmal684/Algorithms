#pragma once

#include<sstream>
struct Digit
{
	int value;

	Digit() = default;
	Digit(const int& val) :value(val) {};
	bool operator == (const Digit& dg) const;
	bool operator < (const Digit& dg) const;
	bool operator > (const Digit& dg) const;
	int operator  - (const Digit& dg) const;
};

std::ostream& operator<<(std::ostream& output, const Digit& dg);





