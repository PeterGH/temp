#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include "Matrix.h"
using namespace std;
namespace Test {
	class __declspec(dllexport) Palindrome {
	public:
		Palindrome(void) {}
		~Palindrome(void) {}
		// input: c_0, c_1, c_2, ..., c_i, ..., c_j, ..., c_(n-1)
		// Let L_(i, j) be the length of the longest palindrome subsequence of input c[i..j]
		// L_(i, j) = 1,                             if i == j
		//            2,                             if i+1 == j, c_i == c_j
		//            1,                             if i+1 == j, c_i != c_j
		//            2 + L_(i+1, j-1),              if c_i == c_j, i+1 < j
		//            max(L_(i, j-1), L_(i+1, j),    if c_i != c_j, i+1 < j
		//
		//	       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
		// 0(c)    1       1       1       1       3       5       5       5       5
		// 1(h)    0       1       1       1       3       3       3       3       3
		// 2(a)    0       0       1       1       3       3       3       3       3
		// 3(r)    0       0       0       1       1       1       1       1       3
		// 4(a)    0       0       0       0       1       1       1       1       1
		// 5(c)    0       0       0       0       0       1       1       1       1
		// 6(t)    0       0       0       0       0       0       1       1       1
		// 7(e)    0       0       0       0       0       0       0       1       1
		// 8(r)    0       0       0       0       0       0       0       0       1
		static void LengthTable(string & input, Matrix<size_t> & length)
		{
			for (size_t i = 0; i < input.length(); i++) {
				// Set L_(i, i)
				length(i, i) = 1;

				// Set L_(i, i+1)
				if (i + 1 < input.length()) {
					if (input[i] == input[i + 1]) {
						length(i, i + 1) = 2;
					} else {
						length(i, i + 1) = 1;
					}
				}
			}

			for (size_t j = 2; j < input.length(); j++) {
				for (size_t i = 0; i + j < input.length(); i++) {
					// Set L_(i, i+j)
					if (input[i] == input[i + j]) {
						length(i, i + j) = 2 + length(i + 1, i + j - 1);
					} else {
						length(i, i + j) = max(length(i, i + j - 1), length(i + 1, i + j));
					}
				}
			}
		}

		static void LongestSubsequenceByTable(string & input, string & output)
		{
			Matrix<size_t> length(input.length(), input.length());

			// Compute the length table
			LengthTable(input, length);

			size_t i = 0;
			size_t j = input.length() - 1;

			if (length(i, j) == 1) {
				// no Parlindrome found, return the last char
				output.append(&input[j], 1);
				return;
			}

			size_t k = 0;

			while ((j - i) > 1) {
				while (length(i, j - 1) == length(i, j)) {
					j--;
				}

				// The while loop stop when L_(i, j-1) != L_(i, j)
				// Now input[j] must be in the palindrome
				char c = input[j];
				j--;

				// Output a pair of c.
				// k will be the next insertion place.
				output.insert(k++, 1, c);
				output.insert(k, 1, c);

				while (input[i] != c) {
					i++;
				}

				i++;
			}

			// j = i or j = i+1
			output.insert(k, 1, input[j]);
			if (i + 1 == j && input[i] == input[j]) {
				// The palindrome is of form xxxccxxxx
				output.insert(k, 1, input[j]);
			}
		}

		// k       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
		// 0       1       1       1       1       1       1       1       1       1
		// 1       1       1       1       1       1       1       1       1       1
		// 2       1       1       1       1       3       1       1       1       1
		// 3       1       1       1       1       3       3       1       1       1
		// 4       1       1       1       1       3       3       3       1       1
		// 5       1       1       1       1       3       5       3       3       1
		// 6       1       1       1       1       3       5       5       3       3
		// 7       1       1       1       1       3       5       5       5       3
		// 8       1       1       1       1       3       5       5       5       5
		// At step k, length[i] is the length of the longest palindrome subsequence from input[i-k] to input[i]
		static void LengthArray(string & input, size_t length[])
		{
			unique_ptr<size_t[]> len2(new size_t[input.length()]);
			unique_ptr<size_t[]> len1(new size_t[input.length()]);

			// Compute all length=1 substrings
			for (int i = input.length() - 1; i >= 0; i--) {
				length[i] = 1;
				len2[i] = length[i];
			}

			// Compute all length=2 substrings
			for (int i = input.length() - 1; i >= 1; i--) {
				if (input[i - 1] == input[i]) {
					length[i] = 2;
				}
				len1[i] = length[i];
			}

			// Compute all length=(k+1) substrings
			for (int k = 2; k < (int)input.length(); k++) {
				for (int i = input.length() - 1; i >= k; i--) {
					if (input[i - k] == input[i]) {
						length[i] = 2 + len2[i - 1];
					} else {
						length[i] = max(len1[i - 1], len1[i]);
					}
				}

				memcpy(len2.get(), len1.get(), input.length() * sizeof(size_t));
				memcpy(len1.get(), length, input.length() * sizeof(size_t));
			}
		}

		static void LongestSubsequenceByArray(string & input, string & output)
		{
			unique_ptr<size_t[]> length(new size_t[input.length()]);
			LengthArray(input, length.get());

			int i = 0;
			int j = (int)input.length() - 1;

			if (length[j] == 1) {
				// no Parlindrome found, return the last char
				output.append(&input[j], 1);
				return;
			}

			int k = 0;

			while ((j - i + 1) > max((int)length[j], 2)) {
				while (length[j - 1] == length[j]) j--;
				char c = input[j];
				j--;
				output.insert(k++, 1, c);
				output.insert(k, 1, c);
				while (input[i] != c) i++;
				i++;
			}

			if (j == i + 1 && input[i] != input[j]) {
				output.insert(k, 1, input[j]);
			} else {
				// input[i..j] is a palindrome of length[j]
				for (int p = j; p >= i; p--) {
					output.insert(k, 1, input[p]);
				}
			}
		}


		// Determine if a string is palindrome.
		// 1. Consider alphanumeric characters only. Ignore others.
		// 2. Ignore case
		static bool IsPalindrom(const string & input)
		{
			if (input.size() == 0) return true;

			auto isAlphaNumeric = [&](char c)->bool {
				return c >= 'a' && c <= 'z'
					|| c >= 'A' && c <= 'Z'
					|| c >= '0' && c <= '9';
			};

			auto equal = [&](char a, char b)->bool {
				if (a >= 'a' && a <= 'z' && (b - 'a' == a - 'a' || b - 'A' == a - 'a')) return true;
				else if (a >= 'A' && a <= 'Z' && (b - 'a' == a - 'A' || b - 'A' == a - 'A')) return true;
				else if (a >= '0' && a <= '9' && b == a) return true;
				return false;
			};

			int i = 0;
			int j = input.size() - 1;
			while (i <= j) {
				while (i <= j && !isAlphaNumeric(input[i])) i++;
				while (i <= j && !isAlphaNumeric(input[j])) j--;
				if (i > j) return true;
				if (!equal(input[i], input[j])) return false;
				i++;
				j--;
			}
			return true;
		}


		// Partition input into a set of palindrom substrings.
		// Return all possible sets.
		static vector<vector<string>> Partition(const string & input)
		{
			function<void(const string &, size_t, map<size_t, vector<vector<string>>> &)>
			partition = [&](
				const string & s,
				size_t index,
				map<size_t, vector<vector<string>>> & sets)
			{
				if (sets.find(index) == sets.end()) {
					sets[index] = vector<vector<string>>{};
				}

				for (size_t k = index; k < s.length(); k++) {
					int i = index;
					int j = k;
					while (i <= j) {
						if (s[i] != s[j]) break;
						i++;
						j--;
					}
					if (i > j) {
						// s[index..k] is a palindrom
						if (k == s.length() - 1) {
							sets[index].push_back(vector<string> { s.substr(index, k - index + 1) });
						} else {
							if (sets.find(k + 1) == sets.end()) {
								partition(s, k + 1, sets);
							}
							for_each(sets[k + 1].begin(), sets[k + 1].end(), [&](vector<string> & r) {
								vector<string> set = { s.substr(index, k - index + 1) };
								set.insert(set.end(), r.begin(), r.end());
								sets[index].push_back(set);
							});
						}
					}
				}
			};

			map<size_t, vector<vector<string>>> partitions;
			partition(input, 0, partitions);
			return partitions[0];
		}


		// Partition input into a set of palindrom substrings.
		// Return the partion with minimum cut, i.e., the count of palindrome substrins is as less as possible.
		static vector<string> MinCutPartition(const string & input)
		{
			function<void(const string &, size_t, map<size_t, vector<string>> &)>
			partition = [&](
				const string & s,
				size_t index,
				map<size_t, vector<string>> & set)
			{
				if (set.find(index) == set.end()) {
					set[index] = vector<string>{};
				}

				size_t minIndex = index;
				size_t minCuts = s.length();
				for (size_t k = index; k < s.length(); k++) {
					int i = index;
					int j = k;
					while (i <= j) {
						if (s[i] != s[j]) break;
						i++;
						j--;
					}
					if (i > j) {
						// s[index..k] is a palindrom
						if (k == s.length() - 1) {
							set[index].push_back(s.substr(index, k - index + 1));
							return;
						} else {
							if (set.find(k + 1) == set.end()) {
								partition(s, k + 1, set);
							}
							if (set[k + 1].size() < minCuts) {
								minCuts = set[k + 1].size();
								minIndex = k + 1;
							}
						}
					}
				}

				set[index].push_back(s.substr(index, minIndex - index));
				set[index].insert(set[index].end(), set[minIndex].begin(), set[minIndex].end());
			};

			map<size_t, vector<string>> mincut;
			partition(input, 0, mincut);
			return mincut[0];
		}

		// Partition input into a set of palindrom substrings.
		// Return the partion with minimum cut, i.e., the count of palindrome substrins is as less as possible.
		static int MinCutPartition2(const string & input)
		{
			unique_ptr<int[]> mincut(new int[input.length()]);
			vector<vector<bool>> palindrome(input.size(), vector<bool>(input.size(), false));
			for (int i = input.length() - 1; i >= 0; i--) {
				mincut[i] = input.length() - i - 1;
				for (int j = i; j < (int)input.length(); j++) {
					if (input[i] == input[j]) {
						if (j - i <= 1) {
							palindrome[i][j] = true;
						} else {
							palindrome[i][j] = palindrome[i + 1][j - 1];
						}
					} else {
						palindrome[i][j] = false;
					}
					if (palindrome[i][j]) {
						// input[i..j] is a palindrome
						if (j == (int)input.length() - 1) {
							mincut[i] = 0;
							break;
						} else {
							if (mincut[j + 1] + 1 < mincut[i]) {
								mincut[i] = mincut[j + 1] + 1;
							}
						}
					}
				}
			}
			return mincut[0];
		}
	};
}