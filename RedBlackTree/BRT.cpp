// BRT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include "RedBlackTree.h"
#include "Digit.h"


int RandomInt(const unsigned int rangeBegin, const unsigned int rangeEnd) {
    static std::default_random_engine rng(time(NULL));
    std::uniform_int_distribution < std::mt19937::result_type > dist6(rangeBegin, rangeEnd);

    return dist6(rng);
}

#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
void test()
{
	std::vector<int> v(8);
	std::iota(v.begin(), v.end(), 0);
	std::map<int, int> heights, root_data;
	int krok = 1;
	do
	{
		RedBlackTree<int> t;

		for (int i : v) 
			t.Add(i);		

		++heights[t.getHeight(t.getRoot())];
		++root_data[t.getRoot()->data];
	} while (std::next_permutation(v.begin(), v.end()));
	for (auto [height, cnt] : heights)
		std::cout << height << ": " << cnt << std::endl;
	std::cout << "***" << std::endl;
	for (auto [data, cnt] : root_data)
		std::cout << data << ": " << cnt << std::endl;
}
int main()
{
	test();
    const int MAX_ORDER = 7;
    const int UPPER_BOUND = 100000;
    RedBlackTree<Digit> rbt;

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);

        clock_t t1 = clock();

        for (int i = 0; i < n; i++) {
            rbt.Add(Digit(RandomInt(1, UPPER_BOUND)));
        }

        clock_t t2 = clock();

        double addTime = (t2 - t1) / (double)CLOCKS_PER_SEC;

        cout << "Czas dodania : " << addTime << " s" << endl;
        cout << rbt.toString() << endl;


        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();


        for (int i = 0; i < m; i++)
        {
            RedBlackTree<Digit>::Node* wynik = rbt.Search(Digit(RandomInt(1, UPPER_BOUND)));
            if (wynik != NULL)
                hits++;

        }

        t2 = clock();
        double searchTime = (t2 - t1)/(double)CLOCKS_PER_SEC;
        cout << "Czas wyszukiwania: " << searchTime << " s" << endl;
        cout << "Trafienia: " << hits << endl;
        cout << "wysokosc/log2(n): " << rbt.getHeight(rbt.getRoot()) / log2(rbt.getSize());
        cout << "" << endl;

        rbt.Clear();

    }	

}

