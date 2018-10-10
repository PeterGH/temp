#pragma once
#include "Random.h"

namespace My {
	template<class T> class QuickSort {
	private:
		static int Partition(T * A, int l, int h);
		static int RandomPartition(T * A, int l, int h);
		static void Sort(T * A, int l, int h);
		static void RandomSort(T * A, int l, int h);
		static void ParallelSort(T * A, int l, int h);
		static T & RandomSelect(T * A, int l, int h, int i);
	public:	
		static void Sort(T * A, int L);
		static void RandomSort(T * A, int L);
		static void ParallelSort(T * A, int L);
		static T & RandomSelect(T * A, int L, int i);
	};

	// Partition A[l..i], A[(i+1)..(j-1)], A[j..h]
	// such that A[l..i] < A[h] <= A[(i+1)..(j-1)]
	// If all elements are equal, then return index l
	template<class T> int QuickSort<T>::Partition(T * A, int l, int h)
	{
		if (l >= 0 && l < h) {
			int i = l - 1;
			for (int j = l; j < h; j ++) {
				if (A[j] < A[h]) {
					// In MIT Introduction to Algorithm, the check is <=.
					// The difference is:
					// 1. <= incurs more swaps, but it is stable because all elements equal to A[h] 
					//    are still in their original order
					// 2. < incurs less swaps, but it is unstable
					i ++;
					swap(A[i], A[j]);
				}
			}

			// now A[l..i] < A[h], and A[(i+1)..(h-1)] >= A[h]
			i ++;
			swap(A[i], A[h]);

			// now A[l..(i-1)] < A[i] <= A[(i+1)..h]
			return i;
		} else {
			return -1;
		}
	}

	template<class T> int QuickSort<T>::RandomPartition(T * A, int l, int h)
	{
		static My::Random rnd;
		if (l >= 0 && l < h) {
			int i = l + rnd.Next(h - l);
			swap(A[i], A[h]);
			i = Partition(A, l, h);
			return i;
		} else {
			return -1;
		}
	}

	template<class T> void QuickSort<T>::Sort(T * A, int l, int h)
	{
		if (l >= 0 && l < h) {
			int m = Partition(A, l, h);
			if (l <= m && m <= h) {
				Sort(A, l, m - 1);
				Sort(A, m + 1, h);
			}
		}
	}

	template<class T> void QuickSort<T>::RandomSort(T * A, int l, int h)
	{
		if (l >= 0 && l < h) {
			int m = RandomPartition(A, l, h);
			if (l <= m && m <= h) {
				RandomSort(A, l, m - 1);
				RandomSort(A, m + 1, h);
			}
		}
	}

	template<class T> void QuickSort<T>::ParallelSort(T * A, int l, int h)
	{
		if (l >= 0 && l < h) {
			int m = Partition(A, l, h);
			if (l <= m && m <= h) {
				parallel_invoke(
					[&A, l, m]{ParallelSort(A, l, m - 1);},
					[&A, m, h]{ParallelSort(A, m + 1, h);}
				);
			}
		}
	}

	// Return the i-th (zero-based) element from A[l..h]
	template<class T> T & QuickSort<T>::RandomSelect(T * A, int l, int h, int i)
	{
		if (l == h) return A[l];
		else {
			int m = RandomPartition(A, l, h);
			int k = m - l;
			if (i == k) {
				// l ......... m ......... h
				// 0 ......... k
				// 0 ......... i
				return A[m];
			} else if (i < k) {
				// l ............ m ...... h
				// 0 ............ k
				// 0 ...... i
				return RandomSelect(A, l, m - 1, i);
			} else {
				// l ...... m ............ h
				// 0 ...... k
				// 0 ............ i
				return RandomSelect(A, m + 1, h, i - k - 1);
			}
		}		
	}

	template<class T> void QuickSort<T>::Sort(T * A, int L)
	{
		if (L > 1) {
			Sort(A, 0, L - 1);
		}
	}

	template<class T> void QuickSort<T>::RandomSort(T * A, int L)
	{
		if (L > 1) {
			RandomSort(A, 0, L - 1);
		}
	}

	template<class T> void QuickSort<T>::ParallelSort(T * A, int L)
	{
		if (L > 1) {
			ParallelSort(A, 0, L - 1);
		}
	}

	// This will change the ordering of elements in A,
	// because RandomPartition re-order the elements
	// i is 0-indexed
	template<class T> T & QuickSort<T>::RandomSelect(T * A, int L, int i)
	{
		if (A == nullptr || L <= 0 || i < 0 || i > L)
			throw invalid_argument("QuickSort::RandomSelect(A, L, i)");

		return RandomSelect(A, 0, L - 1, i);
	}
}