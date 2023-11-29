// Dynamic_array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DynamicArray.h"
#include "Digit.h";
#include "Utils.h";

int main()
{	
	DynamicArray<Digit> digits;
	
	const int order = 7;
	const int n = pow(10, order);

	clock_t t1 = clock();
	double max_time_per_element = 0.0;

	for (int i = 0; i < n; i++)
	{
		
		clock_t t1_element = clock();

		digits.Add(Digit(RandomInt(1,50)));

		clock_t t2_element = clock();
		double time_per_element = (t2_element - t1_element)/(double)CLOCKS_PER_SEC;

		if (time_per_element > max_time_per_element)
		{
			max_time_per_element = time_per_element;
			std::cout << "Czas : " << max_time_per_element << " s. Index: " << i << std::endl;
		}

	}

	clock_t t2 = clock();
	std::cout << "Czas: " << (t2 - t1)/(double)CLOCKS_PER_SEC << " s."<<std::endl;
	std::cout << digits.ToString();

	digits.Clear();

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
