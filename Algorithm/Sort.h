#pragma once

#include <functional>
#include <ppl.h>
#include "Array.h"

using namespace concurrency;
using namespace std;

namespace Test {
	class Sort {
	public:
		// ColumnSort is described in MIT Introduction to Algorithms 3rd edition Chapter 8 problem 8-7.
		// Sort an array of r rows and s columns such that
		// 1. r must be even
		// 2. s must be a divisor of r
		// 3. r >= 2s^2
		//
		// The steps are
		// 0. Given an array
		//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
		//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
		//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
		//                             ......
		//                             ......
		//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
		//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
		// 1. Sort each column
		// 2. Transpose the array. Turn the leftmost column into top r/s rows in order,
		//    and then do the same for the rest of columns in order
		//     (0,0)     (1,0)       (2,0)       ...... (s-2,0)    (s-1,0)
		//     (s,0)     (s+1,0)     (s+2,0)     ...... (2s-2,0)   (2s-1,0)
		//                                       ......
		//     (r-s,0)   (r-s+1,0)   (r-s+2,0)   ...... (r-2,0)    (r-1,0)
		//     (0,1)     (1,1)       (2,1)       ...... (s-2,1)    (s-1,1)
		//     (s,1)     (s+1,1)     (s+2,1)     ...... (2s-2,1)   (2s-1,1)
		//                                       ......
		//     (r-s,1)   (r-s+1,1)   (r-s+2,1)   ...... (r-2,1)    (r-1,1)
		//                                       ......
		//                                       ......
		//     (0,s-1)   (1,s-1)     (2,s-1)     ...... (s-2,s-1)  (s-1,s-1)
		//     (s,s-1)   (s+1,s-1)   (s+2,s-1)   ...... (2s-2,s-1) (2s-1,s-1)
		//                                       ......
		//     (r-s,s-1) (r-s+1,s-1) (r-s+2,s-1) ...... (r-2,s-1)  (r-1,s-1)
		// 3. Sort each column
		// 4. Revert step 2
		//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
		//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
		//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
		//                             ......
		//                             ......
		//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
		//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
		// 5. Sort each column
		// 6. Shift leftmost column down by r/2 and into the top of its right next column.
		//    Do the same for the rest of columns in order
		//               (r/2,0)   (r/2,1)   (r/2,2)   ...... (r/2,s-3)   (r/2,s-2)   (r/2,s-1)
		//               (r/2+1,0) (r/2+1,1) (r/2+1,2) ...... (r/2+1,s-3) (r/2+1,s-2) (r/2+1,s-1)
		//               (r/2+2,0) (r/2+2,1) (r/2+2,2) ...... (r/2+2,s-3) (r/2+2,s-2) (r/2+2,s-1)
		//                                             ......
		//                                             ......
		//               (r-1,0)   (r-1,1)   (r-1,2)   ...... (r-1,s-3)   (r-1,s-2)   (r-1,s-1)
		//     (0,0)     (0,1)     (0,2)     ......           (0,s-2)     (0,s-1)
		//     (1,0)     (1,1)     (1,2)     ......           (1,s-2)     (1,s-1)
		//     (2,0)     (2,1)     (2,2)     ......           (2,s-2)     (2,s-1)
		//                                   ......
		//                                   ......
		//     (r/2-2,0) (r/2-2,1) (r/2-2,2) ......           (r/2-2,s-2) (r/2-2,s-1)
		//     (r/2-1,0) (r/2-1,1) (r/2-1,2) ......           (r/2-1,s-2) (r/2-1,s-1)
		// 7. Sort each column
		// 8. Revert step 6
		//     (0,0)   (0,1)   (0,2)   ...... (0,s-2)   (0,s-1)
		//     (1,0)   (1,1)   (1,2)   ...... (1,s-2)   (1,s-1)
		//     (2,0)   (2,1)   (2,2)   ...... (2,s-2)   (2,s-1)
		//                             ......
		//                             ......
		//     (r-2,0) (r-2,1) (r-2,2) ...... (r-2,s-2) (r-2,s-1)
		//     (r-1,0) (r-1,1) (r-1,2) ...... (r-1,s-2) (r-1,s-1)
		//
		// When step 8 completes, the matrix is sorted in column-major order:
		// Reading down the leftmost column and continuing with the rest of columns,
		// the elements are in sorted order.
		//
		// This implementation use a row-based variant, a.k.a. RowSort,
		// to sort a two-dimensional matrix stored in an array.
		// Sort an array of s rows and r columns such that
		// 1. r must be even
		// 2. s must be a divisor of r
		// 3. r >= 2s^2
		//
		// The steps are
		// 0. Given an array
		//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
		//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
		//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
		//                             ......
		//                             ......
		//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
		//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
		// 1. Sort each row
		// 2. Transpose the array. Turn the topmost row into left r/s columns in order,
		//    and then do the same for the rest of rows in order
		//     (0,0)   (0,s)    ...... (0,r-s)   (1,0)   (1,s)    ...... (1,r-s)   ...... (s-1,0)   (s-1,s)    ...... (s-1,r-s)
		//     (0,1)   (0,s+1)  ...... (0,r-s+1) (1,1)   (1,s+1)  ...... (1,r-s+1) ...... (s-1,1)   (s-1,s+1)  ...... (s-1,r-s+1)
		//     (0,2)   (0,s+2)  ...... (0,r-s+2) (1,2)   (1,s+2)  ...... (1,r-s+2) ...... (s-1,2)   (s-1,s+2)  ...... (s-1,r-s+2)
		//                      ......                            ......           ......                      ......
		//                      ......                            ......           ......                      ......
		//     (0,s-2) (0,2s-2) ...... (0,r-2)   (1,s-2) (1,2s-2) ...... (1,r-2)   ...... (s-1,s-2) (s-1,2s-2) ...... (s-1,r-2)
		//     (0,s-1) (0,2s-1) ...... (0,r-1)   (1,s-1) (1,2s-1) ...... (1,r-1)   ...... (s-1,s-1) (s-1,2s-1) ...... (s-1,r-1)
		// 3. Sort each row
		// 4. Revert step 2
		//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
		//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
		//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
		//                             ......
		//                             ......
		//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
		//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
		// 5. Sort each row
		// 6. Shift topmost row right by r/2 and into the left of its down next row.
		//    Do the same for the rest of rows in order
		//                                                                  (0,0)   (0,1)   (0,2)   ...... (0,r/2-2)   (0,r/2-1)
		//     (0,r/2)   (0,r/2+1)   (0,r/2+2)   ...... (0,r-2)   (0,r-1)   (1,0)   (1,1)   (1,2)   ...... (1,r/2-2)   (1,r/2-1)
		//     (1,r/2)   (1,r/2+1)   (1,r/2+2)   ...... (1,r-2)   (1,r-1)   (2,0)   (2,1)   (2,2)   ...... (2,r/2-2)   (2,r/2-1)
		//                                       ......                                             ......
		//                                       ......                                             ......
		//     (s-3,r/2) (s-3,r/2+1) (s-3,r/2+2) ...... (s-3,r-2) (s-3,r-1) (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r/2-2) (s-2,r/2-1)
		//     (s-2,r/2) (s-2,r/2+1) (s-2,r/2+2) ...... (s-2,r-2) (s-2,r-1) (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r/2-2) (s-1,r/2-1)
		//     (s-1,r/2) (s-1,r/2+1) (s-1,r/2+2) ...... (s-1,r-2) (s-1,r-1)
		// 7. Sort each row
		// 8. Revert step 6
		//     (0,0)   (0,1)   (0,2)   ...... (0,r-2)   (0,r-1)
		//     (1,0)   (1,1)   (1,2)   ...... (1,r-2)   (1,r-1)
		//     (2,0)   (2,1)   (2,2)   ...... (2,r-2)   (2,r-1)
		//                             ......
		//                             ......
		//     (s-2,0) (s-2,1) (s-2,2) ...... (s-2,r-2) (s-2,r-1)
		//     (s-1,0) (s-1,1) (s-1,2) ...... (s-1,r-2) (s-1,r-1)
		//
		// When step 8 completes, the matrix is sorted in row-major order:
		// Reading right the topmost row and continuing with the rest of rows,
		// the elements are in sorted order.
		class __declspec(dllexport) RowSort {
		private:
			template<class T> static void check(T * input, const int length, const int columns)
			{
				if (input == nullptr) throw invalid_argument("input is nullptr");
				if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
				if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
			}

		public:
			// Check if each column is sorted
			template<class T> static bool IsColumnsSorted(T * input, const int length, const int columns)
			{
				check(input, length, columns);
				if (length <= columns) return true; // Only one row

				// 0      ... c-1
				// c      ... 2c-1
				//        ...
				// (r-1)c ... rc-1
				// rc ... l-1
				int rows = length / columns;
				for (int i = 0; i < columns; i++) {
					int end = i + rows * columns;
					if (end >= length) end -= columns;
					for (int j = i; j < end; j += columns) {
						if (input[j] > input[j + columns]) return false;
					}
				}

				return true;
			}

			// Check if each row is sorted
			template<class T> static bool IsRowsSorted(T * input, const int length, const int columns)
			{
				check(input, length, columns);
				if (columns == 1) return true; // Only one column

				// 0      ... c-1
				// c      ... 2c-1
				//        ...
				// (r-2)c ... rc-1
				// (r-1)c ... l-1
				int rows = length / columns;
				if (length % columns > 0) rows++;
				int begin = 0;
				for (int i = 0; i < rows; i++) {
					int end = begin + columns - 1;
					if (end >= length) end = length - 1;
					for (int j = begin; j < end; j++) {
						if (input[j] > input[j + 1]) return false;
					}

					begin += columns;
				}

				return true;
			}

			// Check if input is sorted in row-major order
			template<class T> static bool IsSorted(T * input, const int length, const int columns)
			{
				check(input, length, columns);

				// 0      ... c-1
				// c      ... 2c-1
				//        ...
				// (r-2)c ... rc-1
				// (r-1)c ... l-1
				int rows = length / columns;
				if (length % columns > 0) rows++;
				int begin = 0;
				for (int i = 0; i < rows; i++) {
					int end = begin + columns - 1;
					if (end >= length - 1) end = length - 2;
					for (int j = begin; j <= end; j++) {
						// When j = end, j+1 is the begin of next row
						if (input[j] > input[j + 1]) return false;
					}

					begin += columns;
				}

				return true;
			}

			// Sort each row
			template<class T> static void SortRows(T * input, const int length, const int columns)
			{
				check(input, length, columns);

				int rows = length / columns;
				if (length % columns > 0) rows++;
				int begin = 0;
				for (int i = 0; i < rows; i++) {
					int end = begin + columns - 1;
					if (end >= length) end = length - 1;
					MergeSort::Sort(input, begin, end);
					begin += columns;
				}
			}

			// Sort a matrix so that each row is sorted and each column is sorted
			template<class T> static void Sort(T * input, const int length, const int columns)
			{
				check(input, length, columns);
				if (columns % 2 != 0) throw invalid_argument(String::Format("columns %d is not even.", columns));
				if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));
				int rows = length / columns;
				if (columns % rows > 0) throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));
				if (columns < 2 * rows * rows) throw invalid_argument(String::Format("columns %d is less than 2 * %d * %d.", columns, rows, rows));

				SortRows(input, length, columns);
				Array::TransposeRowsToColumns<T>(input, length, columns);
				SortRows(input, length, columns);
				Array::TransposeColumnsToRows<T>(input, length, columns);
				SortRows(input, length, columns);
				Array::RotateRight<T>(input, length, columns >> 1);
				SortRows(&input[columns], length - columns, columns);
				Array::RotateLeft<T>(input, length, columns >> 1);
			}

			// Parallel check if each column is sorted
			template<class T> static bool ParallelIsColumnsSorted(T * input, const int length, const int columns)
			{
				check(input, length, columns);
				if (length <= columns) return true; // Only one row

				// 0      ... c-1
				// c      ... 2c-1
				//        ...
				// (r-1)c ... rc-1
				// rc ... l-1
				int rows = length / columns;
				bool sorted = true;
				cancellation_token_source tokenSource;
				run_with_cancellation_token([&]() {
					parallel_for(int(0), columns, [&](int i) {
						int end = i + rows * columns;
						if (end >= length) end -= columns;
						for (int j = i; j < end; j += columns) {
							if (input[j] > input[j + columns]) {
								sorted = false;
								tokenSource.cancel();
							}
						}
					});
				}, tokenSource.get_token());

				return sorted;
			}

			// Parallel check if each row is sorted
			template<class T> static bool ParallelIsRowsSorted(T * input, const int length, const int columns)
			{
				check(input, length, columns);
				if (columns == 1) return true; // Only one column

				// 0      ... c-1
				// c      ... 2c-1
				//        ...
				// (r-2)c ... rc-1
				// (r-1)c ... l-1
				int rows = length / columns;
				if (length % columns > 0) rows++;
				bool sorted = true;
				cancellation_token_source tokenSource;
				run_with_cancellation_token([&]() {
					parallel_for(int(0), rows, [&](int i) {
						int begin = i * columns;
						int end = begin + columns - 1;
						if (end >= length) end = length - 1;
						for (int j = begin; j < end; j++) {
							if (input[j] > input[j + 1]) {
								sorted = false;
								tokenSource.cancel();
							}
						}
					});
				}, tokenSource.get_token());

				return sorted;
			}

			// Parallel check if each row is sorted and if each column is sorted
			template<class T> static bool ParallelIsSorted(T * input, const int length, const int columns)
			{
				check(input, length, columns);

				// 0      ... c-1
				// c      ... 2c-1
				//        ...
				// (r-2)c ... rc-1
				// (r-1)c ... l-1
				int rows = length / columns;
				if (length % columns > 0) rows++;
				bool sorted = true;
				cancellation_token_source tokenSource;
				run_with_cancellation_token([&]() {
					parallel_for(int(0), rows, [&](int i) {
						int begin = i * columns;
						int end = begin + columns - 1;
						if (end >= length - 1) end = length - 2;
						for (int j = begin; j <= end; j++) {
							if (input[j] > input[j + 1]) {
								// When j = end, j+1 is the begin of next row
								sorted = false;
								tokenSource.cancel();
							}
						}
					});
				}, tokenSource.get_token());

				return sorted;
			}

			// Parallel sort each row
			template<class T> static void ParallelSortRows(T * input, const int length, const int columns)
			{
				check(input, length, columns);

				int rows = length / columns;
				if (length % columns > 0) rows++;
				parallel_for(int(0), rows, [&](int i) {
					int begin = i * columns;
					int end = begin + columns - 1;
					if (end >= length) end = length - 1;
					MergeSort::Sort<T>(input, begin, end);
				});
			}

			// Parallel sort a matrix so that each row is sorted and each column is sorted
			template<class T> static void ParallelSort(T * input, const int length, const int columns)
			{
				check(input, length, columns);
				if (columns % 2 != 0) throw invalid_argument(String::Format("columns %d is not even.", columns));
				if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));
				int rows = length / columns;
				if (columns % rows > 0) throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));
				if (columns < 2 * rows * rows) throw invalid_argument(String::Format("columns %d is less than 2 * %d * %d.", columns, rows, rows));

				ParallelSortRows(input, length, columns);
				Array::TransposeRowsToColumns<T>(input, length, columns);
				ParallelSortRows(input, length, columns);
				Array::TransposeColumnsToRows<T>(input, length, columns);
				ParallelSortRows(input, length, columns);
				Array::RotateRight<T>(input, length, columns >> 1);
				ParallelSortRows(&input[columns], length - columns, columns);
				Array::RotateLeft<T>(input, length, columns >> 1);
			}
		};

		class __declspec(dllexport) CountingSort {
		private:
			static void GetRange(const int * input, int length, int & minValue, int & range)
			{
				if (input == nullptr || length <= 0) {
					range = -1;
					return;
				}

				int minIndex;
				int maxIndex;
				Array::MinMax(input, length, minIndex, maxIndex);
				if (minIndex < 0 || maxIndex < 0 || minIndex >= length || maxIndex >= length) {
					range = -1;
					return;
				}

				minValue = input[minIndex];
				int maxValue = input[maxIndex];
				range = maxValue - minValue + 1;
			}

		public:
			// Sort input and return the result in output.
			// Not in-place. Stable.
			static void Sort(const int * input, int length, int * output)
			{
				if (input == nullptr || length <= 0 || output == nullptr) return;

				int minValue;
				int range = -1;
				GetRange(input, length, minValue, range);
				if (range == -1) return;

				unique_ptr<int[]> count(new int[range]);
				memset(count.get(), 0, range * sizeof(int));

				for (int i = 0; i < length; i++) {
					int delta = input[i] - minValue;
					count[delta]++;
				}

				for (int i = 1; i < range; i++) {
					count[i] += count[i - 1];
				}

				for (int i = length - 1; i >= 0; i--) {
					int delta = input[i] - minValue;
					output[count[delta] - 1] = input[i];
					count[delta]--;
				}
			}

			// Sort in place
			// In-place sort. Not stable.
			static void Sort(int * input, int length)
			{
				if (input == nullptr || length <= 0) return;

				int minValue;
				int range = -1;
				GetRange(input, length, minValue, range);
				if (range == -1) return;

				unique_ptr<int[]> count(new int[range]);
				memset(count.get(), 0, range * sizeof(int));

				for (int i = 0; i < length; i++) {
					int delta = input[i] - minValue;
					count[delta] ++;
				}

				for (int i = 1; i < range; i++) {
					count[i] += count[i - 1];
				}

				BitSet bits(length);
				for (int i = length - 1; i >= 0; i--) {
					if (bits.Test(i)) continue;
					while (true) {
						// Use input[i] as a temporay place to store the next value to be placed.
						int delta = input[i] - minValue;
						int currentIndex = count[delta] - 1;
						count[delta]--;
						bits.Set(currentIndex);
						if (currentIndex == i) break;
						int nextValue = input[currentIndex];
						input[currentIndex] = input[i];
						input[i] = nextValue;
					}
				}
			}
		};
	};
}