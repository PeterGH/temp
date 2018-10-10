#include "MRNumberTest.h"
#include "MyString.h"

void MRNumberTest::Init(void)
{
	Add("MRNumber", [&]() {
		int c[] = {1, 3, 2};
		My::MRNumber ctr(c, 3);
		ASSERT1(6 == ctr.Max());
		ASSERT1(0 == ctr[0]);
		ASSERT1(0 == ctr[1]);
		ASSERT1(0 == ctr[2]);
		ctr ++;
		ASSERT1(0 == ctr[0]);
		ASSERT1(1 == ctr[1]);
		ASSERT1(0 == ctr[2]);
		++ ctr;
		ASSERT1(0 == ctr[0]);
		ASSERT1(2 == ctr[1]);
		ASSERT1(0 == ctr[2]);
		My::MRNumber ctr2 = ctr;
		ASSERT1(0 == ctr2[0]);
		ASSERT1(2 == ctr2[1]);
		ASSERT1(0 == ctr2[2]);
		ctr2 ++;
		++ ctr2;
		ASSERT1(0 == ctr2[0]);
		ASSERT1(1 == ctr2[1]);
		ASSERT1(1 == ctr2[2]);
		ctr2 ++;
		++ ctr2;
		ASSERT1(0 == ctr2[0]);
		ASSERT1(0 == ctr2[1]);
		ASSERT1(0 == ctr2[2]);
		ctr2 ++;
		++ ctr2;
		ASSERT1(0 == ctr2[0]);
		ASSERT1(2 == ctr2[1]);
		ASSERT1(0 == ctr2[2]);
		ctr2.Reset();
		ASSERT1(0 == ctr2[0]);
		ASSERT1(0 == ctr2[1]);
		ASSERT1(0 == ctr2[2]);	
	});
}