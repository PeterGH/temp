#pragma once
#include <functional>
using namespace std;
namespace Test {
	class Count {
	public:
		// An inversion is a pair {input[i], input[j]} such that input[i] > input[j] when i < j.
		// We can extend the concept to two sub arrays of input, and the set of inversions
		// contains every inversion whose elements each falls into different sub arrays, e.g.,
		// input[i] is in the first sub array while input[j] is in the second.
		// Sorting the two sub arrays separately does not change the count of inversions
		// between the two sub arrays.
		// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
		// count inversions between input[head..(middle-1)] and input[middle..tail] by merging
		// them into a sorted array input[head..tail].
		template<class T> static int Inversions(T * input, size_t length);
	};

	template<class T> int Count::Inversions(T * input, size_t length)
	{
		if (input == nullptr || length <= 1) return 0;

		// Count inversions between a[h..(m-1)] and a[m..t], assuming both subarrays are sorted
		function<int(T *, int, int, int)> merge = [&](T * a, int h, int m, int t)->int{
			int c = 0;
			// head and middle point to the heads of two sub sorted arrays.
			while (h < m && m <= t) {
				if (a[h] <= a[m]) {
					h++;
				} else {
					T x = a[m];
					for (int i = m; i > (int)h; i--) {
						a[i] = a[i - 1];
					}
					a[h] = x;
					// There (m - h) elements moved.
					// Each of them paired with a[m] is an inversion.
					c += (m - h);
					// Move to the next pair of elements
					h++;
					m++;
				}
			}

			return c;
		};

		function<int(T *, int, int)> count = [&](T * a, int h, int t)->int{
			if (a == nullptr || h >= t) return 0;
			int c = 0;
			if (h < t) {
				int m = h + ((t - h) >> 1) + 1;
				c += count(a, h, m - 1);
				c += count(a, m, t);
				c += merge(a, h, m, t);
			}
			return c;
		};

		return count(input, 0, length - 1);
	}
}