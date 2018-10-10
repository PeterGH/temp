#pragma once
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
#include "..\Algorithm\UnitTimeTaskScheduler.h"
class UnitTimeTaskSchedulerTest : public Test::TestClass {
public:
	UnitTimeTaskSchedulerTest(Test::Log & log) : Test::TestClass(log) {}
	~UnitTimeTaskSchedulerTest(void) {}
	void Init(void);
};

