#pragma once
#include <memory>
#include "Mask.h"
#include "MinMax.h"
using namespace std;
namespace My {
	class __declspec(dllexport) CountingSort {
	private:
		static void GetRange(const int * input, int length, int & minValue, int & range);

	public:
		static void Sort(const int * input, int length, int * output);
		static void Sort(int * input, int length);
	};
}