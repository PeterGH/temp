#pragma once

#include "..\Algorithm\SortedSingleLinkList.h"
#include "..\Algorithm\TestClass.h"

class SortedSingleLinkListTest : public Test::TestClass {
public:
	SortedSingleLinkListTest(Test::Log & log) : Test::TestClass(log) {}
	~SortedSingleLinkListTest(void) {}
	void Init(void);
};
