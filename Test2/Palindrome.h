#pragma once
#include <string>
#include "Array.h"
using namespace std;
namespace My {
	class __declspec(dllexport) Palindrome {
	public:
		Palindrome(void) {}
		~Palindrome(void) {}
		static void LengthTable(string & input, Array2D<size_t> & length);
		static void LongestSubsequenceByTable(string & input, string & output);
		static void LengthArray(string & input, size_t length[]);	
		static void LongestSubsequenceByArray(string & input, string & output);
	};
}

