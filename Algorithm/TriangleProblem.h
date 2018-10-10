#pragma once

#include <algorithm>
#include <vector>

using namespace std;

namespace Test {
	class TriangleProblem {
	public:
		class MinPathSum {
		public:
			// Given a triangle, find the minimum path sum from top to bottom. Each step may move to only adjacent numbers on the row below.
			// For example, given the following triangle
			// [     [2],
			//      [3,4],
			//     [6,5,7],
			//    [4,1,8,3]]
			// The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
			//
			//          0
			//         0 1
			//        0 1 2
			//       0 1 2 3
			//      0 1 2 3 4
			//        ......
			// minSum[i] = e[i] + min { minSum[i-1], minSum[i] }
			__declspec(dllexport) static int Solve(vector<vector<int>> & triangle)
			{
				if (triangle.size() == 0) return 0;
				vector<int> sum;
				sum.push_back(triangle[0][0]);
				for (size_t i = 1; i < triangle.size(); i++) {
					vector<int> & row = triangle[i];
					sum.push_back(row[i] + sum[i - 1]);
					for (int j = i - 1; j > 0; j--)
						sum[j] = row[j] + min(sum[j - 1], sum[j]);
					sum[0] = row[0] + sum[0];
				}
				int min = sum[0];
				for (size_t i = 1; i < sum.size(); i++)
					if (sum[i] < min) min = sum[i];
				return min;
			}
		};
	};
}