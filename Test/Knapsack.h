#pragma once
#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "Matrix.h"
using namespace std;
namespace Test {
	class __declspec(dllexport) Knapsack {
	public:
		Knapsack(void) {}
		~Knapsack(void) {}
		static void ComputeValues(vector<pair<int,int>> & items, Matrix<int> & values);
		static void SelectItems(vector<pair<int,int>> & items, Matrix<int> & values, vector<pair<int,int>> & selected);
		static void PrintSolution(vector<pair<int,int>> & items, Matrix<int> & values);
	};
}

