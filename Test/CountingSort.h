#pragma once
#include <memory>
#include "Array.h"
#include "BitSet.h"

using namespace std;

namespace Test {
	class __declspec(dllexport) CountingSort {
	private:
		static void GetRange(const int * input, int length, int & minValue, int & range);

	public:
		// Sort input and return the result in output
		static void Sort(const int * input, int length, int * output);
		// Sort in place
		static void Sort(int * input, int length);
	};
}

