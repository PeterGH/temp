#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include "Partition.h"
#include "Sort.h"
using namespace std;
namespace Test {
	class _declspec(dllexport) Search {
	public:
		
		// Find a subarray of contiguous elements whose sum is maximized
		// If array contains both positive and negative numbers, return the maximum subarray
		// If array contains positive numbers, return entire array A
		// If array contains non-positive numbers, return the maximum number
		// Parameter sum is the summation of the returned subarray
		// Parameters start and end are the start and end indices of the returned subarray
		template<class T> static void MaxSum(const T * input, int length, int & start, int & end, T & sum);
		template<class T> static void MaxSum2(const T * input, int length, int & start, int & end, T & sum);
	};

	template<class T> void Search::MaxSum(const T * input, int length, int & start, int & end, T & sum)
	{
		start = -1;
		end = -1;
		sum = INT_MIN;

		if (input == nullptr || length <= 0) return;

		// Track the last maximum sum so far
		start = 0;
		end = 0;
		sum = 0;

		// Track the current streak
		int l = 0; // Beginning
		T c = 0; // Cumulative sum up to current element
		int max = 0; // The index of the maximum element seen so far

		for (int i = 0; i < length; i++) {
			c += input[i];

			if (c > sum) {
				// Current element is positive and the current sum is larger than the last one.
				// Update the last seen maximum sum
				start = l;
				end = i;
				sum = c;
			} else if (c <= 0) {
				// Current element is negative and everything cancel out
				// Reset and start from the next element
				l = i + 1;
				c = 0;
			}

			// Record the max element so far
			if (input[i] >= input[max]) max = i;
		}

		if (sum <= 0) {
			// All elements are zero or negative
			// Return the maximum element
			start = max;
			end = max;
			sum = input[max];
		}
	}

	template<class T> void Search::MaxSum2(const T * input, int length, int & start, int & end, T & sum)
	{
		start = -1;
		end = -1;
		sum = INT_MIN;

		if (input == nullptr || length <= 0) return;

		int minIndex = -1;
		int minSum = 0; // sum[0..minIndex]
		int s = 0; // sum[0..i]
		for (int i = 0; i < length; i++) {
			s += input[i];
			int d = s - minSum;
			if (d >= sum) {
				start = minIndex + 1;
				if (d != sum || input[i] != 0 || sum == 0) end = i;
				sum = d;
			}
			if (s <= minSum) {
				minSum = s;
				minIndex = i;
			}
		}
	}

}
