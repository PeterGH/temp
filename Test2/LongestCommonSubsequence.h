#pragma once
#include <string>
using namespace std;

namespace My {
	class __declspec(dllexport) LongestCommonSubsequence
	{
	public:
		LongestCommonSubsequence(void) {}
		~LongestCommonSubsequence(void) {}
		static void PrintTable(int * T, size_t m, size_t n);
		static void LengthTable(string & x, string & y, int * length, int * select);
		static void PrintLCS(string & x, string & y);
	};
}

