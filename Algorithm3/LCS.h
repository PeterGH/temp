#pragma once

#include <string>
using namespace std;

class __declspec(dllexport) LCS
{
public:
	LCS(void);
	~LCS(void);
	
	static void PrintTable(int * T, size_t m, size_t n);
	static void LengthTable(string & x, string & y, int * length, int * select);
	static void PrintLCS(string & x, string & y);
};

