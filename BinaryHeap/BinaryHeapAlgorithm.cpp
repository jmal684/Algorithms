// BinaryHeapAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include "BinaryHeap.h"
#include "Digit.h"

int RandomInt(const unsigned int rangeBegin, const unsigned int rangeEnd) {
    static std::default_random_engine rng(time(NULL));
    std::uniform_int_distribution < std::mt19937::result_type > dist6(rangeBegin, rangeEnd);

    return dist6(rng);
}
int main()
{
    const int MAX_ORDER = 7;
    const int UPPER_BOUND = 100000;
    BinaryHeap<Digit> bh;
    for (int o = 1; o <= MAX_ORDER ; o++)
    {
        const int n = pow(10, o);
        

        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            bh.Add(Digit(RandomInt(1, UPPER_BOUND)));        
        }
        clock_t t2 = clock();

        double addTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Czas dodania: " << addTime << " s." << std::endl;
        std::cout << bh.toString();

        t1 = clock();

        for (int i = 0; i < n; i++)
        {
            bh.Poll();          
        }
        t2 = clock();
        double deleteTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Czas usuwania: " << addTime << " s." << std::endl;
        std::cout << bh.toString();
        bh.Clear();
       
    } 

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
