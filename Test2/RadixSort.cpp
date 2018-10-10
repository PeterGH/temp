#include "RadixSort.h"
#include <functional>
#include <algorithm>

namespace My {
	
	// Assume all the MRInteger instances in the vector have the same bases.
	void RadixSort::Sort(std::vector<MRInteger> & numbers)
	{
		std::function<std::function<bool(const MRInteger &, const MRInteger &)> (int)> compare = [](int radix) {
			std::function<bool(const MRInteger &, const MRInteger &)> c = [=](const MRInteger & left, const MRInteger & right) -> bool {
				// It will fail if I change < to <=
				return left[radix] < right[radix];
			};

			return c;
		};

		for (unsigned int i = 0; i < numbers.front().Length(); i ++) {
			std::function<bool(const MRInteger &, const MRInteger &)> c = compare(i);
			std::stable_sort(numbers.begin(), numbers.end(), c);
		}
	}
}
