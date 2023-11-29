

#include <iostream>
#include <random>
#include <cmath>
#include "Digit.h";
#include "BinarySearchTree.h"


int RandomInt(const unsigned int rangeBegin, const unsigned int rangeEnd) {
    static std::default_random_engine rng;
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
    std::map<int, int> heights, min_node_data;
    int krok = 0;

    do
    {


        BinarySearchTree<int> t;
        for (int i : v)
            t.Add(i);
        ++heights[t.getHeight(t.getRoot())];

        for (int i : v)
        {
            ++krok;
            ++min_node_data[t.get_min_node_data()];     

            t.Delete(i);

        }
    } while (std::next_permutation(v.begin(), v.end()));
    for (auto [height, cnt] : heights)
        std::cout << height << ": " << cnt << std::endl;
    std::cout << "***" << std::endl;
    for (auto [data, cnt] : min_node_data)
        std::cout << data << ": " << cnt << std::endl;
}
int main()
{

   test();

    const int MAX_ORDER = 7;
    const int UPPER_BOUND = 100000;
    BinarySearchTree<Digit> bst;

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);

        clock_t t1 = clock();

        for (int i = 0; i < n; i++) {
            bst.Add(Digit(RandomInt(1, UPPER_BOUND)));
        }

        clock_t t2 = clock();

        double addTime = t2 - t1;

        cout << "Czas: " << addTime << endl;
        cout << "Stosunek wysokosci drzewa do rozmiaru danych: " << (double)bst.getHeight(bst.getRoot()) / bst.getSize() << endl;
        cout << "Logartym z rozmiaru danych: " << log2(bst.getSize()) << endl;
        cout << "Stosunek wysokosci drzewa do logarytmu z rozmiaru danych: " << (double)bst.getHeight(bst.getRoot()) / (log2(bst.getSize())) << endl;
        cout << bst.toString() << endl;


        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();


        for (int i = 0; i < m; i++)
        {
            BinarySearchTree<Digit>::Node* wynik = bst.Search(Digit(RandomInt(1, UPPER_BOUND)));
            if (wynik != NULL)
                hits++;

        }

        t2 = clock();
        double searchTime = t2 - t1;
        cout << "Czas: " << searchTime << endl;
        cout << "Trafienia: " << hits << endl;
        cout << "" << endl;

        bst.Clear();

    }








}

