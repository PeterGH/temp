#pragma once
namespace My {
	template<class T> class MinMax {
	public:
		static void Get(const T * input, int length, int & minIndex, int & maxIndex);
	};

	// minIndex will be the index of the minimum value (first index if there are more than on minimum value
	// maxIndex will be the index of the maximum value (last index if there are more than on maximum value
	template<class T> void MinMax<T>::Get(const T * input, int length, int & minIndex, int & maxIndex)
	{
		minIndex = -1;
		maxIndex = -1;
		if (input == nullptr || length <= 0) return;
		
		int startIndex = 0;
		if (length % 2 == 1) {
			minIndex = 0;
			maxIndex = 0;
			startIndex = 1;
		} else {
			if (input[0] <= input[1]) {
				minIndex = 0;
				maxIndex = 1;
			} else {
				minIndex = 1;
				maxIndex = 0;
			}

			startIndex = 2;
		}

		for (int i = startIndex; i < length; i += 2) {
			if (input[i] <= input[i+1]) {
				if (input[i] < input[minIndex]) minIndex = i;
				if (input[i+1] >= input[maxIndex]) maxIndex = i+1;
			} else {
				if (input[i+1] < input[minIndex]) minIndex = i+1;
				if (input[i] >= input[maxIndex]) maxIndex = i;
			}
		}
	}
}