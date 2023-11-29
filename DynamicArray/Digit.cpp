#include "Digit.h"
std::ostream& operator<<(std::ostream& output, const Digit& dg) {
	output << dg.value;
	return output;
}

bool Digit::operator==(Digit& dg) {
	if (value == dg.value)
	{
		return true;
	}

	return false;
}
bool Digit::operator<(Digit& dg) {
	if (value < dg.value) return true;
	return false;	
}
bool Digit::operator>(Digit& dg) {
	if (value > dg.value) return true;
	return false;
}

int Digit::operator-(Digit& dg) {
	return value - dg.value;
}