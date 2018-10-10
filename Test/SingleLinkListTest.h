#pragma once

#include "..\Algorithm\SingleLinkList.h"
#include "..\Algorithm\TestClass.h"

class SingleLinkListTest : public Test::TestClass {
public:
	SingleLinkListTest(Test::Log & log) : Test::TestClass(log) {}
	~SingleLinkListTest(void) {}
	void Init(void);
};

