#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

using namespace std;

namespace Test {
	class Combination {
	public:

		// Given a collection of integers that might contain duplicates, return all possible subsets.
		// Elements in a subset must be in non-descending order.
		__declspec(dllexport) static vector<vector<int>> All(vector<int> & s)
		{
			sort(s.begin(), s.end());
			vector<vector<int>> sets = { vector<int> { } };
			for_each(s.begin(), s.end(), [&](int n) {
				int size = sets.size();
				for (int i = 0; i < size; i++) {
					vector<int> ex(sets[i].begin(), sets[i].end());
					ex.push_back(n);
					sets.push_back(ex);
				}
			});
			return sets;
		}

		// Given a collection of integers that might contain duplicates, return all possible subsets.
		// Note:
		//   Elements in a subset must be in non-descending order.
		//   The solution set must not contain duplicate subsets.
		// For example, if S = [1,2,2], a solution is:
		// [
		//  [2],
		//  [1],
		//  [1,2,2],
		//  [2,2],
		//  [1,2],
		//  []
		// ]
		__declspec(dllexport) static vector<vector<int>> Unique(vector<int> & s)
		{
			sort(s.begin(), s.end());
			vector<vector<int>> sets = { vector<int> { } };
			size_t i = 0;
			while (i < s.size()) {
				int size = sets.size();
				size_t j = i;
				while (j < s.size() - 1 && s[j + 1] == s[j]) j++;
				// s[i..j] are duplicates
				for (int k = 0; k < size; k++) {
					vector<int> c;
					for (size_t l = i; l <= j; l++) {
						c.push_back(s[l]);
						vector<int> ex(sets[k].begin(), sets[k].end());
						ex.insert(ex.end(), c.begin(), c.end());
						sets.push_back(ex);
					}
				}
				i = j + 1;
			}
			return sets;
		}

		// Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
		// For example,
		// If n = 4 and k = 2, a solution is:
		// [
		//  [2,4],
		//  [3,4],
		//  [2,3],
		//  [1,2],
		//  [1,3],
		//  [1,4],
		// ]
		// Let s(i, j) be the solution of choosing j numbers out of {1, 2, ..., i}
		// then we need s(n, k).
		// s(i, j) = s(i-1, j-1) + s(i-1, j)
		// where s(i-1, j-1) contains solutions each of which contains i, and
		// s(i-1, j) contains solutions each of which does not contain i.
		__declspec(dllexport) static vector<vector<int>> NSelectK(int n, int k)
		{
			if (n < k) return vector<vector<int>> { { } };

			function<void(int, int, map<pair<int, int>, vector<vector<int>>> &)>
			solve = [&](int i, int j, map<pair<int, int>, vector<vector<int>>> & s) {
				pair<int, int> p = make_pair(i, j);
				s[p] = vector<vector<int>>{};

				if (i <= 0 || j <= 0 || i < j) {
					s[p].push_back(vector<int> { });
					return;
				}

				if (i == j) {
					vector<int> v;
					for (int k = 1; k <= j; k++) {
						v.push_back(k);
					}
					s[p].push_back(v);
					return;
				}

				pair<int, int> q1 = make_pair(i - 1, j - 1);
				if (s.find(q1) == s.end()) solve(i - 1, j - 1, s);
				for_each(s[q1].begin(), s[q1].end(), [&](vector<int> & v) {
					vector<int> ex(v.begin(), v.end());
					ex.push_back(i);
					s[p].push_back(ex);
				});

				pair<int, int> q2 = make_pair(i - 1, j);
				if (s.find(q2) == s.end()) solve(i - 1, j, s);
				for_each(s[q2].begin(), s[q2].end(), [&](vector<int> & v) {
					s[p].push_back(v);
				});
			};

			map<pair<int, int>, vector<vector<int>>> sets;
			solve(n, k, sets);
			pair<int, int> p = make_pair(n, k);
			return sets[p];
		}

		// Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
		// For example,
		// If n = 4 and k = 2, a solution is:
		// [
		//  [2,4],
		//  [3,4],
		//  [2,3],
		//  [1,2],
		//  [1,3],
		//  [1,4],
		// ]
		// Let s(i, j) be the solution of choosing j numbers out of {1, 2, ..., i}
		// then we need s(n, k).
		// s(i, j) = s(i-1, j-1) + s(i-1, j)
		// where s(i-1, j-1) contains solutions each of which contains i, and
		// s(i-1, j) contains solutions each of which does not contain i.
		//
		// s(1,1)
		// s(2,1)     s(2,2)
		// s(3,1)     s(3,2)     s(3,3)
		// s(4,1)     s(4,2)     s(4,3)     s(4,4)
		// ......     ......     ......     ......
		// ......     ......     ......     ......  ......
		// ......     ......     ......     ......  ...... ......
		// ......     ......     ......     ......  ...... s(k,k-1)   s(k,k)
		// ......     ......     ......     ......  ...... s(k+1,k-1) s(k+1,k)
		// ......     ......     ......     ......  ...... ......     ......
		// ......     ......     ......     ......  ...... ......     ......
		// s(n-k+1,1) s(n-k+1,2) ......     ......  ...... ......     ......
		//            s(n-k+2,2) ......     ......  ...... ......     ......
		//                       s(n-k+2,3) ......  ...... ......     ......
		//                                  ......  ...... ......     ......
		//                                          ...... ......     ......
		//                                                 s(n-1,k-1) s(n-1,k)
		//                                                            s(n,k)
		//
		__declspec(dllexport) static vector<vector<int>> NSelectK2(int n, int k)
		{
			if (n <= 0 || k <= 0 || n < k) return vector<vector<int>> { { } };

			// Represent a column
			vector<vector<vector<int>>> s(n - k + 1, vector<vector<int>> { { } });

			for (int j = 1; j <= k; j++) {
				// s(0+j,j) = {{1,2,...,j}}
				s[0][0].push_back(j);
				for (int i = 1; i <= n - k; i++) {
					// Extend s(i+j,j) by adding i+j to each of s(i+j-1,j-1)
					for_each(s[i].begin(), s[i].end(), [&](vector<int> & v) {
						v.push_back(i + j);
					});
					// Extend s(i+j,j) by adding s(i+j-1,j)
					for_each(s[i - 1].begin(), s[i - 1].end(), [&](vector<int> & v) {
						s[i].push_back(v);
					});
				}
			}

			return s[n - k];
		}

		__declspec(dllexport) static vector<vector<int>> NSelectK3(int n, int k)
		{
			vector<vector<int>> sets = { vector<int> { } };
			vector<vector<int>> output = {};
			for (int i = 1; i <= n; i++) {
				int size = sets.size();
				for (int j = 0; j < size; j++) {
					if ((int)sets[j].size() < k) {
						vector<int> ex(sets[j].begin(), sets[j].end());
						ex.push_back(i);
						if ((int)ex.size() == k) {
							output.push_back(ex);
						} else {
							sets.push_back(ex);
						}
					}
				}
			}
			return output;
		}

		__declspec(dllexport) static vector<vector<int>> NSelectK4(int n, int k)
		{
			function<void(vector<int>, int, int, vector<vector<int>> &)>
			solve = [&](vector<int> pre, int i, int k1, vector<vector<int>> & s) {
				if (k1 == 0) {
					s.push_back(pre);
					return;
				}
				if (n - i + 1 == k1) {
					for (int j = i; j <= n; j++) {
						pre.push_back(j);
					}
					s.push_back(pre);
					return;
				}
				for (int j = i; j <= n - k1 + 1; j++) {
					vector<int> p(pre.begin(), pre.end());
					p.push_back(j);
					solve(p, j + 1, k1 - 1, s);
				}
			};
			vector<vector<int>> set = {};
			solve(vector<int>{}, 1, k, set);
			return set;
		}
	};
}

