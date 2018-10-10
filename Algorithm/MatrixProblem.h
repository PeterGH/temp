#pragma once

#include <functional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include "String.h"

using namespace std;

namespace Test {
	class MatrixProblem {
	public:
		static vector<pair<int, int>> GetNeighbors(const pair<int, int> & cell, int rows, int cols) {
			vector<pair<int, int>> r;
			for (int i = cell.first - 1; i <= cell.first + 1; i++) {
				for (int j = cell.second - 1; j <= cell.second + 1; j++) {
					if (0 <= i && i < rows && 0 <= j && j < cols
						&& (i != cell.first || j != cell.second))
						r.push_back(make_pair(i, j));
				}
			}
			return r;
		};

		static pair<int, int> RandomNeighbor(const pair<int, int> & cell, int rows, int cols) {
			vector<pair<int, int>> n = GetNeighbors(cell, rows, cols);
			return n[rand() % n.size()];
		};

		class Generator {
		public:
			__declspec(dllexport) static char RandomChar()
			{
				return 'a' + (rand() % 26);
			}

			__declspec(dllexport) static vector<vector<char>> RandomWithoutWord(const string & word)
			{
				set<char> unique = String::UniqueChars(word);
				vector<vector<char>> matrix;
				size_t len = max(((int)word.size() + 1) >> 1, 2);
				for (size_t i = 0; i < len; i++) {
					vector<char> r;
					for (size_t j = 0; j < len; j++) {
						char c;
						while (true) {
							c = RandomChar();
							if (unique.find(c) == unique.end()) break;
						}
						r.push_back(c);
					}
					matrix.push_back(r);
				}
				return matrix;
			}

			__declspec(dllexport) static vector<vector<char>> RandomWithWord(const string & word)
			{
				vector<vector<char>> matrix = RandomWithoutWord(word);
				if (word.length() == 0) return matrix;
				int rows = matrix.size();
				int cols = matrix[0].size();
				int i = rand() % rows;
				int j = rand() % cols;
				size_t l = 0;
				matrix[i][j] = word[l];
				pair<int, int> c = make_pair(i, j);
				set<pair<int, int>> visited;
				visited.insert(c);
				for (l = 1; l < word.length(); l++) {
					while (true) {
						pair<int, int> n = RandomNeighbor(c, rows, cols);
						if (visited.find(n) == visited.end()) {
							visited.insert(n);
							c = n;
							break;
						}
					}
					matrix[c.first][c.second] = word[l];
				}
				return matrix;
			}
		};

		class SearchWord {
		public:
			// Allow one cell to be used twice
			__declspec(dllexport) static bool Existed(const vector<vector<char>> & matrix, const string & word)
			{
				if (word.length() == 0 || matrix.size() == 0 || matrix[0].size() == 0) return false;

				function<bool(const pair<int, int> &, const string &)>
				search = [&](const pair<int, int> & cell, const string & w) -> bool {
					if (matrix[cell.first][cell.second] != w[0]) return false;
					if (w.length() == 1) return true;
					vector<pair<int, int>> neighbors = GetNeighbors(cell, (int)matrix.size(), (int)matrix[0].size());
					for (size_t i = 0; i < neighbors.size(); i++) {
						if (search(neighbors[i], w.substr(1))) return true;
					}
					return false;
				};

				for (int i = 0; i < (int)matrix.size(); i++) {
					for (int j = 0; j < (int)matrix[0].size(); j++) {
						auto p = make_pair(i, j);
						if (search(p, word)) return true;
					}
				}
				return false;
			}

			// This is buggy
			__declspec(dllexport) static bool Existed2(const vector<vector<char>> & matrix, const string & word)
			{
				if (word.length() == 0 || matrix.size() == 0 || matrix[0].size() == 0) return false;

				function<bool(const pair<int, int> &)>
				search = [&](const pair<int, int> & cell) -> bool {
					if (matrix[cell.first][cell.second] != word[0]) return false;
					if (word.length() == 1) return true;
					unordered_map<pair<int, int>, vector<pair<int, int>>> neighbors;
					stack<pair<int, int>> path;
					path.push(cell);
					neighbors[cell] = GetNeighbors(cell, (int)matrix.size(), (int)matrix[0].size());
					while (!path.empty()) {
						pair<int, int> c = path.top();
						if (neighbors.find(c) == neighbors.end())
							neighbors[c] = GetNeighbors(c, (int)matrix.size(), (int)matrix[0].size());
						while (neighbors[c].size() > 0) {
							pair<int, int> n = neighbors[c][0];
							// This has a problem. If c is visited again, then we might miss some options
							// because some of its neighbors have already been erased.
							// Look at the tests for failures.
							neighbors[c].erase(neighbors[c].begin());
							if (matrix[n.first][n.second] == word[path.size()]) {
								if (path.size() == word.length() - 1) return true;
								path.push(n);
								break;
							}
						}
						if (c == path.top()) path.pop();
					}
					return false;
				};

				for (int i = 0; i < (int)matrix.size(); i++) {
					for (int j = 0; j < (int)matrix[0].size(); j++) {
						auto p = make_pair(i, j);
						if (search(p)) return true;
					}
				}
				return false;
			}
		};

		// Given a chess board containing 'X' and 'O'.
		// Capture the regions of 'o's and flip 'o's to 'x's.
		// Ignore the regions on the board boundary.
		// X X X X          X X X X
		// X O O X    =>    X X X X
		// X X O X          X X X X
		// X O X X          X O X X
		class SurroundedRegion {
		public:
			__declspec(dllexport) static void Capture(vector<vector<char>> & board)
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
								for_each(region.begin(), region.end(), [&](pair<int, int> p) {
									board[p.first][p.second] = 'X';
								});
							}
						}
					}
				}
			}

			__declspec(dllexport) static void Capture2(vector<vector<char>> & board)
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
		};
	};
}