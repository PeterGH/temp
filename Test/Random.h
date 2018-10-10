#pragma once
#pragma once

#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "String.h"
using namespace std;

namespace Test {
	class Random {
	private:
		Random();
		~Random() {}
	public:
		// Call rand() to get a random number in [0, RAND_MAX]
		__declspec(dllexport) static int Next(void);

		// Return a random value in [0, max]
		__declspec(dllexport) static int Next(int max);

		// Return a value in [min, max]
		__declspec(dllexport) static int Next(int min, int max);

		// Select m samples from [0, n-1] in 
		// which each m samples is equally likely.
		// The algorithm is described in exercise 5.3-7 in MIT Introduction to Algorithm, Third Edition.
		__declspec(dllexport) static void Sample(unsigned int n, unsigned int m, vector<unsigned int> & samples);
		__declspec(dllexport) static void Sample2(unsigned int n, unsigned int m, vector<unsigned int> & samples);
	};
}

