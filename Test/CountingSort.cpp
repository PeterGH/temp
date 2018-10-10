#include "CountingSort.h"

namespace Test {

	void CountingSort::GetRange(const int * input, int length, int & minValue, int & range)
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

	// Not in-place. Stable.
	void CountingSort::Sort(const int * input, int length, int * output)
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
			count[delta] ++;
		}

		for (int i = 1; i < range; i++) {
			count[i] += count[i - 1];
		}

		for (int i = length - 1; i >= 0; i--) {
			int delta = input[i] - minValue;
			output[count[delta] - 1] = input[i];
			count[delta] --;
		}
	}

	// In-place sort. Not stable.
	void CountingSort::Sort(int * input, int length)
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
				count[delta] --;
				bits.Set(currentIndex);
				if (currentIndex == i) break;
				int nextValue = input[currentIndex];
				input[currentIndex] = input[i];
				input[i] = nextValue;
			}
		}
	}
}
