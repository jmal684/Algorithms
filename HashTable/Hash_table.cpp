// Hash_table.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "HashTable.h"



int main()
{
	const int MAX_ORDER = 7;

	HashTable<int> ht;

	for (int o = 1; o < MAX_ORDER; o++)
	{
		const int n = pow(10, o);
		
		clock_t t1 = clock();

		for (int i = 0; i < n; i++)
		{
			ht.Insert(GenerateString(), i);
		}

		clock_t t2 = clock();

		double addTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Czas dodania: " << addTime << " s." << std::endl;
		std::cout << ht.toString();

		const int m = pow(10, 4);
		int hits = 0;
		t1 = clock();

		for (int i = 0; i < m; i++)
		{
			std::pair<string, int>* entry = ht.Search(GenerateString());
			if (entry != nullptr)
				hits++;
		}

		t2 = clock();

		double searchTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Czas wyszukiwania: " << searchTime << " s." << std::endl;
		std::cout << "Liczba trafien: " << hits << std::endl;
		std::cout << ht.toString();
		std::cout << ht.PrintStatistics();

		ht.Clear();
	}

}


