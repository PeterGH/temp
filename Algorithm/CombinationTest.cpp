#include "Header.h"

void CombinationTest::Init(void)
{
	Add("Subsets", [&]() {
		auto check = [&](vector<int> & s) {
			Logger().WriteInformation("%d elements\n", s.size());
			Logger().Print(s);
			int expectSize = 1 << s.size();
			vector<vector<int>> sets = Combination::All(s);
			int actualSize = sets.size();
			Logger().WriteInformation("%d subsets\n", actualSize);
			for_each(sets.begin(), sets.end(), [&](vector<int> & ss) {
				Logger().Print(ss);
				bool sorted = is_sorted(ss.begin(), ss.end());
				ASSERT1(sorted);
			});
			ASSERT1(actualSize == expectSize);
			vector<vector<int>> uniquesets = Combination::Unique(s);
			int actualUniqueSize = uniquesets.size();
			Logger().WriteInformation("%d unique subsets\n", actualUniqueSize);
			for_each(uniquesets.begin(), uniquesets.end(), [&](vector<int> & ss) {
				Logger().Print(ss);
				bool sorted = is_sorted(ss.begin(), ss.end());
				ASSERT1(sorted);
			});
			ASSERT1(actualUniqueSize <= expectSize);
			Logger().WriteInformation("\n");
		};

		check(vector<int> { 1, 2, 2 });
	});

	Add("NSelectK", [&]() {
		auto check = [&](int n, int k) {
			vector<vector<int>> sets = Combination::NSelectK(n, k);
			vector<vector<int>> sets2 = Combination::NSelectK2(n, k);
			vector<vector<int>> sets3 = Combination::NSelectK3(n, k);
			vector<vector<int>> sets4 = Combination::NSelectK4(n, k);
			Logger().WriteInformation("NSelectK(%d, %d):\n", n, k);
			Logger().Print(sets);
			Logger().WriteInformation("NSelectK2(%d, %d):\n", n, k);
			Logger().Print(sets2);
			Logger().WriteInformation("NSelectK3(%d, %d):\n", n, k);
			Logger().Print(sets3);
			Logger().WriteInformation("NSelectK4(%d, %d):\n", n, k);
			Logger().Print(sets4);
			ASSERT1(sets.size() == sets2.size());
			ASSERT1(sets.size() == sets3.size());
			ASSERT1(sets.size() == sets4.size());
		};

		check(1, 1);
		check(2, 1);
		check(2, 2);
		check(3, 1);
		check(3, 2);
		check(3, 3);
		check(4, 1);
		check(4, 2);
		check(4, 3);
		check(4, 4);
		check(5, 1);
		check(5, 2);
		check(5, 3);
		check(5, 4);
		check(5, 5);
	});
}