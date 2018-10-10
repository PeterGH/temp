#pragma once

#include <string>
#include <vector>
#include "..\Algorithm\AVLTree.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

using namespace std;

class AVLTreeTest : public Test::TestClass {
public:
	AVLTreeTest(Test::Log & log) : Test::TestClass(log) {}
	~AVLTreeTest(void) {}
	void Init(void);
};

