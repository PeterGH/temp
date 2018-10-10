#pragma once

#include "..\Algorithm\BitSet.h"
#include "..\Algorithm\TestClass.h"

class BitSetTest : public Test::TestClass {
public:
	BitSetTest(Test::Log & log) : Test::TestClass(log) {}
	~BitSetTest(void) {}
	void Init(void);
};

