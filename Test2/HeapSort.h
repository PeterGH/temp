#pragma once

namespace My {
	
	// Sort using max heap
	template<class T> class HeapSort {
	private:
		//         0
		//    1          2
		//  3   4     5     6
		// 7 8 9 10 11 12 13 14
		// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
		// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
		static unsigned int Parent(unsigned int i) { return (i - 1) >> 1; }
		static unsigned int Left(unsigned int i) { return (i << 1) + 1; }
		static unsigned int Right(unsigned int i) { return (i << 1) + 2; }
		static unsigned int Height(unsigned int length);
		static void Swap(T * A, unsigned int i, unsigned int j);
		static void Heapify(T * A, unsigned int i, unsigned int L);
	public:
		static void Heapify(T * A, unsigned int L);
		static void ParallelHeapify(T * A, unsigned int L);
		static void Sort(T * A, unsigned int L);
	};
	
	// 2^(Height - 1) - 1 < _length <= 2^Height - 1
	// There are Height bits and the pattern is between:
	// 10000 ... 000
	// 11111 ... 111
	template<class T> unsigned int HeapSort<T>::Height(unsigned int length)
	{
		unsigned int x = length;
		unsigned int h = 0;
		while (x > 0) {
			x = x >> 1;
			h ++;
		}
		
		return h;
	}
	
	template<class T> void HeapSort<T>::Swap(T * A, unsigned int i, unsigned int j)
	{
		if (i == j) return;
		T temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
	
	// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
	// The assumption is the subtrees rooted at i are already heapified.
	template<class T> void HeapSort<T>::Heapify(T * A, unsigned int i, unsigned L)
	{
		if (i >= L) return;
		unsigned int max = i;
		unsigned int l = Left(i);
		if (l < L && A[l] > A[i]) {
			max = l;
		}
		
		unsigned int r = Right(i);
		if (r < L && A[r] > A[max]) {
			max = r;
		}
		
		if (max != i) {
			Swap(A, i, max);
			Heapify(A, max, L);
		}
	}
	
	// Construct the array into a heap
	template<class T> void HeapSort<T>::Heapify(T * A, unsigned int L)
	{
		unsigned height = Height(L);
		
		// Do not define i as unsigned int, otherwise the for loop will continue forever 
		// because i is unsigned and thus i is always non-negative. When i = 0, (i --) becomes 4294967295
		// for (unsigned int i = ((1 << (_height - 1)) - 2) ; i >= 0; i --) {
		for (long long i = ((1 << (height - 1)) - 2) ; i >= 0; i --) {
			Heapify(A, (unsigned int)i, L);
		}
	}

	// Construct the array into a heap
	template<class T> void HeapSort<T>::ParallelHeapify(T * A, unsigned int L)
	{
		unsigned height = Height(L);
		
		for (long long h = (height - 1); h > 0; h --) {
			// For h, the index is in [((1 << (h-1)) - 1), ((1 << h) - 2)]
			parallel_for(
				unsigned int ((1 << (h-1)) - 1), 
				unsigned int ((1 << h) - 1),
				[&](unsigned int i) {
					Heapify(A, (unsigned int)i, L);
				}
			);
		}
	}

	template<class T> void HeapSort<T>::Sort(T * A, unsigned int L)
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

