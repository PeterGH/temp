#include "FiniteAutomation.h"
#include "String.h"

namespace My {

	//
	// FiniteAutomation
	//

	FiniteAutomation::FiniteAutomation(char * pattern, int length)
	{
		if (pattern == nullptr) return;
		if (length <= 0) return;

		this->ComputeTransition(pattern, length);
	}

	FiniteAutomation::~FiniteAutomation(void)
	{
		for_each(this->transition.begin(), this->transition.end(), [](pair<int, map<char, int>*> it)->void {
			if (it.second != nullptr) {
				delete it.second;
				it.second = nullptr;
			}
		});
	}

	void FiniteAutomation::ComputeTransition(char * pattern, int length)
	{
		// Construct state transition given pattern
		// Valid states are -1, 0, 1, ..., (length-1)

		unique_ptr<char[]> uniquechars(new char[length+1]);
		//strcpy_s(uniquechars.get(), length+1, pattern);
		memcpy(uniquechars.get(), pattern, length*sizeof(char));
		uniquechars.get()[length] = '\0';
		int count = String::RemoveDuplicateChars(uniquechars.get(), length);

		// Initialize starting state -1
		map<char, int>* initState = new map<char, int>();
		initState->insert(pair<char, int>(pattern[0], 0));
		this->transition.insert(pair<int, map<char, int>*>(-1, initState));

		unique_ptr<char[]> buffer(new char[length + 2]);

		for (int state = 0; state < length; state ++) {
			buffer[state] = pattern[state];
			map<char, int>* nextState = new map<char, int>();		
			// Build nextState given each unique char
			for (int i = 0; i < count; i ++) {
				char c = uniquechars[i];
				buffer[state+1] = c;
				buffer[state+2] = '\0';
				int index = Suffix(pattern, buffer.get());
				if (index != -1) {
					nextState->insert(pair<char, int>(c, index));
				}
			}

			this->transition.insert(pair<int, map<char, int>*>(state, nextState));
		}
	}

	vector<int> FiniteAutomation::SearchString(char * input, int length)
	{
		vector<int> indices;
		if (input == nullptr || length <= 0) return indices;
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

	// Find the longest prefix substring of pattern that is also a suffix of input
	int FiniteAutomation::Suffix(char* pattern, char* input)
	{
		if (pattern == nullptr) return -1;
		if (input == nullptr) return -1;
		int m = (int)strlen(pattern);
		if (m <= 0) return -1;
		int n = (int)strlen(input);
		if (n <= 0) return -1;

		for (int i = min(m-1, n-1); i >= 0; i --) {
			// Start from pattern[i], move backward to pattern[0]
			int j = 0;
			while (pattern[i-j] == input[n-1-j] && j <= i) {
				j ++;
			}

			if (j == i+1) {
				// pattern[0..i] == input[(n-1-i)..(n-1)]
				return i;
			}
		}

		return -1;
	}

	void FiniteAutomation::Print(void)
	{
		for_each(this->transition.begin(), this->transition.end(), [](pair<int, map<char, int>*> it)->void {
			printf_s("State %d\n", it.first);
			for_each(it.second->begin(), it.second->end(), [](pair<char, int> iit)->void {
				printf_s("\t%c -> %d\n", iit.first, iit.second);
			});
		});
	}

	int FiniteAutomation::PatternLength(void)
	{
		return this->transition.size() - 1;
	}

	//
	// FiniteAutomationWithWildChar
	//

	FiniteAutomationWithWildChar::FiniteAutomationWithWildChar(char * pattern, int length)
	{
		if (pattern == nullptr) return;
		if (length <= 0) return;

		int i = 0;
		for (int j = 0; j < length; j++) {
			if (pattern[j] != FiniteAutomationWithWildChar::WildChar) {
				if (j > 0 && pattern[j-1] == FiniteAutomationWithWildChar::WildChar) {
					i = j;
				}

				if (j == length - 1) {
					this->patterns.push_back(unique_ptr<FiniteAutomation>(new FiniteAutomation(&pattern[i], j-i+1)));
				}
			} else {
				if (j > 0 && pattern[j-1] != FiniteAutomationWithWildChar::WildChar) {
					this->patterns.push_back(unique_ptr<FiniteAutomation>(new FiniteAutomation(&pattern[i], j-i)));
				}
			}
		}
	}

	void FiniteAutomationWithWildChar::Print(void)
	{
		for_each (this->patterns.begin(), this->patterns.end(), [&](unique_ptr<FiniteAutomation> &it) {
			it->Print();
		});
	}

	multimap<int, int> FiniteAutomationWithWildChar::SearchString(char * input, int length)
	{
		multimap<int, int> indices;

		vector<unique_ptr<FiniteAutomation>>::iterator it = this->patterns.begin();

		vector<int> found = (*it)->SearchString(input, length);
		int patternLength = (*it)->PatternLength();
		vector<unique_ptr<FiniteAutomation>>::iterator next = it;
		next++;
		if (next == this->patterns.end()) {
			for_each (found.begin(), found.end(), [&](int p) {
				indices.insert(pair<int, int>(p, (p + patternLength - 1)));
			});
		} else {
			for_each (found.begin(), found.end(), [&](int p) {
				SearchString(next, input, p + patternLength, length - p - patternLength, p, indices);
			});
		}

		return indices;
	}

	void FiniteAutomationWithWildChar::SearchString(
		const vector<unique_ptr<FiniteAutomation>>::iterator & it, char * input, int start, int length, int first, multimap<int, int> & indices)
	{
		vector<int> found = (*it)->SearchString(&input[start], length);
		int patternLength = (*it)->PatternLength();
		vector<unique_ptr<FiniteAutomation>>::iterator next = it;
		next++;
		if (next == this->patterns.end()) {
			for_each (found.begin(), found.end(), [&](int p) {
				indices.insert(pair<int, int>(first, (start + p + patternLength - 1)));
			});
		} else {
			for_each (found.begin(), found.end(), [&](int p) {
				SearchString(next, input, start + p + patternLength, length - p - patternLength, first, indices);
			});
		}
	}


}