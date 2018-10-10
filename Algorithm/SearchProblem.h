#pragma once

#include <algorithm>
#include <stdexcept>
#include "BinarySearch.h"
#include "Partition.h"
#include "Sort.h"

using namespace std;

namespace Test {
	class SearchProblem {
	public:
		// Find the median from two sorted arrays.
		// If the two arrays contain odd number of elements, then the median is unique.
		// If the two arrays contain even number of elements, then return the lower median.
		template<class T> static T FindMedian(const T * input1, int length1, const T * input2, int length2)
		{
			if (input1 == nullptr) throw invalid_argument("input1 is a nullptr");
			if (length1 <= 0) throw invalid_argument(String::Format("length1 %d is invalid", length1));
			if (input2 == nullptr) throw invalid_argument("input2 is a nullptr");
			if (length2 <= 0) throw invalid_argument(String::Format("length2 %d is invalid", length2));

			const T * shortArray;
			int shortLength;
			const T * longArray;
			int longLength;

			if (length1 <= length2) {
				shortLength = length1;
				shortArray = input1;
				longLength = length2;
				longArray = input2;
			} else {
				shortLength = length2;
				shortArray = input2;
				longLength = length1;
				longArray = input1;
			}

			int medianIndex = (shortLength + longLength - 1) / 2;
			if (shortArray[shortLength - 1] <= longArray[0]) {
				if (medianIndex == shortLength - 1) {
					// +---------------------------------------+  +---------------------------------------+
					// 0                                      s-1 0                                      l-1
					// s = l
					// m = s - 1 = l - 1
					return shortArray[medianIndex];
				} else {
					// +---------------------------------------+  +-----+------------------------------------------+
					// 0                                      s-1 0    m-s                                        l-1
					// s < l
					// m = (s + l - 1) / 2
					//   = k - 1    if (s + l) = 2k
					//     k - 1    if (s + l) = 2k - 1
					// s - 1 < m < l - 1
					return longArray[medianIndex - shortLength];
				}
			} else if (longArray[longLength - 1] <= shortArray[0]) {
				// +---------------------------------------+---------+  +---------------------------------------+
				// 0                                       m        l-1 0                                      s-1
				// s <= l
				// m = (s + l - 1) / 2
				//   = k - 1    if (s + l) = 2k
				//     k - 1    if (s + l) = 2k - 1
				// s - 1 <= m <= l - 1
				return longArray[medianIndex];
			}

			// +---------------------------------------+
			// 0             m-1 m m+1                s-1
			// +-----------------------------------------------+
			// 0             n-1 n n+1                        l-1
			//
			// From (m + 1) + (n + 1) = medianIndex + 1
			// get: m + n = medianIndex - 1
			// Median = S[m] if L[n] < S[m] <= L[n+1], i.e. S[m] is the lower median and L[n+1] is the higher median
			//          L[n] if S[m] < L[n] <= S[m+1], i.e. L[n] is the lower median and S[m+1] is the higher median
			//          S[m] if S[m] == L[n], i.e. S[m] or L[n] is the lower median and min(S[m+1], L[n+1]) is the higher median
			//          max(S[m-1], L[n+1]) if S[m] > L[n+1], and S[m] is the higher median
			//          max(S[m+1], L[n-1]) if L[n] > S[m+1], and L[n] is the higher median

			int low = 0;
			int high = shortLength - 1;
			while (true) {
				// (1) If low < high - 1, then low < m < high
				// (2) If low = high - 1, then low = m < high
				// (3) If low = high, then low = m = high
				int m = (low + high) >> 1;
				int n = medianIndex - m - 1;
				if (shortArray[m] > longArray[n]) {
					if (shortArray[m] <= longArray[n + 1]) {
						return shortArray[m];
					} else {
						if (m < high) {
							// Case (1) or (2)
							high = m;
						} else {
							// Case (3)
							// s[m] > l[n] and s[m] > l[n+1]
							// Compare s[m-1] and l[n+1] as one of them is the median
							if (m - 1 >= 0 && shortArray[m - 1] > longArray[n + 1]) return shortArray[m - 1];
							else return longArray[n + 1];
						}
					}
				} else if (longArray[n] > shortArray[m]) {
					if (longArray[n] <= shortArray[m + 1]) {
						return longArray[n];
					} else {
						if (low < m) {
							// Case (1)
							low = m;
						} else {
							// Case (2) or (3)
							// l[n] > s[m] and l[n] > s[m+1]
							// Compare l[n-1] and s[m+1]
							if (n - 1 >= 0 && longArray[n - 1] > shortArray[m + 1]) return longArray[n - 1];
							else return shortArray[m + 1];
						}
					}
				} else {
					return shortArray[m];
				}
			}
		}

		// Find k closest neighbors to the i-th order element.
		// Parameter pivotIndex is the order of the input element.
		// When the method finishes, the first 1 + countNeighbors elements are the pivot element and its closest neighbors.
		template<class T> static T SelectClosestNeighbors(T * input, int length, int pivotIndex, int countNeighbors)
		{
			if (input == nullptr) throw invalid_argument("input is nullptr");
			if (length <= 0) throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
			if (pivotIndex < 0 || pivotIndex >= length) throw invalid_argument(String::Format("pivotIndex %d is not in [0, %d]", pivotIndex, length - 1));
			if (countNeighbors < 0 || countNeighbors >= length) throw invalid_argument(String::Format("countNeighbors %d is not in [0, %d]", countNeighbors, length - 1));
			Partition::PartitionArrayByOrder(input, 0, length - 1, pivotIndex);
			T pivot = input[pivotIndex];
			Partition::PartitionArrayByOrder<T, int>(input, 0, length - 1, countNeighbors, [&pivot](T v)->int { return abs(v - pivot); });
			return pivot;
		}

		class KthOrder {
		public:
			// Find the k-th order statistic (smallest element) from two sorted arrays.
			// k = 1, 2, ...
			template<class T> static T Solve(int k, const T * input1, int length1, const T * input2, int length2)
			{
				if (input1 == nullptr) throw invalid_argument("input1 is a nullptr");
				if (length1 <= 0) throw invalid_argument(String::Format("length1 %d is invalid", length1));
				if (input2 == nullptr) throw invalid_argument("input2 is a nullptr");
				if (length2 <= 0) throw invalid_argument(String::Format("length2 %d is invalid", length2));
				if (k <= 0) throw invalid_argument(String::Format("k %d is invalid", k));
				if (k > length1 + length2) throw invalid_argument(String::Format("k(%d) is greater than length1(%d) + length2(%d)", k, length1, length2));

				const T * shortArray;
				int shortLength;
				const T * longArray;
				int longLength;

				if (length1 <= length2) {
					shortLength = length1;
					shortArray = input1;
					longLength = length2;
					longArray = input2;
				} else {
					shortLength = length2;
					shortArray = input2;
					longLength = length1;
					longArray = input1;
				}

				if (shortArray[shortLength - 1] <= longArray[0]) {
					if (k <= shortLength) {
						// +-----------------------+---------------+  +---------------------------------------+
						// 0                      k-1             s-1 0                                      l-1
						return shortArray[k - 1];
					} else {
						// +---------------------------------------+  +-----+------------------------------------------+
						// 0                                      s-1 0   k-s-1                                       l-1
						return longArray[k - shortLength - 1];
					}
				} else if (longArray[longLength - 1] <= shortArray[0]) {
					if (k <= longLength) {
						// +---------------------------------------+---------+  +---------------------------------------+
						// 0                                      k-1       l-1 0                                      s-1
						return longArray[k - 1];
					} else {
						// +-------------------------------------------------+  +--------+------------------------------+
						// 0                                                l-1 0      k-l-1                           s-1
						return shortArray[k - longLength - 1];
					}
				}

				if (k == 1) {
					return std::min<T>(shortArray[0], longArray[0]);
				}

				if (k == shortLength + longLength) {
					return std::max<T>(shortArray[shortLength - 1], longArray[longLength - 1]);
				}

				// +---------------------------------------+
				// 0             m-1 m m+1                s-1
				// +-----------------------------------------------+
				// 0             n-1 n n+1                        l-1
				//
				// From (m+1) + (n+1) = k
				// get: m + n = k - 2
				// k-th = S[m] if L[n] < S[m] <= L[n+1]
				//        L[n] if S[m] < L[n] <= S[m+1]
				//        S[m] if S[m] == L[n]
				//        max(S[m-1], L[n+1]) if S[m] > L[n+1]
				//        max(S[m+1], L[n-1]) if L[n] > S[m+1]

				int low = 0;
				int high = std::min<int>(k - 1, shortLength - 1);
				while (low <= high) {
					// (1) If low < high - 1, then low < m < high
					// (2) If low = high - 1, then low = m < high
					// (3) If low = high, then low = m = high
					int m = (low + high) >> 1;
					int n = k - m - 2;
					if (n >= longLength) {
						// this may happen if k > m + longLength + 1
						low = low < m ? m : m + 1;
					} else if (shortArray[m] > longArray[n]) {
						if (n == longLength - 1 || shortArray[m] <= longArray[n + 1]) {
							return shortArray[m];
						} else {
							if (m < high) {
								// Case (1) or (2)
								high = m;
							} else {
								// Case (3)
								// s[m] > l[n] and s[m] > l[n+1]
								// Compare s[m-1] and l[n+1] as one of them is the k-th
								if (m - 1 >= 0 && shortArray[m - 1] > longArray[n + 1])
									return shortArray[m - 1];
								else return longArray[n + 1];
							}
						}
					} else if (longArray[n] > shortArray[m]) {
						if (m == shortLength - 1 || longArray[n] <= shortArray[m + 1]) {
							return longArray[n];
						} else {
							if (low < m) {
								// Case (1)
								low = m;
							} else {
								// Case (2) or (3)
								// l[n] > s[m] and l[n] > s[m+1]
								// Compare l[n-1] and s[m+1] as one of them is the k-th
								if (n - 1 >= 0 && longArray[n - 1] > shortArray[m + 1])
									return longArray[n - 1];
								else return shortArray[m + 1];
							}
						}
					} else {
						return shortArray[m];
					}
				}

				throw runtime_error(String::Format("Unable to find %d-th smallest element", k));
			}

			template<class T> static T Solve2(int k, const T * input1, int length1, const T * input2, int length2)
			{
				if (input1 == nullptr) throw invalid_argument("input1 is a nullptr");
				if (length1 <= 0) throw invalid_argument(String::Format("length1 %d is invalid", length1));
				if (input2 == nullptr) throw invalid_argument("input2 is a nullptr");
				if (length2 <= 0) throw invalid_argument(String::Format("length2 %d is invalid", length2));
				if (k <= 0) throw invalid_argument(String::Format("k %d is invalid", k));
				if (k > length1 + length2) throw invalid_argument(String::Format("k(%d) is greater than length1(%d) + length2(%d)", k, length1, length2));

				if (k == 1) {
					return std::min<T>(input1[0], input2[0]);
				}

				// +-----------------------------------+
				// 0             m m+1                s-1
				// +-------------------------------------------+
				// 0             n n+1                        l-1
				//
				// find m + n = k - 2
				// k-th = S[m] if L[n] < S[m]
				//        L[n] if S[m] < L[n]
				//        S[m] if S[m] == L[n]

				int m = -1;
				int n = -1;
				while (m + n < k - 2) {
					if (m < length1 - 1 && n < length2 - 1) {
						if (input1[m + 1] <= input2[n + 1]) {
							m++;
						} else {
							n++;
						}
					} else if (m < length1 - 1 && n == length2 - 1) {
						m++;
					} else if (m == length1 - 1 && n < length2 - 1) {
						n++;
					} else {
						break;
					}
				}

				if (m + n == k - 2) {
					if (n == -1) {
						return input1[m];
					} else if (m == -1) {
						return input2[n];
					} else {
						return std::max<T>(input1[m], input2[n]);
					}
				} else {
					throw runtime_error(String::Format("Unable to find %d-th smallest element", k));
				}
			}
		};

		class Intersection {
		public:
			// Find the first common element of two sorted arrays
			// Return a pair of indices of found element. If not found, then return a pair (-1, -1)
			// http://leetcode.com/2010/03/here-is-phone-screening-question-from.html
			template<class T> static pair<int, int> Solve(const T * input1, int length1, const T * input2, int length2)
			{
				if (input1 == nullptr) throw invalid_argument("input1 is a nullptr");
				if (length1 <= 0) throw invalid_argument(String::Format("length1 %d is invalid", length1));
				if (input2 == nullptr) throw invalid_argument("input2 is a nullptr");
				if (length2 <= 0) throw invalid_argument(String::Format("length2 %d is invalid", length2));

				const T * shortArray;
				int shortLength;
				const T * longArray;
				int longLength;

				if (length1 <= length2) {
					shortLength = length1;
					shortArray = input1;
					longLength = length2;
					longArray = input2;
				} else {
					shortLength = length2;
					shortArray = input2;
					longLength = length1;
					longArray = input1;
				}

				for (int i = 0; i < shortLength; i++) {
					int j = BinarySearch::Search<T>(shortArray[i], longArray, longLength, true);
					if (j != -1) {
						if (shortArray == input1) {
							return make_pair(i, j);
						} else {
							return make_pair(j, i);
						}
					}
				}

				return make_pair(-1, -1);
			}

			template<class T> static pair<int, int> Solve2(const T * input1, int length1, const T * input2, int length2)
			{
				if (input1 == nullptr) throw invalid_argument("input1 is a nullptr");
				if (length1 <= 0) throw invalid_argument(String::Format("length1 %d is invalid", length1));
				if (input2 == nullptr) throw invalid_argument("input2 is a nullptr");
				if (length2 <= 0) throw invalid_argument(String::Format("length2 %d is invalid", length2));

				int i = 0;
				int j = 0;
				while (i < length1 && j < length2) {
					if (input1[i] < input2[j]) {
						i++;
					} else if (input1[i] > input2[j]) {
						j++;
					} else {
						return make_pair(i, j);
					}
				}

				return make_pair(-1, -1);
			}
		};
	};
}