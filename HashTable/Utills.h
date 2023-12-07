#pragma once
#include <random>
#include <iostream>

int RandomInt(const unsigned int rangeBegin, const unsigned int rangeEnd) {
    static std::default_random_engine rng(time(NULL));
    std::uniform_int_distribution < std::mt19937::result_type > dist6(rangeBegin, rangeEnd);

    return dist6(rng);
}
