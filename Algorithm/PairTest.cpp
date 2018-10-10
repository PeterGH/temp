#include "Header.h"

void PairTest::Init(void)
{
	Add("Compare", [&]() {
		auto check = [&](pair<int, int> p0, pair<int, int> p1) {
			char e;
			if (p0 < p1) e = '<';
			else if (p0 == p1) e = '=';
			else e = '>';
			Logger().WriteInformation("<%d,%d> %c <%d,%d>\n", p0.first, p0.second, e, p1.first, p1.second);
		};
		check(make_pair(-1, -1), make_pair(-1, -1));
		check(make_pair(-1, -2), make_pair(-1, -3));
		check(make_pair(-1, -4), make_pair(-1, -2));
		check(make_pair(-2, -1), make_pair(-1, -1));
		check(make_pair(-1, -1), make_pair(-2, -1));
		check(make_pair(0, 0), make_pair(0, 0));
		check(make_pair(0, -1), make_pair(0, 1));
		check(make_pair(0, 1), make_pair(0, -1));
		check(make_pair(1, 0), make_pair(-1, 0));
		check(make_pair(-1, 0), make_pair(1, 0));
	});
}