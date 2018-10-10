#pragma once

#include "..\Algorithm\TestClass.h"

class TestClassTest : public Test::TestClass {
public:
	TestClassTest(Test::Log & log) : Test::TestClass(log) {}
	~TestClassTest(void) {}
	void Init(void);
};

