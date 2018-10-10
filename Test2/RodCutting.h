#pragma once
#include <vector>
using namespace std;
namespace My {
	class __declspec(dllexport) RodCutting {
	public:
		RodCutting(void) {}
		~RodCutting(void) {}
		static void ComputeFirstCut(const vector<double> & utility, vector<double> & maxUtility, vector<int> & firstCut);
		static void PrintResult(const vector<double> & utility);
	};
}

