#pragma once
#include "..\Algorithm\RodCut.h"
#include "..\Algorithm\TestClass.h"

class RodCutTest : public Test::TestClass {
public:
	RodCutTest(Test::Log & log) : Test::TestClass(log) {}
	~RodCutTest(void) {}
	void Init(void);
};

