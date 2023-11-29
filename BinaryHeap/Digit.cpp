#include "Digit.h"
std::ostream& operator<<(std::ostream& output, const Digit& dg) {
	output << dg.value;
	return output;
}

bool Digit::operator==(const Digit& dg) const {
	if (value == dg.value)
	{
		return true;
	}

	return false;
}
bool Digit::operator<(const Digit& dg) const {
	if (value < dg.value) return true;
	return false;	
}
bool Digit::operator>(const Digit& dg) const {
	if (value > dg.value) return true;
	return false;
}

int Digit::operator-(const Digit& dg) const  {
	return value - dg.value;
}