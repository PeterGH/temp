#pragma once

#include <vector>

using namespace std;

class __declspec(dllexport) RodCutting
{
public:
	RodCutting(void);
	~RodCutting(void);

	static void ComputeFirstCut(vector<double> & utility, vector<double> & maxUtility, vector<int> & firstCut);
	static void PrintResult(vector<double> & utility);
};