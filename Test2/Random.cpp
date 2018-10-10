#include "Random.h"

namespace My {
	
	Random::Random(void)
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
		if (max < 0) {
			throw invalid_argument("Random::Next(max): max is less than zero");
		}

		if (max > RAND_MAX - 1) {
			throw invalid_argument("Random::Next(max): max is greater than RAND_MAX-1");
		}

		int r = rand() / (RAND_MAX / (max + 1));

		// r might be larger than max if rand() is too close to RAND_MAX

		// +--------+--------+--------+-- ........ --+--------+--------+--------+----+
		// 0        1        2        3             max-2    max-1    max     max+1 RAND_MAX
		if (r > max) r = max;
		return r;
	}

	int Random::Next(int min, int max)
	{
		if (min > max) {
			throw invalid_argument("Random::Next(min, max): min is larger than max");
		}

		if (max - min > RAND_MAX - 1) {
			throw invalid_argument("Random::Next(min, max): max-min is greater than RAND_MAX-1");
		}

		int r = min + Next(max - min);
		return r;
	}

	void Random::Sample(unsigned int n, unsigned int m, vector<unsigned int> & samples)
	{
		if (m == 0) return;
		if (m > n) throw invalid_argument("Sample(n, m, samples): n is less than m");
		Sample(n - 1, m - 1, samples);
		unsigned int i = (unsigned int)Next(n - 1);
		if (find(samples.begin(), samples.end(), i) == samples.end()) {
			samples.push_back(i);
		} else {
			samples.push_back(n - 1);
		}
	}
}
