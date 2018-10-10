#pragma once

#include <functional>
#include "BinarySearch.h"
#include "Matrix.h"
#include "Random.h"

using namespace std;

namespace Test {
	class _declspec(dllexport) Partition {
	public:
		
		// Divide input into K partitions such that the maximum sum over each partition is minimized.
		// The elements of input should not be moved, and partitions should not overlap.
		template<class T> static T MinMaxPartitionSum(const T * input, int length, int * indices, int partitions);
		template<class T> static T MinMaxPartitionSum2(const T * input, int length, int * indices, int partitions);
	};

	// http://leetcode.com/2011/04/the-painters-partition-problem.html
	// input        I_0 I_1 I_2 ...... I_i
	// partitions   p_0 p_1 p_2 ...... p_j
	// Let S(i, j) be the solution with input[0..i] and partitions[0..j]
	// S(i, j) = min{
	//                max{S(i-1, j-1), I_i},
	//                max{S(i-2, j-1), I_(i-1) + I_i},
	//                max{S(i-3, j-1), I_(i-2) + I_(i-1) + I_i},
	//                ......
	//                max{S(j, j-1),   I_(j+1) + I_(j+2) + ... + I_(i-2) + I_(i-1) + I_i},
	//                max{S(j-1, j-1), I_j + I_(j+1) + ... + I_(i-2) + I_(i-1) + I_i}
	//           }
	//
	// S(i,j)    0       1       2       3       4      ...... j-2       j-1       j
	//   0      (0,0)
	//   1      (1,0)   (1,1)
	//   2      (2,0)   (2,1)   (2,2)
	//   3      (3,0)   (3,1)   (3,2)   (3,3)
	//   4      (4,0)   (4,1)   (4,2)   (4,3)   (4,4)
	//           ......
	//   j-1    (j-1,0) (j-1,1) (j-1,2) (j-1,3) (j-1,4) ...... (j-1,j-2) (j-1,j-1)
	//   j      (j,0)   (j,1)   (j,2)   (j,3)   (j,4)   ...... (j,j-2)   (j,j-1)   (j,j)
	//   j+1    (j+1,0) (j+1,1) (j+1,2) (j+1,3) (j+1,4) ...... (j+1,j-2) (j+1,j-1) (j+1,j)
	//           ......
	//   i-1    (i-1,0) (i-1,1) (i-1,2) (i-1,3) (i-1,4) ...... (i-1,j-2) (i-1,j-1) (i-1,j)
	//   i      (i,0)   (i,1)   (i,2)   (i,3)   (i,4)   ...... (i,j-2)   (i,j-1)   (i,j)
	//
	template<class T> T Partition::MinMaxPartitionSum(const T * input, int length, int * indices, int partitions)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
		if (indices == nullptr) throw invalid_argument("indices is nullptr");
		if (partitions > length) throw invalid_argument(String::Format("length %d is less than partitions %d", length, partitions));

		Matrix<T> S(length, partitions);
		Matrix<int> I(length, partitions);

		// Initialize column 0
		S(0, 0) = input[0];
		I(0, 0) = 0;
		for (int i = 1; i < length; i++) {
			// input[0..i] assigned to partition[0]
			S(i, 0) = S(i-1, 0) + input[i];
			// partition[0] starts at index 0
			I(i, 0) = 0;
		}

		for (int j = 1; j < partitions; j++) {
			for (int i = j; i < length; i++) {
				T s = input[i];
				S(i, j) = std::max(S(i - 1, j - 1), s);
				I(i, j) = i;
				for (int k = i-2; k >= j - 1; k--) {
					s += input[k+1];
					T maxS = std::max(S(k,j-1), s);
					if (maxS <= S(i, j)) {
						S(i, j) = maxS;
						I(i, j) = k + 1;

						// Given { 100, 100, 100, 100, 100, 100, 100, 100, 100 } and 4 partitions
						// If maxS < S(i, j), then the partions are:
						//   300 = sum{A[0..2]} = 100 + 100 + 100
                        //   300 = sum{A[3..5]} = 100 + 100 + 100
                        //   200 = sum{A[6..7]} = 100 + 100
                        //   100 = sum{A[8..8]} = 100
						// If maxS <= S(i, j), then the partions are:
						//   200 = sum{A[0..1]} = 100 + 100
                        //   200 = sum{A[2..3]} = 100 + 100
                        //   200 = sum{A[4..5]} = 100 + 100
                        //   300 = sum{A[6..8]} = 100 + 100 + 100

						// For some k1 < k2, the following two values may be the same
						//   max{S(k1, j-1), I_(k1+1) + ... + I_i}
	                    //   max{S(k2, j-1), I_(k2+1) + ... + I_i}
						// We want to partition at k1+1 instead of k2+1 so that the last partion would not necessarily take too few load
					}
				}
			}
		}

		// S.Print();
		// I.Print();

		int i = length - 1;
		for (int j = partitions - 1; j >= 0; j--) {
			indices[j] = I(i, j);
			i = indices[j] - 1;
		}

		return S(length - 1, partitions - 1);
	}

	// This implementation has some problem getting wrong indices even though the return value can be correct.
	template<class T> T Partition::MinMaxPartitionSum2(const T * input, int length, int * indices, int partitions)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
		if (indices == nullptr) throw invalid_argument("indices is nullptr");
		if (partitions > length) throw invalid_argument(String::Format("length %d is less than partitions %d", length, partitions));

		T min = input[0];
		T max = input[0];
		T sum = 0;
		for (int i = 0; i < length; i++) {
			sum += input[i];
			if (input[i] > max) {
				max = input[i];
			}
			if (input[i] < min) {
				min = input[i];
			}
		}

		if (partitions == length) {
			// One input item per partition
			for (int i = 0; i < partitions; i++) {
				indices[i] = i;
			}
			// The cost is the maximum of input items
			return max;
		}

		T cost = min;

		// Calculate partitions
		// Update indices and cost accordingly
		auto GetPartitions = [&](T m) -> int {
			// temporary sum per partition
			T s = 0;
			// maximum sum
			T c = 0;
			indices[0] = 0;
			int j = 1;
			for (int i = 0; i < length; i++) {
				s += input[i];
				if (s >= m && i != length - 1) {
					if (j < partitions) {
						indices[j] = i;
					}
					j++;
					s -= input[i];
					if (s > c) {
						c = s;
					}
					s = input[i];
				}
			}

			if (s > c) {
				c = s;
			}

			cost = c;
			return j;
		};

		T low = max;
		T high = sum;

		int lowPartitions = GetPartitions(low);

		if (lowPartitions < partitions) {
			low = min;
			high = max;
		}

		while (low < high) {
			T mid = (low + high) >> 1;
			int midPartions = GetPartitions(mid);
			cout << low << ", " << mid << ", " << high << ", " << midPartions << ", " << cost << endl;

			if (midPartions > partitions) {
				low = mid + 1;
			} else if (midPartions < partitions) {
				high = mid - 1;
			} else {
				// low = (low + mid) >> 1;
				// high = (mid + high) >> 1;
				return cost;
			}
		}

		if (low == high) {
			GetPartitions(low);
		}

		return cost;
	}
}