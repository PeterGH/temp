#include "Rotation.h"

namespace My {
	void Rotation::Left(char * input, int length, int distance)
	{
		if (input == nullptr) return;
		if (length <= 0) return;
		if (distance <= 0) return;
		distance = distance % length;
		if (distance == 0) return;

		int i = 0;
		int j = length - 1;
		int k = distance;
		// input[i..k-1] and input[k..j]
		while (i < k && k <= j) {
			if (k - i < j - k + 1) {
				// Left range is shorter
				// input[i..k-1], input[k..j-(k-i)], input[j-(k-i)+1..j]
				Rotation::Swap(&input[i], &input[j-(k-i)+1], k-i);
				j = j - (k-i);
			} else if (k - i > j - k + 1) {
				// Right range is shorter
				// input[i..i+(j-k)], input[i+(j-k)+1..k-1], input[k..j]
				Rotation::Swap(&input[i], &input[k], j-k+1);
				i = i + (j-k) + 1;
			} else {
				// Both ranges have the same length
				Rotation::Swap(&input[i], &input[k], k - i);
				break;
			}
		}
	}

	void Rotation::Right(char * input, int length, int distance)
	{
		if (input == nullptr) return;
		if (length <= 0) return;
		if (distance <= 0) return;
		distance = distance % length;
		if (distance == 0) return;
		Rotation::Left(input, length, length - distance);
	}

	void Rotation::Swap(char * first, char * second, int count)
	{
		char t;
		for (int i = 0; i < count; i++) {
			t = first[i];
			first[i] = second[i];
			second[i] = t;
		}
	}
}