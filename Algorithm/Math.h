#pragma once

#include <string>

using namespace std;

namespace Test {
	class Math {
	public:
		__declspec(dllexport) static size_t CountBits(unsigned int n)
		{
			int c = 0;
			while (n != 0) {
				n = n >> 1;
				c++;
			}
			return c;
		};

		__declspec(dllexport) static size_t CountBitOnes(unsigned int n)
		{
			int c = 0;
			while (n != 0) {
				// erase one bit from the lower end
				// 0x####0100 & 0x####00FF = 0x####0000
				n = n & (n - 1);
				c++;
			}
			return c;
		};

		__declspec(dllexport) static int LowerMedian(int b, int e)
		{
			// If e - b + 1 = 2m
			// +----------------+    +------------------+
			// b               b+m-1 b+m             e = b+2m-1
			// The median index is b+m-1 = b + (e - b) / 2, rounding to the lower boundary
			//
			// If e - b + 1 = 2m-1
			// +----------------+    +     +------------------+
			// b               b+m-2 b+m-1 b+m+1             e = b+2m-2
			// The median index is b+m-1 = b + (e - b) / 2
			return b + ((e - b) >> 1);
		}

		__declspec(dllexport) static int HigherMedian(int b, int e)
		{
			// If e - b + 1 = 2m
			// +----------------+    +------------------+
			// b               b+m-1 b+m             e = b+2m-1
			// The median index is b+m = b + (e - b + 1) / 2, rounding to the lower boundary
			//
			// If e - b + 1 = 2m-1
			// +----------------+    +     +------------------+
			// b               b+m-2 b+m-1 b+m+1             e = b+2m-2
			// The median index is b+m-1 = b + (e - b + 1) / 2
			return b + ((e - b + 1) >> 1);
		}

		__declspec(dllexport) static long long ToInteger(const string & input)
		{
			if (input.length() == 0) throw invalid_argument("input is empty");
			long long s = 0;
			bool negative = input[0] == '-';
			for (size_t i = negative ? 1 : 0; i < input.length(); i++) {
				if (input[i] < '0' || input[i] > '9') throw invalid_argument("input is not an integer");
				s = s * 10 + input[i] - '0';
			}
			return negative ? -s : s;
		}

		template<class T> __declspec(dllexport) static T GreatestCommonDivisor(T n0, T n1)
		{
			if (n0 == 0 && n1 == 0) throw invalid_argument("(0, 0) has no greatest common divisor");
			if (n0 < 0) n0 = -n0;
			if (n1 < 0) n1 = -n1;
			if (n0 == 0) return n1;
			if (n1 == 0) return n0;
			if (n1 > n0) swap(n0, n1);
			T r = n0 % n1;
			while (r != 0) {
				n0 = n1;
				n1 = r;
				r = n0 % n1;
			}
			return n1;
		}
	};
}

