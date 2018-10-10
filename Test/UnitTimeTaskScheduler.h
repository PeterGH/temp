#pragma once
#pragma once
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
namespace Test {
	class __declspec(dllexport) UnitTimeTaskScheduler {
	public:
		UnitTimeTaskScheduler() {}
		~UnitTimeTaskScheduler() {}

		// Separate a set of tasks with <deadline, weight> into a subset of ontime and a subset of late, so that
		// the tasks of ontime can be scheduled before their deadlines and the total sum of weights is maximized.
		// Each deadline is greater than 0 and less or equal to the count of tasks.
		static void Schedule(vector<pair<int, int>> & tasks, vector<pair<int, int>> & ontime, vector<pair<int, int>> & late);
	};
}
