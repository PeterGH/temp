#pragma once

#include <algorithm>
#include <assert.h>
#include <bitset>
#include <deque>
#include <functional>
#include <map>
#include <memory>
#include <ppl.h>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace concurrency;
using namespace std;

namespace Test {

	
	// Reverse subarray from input[i] to input[j]
	template<class T> static void Reverse(vector<T> & input, int i, int j)
	{
		assert(i >= 0);
		assert(i <= j);
		assert(j < input.size());
		while (i < j) {
			swap(input[i], input[j]);
			i++;
			j--;
		}
	}

#pragma region String

	// Remove duplicate characters from string input.
	// Return the new length of string input with only unique characters.
	static int RemoveDuplicateChars(char * input, int length)
	{
		if (input == nullptr) return -1;
		if (length <= 0) return length;
		bitset<256> mask;

		// Using i to point to the last position of a non-dup char that has been checked.
		// Next non-dup char should be copied to the position i+1.
		// 0 | 1 | ... | i | ... | j | ... | n-1
		// ~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~
		// Non-dup chars         chars to check

		int i = -1;
		for (int j = 0; j < length; j++) {
			if ('\0' == input[j]) break;
			if (!mask.test(input[j])) {
				// The bit is zero, and it means input[j] is not a dup.
				mask.set(input[j]);
				i++;
				if (i < j) {
					// Have skipped some dups
					// Move current non-dup char to the front.
					input[i] = input[j];
				}
			}
		}

		input[++i] = '\0';
		// Now i equals to the new length.
		return i;
	}

	static bool ContainsUniqueChars(const string & input)
	{
		bitset<256> mask;
		for (size_t i = 0; i < input.length(); i++) {
			if (mask.test(input[i])) return false;
			mask.set(input[i]);
		}
		return true;
	}

	// Pattern can include:
	// '.'	Any single character
	// '*'  Zero or more occurrences of previous character
	// Any other characters
	// Return true if the entire input string match the pattern.
	static bool IsMatch1(const char * input, const char * pattern)
	{
		if (input == nullptr || pattern == nullptr) return false;
		while (*pattern == '*') pattern++;
		if (*input == '\0' && *pattern == '\0') return true;
		if (*pattern == '\0') return false;
		if (*(pattern + 1) != '*') {
			// input    a#######
			//          ""
			// pattern  b####
			//          a####
			//          .####
			return (*input == *pattern || *pattern == '.' && *input != '\0')
				&& IsMatch1(input + 1, pattern + 1);
		}
		// input    a#######
		//          ""
		// pattern  b***####
		//          a***###
		//          .***###
		while (*input == *pattern || (*pattern == '.' && *input != '\0')) {
			// input    a#######
			// pattern  a***###
			//          .***###
			if (IsMatch1(input++, pattern + 2)) return true;
		}
		// input    a#######
		//          ""
		// pattern  b***####
		return IsMatch1(input, pattern + 2);
	}

	static bool IsMatch2(const char * input, const char * pattern)
	{
		if (input == nullptr || pattern == nullptr) return false;
		while (*pattern == '*') pattern++;
		while ((*input == *pattern || *pattern == '.')
			&& *input != '\0'
			&& *pattern != '\0'
			&& *(pattern + 1) != '*') {
			// input    a#######
			// pattern  a####
			//          .####
			input++;
			pattern++;
		}
		if (*input == '\0' && *pattern == '\0') return true; // input and pattern match
		if (*pattern == '\0') return false; // input has more characters unmatched
		if (*(pattern + 1) != '*') {
			// input    a#######
			//          '\0'
			// pattern  b####
			return false;
		}
		// input    a#######
		//          '\0'
		// pattern  b***####
		//          a***###
		//          .***###
		// Now *(pattern+1) == '*'
		if (*input != *pattern && *pattern != '.') {
			// input    a#######
			//          '\0'
			// pattern  b*###
			return IsMatch2(input, pattern + 2);
		}
		// input    a#######
		//          '\0'
		// pattern  a*###
		//          .*###
		while (*input != '\0' && (*input == *pattern || *pattern == '.')) {
			if (IsMatch2(input, pattern + 2)) return true;
			input++;
		}
		// input	'\0'
		// input    b#######
		// pattern  a*###
		return IsMatch2(input, pattern + 2);
	}

	static void LongestSubStringWithUniqueChars1(const string & input, size_t & index, size_t & length)
	{
		index = 0;
		length = 0;
		bitset<256> visited;
		size_t i = 0;
		size_t j = 0;
		while (j < input.length()) {
			if (visited[input[j]] == true) {
				if (j - i > length) {
					index = i;
					length = j - i;
				}
				while (input[i] != input[j]) {
					visited[input[i]] = false;
					i++;
				}
				i++;
			}
			else visited[input[j]] = true;
			j++;
		}
		if (j - i > length) {
			index = i;
			length = j - i;
		}
	}

	static void LongestSubStringWithUniqueChars2(const string & input, size_t & index, size_t & length)
	{
		index = 0;
		length = 0;
		map<char, size_t> position;
		size_t i = 0;
		size_t j = 0;
		while (j < input.length()) {
			if (position.find(input[j]) != position.end()
				&& position[input[j]] >= i) {
				if (j - i > length) {
					index = i;
					length = j - i;
				}
				i = position[input[j]] + 1;
			}
			position[input[j]] = j;
			j++;
		}
		if (j - i > length) {
			index = i;
			length = j - i;
		}
	}

	class ShortestSubStringContainingGivenChars {
	private:
		static void UpdateMap(map<char, int> & m, char c)
		{
			if (m.find(c) == m.end()) m[c] = 1;
			else m[c]++;
		}

		// check if m1 contains m2
		static bool Contain(map<char, int> m1, map<char, int> m2)
		{
			if (m1.size() < m2.size()) return false;
			for (map<char, int>::iterator it = m2.begin(); it != m2.end(); it++) {
				if (m1.find(it->first) == m1.end()) return false;
				if (m1[it->first] < it->second) return false;
			}
			return true;
		}
	public:
		// http://leetcode.com/2010/11/finding-minimum-window-in-s-which.html
		// Find the shortest substring containing all the characters in a given set
		// The given set may contain duplicate chars
		static void Solve1(const string & chars, const string & input, int & index, int & length)
		{
			index = -1;
			length = INT_MAX;

			map<char, int> charMap;
			for (unsigned int i = 0; i < chars.length(); i++) {
				UpdateMap(charMap, chars[i]);
			}

			map<char, int> count;
			int i = 0;
			int j = 0;
			while (j < (int)input.length() && count.size() < charMap.size() - 1) {
				if (charMap.find(input[j]) != charMap.end()) UpdateMap(count, input[j]);
				j++;
			}
			while (j < (int)input.length()) {
				if (charMap.find(input[j]) != charMap.end()) {
					UpdateMap(count, input[j]);
					if (Contain(count, charMap)) {
						while (Contain(count, charMap)) {
							if (count.find(input[i]) != count.end()) count[input[i]]--;
							i++;
						}
						int l = j - i + 2; // j - (i-1) + 1
						if (l < length) {
							index = i - 1;
							length = l;
						}
					}
				}
				j++;
			}
		}

		static void Solve2(const string & chars, const string & input, int & index, int & length)
		{
			index = -1;
			length = INT_MAX;

			map<char, int> charMap;
			for (unsigned int i = 0; i < chars.length(); i++) {
				UpdateMap(charMap, chars[i]);
			}

			for (unsigned int i = 0; i < input.length(); i++) {
				if (charMap.find(input[i]) != charMap.end()) {
					map<char, int> count;
					unsigned int j = i;
					while (j < input.length()) {
						if (charMap.find(input[j]) != charMap.end()) {
							UpdateMap(count, input[j]);
							if (Contain(count, charMap)) {
								int l = j - i + 1;
								if (l < length) {
									index = i;
									length = l;
								}
								break;
							}
						}
						j++;
					}
				}
			}
		}

		// Assuming the given set does not contain duplicate characters
		static void SolveGivenUniqueChars1(const string & chars, const string & input, int & index, int & length)
		{
			index = -1;
			length = INT_MAX;
			map<char, int> count;
			int i = 0;
			char c;
			for (unsigned int j = 0; j < input.length(); j++) {
				c = input[j];
				if (chars.find(c) != string::npos) {
					if (count.find(c) == count.end()) count[c] = 1;
					else count[c]++;
					if (count.size() == chars.length()) {
						while (count.size() == chars.length()) {
							c = input[i];
							if (count.find(c) != count.end()) {
								count[c]--;
								if (count[c] == 0) count.erase(c);
							}
							i++;
						}
						int l = j - i + 2; // j - (i-1) + 1
						if (l < length) {
							index = i - 1;
							length = l;
						}
					}
				}
			}
		}

		// Assuming the given set does not contain duplicate characters
		static void SolveGivenUniqueChars2(const string & chars, const string & input, int & index, int & length)
		{
			index = -1;
			length = INT_MAX;
			queue<int> indices;
			map<char, int> found; // track found chars and their most recent indices
			for (unsigned int i = 0; i < input.length(); i++) {
				if (chars.find(input[i]) != string::npos) {
					indices.push(i);
					found[input[i]] = i; // insert or update with the latest index
					if (found.size() == chars.length()) {
						// found all chars
						// pop old indices that are not the most recent
						while (indices.front() != found[input[indices.front()]]) indices.pop();
						int l = indices.back() - indices.front() + 1;
						if (l < length) {
							// Update if the current one is shorter
							index = indices.front();
							length = l;
						}
						// erase the oldest char in order to start next search
						found.erase(input[indices.front()]);
						indices.pop();
					}
				}
			}
			if (index == -1) length = 0;
		}
	};

	// http://leetcode.com/2010/11/microsoft-string-replacement-problem.html
	// Replace a pattern with a shorter string in place.
	// Continous occurrences of the pattern should be replaced with one shorter string.
	static void ReplaceWithShorterString(char * input, const char * pattern, const char * shorter)
	{
		if (input == nullptr || pattern == nullptr || shorter == nullptr
			|| *input == '\0' || *pattern == '\0' || *shorter == '\0')
			return;
		char * i = input; // Next insert position
		char * j = input; // Next check position
		const char * s = shorter;
		const char * p = pattern;
		while (*j != '\0') {
			bool found = false;
			while (*j == *p) {
				char * k = j;
				while (*k != '\0' && *p != '\0' && *k == *p) {
					// Do not use *k++ == *p++ in the while condition statement,
					// because k and p will advance even if *k and *p are different.
					k++;
					p++;
				}
				if (*p == '\0') {
					// Found one pattern, skip it and
					// check for next continous pattern
					found = true;
					j = k;
					p = pattern;
				} else {
					// Input is done or not match
					p = pattern;
					break;
				}
			}
			if (found) {
				while (*s != '\0') *i++ = *s++;
				s = shorter;
			}
			if (*j != '\0') {
				// j may reach the end if the input ends with the pattern
				*i++ = *j++;
			}
		}
		*i = '\0';
	}

	// An input string may contains leading and ending spaces, and
	// may contain contiguous spaces in the middle. Remove the leading
	// and ending spaces, and nomalize each group of contiguous spaces
	// in the middle into one space.
	static void RemoveExtraSpaces(char * input)
	{
		if (input == nullptr) return;
		char * i = input - 1; // Track the end of the last word seen so far
		char * j = input;     // Track the next char in input
		while (*j != '\0') {
			while (*j == ' ') j++;
			if (*j == '\0') break;
			if (i + 1 != input) {
				i++;
				*i = ' ';
			}
			while (*j != ' ' && *j != '\0') {
				i++;
				if (i < j) *i = *j;
				j++;
			}
		}
		i++;
		*i = '\0';
	}

	// input is a sentence of words separated by spaces.
	// There can be multiple spaces between two words.
	// Reverse the order of words, and condense multiple spaces between
	// two words into one.
	static void ReverseWords(string & input)
	{
		size_t len = input.length();
		size_t i = 0;
		while (i < len && input[i] == ' ') i++;
		if (i == len) {
			input.clear();
			return;
		}
		while (i < len) {
			size_t j = input.find_first_of(" ", i);
			if (j == string::npos) j = len;
			input.insert(len, input, i, j - i);
			input.insert(len, 1, ' ');
			while (j < len && input[j] == ' ') j++;
			i = j;
		}
		input = input.substr(i + 1);
	}

	// input is a sentence of words separated by spaces.
	// There can be multiple spaces between two words.
	// Reverse the order of words, and condense multiple spaces between
	// two words into one.
	static void ReverseWords(char * input)
	{
		if (input == nullptr) return;
		RemoveExtraSpaces(input);
		auto reverse = [&](char * s, char * t) {
			while (s < t) {
				char v = *s;
				*s++ = *t;
				*t-- = v;
			}
		};
		char * s = input;
		char * t = s;
		while (*s != '\0') {
			if (*s == ' ') s++;
			t = s;
			while (*t != '\0' && *t != ' ') t++;
			t--;
			reverse(s, t);
			s = ++t;
		}
		reverse(input, --s);
	}

	// Return a pointer to the first occurrence of input2 in input1, or nullptr
	static const char * StrStr1(const char * input1, const char * input2)
	{
		if (input1 == nullptr || input2 == nullptr) return nullptr;
		if (*input2 == '\0') return input1;
		const char * q = input1;
		const char * p = input2;
		while (*(q + 1) != '\0' && *(p + 1) != '\0') {
			q++;
			p++;
		}
		if (*(q + 1) == '\0' && *(p + 1) != '\0') {
			return nullptr; // input2 is longer than input1
		}
		// now input1 is not shorter than input2
		// set p to the beginning of input1
		p = input1;
		// Hop p and q at same step until q reaches the end of input1
		while (*q != '\0') {
			if (*p == *input2) {
				const char * r = p;
				const char * s = input2;
				while (*s != '\0' && *r == *s) {
					r++;
					s++;
				}
				if (*s == '\0') return p;
			}
			p++;
			q++;
		}
		return nullptr;
	}

	// Return a pointer to the first occurrence of input2 in input1, or nullptr
	static const char * StrStr2(const char * input1, const char * input2)
	{
		if (input1 == nullptr || input2 == nullptr) return nullptr;
		const char * p = input1;
		while (*p != '\0') {
			if (*p == *input2) {
				const char * r = p;
				const char * s = input2;
				while (*r != '\0' && *s != '\0' && *r == *s) {
					r++;
					s++;
				}
				if (*s == '\0') return p;
			}
			p++;
		}
		return *input2 == '\0' ? input1 : nullptr;
	}

#pragma endregion

	class BreakWords {
	private:
		static bool StartWith(const string & s1, const string & s2)
		{
			if (s1.length() < s2.length()) return false;
			for (size_t i = 0; i < s2.length(); i++) {
				if (s1[i] != s2[i]) return false;
			}
			return true;
		}
	public:
		// Given a input string, break it by inserting spaces so that each word is in a given dictionary.
		// Return all possible sentences by breaking the string.
		static vector<string> Solve1(const string & input, unordered_set<string> & dictionary)
		{
			function<void(const string &, unordered_set<string> &, const string &, vector<string> &)>
			breakWord = [&](
				const string & s,
				unordered_set<string> & dict,
				const string & sentence,
				vector<string> & results)
			{
				size_t len = s.length();
				for_each(dict.begin(), dict.end(), [&](string w) {
					size_t wlen = w.length();
					if (StartWith(s, w)) {
						string sen(sentence);
						if (sen.length() > 0) sen.append(1, ' ');
						sen.append(w);
						if (len == wlen) results.push_back(sen);
						else breakWord(s.substr(wlen), dict, sen, results);
					}
				});
			};
			vector<string> sentences;
			breakWord(input, dictionary, string(), sentences);
			return sentences;
		}

		// Given a input string, break it by inserting spaces so that each word is in a given dictionary.
		// Return all possible sentences by breaking the string.
		static vector<string> Solve2(const string & input, unordered_set<string> & dictionary)
		{
			function<void(const string &, size_t, unordered_set<string> &, map<size_t, vector<string>> &)>
			breakWord = [&](
				const string & s,
				size_t index,
				unordered_set<string> & dict,
				map<size_t, vector<string>> & results)
			{
				if (results.find(index) == results.end()) results[index] = vector<string>{};
				size_t len = s.length() - index;
				for_each(dict.begin(), dict.end(), [&](string w) {
					size_t wlen = w.length();
					if (StartWith(s.substr(index), w)) {
						size_t wi = index + wlen;
						if (wi == s.length()) results[index].push_back(w);
						else {
							if (results.find(wi) == results.end()) breakWord(s, wi, dict, results);
							for_each(results[wi].begin(), results[wi].end(), [&](string r) {
								string rs(w);
								rs.append(1, ' ');
								rs.append(r);
								results[index].push_back(rs);
							});
						}
					}
				});
			};
			map<size_t, vector<string>> sentences;
			breakWord(input, 0, dictionary, sentences);
			return sentences[0];
		}

		static bool Solvable(const string & input, unordered_set<string> & dictionary)
		{
			function<void(const string &, size_t, unordered_set<string> &, map<size_t, bool> &)>
			breakWord = [&](
				const string & s,
				size_t index,
				unordered_set<string> & dict,
				map<size_t, bool> & results)
			{
				if (results.find(index) == results.end()) results[index] = false;
				size_t len = s.length() - index;
				for_each(dict.begin(), dict.end(), [&](string w) {
					size_t wlen = w.length();
					if (StartWith(s.substr(index), w)) {
						size_t wi = index + wlen;
						if (wi == s.length()) {
							results[index] = true;
							return;
						} else {
							if (results.find(wi) == results.end()) breakWord(s, wi, dict, results);
							if (results[wi]) {
								results[index] = true;
								return;
							}
						}
					}
				});
			};
			map<size_t, bool> sentences;
			breakWord(input, 0, dictionary, sentences);
			return sentences[0];
		}
	};

#pragma region Longest Consecutive Sequence

	// Find the elements forming the longest contiguous sequence.
	// Given [100, 4, 200, 1, 3, 2], The longest consecutive elements sequence is [1, 2, 3, 4].
	// Return: first = 1, length = 4.

	static void LongestConsecutiveSequence1(const vector<int> & input, int & first, size_t & length)
	{
		if (input.size() == 0) {
			length = 0;
			return;
		}
		first = input[0];
		length = 1;
		// Given a open range (begin, end), track the begin and end using two hash tables.
		unordered_map<int, int> end; // (begin, end)
		unordered_map<int, int> begin; // (end, begin)
		for_each(input.begin(), input.end(), [&](int i) {
			// i must fall into one of cases:
			// 1. i begins one range and ends another range.
			// 2. i begins one range or ends one range.
			// 3. i is inside one range.
			// 4. i is outside of any range.
			bool iBegin = end.find(i) != end.end(); // (i, end[i])
			bool iEnd = begin.find(i) != begin.end(); // (begin[i], i) 
			if (iEnd && iBegin) {
				// merge (begin[i], i) with (i, end[i])
				if (end[i] - begin[i] - 1 > length) {
					length = end[i] - begin[i] - 1;
					first = begin[i] + 1;
				}
				end[begin[i]] = end[i];
				begin[end[i]] = begin[i];
				end.erase(i);
				begin.erase(i);
			} else if (iBegin) {
				// expand (i, end[i]) to (i-1, end[i])
				if (end[i] - i > length) {
					length = end[i] - i;
					first = i;
				}
				// if (i-1, end[i-1]) exists, then should not change it,
				// because (i, end[i]) must be inside (i-1, end[i-1]).
				if (end.find(i - 1) == end.end()) {
					end[i - 1] = end[i];
					begin[end[i]] = i - 1;
					end.erase(i);
				}
			} else if (iEnd) {
				// expand (begin[i], i) to (begin[i], i+1)
				if (i - begin[i] > length) {
					length = i - begin[i];
					first = begin[i] + 1;
				}
				// if (begin[i+1], i+1) exists, then should not change it,
				// because (begin[i], i) must be inside (begin[i+1], i+1).
				if (begin.find(i + 1) == begin.end()) {
					begin[i + 1] = begin[i];
					end[begin[i]] = i + 1;
					begin.erase(i);
				}
			} else {
				// add new range (i-1, i+1) and (i+1, i-1)
				// the new range may already be covered in existing range, e.g.
				// { 0, 1, 2, 1}, when the second 1 occurrs, a new range (0,2) is added,
				// but the first three numbers already generate range (-1, 3).
				if (1 > length) {
					length = 1;
					first = i;
				}
				if (end.find(i - 1) == end.end()
					&& begin.find(i + 1) == begin.end()) {
					end[i - 1] = i + 1;
					begin[i + 1] = i - 1;
				}
			}
		});
	}

	static void LongestConsecutiveSequence2(vector<int> & input, int & first, size_t & length)
	{
		if (input.size() == 0) {
			length = 0;
			return;
		}
		first = input[0];
		length = 1;
		sort(input.begin(), input.end());
		int f = input[0];
		int l = 1;
		for (size_t i = 1; i < input.size(); i++) {
			if (input[i] == input[i - 1]) continue;
			else if (input[i] == input[i - 1] + 1) l++;
			else { // input[i] > input[i - 1] + 1
				if (l > length) {
					first = f;
					length = l;
				}
				f = input[i];
				l = 1;
			}
		}
		if (l > length) {
			first = f;
			length = l;
		}
	}

#pragma endregion

#pragma region Permutation

	class PermutationGenerator {
	private:
		unsigned int _length;
		unsigned long long _totalCount;
		// Internal counter to track the permutation state.
		// It is a multiple-radix integer, where the base
		// of position i is i + 1.
		// 0 <= _counter[i] < i + 1
		unique_ptr<unsigned int[]> _counter;

		void IncreaseCounter(void)
		{
			for (unsigned int i = 0; i < _length; i++) {
				_counter[i] = (_counter[i] + 1) % (i + 1);
				if (_counter[i] != 0) {
					// Current position does not round off (i + 1).
					// No need to continue.
					break;
				}
			}
		}

	public:
		PermutationGenerator(unsigned int length)
		{
			assert(length > 0);
			_length = length;
			_counter = unique_ptr<unsigned int[]>(new unsigned int[length]);
			memset(_counter.get(), 0, length * sizeof(unsigned int));
			_totalCount = Factorial(length);
		}

		~PermutationGenerator(void) {}

		// Total number of permutations
		const unsigned long long TotalCount(void) const
		{
			return _totalCount;
		}

		// Current counter value at position index
		const unsigned int operator[](unsigned int index) const
		{
			assert(index < _length);
			return _counter[index];
		}

		// Get next permutation in-place
		template<class T> void Next(vector<T> & input)
		{
			int len = (int)min((unsigned int)input.size(), _length);
			for (int i = len - 1; i >= 0; i--) {
				if (_counter[i] > 0)
					swap(input[i], input[i - _counter[i]]);
			}

			// Prepare for the next permutation
			IncreaseCounter();
		}
	};

	// Get a random permutation in-place
	template<class T> static void RandomPermutation(vector<T> & input)
	{
		int len = (int)input.size() - 1;
		for (int i = len; i >= 0; i--) {
			// The rand function returns a pseudorandom integer
			// in the range 0 (inclusive) to RAND_MAX (32767).
			// We need r in [0, i]
			int r = rand() % (i + 1);
			swap(input[i], input[i - r]);
		}
	}

	// The set {1, 2, 3, ..., n} contains a total of n! unique permutations.
	// By listing and labeling all of the permutations in order,
	// We get the following sequence (ie, for n = 3):
	// 1. "123"
	// 2. "132"
	// 3. "213"
	// 4. "231"
	// 5. "312"
	// 6. "321"
	// Given n and k, return the k-th permutation sequence.
	// Note: Given n will be between 1 and 9 inclusive.
	static string KthPermutation(int n, int k)
	{
		assert(n > 0);
		assert(n < 10);
		if (n <= 0 || k <= 0) return string();

		int i = 1; // Count number of digits to permute
		int m = 1; // Count number of permutations of i digits, i.e. i!

		while (m < k && i < n) {
			i++;
			m *= i;
		}

		if (m < k) return string(); // k > n!

		// Now m = i!, and (i-1)! < k <= i!

		// 1 2 3 ...... n-i n-i+1 n-i+2 ...... n-1 n
		// ~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~
		//     not permute         permute i digits

		string output;

		// append {1, 2, 3, ..., n-i}
		for (int j = 1; j <= n - i; j++) {
			output.append(1, '0' + j);
		}

		// Permute the last i digits
		vector<int> permute;

		// Initialize with {n-i+1, ..., n}
		for (int j = n - i + 1; j <= n; j++) {
			permute.push_back(j);
		}

		while (i > 0) {
			// For each loop, the variables are defined as:
			//   i, number of digits to permute
			//   m, number of permutations of i digits
			//   k, index (1-based) of target in m permutations

			/*
			if (i == 1) {
			// k = 1 since k <= m = i! = 1
			output.append(1, '0' + permute[permute.size() - 1]);
			break;
			} else if (i == 2) {
			if (k == 1) {
			output.append(1, '0' + permute[permute.size() - 2]);
			output.append(1, '0' + permute[permute.size() - 1]);
			} else { // k = 2
			output.append(1, '0' + permute[permute.size() - 1]);
			output.append(1, '0' + permute[permute.size() - 2]);
			}
			break;
			}
			*/

			// Permute 1 2 3 4 5 ...... i-1 i, will get i ranges determined by the first digit
			//   1 ......
			//   1 ......
			//   2 ......
			//   2 ......
			//   ......
			//   ......
			//   i-1 ......
			//   i-1 ......
			//   i ......
			//   i ......

			m = m / i; // Count permutations per range

			int j = (k - 1) / m + 1; // Get the range index (1-based) which k falls into

			// 1 2 3 4 5 ... j-1 j   j+1 ... i-1 i
			// j 1 2 3 4 5 ...   j-1 j+1 ... i-1 i
			int t = permute[j - 1];
			permute.erase(permute.begin() + j - 1);
			output.append(1, '0' + t);

			i--; // Move on to the rest i - 1 digits
			k = ((k - 1) % m) + 1; // Get the index in the j-th range
		}

		return output;
	}

#pragma endregion

	template<class T> class Queue {
	private:
		stack<T> in, out;
		
		static void Flush(stack<T> & from, stack<T> & to)
		{
			while (!from.empty()) {
				T v = from.top();
				from.pop();
				to.push(v);
			}
		}

	public:
		Queue(void) {}
		~Queue(void) {}

		T & Back(void)
		{
			if (in.empty()) {
				if (out.empty()) throw runtime_error("Queue is empty");
				Flush(out, in);
			}

			return in.top();
		}

		bool Empty(void) const
		{
			return out.empty() && in.empty();
		}

		T & Front(void)
		{
			if (out.empty()) Flush(in, out);
			if (out.empty()) throw runtime_error("Queue is empty");
			return out.top();
		}

		void Pop(void)
		{
			if (out.empty()) Flush(in, out);
			if (out.empty()) throw runtime_error("Queue is empty");
			out.pop();
		}

		void Push(const T & value)
		{
			in.push(value);
		}

		size_t Size(void) const
		{
			return out.size() + in.size();
		}
	};

	template<class T> class Stack {
	private:
		queue<T> queue0, queue1;

		static void Flush(queue<T> & nonempty, queue<T> & empty, size_t count)
		{
			while (count > 0) {
				T v = nonempty.front();
				nonempty.pop();
				empty.push(v);
				count--;
			}
		}

	public:
		Stack(void) {}
		~Stack(void) {}

		bool Empty(void) const
		{
			return queue0.empty() && queue1.empty();
		}

		void Pop(void)
		{
			if (queue0.empty() && queue1.empty()) throw runtime_error("Stack is empty");
			else if (!queue0.empty()) {
				Flush(queue0, queue1, queue0.size() - 1);
				queue0.pop();
			} else if (!queue1.empty()) {
				Flush(queue1, queue0, queue1.size() - 1);
				queue1.pop();
			}
		}

		void Push(const T & value)
		{
			if (!queue0.empty()) queue0.push(value);
			else if (!queue1.empty()) queue1.push(value);
			else queue0.push(value);
		}

		size_t Size(void) const
		{
			return queue0.size() + queue1.size();
		}

		T & Top(void)
		{
			if (queue0.empty() && queue1.empty()) throw runtime_error("Stack is empty");
			else if (!queue0.empty()) return queue0.back();
			else return queue1.back();
		}
	};

	// This implementation uses a vector as the container and the methods from <algorithm> to manipulate it.
	// The default template parameter Compare is less<T>, which creates a maximum heap.
	// If Compare is greater<T>, then it creates a minimum heap.
	// To track top n numbers in a set, create a min heap of size n,
	// enumerate each number and push it into the heap if it is greater than the root of heap.
	// To track bottom n numbers in a set, create a max heap of size n,
	// enumerate each number and push it into the heap if it is smaller than the root of heap.
	template<class T, class Compare = less<T>> class Heap {
	private:
		vector<T> _elements;
		Compare _compare;
		unsigned long _capacity;

		// Initialize the heap using a given vector
		// If the number of elements in the vector is greater than the heap capacity,
		// then only top (for min heap) or botton elements (for max heap) will be pushed into the heap.
		void Init(const vector<T> & input)
		{
			unsigned long l = min<unsigned long>(_capacity, (unsigned long)input.size());
			for (unsigned long i = 0; i < l; i++) {
				_elements.push_back(input[i]);
			}

			make_heap(_elements.begin(), _elements.end(), _compare);

			for (unsigned long i = l; i < input.size() - 1; i++) {
				if (_compare(input[i], Top())) {
					Pop();
					Push(input[i]);
				}
			}
		}

	public:
		// Create a heap that can contain upto ULONG_MAX elements
		Heap(void) : _capacity(ULONG_MAX) {}

		// Create a heap of specified capacity
		Heap(unsigned long cap) : _capacity(cap) {}

		// Create a heap using an existing container
		Heap(const vector<T> & input)
		{
			_capacity = ULONG_MAX;
			Init(input);
		}

		// Create a heap of specified capacity using an existing container
		Heap(const vector<T> & input, unsigned long cap)
		{
			_capacity = cap;
			Init(input);
		}

		~Heap(void) {}

		// Return true if this is really a heap
		bool IsHeap(void) const { return is_heap(_elements.begin(), _elements.end(), _compare); }

		// Pop the top of heap
		T Pop(void)
		{
			if (_elements.size() == 0) throw runtime_error("Heap is empty.");

			// pop_heap moves the top to the end of container
			pop_heap(_elements.begin(), _elements.end(), _compare);

			// cannot use a reference to the popped top element.
			// pop_back() will destroy the popped element.
			T value = _elements.back();

			// Remvoe the popped to element from the heap
			_elements.pop_back();

			return value;
		}

		// Try to push an element into the heap
		// Return true if an element is pushed into the heap successfully.
		// Return false if the heap is at capacity and the element does not fit into the heap.
		bool Push(const T & e)
		{
			while (_elements.size() >= _capacity) {
				// Check against the top element since it is the gate to the heap
				if (_compare(e, Top())) {
					// Pop the top to make a room for the element
					Pop();
				} else {
					// The element does not fit in the heap
					return false;
				}
			}

			// Add the element to the end of vector
			_elements.push_back(e);

			// push_heap moves the end of vector into the heap
			push_heap(_elements.begin(), _elements.end(), _compare);

			return true;
		}

		// Get the number of elements in the heap
		size_t Size(void) const { return _elements.size(); }

		// Get a reference to the top of heap
		const T & Top(void) const { return _elements.front(); }
	};
	
#pragma region Partition

	// Partition input into two ranges input[low..i] and input[(i+1)..high], such that
	// transform(input[low..i]) <= transform(value) < transform(input[(i+1)..high]).
	// Invariant: given j, divide the input into three ranges input[low..i],
	// input[(i+1)..(j-1)] and input[j..high] using value,
	// such that transform(input[low..i]) <= transform(value) < transform(input[(i+1)..(j-1)]).
	// Return the index i, i.e. the last element less than or equal to value
	// If all elements are less than value, then return index high
	// If all elements are greater than value, then return low-1
	template<class T, class C> static int PartitionByValue(
		vector<T> & input,
		int low,
		int high,
		const T & value,
		function<C(T)> transform = [&](T v)->C { return v; })
	{
		assert(low >= 0);
		assert(high < input.size());
		assert(low <= high);
		int i = low - 1;
		C v = transform(value);
		for (int j = low; j <= high; j++) {
			if (transform(input[j]) <= v) {
				// The check can be <.
				// The difference is:
				// 1. <= incurs more swaps, but it is stable because all elements equal to value
				//    are still in their original order. The return value is the last index of
				//    elements less than or equal to value.
				// 2. < incurs less swaps, but it is unstable. The return value is the last
				//    index of elements less than value.
				i++;
				if (i != j) swap(input[i], input[j]);
			}
		}
		// Now input[low..i] <= value < input[(i+1)..high]
		// Note not necessarily input[i] is the maximum in input[low..i],
		// i.e., it may not be true input[i] == value
		return i;
	}

	template<class T> static int PartitionByValue(vector<T> & input, int low, int high, const T & value)
	{
		return PartitionByValue<T, T>(input, low, high, value);
	}

	// Randomly select an element to partition the input.
	// Return the new index of selected element
	template<class T, class C> static int PartitionRandomly(
		vector<T> & input,
		int low,
		int high,
		function<C(T)> transform = [&](T v)->C { return v; })
	{
		assert(low >= 0);
		assert(high < input.size());
		assert(low <= high);
		int i = low + rand() % (high - low + 1);
		// move element input[i] to input[high], so on return the return index
		// points to the element
		swap(input[i], input[high]);
		return PartitionByValue<T, C>(input, low, high, input[high], transform);
	}

	template<class T> static int PartitionRandomly(vector<T> & input, int low, int high)
	{
		return PartitionRandomly<T, T>(input, low, high);
	}

	// Reorder input[low..high] such that it is partioned by the i-th order element,
	// i.e., input[low..(low+i-1)] <= input[low+i] <= input[low+i+1..high]
	// The order is zero-based, i.e., 0 <= i <= high - low
	// Return the i-th order element
	template<class T, class C> static T & PartitionByOrder(
		vector<T> & input,
		int low,
		int high,
		int i,
		function<C(T)> transform = [&](T v)->C { return v; })
	{
		assert(low >= 0);
		assert(high < input.size());
		assert(low <= high);
		assert(i <= high - low);
		if (low == high) return input[low];
		int m = PartitionRandomly(input, low, high, transform);
		int k = m - low;
		if (i == k) {
			// low ......... m ......... high
			// 0   ......... k
			// 0   ......... i
			return input[m];
		} else if (i < k) {
			// low ............ m ...... high
			// 0   ............ k
			// 0   ...... i
			return PartitionByOrder(input, low, m - 1, i, transform);
		} else {
			// low ...... m ............ high
			// 0   ...... k
			// 0   ............ i
			return PartitionByOrder(input, m + 1, high, i - k - 1, transform);
		}
	}

	template<class T> static T & PartitionByOrder(vector<T> & input, int low, int high, int i)
	{
		return PartitionByOrder<T, T>(input, low, high, i);
	}

#pragma endregion

#pragma region QuickSort

	template<class T> static void QuickSort(vector<T> & input)
	{
		int size = (int)input.size();
		if (size <= 1) return;

		function<void(int, int)>
		sort = [&](int low, int high) {
			// Use input[high] as the gate, so it will be moved to input[middle]
			int middle = PartitionByValue<T, T>(input, low, high, input[high]);
			// Ignore input[middle] in following sort
			if (low < middle) sort(low, middle - 1);
			if (middle < high) sort(middle + 1, high);
		};

		sort(0, size - 1);
	}

	template<class T> static void QuickSortInParallel(vector<T> & input)
	{
		int size = (int)input.size();
		if (size <= 1) return;

		function<void(int, int)>
		sort = [&](int low, int high) {
			// Use input[high] as the gate, so it will be moved to input[middle]
			int middle = PartitionByValue<T, T>(input, low, high, input[high]);
			// Ignore input[middle] in following sort
			parallel_invoke(
				[&, low, middle] { if (low < middle) sort(low, middle - 1); },
				[&, middle, high] { if (middle < high) sort(middle + 1, high); });
		};

		sort(0, size - 1);
	}

	template<class T> static void QuickSortRandomly(vector<T> & input)
	{
		int size = (int)input.size();
		if (size <= 1) return;

		function<void(int, int)>
		sort = [&](int low, int high) {
			int middle = PartitionRandomly<T, T>(input, low, high);
			// Ignore input[middle] in following sort, because
			// it is guaranteed input[middle] is the maximum in input[low..middle],
			// and the minimum in input[middle..high]
			if (low < middle) sort(low, middle - 1);
			if (middle < high) sort(middle + 1, high);
		};

		sort(0, size - 1);
	}

#pragma endregion

	template<class T> static void RadixSort(vector<vector<T>> & input)
	{
		if (input.size() == 0) return;
		if (input[0].size() == 0) return;

		function<function<bool(const vector<T> &, const vector<T> &)>(size_t)>
		compare = [&](size_t radix) {
			function<bool(const vector<T> &, const vector<T> &)>
			c = [=](const vector<T> & left, const vector<T> & right) {
				return left[radix] < right[radix];
			};

			return c;
		};

		size_t len = input[0].size();
		for (size_t i = 0; i < len; i++) {
			function<bool(const vector<T> &, const vector<T> &)> c = compare(i);
			stable_sort(input.begin(), input.end(), c);
		}
	}

#pragma region InsertSort

	template<class T> static void InsertSort(
		vector<T> & input,
		function<bool(const T &, const T &)> greater = [&](const T & x, const T & y)->bool { return x > y; })
	{
		for (int i = 1; i < (int)input.size(); i++) {
			// Record the current key value to insert into input[0..(i-1)]
			T key = input[i];
			int j = i - 1;
			// Shift any values in input[0..(i-1)] greater than the current key to the right,
			// so that the insert position for the current key is vacant.
			// Note the default greater is strict,
			// so the multiple instances of the same value preserve their
			// orignial orders, i.e., the sorting is stable.
			while (j >= 0 && greater(input[j], key)) {
				input[j + 1] = input[j];
				j--;
			}
			input[j + 1] = key;
		}
	}

	// Recursively sort input[0..(length-1)] by insertion
	// Use binary search to find the position to insert an element
	template<class T> static void InsertSortRecursively(vector<T> & input, size_t length)
	{
		if (input.size() <= 1 || length <= 1) return;

		// Recursively sort input[0..(length-2)]
		InsertSortRecursively(input, length - 1);

		// Record the current value to insert into input[0..(length-2)]
		T key = input[length - 1];

		// Find the last position after which the current value should be inserted.
		// -1 <= i <= (length-2)
		int i = PositionToInsert(key, input, 0, (int)length - 2, false);

		// Shift input[(i+1)..(length-2)] so that the position (i+1) for the current value is vacant.
		for (int j = (int)length - 2; j > i; j--) {
			input[j + 1] = input[j];
		}

		// Insert the current value
		input[i + 1] = key;
	}

#pragma endregion

	template<class T> static void SelectSort(
		vector<T> & input,
		function<bool(const T &, const T &)> greater = [&](const T & x, const T & y)->bool { return x > y; })
	{
		if (input.size() <= 1) return;
		for (size_t i = 0; i < input.size() - 1; i++) {
			size_t min = i;
			for (size_t j = i + 1; j < input.size(); j++) {
				if (greater(input[min], input[j])) {
					min = j;
				}
			}
			swap(input[i], input[min]);
		}
	}

#pragma region MergeSort

	// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
	// rearrange elements every step so that input[head..tail] is sorted.
	// In-place and stable.
	template<class T> static void Merge(vector<T> & input, int head, int middle, int tail, int step = 1)
	{
		if (input.size() <= 1 || head < 0 || middle <= 0 || tail < middle || tail <= head || step <= 0) return;
		// head and middle point to the heads of two sub sorted arrays.
		while (head < middle && middle <= tail) {
			if (input[head] <= input[middle]) {
				head += step;
			} else {
				T t = input[middle];
				// Shift input[head..(middle-step)] to input[(head+step)..middle]
				for (int i = middle; i > head; i -= step) {
					input[i] = input[i - step];
				}
				input[head] = t;
				// Move to the next pair of elements
				head += step;
				middle += step;
			}
		}
	}

	template<class T> static void MergeSort(vector<T> & input, int head, int tail, int step = 1)
	{
		if (input.size() <= 1 || head < 0 || tail < 0 || tail < head || step <= 0) return;
		if (head < tail) {
			int middle = head + (((tail - head) / step) >> 1) * step + step;
			parallel_invoke(
				[&input, head, middle, step] { MergeSort(input, head, middle - step, step); },
				[&input, middle, tail, step] { MergeSort(input, middle, tail, step); }
			);
			Merge(input, head, middle, tail, step);
		}
	}

	template<class T> static void MergeSort(vector<T> & input, int step = 1)
	{
		MergeSort(input, 0, (int)input.size() - 1, step);
	}

	// A comparator betweeb two Element<T> instances
	template<class T> struct Greater
		: public binary_function<
					const pair<vector<T>, size_t> &,
					const pair<vector<T>, size_t> &,
					bool>
	{
		bool operator() (const pair<vector<T>, size_t> & left, const pair<vector<T>, size_t> & right) const
		{
			return left.first[left.second] > right.first[right.second];
		}
	};

	// Implementation of merge-sort multiple sorted arrays
	template<class T> void MergeSort(vector<vector<T>> & inputs, vector<T> & output)
	{
		if (inputs.size() == 0) return;

		// A minimum heap
		Heap<pair<vector<T>, size_t>, Greater<T>> heap((unsigned long)inputs.size());

		for (size_t i = 0; i < inputs.size(); i++) {
			if (inputs[i].size() > 0) {
				// Initialize the heap with the first element in each sorted array
				heap.Push(make_pair(inputs[i], 0));
			}
		}

		while (heap.Size() > 0) {
			// Extract the minimum element from the heap
			pair<vector<T>, size_t> min = heap.Pop();

			// append the minum element into the output vector
			output.push_back(min.first[min.second]);

			// Move to the next element in the same array
			min.second++;

			if (min.second < min.first.size()) {
				// The array still has elements.
				// Push the next element into the heap.
				heap.Push(min);
			}
		}
	}

#pragma endregion

#pragma region HeapSort

	// HeapSort use a max heap

	// Rearrange [begin, end] so that it is a heap.
	// The assumption is the subtrees rooted at begin are already heapified.
	// Just need to push down begin if necessary
	template<class T> static void HeapifyElement(vector<T> & input, size_t begin, size_t end)
	{
		assert(input.size() > 0);
		assert(begin < input.size());
		assert(end < input.size());

		while (begin < end) {
			size_t max = begin;
			size_t l = (begin << 1) + 1;
			if (l <= end && input[l] > input[max]) {
				max = l;
			}

			size_t r = (begin << 1) + 2;
			if (r <= end && input[r] > input[max]) {
				max = r;
			}

			if (max == begin) break;

			swap(input[begin], input[max]);
			begin = max;
		}
	}

	// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
	// The assumption is the subtrees rooted at i are already heapified.
	template<class T> static void HeapifyElement(vector<T> & input, size_t begin, size_t end, size_t d)
	{
		assert(input.size() > 0);
		assert(begin < input.size());
		assert(end < input.size());
		assert(d >= 2);

		while (begin < end) {
			size_t max = begin;

			for (size_t j = 0; j < d; j++) {
				size_t c = begin * d + j + 1;
				if (c <= end && input[c] > input[max]) {
					max = c;
				}
			}

			if (max == begin) break;
			
			swap(input[begin], input[max]);
			begin = max;
		}
	}

	// Construct the array into a max heap from bottom up
	template<class T> static void Heapify(vector<T> & input)
	{
		if (input.size() <= 1) return;

		size_t height = 0;
		size_t count = input.size();
		while (count > 0) {
			count = count >> 1;
			height++;
		}

		// The elements at bottom are indexed in [2^(height - 1) - 1, 2^height - 2]
		// We only need to heapify elements above them
		for (long long i = ((1 << (height - 1)) - 2); i >= 0; i--) {
			HeapifyElement(input, (size_t)i, input.size() - 1);
		}
	}

	// d-ary
	//                                                  0
	//                   1                              2                    ...          d
	// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
	// (d^2+d+1) (d^2+d+2) ...
	// ......
	// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
	// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]
	//
	// (d^(h-1)-1)/(d-1) < count <= (d^h-1)/(d-1)
	// d^(h-1) - 1 < count * (d-1) <= d^h - 1
	// There are h d-bits and the pattern is between:
	//  1    0    0    ...  0    0    0
	// (d-1)(d-1)(d-1) ... (d-1)(d-1)(d-1)
	template<class T> static void Heapify(vector<T> & input, size_t d)
	{
		if (input.size() <= 1) return;

		assert(d >= 2);

		size_t height = 0;
		size_t count = input.size() * (d - 1);
		while (count > 0) {
			count = count / d;
			height++;
		}

		long long index = ((long long)pow(d, height - 1) - 1) / (d - 1) - 1;
		for (long long i = index; i >= 0; i--) {
			HeapifyElement(input, (size_t)i, input.size() - 1, d);
		}
	}

	template<class T> static void HeapifyInParallel(vector<T> & input)
	{
		if (input.size() <= 1) return;

		size_t height = 0;
		size_t count = input.size();
		while (count > 0) {
			count = count >> 1;
			height++;
		}

		for (long long h = (height - 1); h > 0; h--) {
			// For h, the index is in [((1 << (h-1)) - 1), ((1 << h) - 2)]
			parallel_for(
				size_t((1 << (h - 1)) - 1),
				size_t((1 << h) - 1),
				[&](size_t i) { HeapifyElement(input, i, input.size() - 1); }
			);
		}
	}

	template<class T> static void HeapifyInParallel(vector<T> & input, size_t d)
	{
		if (input.size() <= 1) return;

		assert(d >= 2);

		size_t height = 0;
		size_t count = input.size() * (d - 1);
		while (count > 0) {
			count = count / d;
			height++;
		}

		for (long long h = height - 1; h > 0; h--) {
			// For h, the index is in [(d ^ (h - 1) - 1) / (d - 1), (d^h - 1) / (d - 1) - 1]
			parallel_for(
				size_t((pow(d, h - 1) - 1) / (d - 1)),
				size_t((pow(d, h) - 1) / (d - 1)),
				[&](size_t i) { HeapifyElement(input, i, input.size() - 1, d); }
			);
		}
	}

	template<class T> static void HeapSort(vector<T> & input)
	{
		if (input.size() <= 1) return;

		// Make a heap
		Heapify(input);

		// Sort
		for (long long i = input.size() - 1; i > 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			swap(input[0], input[i]);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (size_t)i - 1);
		}
	}

	template<class T> static void HeapSort(vector<T> & input, size_t d)
	{
		if (input.size() <= 1) return;

		// Make a heap
		Heapify(input, d);

		// Sort
		for (long long i = input.size() - 1; i > 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			swap(input[0], input[i]);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (size_t)i - 1, d);
		}
	}

	template<class T> static void HeapSortInParallel(vector<T> & input)
	{
		if (input.size() <= 1) return;

		// Make a heap
		HeapifyInParallel(input);

		// Sort
		for (long long i = input.size() - 1; i > 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			swap(input[0], input[i]);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (size_t)i - 1);
		}
	}

	template<class T> static void HeapSortInParallel(vector<T> & input, size_t d)
	{
		if (input.size() <= 1) return;

		// Make a heap
		HeapifyInParallel(input, d);

		// Sort
		for (long long i = input.size() - 1; i > 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			swap(input[0], input[i]);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (size_t)i - 1, d);
		}
	}

#pragma endregion

	// Cache <key, cost> entries.
	// Keys are losely ordered, i.e., overally increasing but some keys
	// are greater than their successors. Trim cache:
	// 1. All keys smaller than a threshold, and
	// 2. The sum of costs of left entries should be smaller than a quota.
	static void TrimCache(map<int, int> & cache, int maxKey, int maxCost)
	{

	}
}