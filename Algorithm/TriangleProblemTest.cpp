#include "Header.h"

void TriangleProblemTest::Init(void)
{
	Add("MinPathSum", [&]() {
		auto check = [&](vector<vector<int>> & triangle, int expect) {
			for_each(triangle.begin(), triangle.end(), [&](vector<int> & r) {
				for_each(r.begin(), r.end(), [&](int i) {
					Logger().WriteInformation(" %d", i);
				});
				Logger().WriteInformation("\n");
			});
			int sum = TriangleProblem::MinPathSum::Solve(triangle);
			Logger().WriteInformation("Sum: %d %s %d\n", sum, sum == expect ? "==" : "!=", expect);
			ASSERT1(sum == expect);
		};
		{
			vector<vector<int>> t = { { -10 } };
			check(t, -10);
		}
		{
			vector<vector<int>> t = {
				{ -10 },
				{ 1, 2 }
			};
			check(t, -9);
		}
		{
			vector<vector<int>> t = {
				{ 2 },
				{ 3, 4 },
				{ 6, 5, 7 },
				{ 4, 1, 8, 3 }
			};
			check(t, 11);
		}
	});
}