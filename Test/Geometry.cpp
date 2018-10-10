#include "Geometry.h"

namespace Test {
	bool Geometry::IsOverlap(const Range & r1, const Range & r2)
	{
		// Non-overlap r1.second <= r2.first || r2.second <= r1.first;
		return r1.first < r2.second && r2.first < r1.second;
	}

	bool Geometry::IsOverlap(const Rectangle & r1, const Rectangle & r2)
	{
		// r1 and r2 overlaps if their projections onto x-axis and y-axis overlap
		// [r1.first.first, r1.second.first] and [r2.first.first, r2.second.first] overlaps.
		// [r1.second.second, r1.first.second] and [r2.second.second, r2.first.second] overlaps.
		return r1.first.first < r2.second.first && r2.first.first < r1.second.first
			&& r1.second.second < r2.first.second && r2.second.second < r1.first.second;
	}

	// slope = (p1.y - p0.y) / (p1.x - p0.x)
	// Reduce the slope so that the numerator and denominator are co-prime
	// Return a pair <deltaX, deltaY> after reduction
	pair<int, int> Geometry::NomalizeSlope(const IntPoint & p0, const IntPoint & p1)
	{
		int dX = p1.x - p0.x;
		int dY = p1.y - p0.y;
		int gcd = Math::GreatestCommonDivisor(dX, dY);
		dX = dX / gcd;
		dY = dY / gcd;
		return make_pair(dX, dY);
	}

	// Find a line containing maximum number of points
	int Geometry::MaxPointsOnALine(vector<IntPoint> & points, set<IntPoint> & output)
	{
		if (points.size() <= 1) {
			output.clear();
			output.insert(points.begin(), points.end());
			return points.size();
		}

		// Use comparer of IntPoint
		sort(points.begin(), points.end());

		map<pair<int, int>, vector<pair<IntPoint, IntPoint>>> slopes;

		for (size_t i = 0; i < points.size() - 1; i++) {
			for (size_t j = i + 1; j < points.size(); j++) {
				if (points[i] == points[j]) {
					// Ignore duplication
					continue;
				}

				pair<int, int> slope = NomalizeSlope(points[i], points[j]);

				// Treat vertical line specially
				if (slope.first == 0) slope.second = 1;
				// Treat horizontal line specially
				if (slope.second == 0) slope.first = 1;

				if (slopes.find(slope) == slopes.end()) {
					slopes[slope] = vector<pair<IntPoint, IntPoint>> { };
				}

				slopes[slope].push_back(make_pair(points[i], points[j]));
			}
		}

		size_t max = 0;

		for (map<pair<int, int>, vector<pair<IntPoint, IntPoint>>>::iterator slope = slopes.begin(); slope != slopes.end(); slope++) {
			// lines of the same slope
			vector<set<IntPoint>> lines;

			for_each(slope->second.begin(), slope->second.end(), [&](pair<IntPoint, IntPoint> & s) {
				vector<set<IntPoint>>::iterator & first = lines.end();
				vector<set<IntPoint>>::iterator & second = lines.end();
				for(vector<set<IntPoint>>::iterator it = lines.begin(); it != lines.end(); it++) {
					// it refers to the set of points on the same line
					if (it->find(s.first) != it->end()) {
						first = it;
					}
					if (it->find(s.second) != it->end()) {
						second = it;
					}
				}

				if (first == lines.end() && second == lines.end()) {
					set<IntPoint> line;
					line.insert(s.first);
					line.insert(s.second);
					lines.push_back(line);
				} else if (first == lines.end()) {
					second->insert(s.first);
				} else if (second == lines.end()) {
					first->insert(s.second);
				} else if (first == second) {
					;
				} else {
					set<IntPoint> line;
					line.insert(first->begin(), first->end());
					line.insert(second->begin(), second->end());
					lines.erase(first);
					lines.erase(second);
					lines.push_back(line);
				}
			});

			for_each(lines.begin(), lines.end(), [&](set<IntPoint> & l){
				if (l.size() > max) {
					max = l.size();
					output.clear();
					output.insert(l.begin(), l.end());
				}
			});
		}

		return max;
	}

	// Given a chess board containing 'X' and 'O'.
	// Capture the regions of 'o's and flip 'o's to 'x's.
	// Ignore the regions on the board boundary.
	// X X X X          X X X X
	// X O O X    =>    X X X X
	// X X O X          X X X X
	// X O X X          X O X X
	void Geometry::CaptureSurroundedRegion(vector<vector<char>> & board)
	{
		int height = board.size();
		if (height == 0) return;
		int width = board[0].size();
		set<pair<int, int>> nocapture;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (board[i][j] == 'O') {
					pair<int, int> p = make_pair(i, j);
					if (nocapture.find(p) != nocapture.end()) {
						continue;
					}
					bool boundary = i == 0 || i == height - 1 || j == 0 || j == width - 1;
					set<pair<int, int>> region;
					queue<pair<int, int>> q;
					region.insert(p);
					q.push(p);
					while (!q.empty()) {
						p = q.front();
						q.pop();
						pair<int, int> n;
						if (p.first > 0 && board[p.first - 1][p.second] == 'O') {
							if (p.first - 1 == 0) boundary = true;
							n = make_pair(p.first - 1, p.second);
							if (region.find(n) == region.end()) {
								region.insert(n);
								q.push(n);
							}
						}
						if (p.second > 0 && board[p.first][p.second - 1] == 'O') {
							if (p.second - 1 == 0) boundary = true;
							n = make_pair(p.first, p.second - 1);
							if (region.find(n) == region.end()) {
								region.insert(n);
								q.push(n);
							}
						}
						if (p.second < width - 1 && board[p.first][p.second + 1] == 'O') {
							if (p.second + 1 == width - 1) boundary = true;
							n = make_pair(p.first, p.second + 1);
							if (region.find(n) == region.end()) {
								region.insert(n);
								q.push(n);
							}
						}
						if (p.first < height - 1 && board[p.first + 1][p.second] == 'O') {
							if (p.first + 1 == height - 1) boundary = true;
							n = make_pair(p.first + 1, p.second);
							if (region.find(n) == region.end()) {
								region.insert(n);
								q.push(n);
							}
						}
					}

					if (boundary) {
						nocapture.insert(region.begin(), region.end());
					} else {
						for_each (region.begin(), region.end(), [&](pair<int, int> p){
							board[p.first][p.second] = 'X';
						});
					}
				}
			}
		}
	}

	// Given a chess board containing 'X' and 'O'.
	// Capture the regions of 'o's and flip 'o's to 'x's.
	// Ignore the regions on the board boundary.
	// X X X X          X X X X
	// X O O X    =>    X X X X
	// X X O X          X X X X
	// X O X X          X O X X
	void Geometry::CaptureSurroundedRegion2(vector<vector<char>> & board)
	{
		int height = board.size();
		if (height == 0) return;
		int width = board[0].size();

		auto search = [&](int i, int j) {
			if (board[i][j] == 'O') {
				board[i][j] = 'C';
				pair<int, int> p = make_pair(i, j);
				queue<pair<int, int>> q;
				q.push(p);
				while (!q.empty()) {
					p = q.front();
					q.pop();
					pair<int, int> n;
					if (p.first > 0 && board[p.first - 1][p.second] == 'O') {
						board[p.first - 1][p.second] = 'C';
						n = make_pair(p.first - 1, p.second);
						q.push(n);
					}
					if (p.second > 0 && board[p.first][p.second - 1] == 'O') {
						board[p.first][p.second - 1] = 'C';
						n = make_pair(p.first, p.second - 1);
						q.push(n);
					}
					if (p.second < width - 1 && board[p.first][p.second + 1] == 'O') {
						board[p.first][p.second + 1] = 'C';
						n = make_pair(p.first, p.second + 1);
						q.push(n);
					}
					if (p.first < height - 1 && board[p.first + 1][p.second] == 'O') {
						board[p.first + 1][p.second] = 'C';
						n = make_pair(p.first + 1, p.second);
						q.push(n);
					}
				}
			}
		};

		for (int i = 0; i < height; i++) {
			search(i, 0);
			search(i, width - 1);
		}

		for (int i = 0; i < width; i++) {
			search(0, i);
			search(height - 1, i);
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (board[i][j] == 'O') {
					board[i][j] = 'X';
				} else if (board[i][j] == 'C') {
					board[i][j] = 'O';
				}
			}
		}
	}
}