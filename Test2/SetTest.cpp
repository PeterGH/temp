#include "SetTest.h"
#include <time.h>

void SetTest::Init(void)
{
	Add("Set", [&](){
		srand((unsigned int)time(NULL));
		int n = 100;
		set<int> sorted;
		for (int i = 0; i < n; i++) {
			sorted.insert(rand());
		}

		bool s = is_sorted(sorted.begin(), sorted.end());
		printf_s("The set is %ssorted\n", s ? "" : "not ");

		for (set<int>::iterator i = sorted.begin(); i != sorted.end(); i ++) {
			printf_s("\t%d", *i);
		}

		printf_s("\n");
	});
}
