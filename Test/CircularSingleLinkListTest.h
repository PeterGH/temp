#pragma once

#include "..\Algorithm\CircularSingleLinkList.h"
#include "..\Algorithm\TestClass.h"

class CircularSingleLinkListTest : public Test::TestClass {
public:
	CircularSingleLinkListTest(Test::Log & log) : Test::TestClass(log) {}
	~CircularSingleLinkListTest(void) {}
	void Init(void);
};
