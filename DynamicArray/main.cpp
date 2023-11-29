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