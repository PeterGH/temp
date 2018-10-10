#pragma once
#include <cmath>
#include <functional>
#include <ppl.h>
#include "Array.h"
#include "Heap.h"
#include "Math.h"
#include "Search.h"
using namespace concurrency;
using namespace std;
namespace Test {
	class Sort {
	public:

		class Heap {
		public:
			// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
			// The assumption is the subtrees rooted at i are already heapified.
			template<class T> static void HeapifyElement(T * input, unsigned int i, unsigned int length);
			// Construct the array into a max heap from bottom up
			template<class T> static void Heapify(T * input, unsigned int length);
			template<class T> static void ParallelHeapify(T * input, unsigned int length);
			template<class T> static void Sort(T * input, unsigned int length);

			// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
			// The assumption is the subtrees rooted at i are already heapified.
			template<class T> static void HeapifyElement(T * input, unsigned int i, unsigned int length, unsigned int d);
			// Construct the array into a max d-ary heap from bottom up
			template<class T> static void Heapify(T * input, unsigned int length, unsigned int d);
			template<class T> static void ParallelHeapify(T * input, unsigned int length, unsigned int d);
			template<class T> static void Sort(T * input, unsigned int length, unsigned int d);
		};
	};
		
	template<class T> void Sort::Heap::HeapifyElement(T * input, unsigned int i, unsigned length)
	{
		if (i >= length) return;
		unsigned int max = i;
		unsigned int l = Math::Tree::Left(i);
		if (l < length && input[l] > input[max]) {
			max = l;
		}

		unsigned int r = Math::Tree::Right(i);
		if (r < length && input[r] > input[max]) {
			max = r;
		}

		if (max != i) {
			Array::Swap(input, i, max);
			HeapifyElement(input, max, length);
		}
	}

	template<class T> void Sort::Heap::Heapify(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		unsigned int height = Math::Tree::Height(length);

		// The elements at bottom are indexed in [2^(height - 1) - 1, 2^height - 2]
		// We only need to heapify elements above them
		for (long i = ((1 << (height - 1)) - 2); i >= 0; i--) {
			HeapifyElement(input, (unsigned int)i, length);
		}
	}

	template<class T> void Sort::Heap::ParallelHeapify(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		unsigned height = Math::Tree::Height(length);

		for (long long h = (height - 1); h > 0; h--) {
			// For h, the index is in [((1 << (h-1)) - 1), ((1 << h) - 2)]
			parallel_for(
				unsigned int((1 << (h - 1)) - 1),
				unsigned int((1 << h) - 1),
				[&](unsigned int i) { HeapifyElement(input, (unsigned int)i, length); }
			);
		}
	}

	template<class T> void Sort::Heap::Sort(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		// Make a heap
		Heapify(input, length);

		// Sort
		for (long long i = length - 1; i >= 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			Array::Swap(input, 0, (unsigned int)i);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (unsigned int)i);
		}
	}

	// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
	// The assumption is the subtrees rooted at i are already heapified.
	template<class T> void Sort::Heap::HeapifyElement(T * input, unsigned int i, unsigned int length, unsigned int d)
	{
		if (i >= length) return;
		unsigned int max = i;

		for (unsigned int j = 0; j < d; j++) {
			unsigned int c = Math::Tree::Child(i, j, d);
			if (c < length && input[c] > input[max]) {
				max = c;
			}
		}

		if (max != i) {
			Array::Swap(input, i, max);
			HeapifyElement(input, max, length, d);
		}
	}

	template<class T> void Sort::Heap::Heapify(T * input, unsigned int length, unsigned int d)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (d <= 1) throw invalid_argument(String::Format("d %d is invalid", d));

		unsigned int height = Math::Tree::Height(length, d);
		long long index = ((long long)pow(d, height - 1) - 1) / (d - 1) - 1;
		for (long long i = index; i >= 0; i--) {
			HeapifyElement(input, (unsigned int)i, length, d);
		}
	}

	template<class T> void Sort::Heap::ParallelHeapify(T * input, unsigned int length, unsigned int d)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (d <= 1) throw invalid_argument(String::Format("d %d is invalid", d));

		unsigned int height = Math::Tree::Height(length, d);

		for (long long h = height - 1; h > 0; h--) {
			// For h, the index is in [(d ^ (h - 1) - 1) / (d - 1), (d^h - 1) / (d - 1) - 1]
			parallel_for(
				unsigned int((pow(d, h - 1) - 1) / (d - 1)),
				unsigned int((pow(d, h) - 1) / (d - 1)),
				[&](unsigned int i) { HeapifyElement(input, (unsigned int)i, length, d); }
			);
		}
	}

	template<class T> void Sort::Heap::Sort(T * input, unsigned int length, unsigned int d)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (d <= 1) throw invalid_argument(String::Format("d %d is invalid", d));

		// Make A a heap
		Heapify(input, length, d);

		// Sort
		for (long i = length - 1; i >= 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			Array::Swap(input, 0, (unsigned int)i);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (unsigned int)i, d);
		}
	}
}