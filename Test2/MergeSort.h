#pragma once

#include <ppl.h>
#include <set>
#include "Heap.h"
using namespace concurrency;

namespace My {

	template<class T> class MergeSort {
	private:
		static void Merge(T * A, int p, int q, int r);
		static int CountInversions(T * A, int p, int q, int r);
	public:
		static void Sort(T * A, int p, int r);
		static void Sort(T * A, int L) { Sort(A, 0, L-1); }
		static void ParallelSort(T * A, int p, int r);
		static void ParallelSort(T * A, int L) { ParallelSort(A, 0, L-1); }

		static int CountInversions(T * A, int p, int r);
		static int CountInversions(T * A, int L) { return CountInversions(A, 0, L-1); }

		// Merg sort multiple sorted sets
		static void Sort(T * inputs[], size_t * sizes, size_t size, vector<T> & output);
	};

	// Assume A[p..(q-1)] and A[q..r] are already sorted.
	// Rearrange A so that A[p..r] is sorted.
	// Merge is in-place and stable.
	template<class T> void MergeSort<T>::Merge(T * A, int p, int q, int r)
	{
		if (A == nullptr || p < 0 || r <= 0 || r < q || q <= p) return;
		// p and q point to the heads of two sub sorted arrays.
		while (p < q && q <= r) {
			if (A[p] <= A[q]) {
				p ++;
			} else {
				// Should move A[q] to position p
				T t = A[q];
				// Shift A[p..(q-1)] to A[(p+1)..q]
				for (int i = q; i > p; i --) {
					A[i] = A[i - 1];
				}

				A[p] = t;
				// Move to the next pair of elements
				p ++;
				q ++;
			}
		}
	}

	// Sort A[p..r] using merge sort
	template<class T> void MergeSort<T>::Sort(T * A, int p, int r)
	{
		if (A == nullptr || p < 0 || r < 0 || r < p) return;
		if (p < r) {
			int q = p + ((r - p) >> 2) + 1;
			Sort(A, p, q - 1);
			Sort(A, q, r);
			Merge(A, p, q, r);
		}
	}

	template<class T> void MergeSort<T>::ParallelSort(T * A, int p, int r)
	{
		if (A == nullptr || p < 0 || r < 0 || r < p) return;
		if (p < r) {
			int q = p + ((r - p) >> 2) + 1;
			// parallel_invoke returns only when two actions finish
			parallel_invoke(
				[&A, p, q]{ ParallelSort(A, p, q - 1); },
				[&A, q, r]{ ParallelSort(A, q, r); }
			);
			// Now two sub arrays are sorted
			// Safe to merge
			Merge(A, p, q, r);
		}
	}

	// An inversion is a pair {A[i], A[j]} such that A[i] > A[j] when i < j.
	// We can extend the concept to two sub arrays of A, and the set of inversions
	// contains every inversion whose elements fall into different sub arrays, e.g.,
	// A[i] is in the first sub array while A[j] is in the second.
	// Sorting the two sub arrays separately does not change the count of inversions
	// between the two sub arrays.
	// Assume A[p..(q-1)] and A[q..r] are already sorted.
	// Count inversions between A[p..(q-1)] and A[q..r] by merging them into a sorted array A[p..r].
	template<class T> int MergeSort<T>::CountInversions(T * A, int p, int q, int r)
	{
		if (A == nullptr || p < 0 || r <= 0 || r < q || q <= p) return 0;
		// p and q point to the heads of two sub sorted arrays.
		int count = 0;
		while (p < q && q <= r) {
			if (A[p] <= A[q]) {
				p ++;
			} else {
				// Should move A[q] to position p
				T t = A[q];
				// Shift A[p..(q-1)] to A[(p+1)..q]
				for (int i = q; i > p; i --) {
					A[i] = A[i - 1];
				}

				A[p] = t;
				// There (q-p) elements moved.
				// Each of them paired with A[q] is an inversion.
				count += (q - p);
				// Move to the next pair of elements
				p ++;
				q ++;
			}
		}

		return count;
	}

	template<class T> int MergeSort<T>::CountInversions(T * A, int p, int r)
	{
		if (A == nullptr || p < 0 || r < 0 || r < p) return 0;
		int count = 0;
		if (p < r) {
			int q = p + ((r - p) >> 2) + 1;
			count += CountInversions(A, p, q - 1);
			count += CountInversions(A, q, r);
			count += CountInversions(A, p, q, r);
		}

		return count;
	}
		
	template<class T> class Element	{
	public:
		const T * sorted;
		const size_t size;
		size_t index;
		Element (const T * s, const size_t l, size_t i) : sorted(s), size(l), index(i) {}
	};

	template<class T> struct Greater : public binary_function<const Element<T> *, const Element<T> *, bool>
	{
		bool operator() (const Element<T> * left, const Element<T> * right) const;
	};

	template<class T> bool Greater<T>::operator() (const Element<T> * left, const Element<T> * right) const
	{
		return left->sorted[left->index] > right->sorted[right->index];
	}

	// Each element of inputs is the address of a sorted array
	// Each element of sizes is the size of corresponding array in inputs
	// size is the size of inputs
	template<class T> void MergeSort<T>::Sort(T * inputs[], size_t * sizes, size_t size, vector<T> & output)
	{
		// A minimum heap
		Heap<Element<T> *, Greater<T>> heap(size);

		for (size_t i = 0; i < size; i++) {
			if (sizes[i] > 0) {
				// Initialize the heap with the first element in each sorted array
				heap.Push(new Element<T>(inputs[i], sizes[i], 0));
			}
		}

		while (heap.Size() > 0) {
			// Extract the minimum element from the heap
			Element<T> * min = heap.Pop();
			// append the minum element into the output vector
			output.push_back(min->sorted[min->index]);
			// Move to the next element in the same array
			min->index ++;
			if (min->index < min->size) {
				// The array still has element
				// Push the next element into the heap
				heap.Push(min);
			} else {
				// The array has been processed. Discard it.
				delete min;
			}
		}
	}
}