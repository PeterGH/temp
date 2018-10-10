#include "TestClassTest.h"

void TestClassTest::Init()
{
	Add("ASSERT1", [&](){
		ASSERTERROR(ASSERT1(false), Test::AssertError);
	});
}