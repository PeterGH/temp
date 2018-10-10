#include "Header.h"

void MRIntegerTest::Init(void)
{
	Add("1", [&]() {
		auto check = [&](MRInteger & c, int e0, int e1, int e2) -> void {
			ASSERT1(e0 == c[0]);
			ASSERT1(e1 == c[1]);
			ASSERT1(e2 == c[2]);
		};

		unsigned int c[] = { 1, 3, 2 };

		MRInteger ctr(c, 3);
		ASSERT1(6 == (int)ctr.Max());
		check(ctr, 0, 0, 0);

		ctr++;
		check(ctr, 0, 1, 0);

		++ctr;
		check(ctr, 0, 2, 0);

		MRInteger ctr2 = ctr;
		check(ctr2, 0, 2, 0);

		ctr2++;
		++ctr2;
		check(ctr2, 0, 1, 1);

		ctr2++;
		++ctr2;
		check(ctr2, 0, 0, 0);

		ctr2++;
		++ctr2;
		check(ctr2, 0, 2, 0);

		MRInteger ctr3(ctr2);
		check(ctr3, 0, 2, 0);

		ctr = ctr3++;
		check(ctr, 0, 2, 0);
		check(ctr3, 0, 0, 1);

		ctr3.Reset();
		check(ctr3, 0, 0, 0);

		MRInteger ctr4(ctr3);
		check(ctr4, 0, 0, 0);

		ctr4 = MRInteger(ctr);
		check(ctr4, 0, 2, 0);
	});

	Add("2", [&]() {
		unsigned int c[] = { 1, 3, 2 };
		MRInteger ctr(c, 3);

		unsigned int c1[] = { 1, 3, 2, 1 };
		MRInteger ctr1(c1, 4);

		ASSERT1(!(ctr < ctr1));
		ASSERT1(!(ctr1 < ctr));
		ASSERT1(ctr == ctr1);
		ASSERT1(ctr1 == ctr);
		ASSERT1(!(ctr != ctr1));
		ASSERT1(!(ctr1 != ctr));
	});

	Add("3", [&]() {
		unsigned int c[] = { 3, 3, 3 };
		MRInteger ctr(c, 3);

		unsigned int c1[] = { 3, 3, 3, 3 };
		MRInteger ctr1(c1, 4);

		ctr++;
		ASSERT1(ctr > ctr1);
		ASSERT1(!(ctr1 > ctr));
		ctr1++;
		ctr1++;
		ASSERT1(!(ctr > ctr1));
		ASSERT1(ctr <= ctr1);
		ASSERT1(ctr1 > ctr);
		ASSERT1(!(ctr1 <= ctr));

		unsigned int d[] = { 0, 1, 1 };
		unsigned int d1[] = { 0, 1, 1, 1 };
		ctr.Set(d, 3);
		ctr1.Set(d1, 4);
		ASSERT1(ctr1 > ctr);
		ASSERT1(!(ctr1 <= ctr));
		ASSERT1(!(ctr > ctr1));
		ASSERT1(ctr <= ctr1);

		unsigned int d2[] = { 0, 1, 2 };
		unsigned int d3[] = { 0, 1, 1, 1 };
		ctr.Set(d2, 3);
		ctr1.Set(d3, 4);
		ASSERT1(ctr1 > ctr);
		ASSERT1(!(ctr1 <= ctr));
		ASSERT1(!(ctr > ctr1));
		ASSERT1(ctr <= ctr1);

		unsigned int d4[] = { 0, 1, 1, 0 };
		ctr1.Set(d4, 4);
		ASSERT1(!(ctr1 > ctr));
		ASSERT1(ctr1 <= ctr);
		ASSERT1(ctr > ctr1);
		ASSERT1(!(ctr <= ctr1));
	});

	Add("4", [&]() {
		unsigned int c[] = { 1, 3, 3 };
		MRInteger ctr(c, 3);

		unsigned int c1[] = { 1, 3, 3, 2 };
		MRInteger ctr1(c1, 4);

		ctr++;
		ASSERT1(!(ctr < ctr1));
		ASSERT1(ctr1 < ctr);
		ctr1++;
		ctr1++;
		ASSERT1(ctr < ctr1);
		ASSERT1(!(ctr >= ctr1));
		ASSERT1(!(ctr1 < ctr));
		ASSERT1(ctr1 >= ctr);

		unsigned int d[] = { 0, 1, 1 };
		unsigned int d1[] = { 0, 1, 1, 1 };
		ctr.Set(d, 3);
		ctr1.Set(d1, 4);
		ASSERT1(ctr < ctr1);
		ASSERT1(!(ctr >= ctr1));
		ASSERT1(!(ctr1 < ctr));
		ASSERT1(ctr1 >= ctr);

		unsigned int d2[] = { 0, 1, 2 };
		unsigned int d3[] = { 0, 1, 1, 1 };
		ctr.Set(d2, 3);
		ctr1.Set(d3, 4);
		ASSERT1(ctr < ctr1);
		ASSERT1(!(ctr >= ctr1));
		ASSERT1(!(ctr1 < ctr));
		ASSERT1(ctr1 >= ctr);

		unsigned int d4[] = { 0, 1, 1, 0 };
		ctr1.Set(d4, 4);
		ASSERT1(!(ctr < ctr1));
		ASSERT1(ctr >= ctr1);
		ASSERT1(ctr1 < ctr);
		ASSERT1(!(ctr1 >= ctr));
	});

	Add("Random", [&]() {
		unsigned int b[] = { 1, 2, 4, 8, 16, 32 };
		MRInteger mri(b, 6);
		std::vector<MRInteger> numbers;
		for (int i = 0; i < 30000; i++) {
			mri.Random();
			numbers.push_back(MRInteger(mri));
		}

		sort(numbers.begin(), numbers.end());

		ASSERT1(std::is_sorted(numbers.begin(), numbers.end(), [&](const MRInteger & second, const MRInteger & first) {
			if (second < first) {
				for (int j = first.Length() - 1; j >= 0; j--) {
					Logger().WriteInformation("\t%d", first[j]);
				}

				Logger().WriteInformation("\n");

				for (int j = second.Length() - 1; j >= 0; j--) {
					Logger().WriteInformation("\t%d", second[j]);
				}

				Logger().WriteInformation("\n");
				return true;
			} else {
				return false;
			}
		}));
	});
}