// FiniteAutomation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Algorithm\FiniteAutomation.h"

int main(int argc, char * argv[])
{
	if (argc < 3) {
		printf_s("Usage: %s [Pattern, English characters in the lower case] [Input string]", argv[0]);
		return -1;
	}

	char * pattern = argv[1];
	My::FiniteAutomationWithWildChar fa(pattern, strlen(pattern));
	fa.Print();
	char * input = argv[2];
	multimap<int, int> indices = fa.SearchString(input, strlen(input));
	for_each (indices.begin(), indices.end(), [](pair<int, int> it) {
		printf_s("\t%d\t%d\n", it.first, it.second);
	});

	return 0;
}

