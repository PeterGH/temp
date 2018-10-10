#include "UnitTimeTaskScheduler.h"

namespace Test {
	// This is discussed in MIT Introduction to Algorithms 3rd edition, Chapter 16.
	// It is solved using the greedy algorithm over a matroid.
	void UnitTimeTaskScheduler::Schedule(vector<pair<int, int>> & tasks, vector<pair<int, int>> & ontime, vector<pair<int, int>> & late)
	{
		function<bool(const pair<int, int> &, const pair<int, int> &)> greaterWeight = 
			[&](const pair<int, int> & first, const pair<int, int> & second) -> bool {
			return first.second > second.second;
		};

		// Sort tasks by weights decreasingly
		stable_sort(tasks.begin(), tasks.end(), greaterWeight);

		// Count number of tasks in set whose deadline is no late than a given value.
		function<int(const vector<pair<int, int>> &, int)> count =
			[&](const vector<pair<int, int>> & set, int deadline) -> int {
			int c = 0;
			for_each(set.begin(), set.end(), [&](const pair<int, int> & t){
				if (t.first <= deadline) c++;
			});

			return c;
		};

		while (!tasks.empty()) {
			pair<int, int> t = tasks.front();
			tasks.erase(tasks.begin());
			bool isLate = false;
			for (int i = 0; i <= (int)ontime.size(); i++) {
				int c = count(ontime, i);
				if (c == i && t.first <= i) {
					// The first i time slots have already been filled.
					// Task t cannot fit in. Put it in the late set.
					isLate = true;
					late.push_back(t);
					break;
				}
			}

			if (!isLate) ontime.push_back(t);
		};

		function<bool(const pair<int, int> &, const pair<int, int> &)> earlier = 
			[&](const pair<int, int> & first, const pair<int, int> & second) -> bool {
			return first.first < second.first;
		};

		stable_sort(ontime.begin(), ontime.end(), earlier);
		stable_sort(late.begin(), late.end(), earlier);
	}
}
