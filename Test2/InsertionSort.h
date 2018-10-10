#pragma once

#include <vector>
#include "BinarySearch.h"

namespace My {

	template<class T> class InsertionSort {
	public:
		static void Sort(T * A, int L);
		static void RecursiveSort(T * A, int L);		
	};

	// Insertion sort is in-place, stable.
	template<class T> void InsertionSort<T>::Sort(T * A, int L)
	{
		if (A == nullptr || L <= 0) return;
		// Cannot compute the length of A by sizeof(A) / sizeof(A[0])
		// Have to use an additional parameter L
		for (int i = 1; i < L; i ++) {
			// Record the current value to insert into A[0..(i-1)]
			T key = A[i];
			// Shift any values in A[0..(i-1)] greater than the current value,
			// so that the right position for the current value is vacant.
			int j = i - 1;
			// Note the comparison is strict,
			// so the multiple instances of the same value preserve their
			// orignial orders, i.e., the sorting is stable.
			while (j >= 0 && A[j] > key) {
				// Right shift A[j] to A[j+1],
				// so that A[j+1] is vacant for insertion
				A[j+1] = A[j];
				j --;
			}
			// Insert the current value
			A[j+1] = key;
		}
	}

	// Recursively sort A[0..(L-1)] by insertion
	// Use binary search to find the position to insert an element
	template<class T> void InsertionSort<T>::RecursiveSort(T * A, int L)
	{
		// Invalid input
		if (A == nullptr || L <= 0) return;
		// Only one element. no need to recurse
		if (L == 1) return;
		// Recursively sort A[0..(L-2)]
		RecursiveSort(A, L - 1);
		// Record the current value to insert into A[0..(L-2)]
		T key = A[L - 1];
		// Find the position after which the current value should be inserted
		// -1 <= i <= (L-2)
		int i = BinarySearch<T>::FindPositionToInsert(key, A, L - 1);
		// Shift A[(i+1)..(L-2)] so that the position (i+1) for the current value is vacant.
		for (int j = L - 2; j > i; j --) {
			A[j + 1] = A[j];
		}
		// Insert the current value
		A[i+1] = key;
	}
}