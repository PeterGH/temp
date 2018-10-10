#include "MaskTest.h"

void MaskTest::Init(void)
{
	Add("MastTest", [&]() {
		Mask m(40);
		m.Set(0);
		ASSERT1(m.IsSet(0));
		m.Toggle(0);
		ASSERT1(! m.IsSet(0));
		m.Set(40);
		ASSERT1(m.IsSet(40));
		m.Clear(40);
		ASSERT1(! m.IsSet(40));
		m.Set(32);
		ASSERT1(m.IsSet(32));
		m.Reset();
		ASSERT1(! m.IsSet(32));
		Mask m2;
		ASSERT1(! m2.IsSet(0));
		Mask m3 = m2;
		ASSERT1(! m3.IsSet(0));
		Mask m4 = m;
		ASSERT1(! m4.IsSet(32));
	});
}
