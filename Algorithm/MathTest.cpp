#include "Header.h"

void MathTest::Init(void)
{
	Add("GCD", [&]() {
		auto check = [&](int n0, int n1, int e) {
			int r = Math::GreatestCommonDivisor<int>(n0, n1);
			Logger().WriteInformation("GCD(%d, %d) = %d\n", n0, n1, r);
			ASSERT1(r == e);
		};
		check(1, 0, 1);
		check(0, 1, 1);
		check(-1, 0, 1);
		check(1, 2, 1);
		check(2, 3, 1);
		check(2, 4, 2);
		check(3, 21, 3);
		check(42, 6, 6);
		check(56, 21, 7);
		check(57, 21, 3);
		check(77, 9, 1);
		check(1, -2, 1);
		check(-2, 3, 1);
		check(-2, -4, 2);
		check(-3, 21, 3);
		check(-42, 6, 6);
		check(-56, -21, 7);
		check(-57, -21, 3);
		check(77, -9, 1);
	});
}