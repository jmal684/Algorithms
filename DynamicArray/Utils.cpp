#include "Utils.h"
#include <random>

int RandomInt(const unsigned int rangeBegin, const unsigned int rangeEnd) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution < std::mt19937::result_type > dist6(rangeBegin, rangeEnd);

	return dist6(rng);
}