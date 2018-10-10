// FindDuplicateInteger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <algorithm>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	array<int, 20> input;

	generate(input.begin(), input.end(), rand);
	for (size_t i = 0; i < input.size(); i ++)	{
		printf("%d ", input[i]);
	}
	printf("\n");
	
	for_each (input.begin(), input.end(), [](int& x)->void { x = x % 20;});
	for (size_t i = 0; i < input.size(); i ++)	{
		printf("%d ", input[i]);
	}
	printf("\n");

	for (size_t j = 1; j < input.size(); j ++) {
		int c = input[j];
		int k = j - 1;
		while (k >= 0 && input[k] > c) {
			input[k + 1] = input[k];
			k --;
		}
		input[k + 1] = c;
		if (k >= 0 && input[k] == c) {
			printf("%d ", c);
		}
	}
	printf("\n");

	return 0;
}

