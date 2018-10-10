#pragma once

#include "..\Algorithm\String.h"
#include "..\Algorithm\TestClass.h"

class StringTest : public Test::TestClass {
public:
	StringTest(Test::Log & log) : Test::TestClass(log) {}
	~StringTest(void) {}
	void Init(void);
};

