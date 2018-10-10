#pragma once

#include <functional>
#include <stdexcept>
#include "String.h"

using namespace std;

namespace Test {
	class Partition {
	public:

		// Reorder input[low..high] such that it is partioned at the indices provided through an array.
		// Parameter low and high give the range of elements in input.
		// Parameter first and last give the range of indices used to partion input.
		// The elements of indices are sorted and are valid indices of input array.
		template<class T> static void PartitionArrayByOrders(T * input, int low, int high, int * indices, int first, int last)
		{
			if (input == nullptr) throw invalid_argument("input is nullptr");
			if (low < 0) throw invalid_argument(String::Format("low %d is less than zero", low));
			if (high < low) throw invalid_argument(String::Format("low %d is greater than high %d", low, high));
			if (indices == nullptr) throw invalid_argument("indices is nullptr");
			if (first < 0) throw invalid_argument(String::Format("first %d is less than zero", first));
			if (last < first) throw invalid_argument(String::Format("first %d is greater than last %d", first, last));
			if (last - first > high - low) throw invalid_argument(String::Format("There are %d indices but only %d elements", last - first, high - low));
			if (low > indices[first]) throw invalid_argument(String::Format("low %d is greater than indices[%d] %d", low, first, indices[first]));
			if (high < indices[last]) throw invalid_argument(String::Format("high %d is less than indices[%d] %d", high, last, indices[last]));
			if (low == high) return;

			if (first == last) {
				if (low <= indices[first] && indices[first] <= high) {
					PartitionArrayByOrder(input, low, high, indices[first] - low);
				}

				return;
			}

			int m = PartitionArrayRandomly(input, low, high);

			// Find the last element index in indices less than m
			int k = first + BinarySearch::PositionToInsert<int>(m, &indices[first], last - first + 1);

			// low ................................ m ............................... high
			//        indices[fist] .... indices[k]   indices[k+1] .... indices[last]
			// first <= k < last, if indices[first] < m < indices[last]
			//
			// low .. m ............................................................. high
			//      k   indices[fist] ................................. indices[last]
			// k < first, if m <= indices[first]
			//
			// low ............................................................... m .... high
			//       indices[fist] ................................. indices[last]   k
			// last <= k, if indices[last] < m

			if (first <= k && k < last) {
				// indices[k] < m <= indices[k+1]
				if (m == indices[k + 1]) {
					PartitionArrayByOrders(input, low, m - 1, indices, first, k);
					if (k + 1 < last) PartitionArrayByOrders(input, m + 1, high, indices, k + 2, last);
				} else {
					PartitionArrayByOrders(input, low, m - 1, indices, first, k);
					PartitionArrayByOrders(input, m + 1, high, indices, k + 1, last);
				}
			} else if (k < first) {
				// m <= indices[first]
				if (m == indices[first])
					PartitionArrayByOrders(input, m + 1, high, indices, first + 1, last);
				else
					PartitionArrayByOrders(input, m + 1, high, indices, first, last);
			} else if (last <= k) {
				PartitionArrayByOrders(input, low, m - 1, indices, first, last);
			}
		}

		// The k-th quantiles of an array with length are k-1 elements evenly dividing the array so that
		// the set of subarrays is sorted, i.e., each element of a subarray is not less than each element of its preceeding subarray,
		// and not greater than each element of its succeeding subarray.
		// This method partition the input array and return the indices of the k-1 elements forming the quantiles.
		// Parameter order defines the order of quantiles, i.e., array indices will be used to return order-1 indices.
		template<class T> static void PartitionArrayByQuantiles(T * input, int length, int * indices, int order)
		{
			if (input == nullptr) throw invalid_argument("input is nullptr");
			if (length <= 0) throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
			if (indices == nullptr) throw invalid_argument("indices is nullptr");
			if (order < 1) throw invalid_argument(String::Format("order %d is less than 1", order));
			if (order > length) throw invalid_argument(String::Format("order %d is greater than length %d", order, length));

			if (order == 1) return;

			int step = length / order;
			int remainder = length % order;

			// 0                                                                                                         L-1
			// +----------+----------+----------+----------+----------+----------+----------+----------+----------+-------+
			// 0         step       2*step             (R-1)*step   R*step                         (O-1)*step   O*step  O*step+R-1
			//            0          1                    R-2        R-1         R                    O-2

			int s = 0;
			if (step > 1) {
				for (int i = 0; i < remainder; i++) {
					indices[i] = s + step;
					s = indices[i];
				}

				for (int i = remainder; i < order - 1; i++) {
					indices[i] = s + step - 1;
					s = indices[i];
				}
			} else {
				for (int i = 0; i < order - 1; i++) {
					indices[i] = s + step;
					s = indices[i];
				}
			}

			PartitionArrayByOrders(input, 0, length - 1, indices, 0, order - 2);
		}

	};
}