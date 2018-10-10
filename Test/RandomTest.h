#pragma once

#include <numeric>
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

class RandomTest : public Test::TestClass {
public:
	RandomTest(Test::Log & log) : Test::TestClass(log) {}
	~RandomTest(void) {}
	void Init(void);
};

