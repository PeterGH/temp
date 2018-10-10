#pragma once
#include "MRInteger.h"
#include <vector>

namespace My {
	
	class RadixSort {
	public:
		__declspec(dllexport) static void Sort(std::vector<MRInteger> & numbers);
	};
}

