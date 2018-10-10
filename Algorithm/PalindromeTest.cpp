#include "Header.h"

void PalindromeTest::Init(void)
{
	Add("Palindrome", [&]() {
		string s = "character";
		string t;
		string a;
		cout << "Input: " << s << endl;
		Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));

		s = "racecar";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));

		s = "raceecar";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));

		s = "racefcar";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));

		s = "ra";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));

		s = "rac";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));
	});

	Add("Number", [&]() {
		auto check = [&](unsigned int n, bool e) {
			bool r = Palindrome::IsPalindrom(n);
			Logger().WriteInformation("%d is %s palindrome\n", n, r ? "" : "not");
			ASSERT1(r == e);
		};

		check(3, true);
		check(33, true);
		check(23, false);
		check(232, true);
		check(1231, false);
		check(12344321, true);
		check(123454321, true);
		check(1234567, false);
	});

	Add("String", [&]() {
		auto check = [&](const string & s, bool e) {
			bool r = Palindrome::IsPalindrom(s);
			Logger().WriteInformation("\"%s\" is %s palindrome\n", s.c_str(), r ? "" : "not");
			ASSERT1(r == e);
		};

		check("", true);
		check("1", true);
		check("a", true);
		check(",", true);
		check("22", true);
		check("23", false);
		check("ab", false);
		check("a1", false);
		check(":3", true);
		check("a;", true);
		check("?b", true);
		check("# #4**", true);
		check("# c**", true);
		check("a, b&*() A;", true);
		check("A man, a plan, a canal: Panama", true);
		check("race a car", false);
		check("^%(&*%$%(", true);
		check("A^%(&*%$%(a", true);
		check("^%9(&*%$9%(", true);
	});

	Add("Substring1", [&]() {
		string i = "babcbabcbaccba";
		string o;
		Logger().WriteInformation("%s\n", i.c_str());
		Palindrome::LongestSubstring(i, o);
		Logger().WriteInformation("%s\n", o.c_str());
		ASSERT1(o == "abcbabcba");
	});

	Add("Substring2", [&]() {
		string i = "xabcbabcbayzaw";
		string o1;
		Logger().WriteInformation("%s\n", i.c_str());
		Palindrome::LongestSubstring(i, o1);
		Logger().WriteInformation("%s\n", o1.c_str());
		string o2;
		Palindrome::LongestSubsequenceByTable(i, o2);
		Logger().WriteInformation("%s\n", o2.c_str());
		string o3;
		Palindrome::LongestSubsequenceByArray(i, o3);
		Logger().WriteInformation("%s\n", o3.c_str());
		ASSERT1(o1 == "abcbabcba");
		ASSERT1(o2 == o1);
		ASSERT1(o3 == o1);
	});

	Add("Substring3", [&]() {
		string i = "xabcbabcbayztw";
		string o1;
		Logger().WriteInformation("%s\n", i.c_str());
		Palindrome::LongestSubstring(i, o1);
		Logger().WriteInformation("%s\n", o1.c_str());
		string o2;
		Palindrome::LongestSubsequenceByTable(i, o2);
		Logger().WriteInformation("%s\n", o2.c_str());
		string o3;
		Palindrome::LongestSubsequenceByArray(i, o3);
		Logger().WriteInformation("%s\n", o3.c_str());
		ASSERT1(o1 == "abcbabcba");
		ASSERT1(o2 == o1);
		ASSERT1(o3 == o1);
	});

	Add("Partition", [&]() {
		auto check = [&](const string & input) {
			Logger().WriteInformation("Input: %s\n", input.c_str());
			vector<vector<string>> partitions = Palindrome::Partition(input);
			vector<string> mincut = Palindrome::MinCutPartition(input);
			size_t mincutSize2 = (size_t)Palindrome::MinCutPartition2(input);
			Logger().WriteInformation("    %d partitions:\n", partitions.size());
			size_t mincutSize = input.length();
			for_each(partitions.begin(), partitions.end(), [&](vector<string> & partition) {
				if (partition.size() < mincutSize) mincutSize = partition.size();
				Logger().WriteInformation("      [");
				for (size_t i = 0; i < partition.size(); i++) {
					if (i != 0) {
						Logger().WriteInformation(", ");
					}
					Logger().WriteInformation("%s", partition[i].c_str());
				}
				Logger().WriteInformation("]\n");
			});
			Logger().WriteInformation("    Min cuts: %d, %d\n", mincut.size() - 1, mincutSize2);
			Logger().WriteInformation("      [");
			for (size_t i = 0; i < mincut.size(); i++) {
				if (i != 0) {
					Logger().WriteInformation(", ");
				}
				Logger().WriteInformation("%s", mincut[i].c_str());
			}
			Logger().WriteInformation("]\n");
			ASSERT1(mincut.size() == mincutSize);
			ASSERT1(mincut.size() == mincutSize2 + 1);
		};

		check("a");
		check("aa");
		check("ab");
		check("aaa");
		check("aab");
		check("abb");
		check("aba");
		check("aaaa");
		check("aaab");
		check("aaba");
		check("abaa");
		check("baaa");
		check("aabb");
		check("abab");
		check("baab");
		check(string(10, 'a'));
	});
}
