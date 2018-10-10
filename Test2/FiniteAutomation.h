#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <vector>
#include <functional>
using namespace std;

namespace My {
	class FiniteAutomation {
	public:
		__declspec(dllexport) FiniteAutomation(char * pattern, int length);
		__declspec(dllexport) FiniteAutomation(void) {}
		__declspec(dllexport) virtual ~FiniteAutomation(void);
		__declspec(dllexport) void Print(void);
		__declspec(dllexport) vector<int> SearchString(char * input, int length);
		__declspec(dllexport) static int Suffix(char* pattern, char* input);
		__declspec(dllexport) int PatternLength(void);
		
	protected:
		void ComputeTransition(char * pattern, int length);

		// For current state i, given a character c determine the next state j
		map<int, map<char, int>*> transition;
	};

	class FiniteAutomationWithWildChar {
	public:
		__declspec(dllexport) FiniteAutomationWithWildChar(char * pattern, int length);
		__declspec(dllexport) ~FiniteAutomationWithWildChar(void) {}
		__declspec(dllexport) void Print(void);
		__declspec(dllexport) multimap<int, int> SearchString(char * input, int length);
	private:
		void SearchString(const vector<unique_ptr<FiniteAutomation>>::iterator & it, char * input, int start, int length, int first, multimap<int, int> & indices);
		static const char WildChar = '*';
		vector<unique_ptr<FiniteAutomation>> patterns;
	};
}
