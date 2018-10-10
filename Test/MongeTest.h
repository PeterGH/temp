#pragma once
#include "..\Algorithm\Monge.h"
#include "..\Algorithm\TestClass.h"
class MongeTest : public Test::TestClass {
public:
	MongeTest(Test::Log & log) : Test::TestClass(log) {}
	~MongeTest(void) {}
	void Init(void);
};

