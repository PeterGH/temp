#include "MongeTest.h"

void MongeTest::Init(void)
{
	Add("Random", [&](){
		for (int i = 0; i < 100; i++) {
			size_t r = 2 + (rand() % 50);
			size_t c = 2 + (rand() % 50);
			Test::Monge<int> m(r, c);
			Test::Monge<int>::Random(m);
			bool b = Test::Monge<int>::IsMonge(m);
			Logger().Print(m);
			ASSERT1(b == true);
		}
	});

	Add("RowMins", [&](){
		for (int i = 0; i < 100; i++) {
			size_t r = 2 + (rand() % 500);
			size_t c = 2 + (rand() % 500);
			Test::Monge<int> m(r, c);
			Test::Monge<int>::Random(m);
			bool b = Test::Monge<int>::IsMonge(m);
			// Logger().Print(m);
			ASSERT1(b == true);

			vector<size_t> mins(r, -1);
			vector<size_t> mins2(r, -1);

			LONGLONG t = TimedCall([&](){ m.FindRowMins(mins); });
			LONGLONG t2 = TimedCall([&](){ m.FindRowMins2(mins2); });

			Logger().WriteInformation("%dx%d, time: %I64d, %I64d\n", r, c, t, t2);

			for (size_t i = 0; i < r; i++) {
				// Logger().WriteInformation("Row %d min (%d, %d), (%d, %d)\n", i, mins[i], m(i, mins[i]), mins2[i], m(i, mins2[i]));
				ASSERT1(mins[i] == mins2[i]);
			}
		}
	});
}