#include "Header.h"

void KMPTest::Init(void)
{
	Add("KMP", [&]() {
		for (int i = 0; i < 50; i++) {
			Logger().WriteInformation("Run %d\n", i);
			string pattern = String::Random(string("abcdefg"), 1 + rand() % 5);
			string input = String::Random(string("abcdefg"), 1 + rand() % 1000);
			KMP kmp(pattern.c_str());
			// kmp.Print();
			vector<int> indices = kmp.SearchString(input.c_str(), strlen(input.c_str()));
			printf_s("Pattern: %s\n", pattern.c_str());
			printf_s("Input: %s\n", input.c_str());
			for_each(indices.begin(), indices.end(), [](int i) {
				printf_s("Found a match at index %d\n", i);
			});
		}
	});
}