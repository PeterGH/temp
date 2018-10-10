#pragma once
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

namespace My {
	class Random {
	public:
		__declspec(dllexport) Random(void);			
		__declspec(dllexport) ~Random(void) {}
		__declspec(dllexport) int Next(void);
		// Return a value in [0, max]
		__declspec(dllexport) int Next(int max);
		// Return a value in [min, max]
		__declspec(dllexport) int Next(int min, int max);
		// Select m samples from [0, n-1] in 
		// which each m samples is equally likely.
		// The algorithm is described in exercise 5.3-7 in MIT Introduction to Algorithm, Third Edition.
		__declspec(dllexport) void Sample(unsigned int n, unsigned int m, vector<unsigned int> & samples);
	};
}
