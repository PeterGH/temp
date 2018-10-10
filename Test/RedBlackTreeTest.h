#pragma once

#include "..\Algorithm\RedBlackTree.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

class RedBlackTreeTest : public Test::TestClass {
public:
	RedBlackTreeTest(Test::Log & log) : Test::TestClass(log) {}
	~RedBlackTreeTest(void) {}
	void Init(void);
};

