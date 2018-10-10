#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include "String.h"
#include "StringProblem.h"

using namespace std;

namespace Test {
	class FiniteAutomation {
	public:
		__declspec(dllexport) FiniteAutomation(const char * pattern)
		{
			if (pattern == nullptr) throw invalid_argument("pattern is nullptr");
			if (pattern[0] == '\0') throw invalid_argument("pattern is empty");
			int length = (int)strlen(pattern);
			if (length <= 0) throw invalid_argument(String::Format("length %d <= 0", length));

			this->ComputeTransition(pattern, length);
		}

		__declspec(dllexport) ~FiniteAutomation(void)
		{
			for_each(this->transition.begin(), this->transition.end(), [](pair<int, map<char, int>*> it)->void {
				if (it.second != nullptr) {
					delete it.second;
					it.second = nullptr;
				}
			});
		}

		__declspec(dllexport) int PatternLength(void)
		{
			return this->transition.size() - 1;
		}

		__declspec(dllexport) void Print(void)
		{
			for_each(this->transition.begin(), this->transition.end(), [](pair<int, map<char, int>*> it)->void {
				printf_s("State %d\n", it.first);
				for_each(it.second->begin(), it.second->end(), [](pair<char, int> iit)->void {
					printf_s("\t%c -> %d\n", iit.first, iit.second);
				});
			});
		}

		// Find occurrences of pattern in the given input
		__declspec(dllexport) vector<int> SearchString(const char * input, int length)
		{
			vector<int> indices;
			if (input == nullptr || input[0] == '\0' || length <= 0) return indices;
			int state = -1;
			for (int i = 0; i < length; i++) {
				map<int, map<char, int>*>::iterator itState = this->transition.find(state);
				if (itState == this->transition.end()) {
					state = -1;
					continue;
				}

				map<char, int>::iterator itChar = itState->second->find(input[i]);
				if (itChar == itState->second->end()) {
					// input[i] is invalid
					state = -1;
				} else {
					state = itChar->second;
					if (state == this->transition.size() - 2) {
						// It is the final state
						indices.push_back(i - state);
					}
				}
			}

			return indices;
		}

	private:
		void ComputeTransition(const char * pattern, int length)
		{
			// Construct state transition given pattern
			// Valid states are -1, 0, 1, ..., (length-1)

			unique_ptr<char[]> uniquechars(new char[length + 1]);
			memcpy(uniquechars.get(), pattern, length * sizeof(char));
			uniquechars.get()[length] = '\0';
			int count = StringProblem::RemoveDuplicateChars(uniquechars.get(), length);

			// Initialize starting state -1
			map<char, int>* initState = new map<char, int>();
			initState->insert(pair<char, int>(pattern[0], 0));
			this->transition.insert(pair<int, map<char, int>*>(-1, initState));

			unique_ptr<char[]> buffer(new char[length + 2]);
			for (int state = 0; state < length; state++) {
				buffer[state] = pattern[state];
				map<char, int>* nextState = new map<char, int>();
				// Build nextState given each unique char
				for (int i = 0; i < count; i++) {
					char c = uniquechars[i];
					buffer[state + 1] = c;
					buffer[state + 2] = '\0';
					int index = Suffix(pattern, buffer.get());
					if (index != -1) {
						nextState->insert(pair<char, int>(c, index));
					}
				}

				this->transition.insert(pair<int, map<char, int>*>(state, nextState));
			}
		}

		// Find the longest prefix substring of pattern that is also a suffix of input
		static int Suffix(const char* pattern, const char* input)
		{
			if (pattern == nullptr) return -1;
			if (input == nullptr) return -1;
			int m = (int)strlen(pattern);
			if (m <= 0) return -1;
			int n = (int)strlen(input);
			if (n <= 0) return -1;

			for (int i = min(m - 1, n - 1); i >= 0; i--) {
				// Start from pattern[i], move backward to pattern[0]
				int j = 0;
				while (pattern[i - j] == input[n - 1 - j] && j <= i) {
					j++;
				}

				if (j == i + 1) {
					// pattern[0..i] == input[(n-1-i)..(n-1)]
					return i;
				}
			}

			return -1;
		}

		// For current state i, given a character c determine the next state j
		map<int, map<char, int>*> transition;
	};
}