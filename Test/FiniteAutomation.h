#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include "String.h"
using namespace std;

namespace Test {
	class FiniteAutomation {
	public:
		__declspec(dllexport) FiniteAutomation(char * pattern, int length);
		__declspec(dllexport) ~FiniteAutomation(void);
		__declspec(dllexport) int PatternLength(void);
		__declspec(dllexport) void Print(void);

		// Find occurrences of pattern in the given input
		__declspec(dllexport) vector<int> SearchString(char * input, int length);		
				
	private:
		void ComputeTransition(char * pattern, int length);
		static int Suffix(char* pattern, char* input);
		
		// For current state i, given a character c determine the next state j
		map<int, map<char, int>*> transition;
	};
}
