#pragma once
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>
#include "Math.h"
using namespace std;
namespace Test {
	class Geometry {
	public:
		__declspec(dllexport) Geometry();
		__declspec(dllexport) ~Geometry();

		// [pair.first, pair.second]
		typedef pair<double, double> Range;

		// (Point.x, Point.y) = (pair.first, pair.second)
		typedef pair<double, double> Point;

		// The sides of Rectangle are in parallel with x-axis or y-axis
		// Top-Left Point = pair.first
		// Bottom-Right Point = pair.second
		typedef pair<Point, Point> Rectangle;

		__declspec(dllexport) static bool IsOverlap(const Range & r1, const Range & r2);
		__declspec(dllexport) static bool IsOverlap(const Rectangle & r1, const Rectangle & r2);

		struct IntPoint {
			int x;
			int y;
			IntPoint() : x(0), y(0) {}
			IntPoint(int a, int b) : x(a), y(b) {}
			bool operator== (const IntPoint & other) const
			{
				return x == other.x && y == other.y;
			}
			bool operator< (const IntPoint & other) const
			{
				if (x == other.x) return y < other.y;
				return x < other.x;
			}
		};

		__declspec(dllexport) static pair<int, int> NomalizeSlope(const IntPoint & p0, const IntPoint & p1);

		__declspec(dllexport) static int MaxPointsOnALine(vector<IntPoint> & points, set<IntPoint> & output);

		__declspec(dllexport) static void CaptureSurroundedRegion(vector<vector<char>> & board);
		__declspec(dllexport) static void CaptureSurroundedRegion2(vector<vector<char>> & board);
	};
}
