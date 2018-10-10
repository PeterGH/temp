#pragma once
#include "..\Algorithm\BinaryNodeWithParent.h"
#include "..\Algorithm\BinaryIterator.h"
#include "..\Algorithm\TestClass.h"
class BinaryIteratorTest : public Test::TestClass {
public:
	BinaryIteratorTest(Test::Log & log) : Test::TestClass(log) {}
	~BinaryIteratorTest(void) {}
	void Init(void);
};

