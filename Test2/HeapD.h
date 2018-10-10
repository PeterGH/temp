#pragma once
#include <cmath>
#include <stdexcept>
using namespace std;
namespace My {
	template<class T> class HeapD {
	private:
		unsigned int d;
		//                                                  0
		//                   1                              2                    ...          d
		// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
		// (d^2+d+1) (d^2+d+2) ...
		// ......
		// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
		// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]

		// Return the index of the parent of node i
		unsigned int Parent(unsigned int i) { return (i - 1) / this->d; }

		// Return the index of the j-th child of node i. j is zero based.
		unsigned int Child(unsigned int i, unsigned int j);

		unsigned int Height(unsigned int length);

		static void Swap(T * A, unsigned int i, unsigned int j);

		void Heapify(T * A, unsigned int i, unsigned int L);

	public:
		HeapD(unsigned int d);
		void Heapify(T * A, unsigned int L);
		void Sort(T * A, unsigned int L);
	};

	template<class T> HeapD<T>::HeapD(unsigned int d)
	{
		if (d == 0)
			throw invalid_argument("HeapD(d): d cannot be zero.");

		this->d = d;
	}

	template<class T> unsigned int HeapD<T>::Child(unsigned int i, unsigned int j)
	{
		if (j >= this->d)
			throw invalid_argument("HeapD::Child(i,j): j must be in [0, d-1].");

		return i * this->d + j + 1;
	}

	// (d^(h-1)-1)/(d-1) < length <= (d^h-1)/(d-1)
	// There are h d-bits and the pattern is between:
	// 1    0    0    0     ... 0    0    0
	// (d-1)(d-1)(d-1)(d-1) ... (d-1)(d-1)(d-1)
	template<class T> unsigned int HeapD<T>::Height(unsigned int length)
	{
		unsigned int x = length * (this->d - 1);
		unsigned int h = 0;
		while (x > 0) {
			x = x / (this->d);
			h ++;
		}
		
		return h;
	}

	template<class T> void HeapD<T>::Swap(T * A, unsigned int i, unsigned int j)
	{
		if (i == j) return;
		T temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
	// The assumption is the subtrees rooted at i are already heapified.
	template<class T> void HeapD<T>::Heapify(T * A, unsigned int i, unsigned L)
	{
		if (i >= L) return;
		unsigned int max = i;

		for (unsigned int j = 0; j < this->d; j++) {
			unsigned int c = Child(i, j);
			if (c < L && A[c] > A[max]) {
				max = c;
			}
		}
		
		if (max != i) {
			Swap(A, i, max);
			Heapify(A, max, L);
		}
	}

	// Construct the array into a heap
	template<class T> void HeapD<T>::Heapify(T * A, unsigned int L)
	{
		unsigned int height = Height(L);
		long long index = ((long long)pow(this->d, height-1) - 1) / (this-> d -1) - 1;
		// Do not define i as unsigned int, otherwise the for loop will continue forever 
		for (long long i = index ; i >= 0; i --) {
			Heapify(A, (unsigned int)i, L);
		}
	}

	template<class T> void HeapD<T>::Sort(T * A, unsigned int L)
	{
		// Make A a heap
		Heapify(A, L);
		
		// Sort
		for (long long i = L - 1; i >= 0; i --) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			Swap(A, 0, (unsigned int)i);
			// Rearrange [0, i - 1] so that it is a heap
			Heapify(A, 0, (unsigned int)i);
		}
	}
}