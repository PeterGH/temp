#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

namespace Test {
	class __declspec(dllexport) LongestCommonSubsequence {
	private:
		static void PrintTable(int * T, size_t m, size_t n);
		static void LengthTable(string & x, string & y, int * length, int * select);		
	public:
		LongestCommonSubsequence(void) {}
		~LongestCommonSubsequence(void) {}
		static void PrintLCS(string & x, string & y);
	};
}

