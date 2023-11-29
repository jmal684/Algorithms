 #pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using std::string;

template <typename T>
class DynamicArray {
private:
	T* arr;
	unsigned int size, capacity, expandCoeff;

public:
	DynamicArray() noexcept : size(0), capacity(2), expandCoeff(2)
	{
		arr = new T[capacity];
	};
	~DynamicArray() {
		delete[] arr;
		arr = nullptr;
	}

	void PrintContent() {
		std::cout << "Size: " << size << " Capacity: " << capacity << std::endl;
		std::cout << "[ ";
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "]" << std::endl;
	}
	void PrintElement(unsigned int index) {
		if (IsIndexInvalid(index)) {
			
		}
		else
		{
			std::cout <<"Element of index "<< index << ": " << arr[index] << std::endl;
		}	
	}
	string ToString( unsigned int rangeBegin = 0, unsigned int rangeEnd = 0 ) {
		if (size <= 0)
		{
			return "[]\n";
		}

		std::ostringstream str;
		str << "size: "<< size << " [";
		
		if (rangeBegin > 0 || rangeEnd > 0) {
			auto isInvalid = [](unsigned int rangeBegin, unsigned int rangeEnd, unsigned int& size){
				if (rangeBegin < 0 || rangeBegin > rangeEnd || rangeEnd >= size) return true;
				else return false;
			};

			
			if (!isInvalid(rangeBegin, rangeEnd, size))
			{
				for (int i = rangeBegin; i <= rangeEnd; i++)
				{
					str << " " << arr[i];
				}
				str << " ]\n";
				return str.str();
			}
			else
			{
				return "Error: Invalid range values\n";
			}

		}
		if (size < 20) {
			for (int i = 0; i < size; i++)
			{
				str << " " << arr[i];
			}
			str << " ]\n";
		}
		else
		{
			for (int i = 0; i < 20; i++)
			{
				str << " " << arr[i];
			}
			str << " ] and " << size - 20 << " more...\n";
		}


		return str.str();
	}

	void Add(const T& data) {
		if ((size + 1) > capacity) {
			IncreaseCapacity();
		}

		arr[size] = data;
		++size;
	}
	void Change(unsigned int index, T&& data) {
		if (IsIndexInvalid(index))
		{
			std::cerr << "Error: Given index out of bounds" << std::endl;
		}
		else
		{
			arr[index] = data;
		}
	}
	void IncreaseCapacity() {
		T* tempNew = new T[capacity * expandCoeff];
		for (int i = 0; i < size; i++)
		{
			tempNew[i] = arr[i];
		}

		delete [] arr;
		arr = tempNew;
		tempNew = nullptr;
		capacity *= expandCoeff;
	}
	void DeleteLast() {		
		T* tempNew = new T[capacity];
		

		for (int i = 0; i < size; i++)
		{
			tempNew[i] = arr[i];
		}
		--size;
		delete[] arr;
		arr = tempNew;
		tempNew = nullptr;

	}
	void Clear() {
		capacity = 2;
		size = 0;
		T* newArr = new T[capacity];

		delete[] arr;
		arr = newArr;
		newArr = nullptr;

	}
	void BubbleSort() {

		bool swapped = false;

		for (int i = 0; i < size-1; i++)
		{
			for (int j = 0; j < (size-1) - i; j++)
			{
				if (Comp(arr[j], arr[j + 1]) > 0)
				{
					std::swap(arr[j], arr[j + 1]);
					swapped = true;
				}				
			}
			
			if (!swapped)
			{
				break;
			}
			swapped = false;
		}		
	}
	int getSize() {
		return size;
	}
	void setSize(int s) {
		size = s;
	}
	bool IsIndexInvalid(int index) {
		return index > size || index < 0 || size <= 0;
	}

	T& operator[](int index) {
		return arr[index];
	}
};

template<typename Object>
int Comp(Object& obj1, Object& obj2) {
	return obj1 - obj2;
}
