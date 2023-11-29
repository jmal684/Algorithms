#pragma once
#include <sstream>
#include <string>

#include "DynamicArray.h"

using std::string;

template<typename T>
class BinaryHeap {
private:
	DynamicArray<T> heap;

public:
	void Add(const T& data) {
		heap.Add(data);
		HeapUp(heap.getSize() - 1);
	}

	void Poll() {
		if (heap.getSize() <= 0) {
			std::cerr << "Poll error: heap is empty" << std::endl;
			return;
		}
		else
		{
			if(heap.getSize() < 20)
				std::cout << "Root: " << heap[0] << std::endl;
		}

		std::swap(heap[0], heap[heap.getSize() - 1]);

		heap.setSize(heap.getSize() - 1);
	
		HeapDown(0);
	}
	void Clear() {
		heap.Clear();
	}
	string toString() {
		return heap.ToString();
	}

private:
	template<typename Object>
	int Compare(const Object& obj1, const Object& obj2) {
		return obj1 - obj2;
	}
	void HeapUp(int index) {
		int parentIndex = floor((index - 1) / 2);
		if (Compare(heap[index], heap[parentIndex])<=0)
			return;
		std::swap(heap[index], heap[parentIndex]);
		HeapUp(parentIndex);
	}
	void HeapDown(int index) {
		int leftChildIndex = 2 * index + 1;
		int rightChildIndex = 2 * index + 2;
		if (leftChildIndex >= heap.getSize() || rightChildIndex >= heap.getSize())
			return;

		if (Compare(heap[index], heap[leftChildIndex]) < 0 && Compare(heap[index], heap[rightChildIndex]) < 0) {
			if (Compare(heap[leftChildIndex], heap[rightChildIndex]) < 0) {
				std::swap(heap[index], heap[rightChildIndex]);
				HeapDown(rightChildIndex);
			}
			else
			{
				std::swap(heap[index], heap[leftChildIndex]);
				HeapDown(leftChildIndex);
			}
		}
		else if (Compare(heap[index], heap[leftChildIndex]) < 0) {
			std::swap(heap[index], heap[leftChildIndex]);
			HeapDown(leftChildIndex);
		}
		else if (Compare(heap[index], heap[rightChildIndex]) < 0) {
			std::swap(heap[index], heap[rightChildIndex]);
			HeapDown(rightChildIndex);
		}
		else
			return;

	}
};
