#pragma once

#include <bitset>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "Matrix.h"

using namespace std;

namespace Test {

	class StringProblem {
	public:

		class WordLadder {
		public:
			// Find the length of shortest transformation sequence from a start string to a end string, such that
			// 1. only one character can be changed at each step
			// 2. each intermediate word must exist in a dictionary
			// Notes:
			// 1. all words are in the lower case
			// 2. start and end may not be in the dictionary
			__declspec(dllexport) static int Solve(const string & start, const string & end, const unordered_set<string> & dictionary)
			{
				if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;
				unordered_set<string> dict;
				dict.insert(dictionary.begin(), dictionary.end());
				if (dict.find(start) == dict.end()) dict.insert(start);
				if (dict.find(end) == dict.end()) dict.insert(end);

				map<string, vector<string>> graph;
				for_each(dict.begin(), dict.end(), [&](string word) {
					graph[word] = vector<string>{};
				});

				for_each(dict.begin(), dict.end(), [&](string word) {
					int wordLen = word.length();
					for (map<string, vector<string>>::iterator it = graph.begin(); it != graph.end(); it++) {
						if (wordLen == it->first.length()) {
							int diff = 0;
							for (int i = 0; i < wordLen; i++) {
								if (word[i] != it->first[i]) diff++;
								if (diff > 1) break;
							}
							if (diff == 1) it->second.push_back(word);
						}
					}
				});

				bool found = false;
				unordered_set<string> visited;
				queue<string> q[2];
				int step = 0;
				q[0].push(start);
				visited.insert(start);
				while (!q[0].empty() || !q[1].empty()) {
					queue<string> & current = q[step & 0x1];
					queue<string> & next = q[(step + 1) & 0x1];
					while (!current.empty()) {
						string word = current.front();
						current.pop();
						for (size_t i = 0; i < graph[word].size(); i++) {
							if (graph[word][i] == end) {
								found = true;
								break;
							}
							if (visited.find(graph[word][i]) == visited.end()) {
								visited.insert(graph[word][i]);
								next.push(graph[word][i]);
							}
						}
						if (found) return step + 2;
					}
					step++;
				}
				return 0;
			}

			__declspec(dllexport) static int Solve2(const string & start, const string & end, const unordered_set<string> & dictionary)
			{
				if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;
				unordered_set<string> dict;
				dict.insert(dictionary.begin(), dictionary.end());

				auto diff1 = [&](const string & first, const string & second)->bool {
					if (first.size() != second.size()) return false;
					int diff = 0;
					for (size_t i = 0; i < first.length(); i++) {
						if (first[i] != second[i]) diff++;
						if (diff > 1) return false;
					}
					return diff == 1;
				};

				vector<string> q[2];
				int step = 0;
				q[0].push_back(start);
				while (!q[0].empty() || !q[1].empty()) {
					vector<string> & current = q[step & 0x1];
					vector<string> & next = q[(step + 1) & 0x1];
					while (!current.empty()) {
						string word = current.front();
						current.erase(current.begin());
						for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++) {
							if (diff1(word, *it)) {
								if (diff1(*it, end)) return step + 3;
								else next.push_back(*it);
							}
						}
					}
					for_each(next.begin(), next.end(), [&](string & s) {
						dict.erase(s);
					});
					step++;
				}
				return 0;
			}

			__declspec(dllexport) static int Solve3(const string & start, const string & end, const unordered_set<string> & dictionary)
			{
				if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;

				unordered_set<string> visited;
				queue<string> q[2];
				int step = 0;
				q[0].push(start);
				visited.insert(start);
				while (!q[0].empty() || !q[1].empty()) {
					queue<string> & current = q[step & 0x1];
					queue<string> & next = q[(step + 1) & 0x1];
					while (!current.empty()) {
						string word = current.front();
						current.pop();
						int wordLen = word.size();
						string temp;
						for (int i = 0; i < wordLen; i++) {
							temp = word;
							for (char j = 'a'; j <= 'z'; j++) {
								temp[i] = j;
								if (temp == end) return step + 2;
								if (dictionary.find(temp) != dictionary.end() && visited.find(temp) == visited.end()) {
									visited.insert(temp);
									next.push(temp);
								}
							}
						}
					}
					step++;
				}
				return 0;
			}

			// Find all shortest transformation sequences from a start string to a end string, such that
			// 1. only one character can be changed at each step
			// 2. each intermediate word must exist in a dictionary
			// Notes:
			// 1. all words are in the lower case
			// 2. start and end may not be in the dictionary
			__declspec(dllexport) static vector<vector<string>> WordLadders(const string & start, const string & end, const unordered_set<string> & dictionary)
			{
				vector<vector<string>> ladders = {};
				if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return ladders;

				unordered_map<string, vector<vector<string>>> path; // Record paths ending at a word
				unordered_map<string, int> level;
				queue<string> q[2];
				int step = 0;
				bool stop = false;
				q[0].push(start);
				level[start] = step;
				path[start] = vector<vector<string>>{};
				path[start].push_back(vector<string> { start });
				while (!q[0].empty() || !q[1].empty()) {
					queue<string> & current = q[step & 0x1];
					queue<string> & next = q[(step + 1) & 0x1];
					while (!current.empty()) {
						string word = current.front();
						current.pop();
						string temp;
						for (size_t i = 0; i < word.size(); i++) {
							temp = word;
							for (char j = 'a'; j <= 'z'; j++) {
								temp[i] = j;
								if (temp == end) {
									for_each(path[word].begin(), path[word].end(), [&](vector<string> & p) {
										vector<string> r(p);
										r.push_back(temp);
										ladders.push_back(r);
									});
									stop = true;
								} else if (dictionary.find(temp) != dictionary.end()) {
									if (level.find(temp) == level.end()) {
										level[temp] = step + 1;
										next.push(temp);
										path[temp] = vector<vector<string>>{};
									}
									if (level[temp] > step) {
										for_each(path[word].begin(), path[word].end(), [&](vector<string> & p) {
											vector<string> r(p);
											r.push_back(temp);
											path[temp].push_back(r);
										});
									}
								}
							}
						}
					}
					if (stop) break; // Found the shortest paths. If need to find all, then do not stop.
					step++;
				}
				return ladders;
			}
		};

		class MatchSubsequence {
		public:
			// Find all subsequences of input string that match a pattern.
			// Return the total count.
			// A subsequence may not be a substring (i.e., contiguous)
			__declspec(dllexport) static int Count(const string & input, const string & pattern)
			{
				if (input.length() < pattern.length() || pattern.length() == 0) return 0;
				if (input.length() == pattern.length()) return input == pattern ? 1 : 0;
				int count = 0;
				for (size_t i = 0; i <= input.length() - pattern.length(); i++) {
					if (input[i] == pattern[0]) {
						if (pattern.length() == 1) count++;
						else count += Count(input.substr(i + 1), pattern.substr(1));
					}
				}
				return count;
			}

			__declspec(dllexport) static int Count2(const string & input, const string & pattern)
			{
				if (input.length() < pattern.length() || pattern.length() == 0) return 0;

				map<pair<size_t, size_t>, int> count;
				function<int(size_t, size_t)>
				search = [&](size_t i, size_t j) -> int
				{
					if (input.length() - i == pattern.length() - j)
						return input.substr(i) == pattern.substr(j) ? 1 : 0;
					int c = 0;
					for (size_t k = i; k <= input.length() - pattern.length() + j; k++) {
						if (input[k] == pattern[j]) {
							pair<size_t, size_t> p = make_pair(k, j);
							if (count.find(p) == count.end()) {
								if (j == pattern.length() - 1) count[p] = 1;
								else count[p] = search(k + 1, j + 1);
							}
							c += count[p];
						}
					}
					return c;
				};

				return search(0, 0);
			}
		};

		// Given a string of length n, we want to break it at some predetermined positions.
		// We can start at any one of the positions to break the string into two parts,
		// and continue with each substring and the rest of positions.
		// For each position there is a cost of splitting depending on the length of
		// substring to break.
		// We want to find a sequence of positions to break the string with minimum cost.
		//     0    1    2    3    ......    i    ......    n-2    n-1
		// p   p[0] p[1] p[2] p[3]           p[i]           p[n-2] p[n-1]
		//     0 = p[0] < p[1] < p[2] < ... < p[i] < ... < p[n-2] < p[n-1] = string length
		// Define c[i,j] as the cost of breaking a substring starting at position p[i]
		// and ending at position p[j].
		// c[i,j] = 0,     if i == j || i+1 == j
		//          p[j] - p[i] + 1 + min {
		//                  c[i,i+1] + c[i+1,j],
		//                  c[i,i+2] + c[i+2,j],
		//                  ......
		//                  c[i,j-2] + c[j-2,j],
		//                  c[i,j-1] + c[j-1,j]},    if i+1 < j
		class __declspec(dllexport) BreakString {
		public:
			BreakString(void) {}
			~BreakString(void) {}

			// cost[i,j] has two properties. The selected position to break substring from position i to j.
			// The second is the cost to break substring from position i to j.
			static void ComputeCostTable(int * positions, int length, Matrix<pair<int, int>> & cost)
			{
				if (positions == nullptr) throw invalid_argument("positions is nullptr");
				if (length <= 0) throw invalid_argument(String::Format("Invalid length %d", length));
				int rows = cost.Rows();
				if (rows != length) throw invalid_argument(String::Format("rows %d != length %d", rows, length));
				int cols = cost.Cols();
				if (cols != length) throw invalid_argument(String::Format("cols %d != length %d", cols, length));

				for (int i = 0; i < length; i++) {
					cost(i, i).first = i;
					cost(i, i).second = 0;
					if (i < length - 1) {
						cost(i, i + 1).first = i;
						cost(i, i + 1).second = 0;
					}
				}

				for (int l = 2; l < length; l++) {
					for (int i = 0; i < length - l; i++) {
						// Compute cost(i, i+l)
						int c = 0x7FFFFFFF;
						int k = i;
						for (int j = i + 1; j < i + l; j++) {
							int t = cost(i, j).second + cost(j, i + l).second;
							if (t < c) {
								c = t;
								k = j;
							}
						}

						cost(i, i + l).first = k;
						cost(i, i + l).second = c + positions[i + l] - positions[i];
					}
				}
			}

			static int ComputeBreaks(int * positions, int length, vector<int> & breaks)
			{
				if (positions == nullptr) throw invalid_argument("positions is nullptr");
				if (length <= 0) throw invalid_argument(String::Format("Invalid length %d", length));
				Matrix<pair<int, int>> cost(length, length);
				ComputeCostTable(positions, length, cost);

				vector<pair<int, int>> range;
				range.push_back(make_pair(0, length - 1));
				while (!range.empty()) {
					pair<int, int> p = range.back();
					range.pop_back();

					int k = cost(p.first, p.second).first;
					breaks.push_back(positions[k]);

					if (k < p.second - 1) {
						range.push_back(make_pair(k, p.second));
					}

					if (p.first < k - 1) {
						range.push_back(make_pair(p.first, k));
					}
				}

				return cost(0, length - 1).second;
			}
		};
	};
}