#pragma once

#include <string>
#include "MyArray.h"
using namespace std;

class __declspec(dllexport) Palindrome
{
public:
	Palindrome(void);
	~Palindrome(void);

	static void LengthTable(string & input, Array2D<size_t> & length);
	static void LongestSubsequenceByTable(string & input, string & output);
	static void LengthArray(string & input, size_t length[]);	
	static void LongestSubsequenceByArray(string & input, string & output);
};

