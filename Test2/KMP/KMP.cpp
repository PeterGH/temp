// KMP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Algorithm\KMP.h"
#include <algorithm>
using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 3) {
		printf_s("Usage: %s [Pattern, English characters in the lower case] [Input string]", argv[0]);
		return -1;
	}

	char * pattern = argv[1];
	My::KMP kmp(pattern);
	kmp.Print();
	char * input = argv[2];
	vector<int> indices = kmp.SearchString(input, strlen(input));
	for_each (indices.begin(), indices.end(), [](int i) {
		printf_s("Found a match at index %d\n", i);
	});

	return 0;
}

