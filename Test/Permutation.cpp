#include "Permutation.h"

namespace Test {
	Permutation::Permutation(unsigned int length)
	{
		std::unique_ptr<unsigned int[]> bases(new unsigned int[length]);
		for (unsigned int i = 0; i < length; i++) {
			bases[i] = i + 1;
		}

		_counter = new MRInteger(bases.get(), length);
	}

	Permutation::~Permutation(void)
	{
		delete _counter;
	}

	string Permutation::GetPermutation(int n, int k)
	{
		if (n <= 0 || k <= 0) return string();

		int i = 1; // Count number of digits to permute
		int m = 1; // Count number of permutations of i digits, i.e. i!

		while (m < k && i < n) {
			i++;
			m *= i;
		}

		if (m < k) return string(); // k > n!

		// Now m = i!, and (i-1)! < k <= i!

		// 1 2 3 ...... n-i n-i+1 n-i+2 ...... n-1 n
		// ~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~
		//     not permute         permute i digits

		string output;

		// append {1, 2, 3, ..., n-i}
		for (int j = 1; j <= n - i; j++) {
			output.append(1, '0' + j);
		}

		// Permute the last i digits
		vector<int> permute;

		// Initialize with {n-i+1, ..., n}
		for (int j = n - i + 1; j <= n; j++) {
			permute.push_back(j);
		}

		while (i > 0) {
			// For each loop, the variables are defined as:
			//   i, number of digits to permute
			//   m, number of permutations of i digits
			//   k, index (1-based) of target in m permutations

			if (i == 1) {
				// k = 1 since k <= m = i! = 1
				output.append(1, '0' + permute[permute.size() - 1]);
				break;
			} else if (i == 2) {
				if (k == 1) {
					output.append(1, '0' + permute[permute.size() - 2]);
					output.append(1, '0' + permute[permute.size() - 1]);
				} else { // k = 2
					output.append(1, '0' + permute[permute.size() - 1]);
					output.append(1, '0' + permute[permute.size() - 2]);
				}
				break;
			}

			// Permute 1 2 3 4 5 ...... i-1 i, will get i ranges determined by the first digit
			//   1 ......
			//   1 ......
			//   2 ......
			//   2 ......
			//   ......
			//   ......
			//   i-1 ......
			//   i-1 ......
			//   i ......
			//   i ......

			m = m / i; // Count permutations per range

			int j = (k - 1) / m + 1; // Get the range index (1-based) which k falls into

			// 1 2 3 4 5 ... j-1 j   j+1 ... i-1 i
			// j 1 2 3 4 5 ...   j-1 j+1 ... i-1 i
			int t = permute[j - 1];
			permute.erase(permute.begin() + j - 1);
			output.append(1, '0' + t);

			i--; // Move on to the rest i - 1 digits
			k = ((k - 1) % m) + 1; // Get the index in the j-th range
		}

		return output;
	}
}