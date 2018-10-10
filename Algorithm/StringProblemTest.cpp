#include "Header.h"

void StringProblemTest::Init(void)
{
	Add("WordLadder", [&]() {
		auto check = [&](const string & start, const string & end, const unordered_set<string> & dict, int expect) {
			Logger().WriteInformation("Dictionary: [");
			int i = 0;
			for_each(dict.begin(), dict.end(), [&](string w) {
				if (i != 0) {
					Logger().WriteInformation(" ");
				}
				Logger().WriteInformation("%s", w.c_str());
				i++;
			});
			Logger().WriteInformation("]\n");
			Logger().WriteInformation("    Start:   %s\n", start.c_str());
			Logger().WriteInformation("    End:     %s\n", end.c_str());
			int length = StringProblem::WordLadder::Solve(start, end, dict);
			int length2 = StringProblem::WordLadder::Solve2(start, end, dict);
			int length3 = StringProblem::WordLadder::Solve3(start, end, dict);
			vector<vector<string>> ladders = StringProblem::WordLadder::WordLadders(start, end, dict);
			Logger().WriteInformation("    Length:  %d %s %d\n", length, length == expect ? "==" : "!=", expect);
			Logger().WriteInformation("    Length2: %d %s %d\n", length2, length2 == expect ? "==" : "!=", expect);
			Logger().WriteInformation("    Length3: %d %s %d\n", length3, length3 == expect ? "==" : "!=", expect);
			Logger().WriteInformation("    Ladders:\n");
			for_each(ladders.begin(), ladders.end(), [&](vector<string> & l) {
				Logger().WriteInformation("            [");
				int i = 0;
				for_each(l.begin(), l.end(), [&](string w) {
					if (i != 0) {
						Logger().WriteInformation(" ");
					}
					Logger().WriteInformation("%s", w.c_str());
					i++;
				});
				Logger().WriteInformation("]\n");
			});
			ASSERT1(length == expect);
			ASSERT1(length2 == expect);
			ASSERT1(length3 == expect);
		};
		{
			unordered_set<string> dict = { "hot" };
			check("hit", "cog", dict, 0);
		}
		{
			unordered_set<string> dict = { "hot", "dot", "dog", "lot", "log" };
			check("hit", "cog", dict, 5);
		}
		{
			unordered_set<string> dict = { "ted", "tex", "red", "tax", "tad", "den", "rex", "pee" };
			check("red", "tax", dict, 4);
		}
	});

	Add("MatchSubsequence", [&]() {
		auto check = [&](const string & input, const string & pattern, int expect) {
			Logger().WriteInformation("Input:   %s\n", input.c_str());
			Logger().WriteInformation("Pattern: %s\n", pattern.c_str());
			int count2 = StringProblem::MatchSubsequence::Count2(input, pattern);
			Logger().WriteInformation("Matches: %d %s %d\n", count2, count2 == expect ? "==" : "!=", expect);
			int count = StringProblem::MatchSubsequence::Count(input, pattern);
			Logger().WriteInformation("Matches: %d %s %d\n", count, count == expect ? "==" : "!=", expect);
			ASSERT1(count == expect);
			ASSERT1(count2 == expect);
		};
		check("r", "r", 1);
		check("s", "r", 0);
		check("rr", "r", 2);
		check("rb", "r", 1);
		check("br", "r", 1);
		check("vb", "r", 0);
		check("rabbbit", "rabbit", 3);
		check("rrrr", "rr", 6);
		check("rrrrr", "rr", 10);
		check("rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr", "rr", 861);
		check("rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr", "rr", 5151);
		check("aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe", "bddabdcae", 10582116);
	});

	Add("BreakString", [&]() {
		int positions[] = { 0, 2, 8, 10, 20 };
		Matrix<pair<int, int>> cost(5, 5);
		StringProblem::BreakString::ComputeCostTable(positions, 5, cost);
		Logger().Print(positions, 5);
		auto print = [&](Log & l, pair<int, int> &p) {
			l.WriteInformation("(%d, %d)", p.first, p.second);
		};
		Logger().Print<pair<int, int>>(cost, print);

		vector<int> breaks;
		int totalCost = StringProblem::BreakString::ComputeBreaks(positions, 5, breaks);
		Logger().WriteInformation("Cost: %d\n", totalCost);
		Logger().WriteInformation("Breaks: ");
		Logger().Print(breaks);
	});
}