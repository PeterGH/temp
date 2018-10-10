#include "Random.h"

namespace Test {
	Random::Random()
	{
		// Seed the random-number generator with the current time so that
		// the numbers will be different every time we run.
		srand((unsigned)time(NULL));
	}

	int Random::Next(void)
	{
		return rand();
	}

	int Random::Next(int max)
	{
		if (max < 0) throw invalid_argument(String::Format("%d is less than zero", max));
		if (max > RAND_MAX) throw invalid_argument(String::Format("%d is greater than RAND_MAX", max));
		
		// +--------+--------+--------+-- ........ --+--------+--------+--------+
		// 0        1        2        3             max-2    max-1    max     RAND_MAX

		double d = (double)RAND_MAX / (max + 1);
		int r = (int)(rand() / d);
		if (r > max) r = max;
		return r;
	}

	int Random::Next(int min, int max)
	{
		if (min > max) throw invalid_argument(String::Format("%d is larger than %d", min, max));
		if (max - min > RAND_MAX) throw invalid_argument(String::Format("%d - %d is greater than RAND_MAX", max, min));
		int r = min + Next(max - min);
		return r;
	}

	void Random::Sample(unsigned int n, unsigned int m, vector<unsigned int> & samples)
	{
		if (m == 0) return;
		if (m > n) throw invalid_argument(String::Format("%d is less than %d", n, m));
		Sample(n - 1, m - 1, samples);
		unsigned int i = (unsigned int)Next(n - 1);
		if (find(samples.begin(), samples.end(), i) == samples.end()) {
			samples.push_back(i);
		} else {
			samples.push_back(n - 1);
		}
	}

	void Random::Sample2(unsigned int n, unsigned int m, vector<unsigned int> & samples)
	{
		if (m == 0) return;
		if (m > n) throw invalid_argument(String::Format("%d is less than %d", n, m));
		for (unsigned int j = n - m; j < n; j++) {
			unsigned int i = (unsigned int)Next(j);
			if (find(samples.begin(), samples.end(), i) == samples.end()) {
				samples.push_back(i);
			} else {
				samples.push_back(j);
			}
		}
	}
}