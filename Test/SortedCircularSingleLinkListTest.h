#pragma once

#include "..\Algorithm\SortedCircularSingleLinkList.h"
#include "..\Algorithm\TestClass.h"

class SortedCircularSingleLinkListTest : public Test::TestClass {
public:
	SortedCircularSingleLinkListTest(Test::Log & log) : Test::TestClass(log) {}
	~SortedCircularSingleLinkListTest(void) {}
	void Init(void);
};

