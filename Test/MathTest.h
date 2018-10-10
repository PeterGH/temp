#pragma once
#include "..\Algorithm\Math.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class MathTest : public TestClass {
public:
	MathTest(Log & log) : TestClass(log) {}
	~MathTest(void) {}
	void Init(void);
};

