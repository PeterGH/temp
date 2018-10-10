#include "Header.h"

void FiniteAutomationTest::Init(void)
{
	Add("Invalid Pattern", [&]() {
		ASSERTERROR(FiniteAutomation fa(nullptr), invalid_argument);
		ASSERTERROR(FiniteAutomation fa(""), invalid_argument);
		ASSERTERROR(FiniteAutomation fa("test"), invalid_argument);
	});

	Add("Invalid Input", [&]() {
		FiniteAutomation fa("a");
		vector<int> i = fa.SearchString("", 0);
		ASSERT1(i.size() == 0);
	});

	Add("1", [&]() {
		FiniteAutomation fa("a");
		fa.Print();

		vector<int> indices = fa.SearchString("b", 1);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("a", 1);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("ba", 2);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 1);

		indices = fa.SearchString("ab", 1);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("bb", 2);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("aa", 2);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 0);
		ASSERT1(indices[1] == 1);

		indices = fa.SearchString("baa", 3);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 1);
		ASSERT1(indices[1] == 2);

		indices = fa.SearchString("aba", 3);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 0);
		ASSERT1(indices[1] == 2);

		indices = fa.SearchString("bba", 3);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 2);
	});

	Add("2", [&]() {
		FiniteAutomation fa("aa");
		fa.Print();

		vector<int> indices = fa.SearchString("b", 1);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("a", 1);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("aa", 2);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("ba", 2);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("baa", 3);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 1);

		indices = fa.SearchString("bab", 3);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("aab", 3);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("aaa", 3);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 0);
		ASSERT1(indices[1] == 1);
	});
}