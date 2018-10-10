#pragma once

#include <vector>
#include "..\Algorithm\InsertionSort.h"
#include "..\Algorithm\TestClass.h"

class InsertionSortTest : public Test::TestClass {
public:
	InsertionSortTest(Test::Log & log) : Test::TestClass(log) {}
	~InsertionSortTest(void) {}
	void Init(void);
};

