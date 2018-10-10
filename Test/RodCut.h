#pragma once
#include <iostream>
#include <vector>
using namespace std;
namespace Test {
	class __declspec(dllexport) RodCut {
	public:
		RodCut(void) {}
		~RodCut(void) {}
		static void ComputeFirstCut(const vector<double> & utility, vector<double> & maxUtility, vector<int> & firstCut);
		static void PrintResult(const vector<double> & utility);
	};
}