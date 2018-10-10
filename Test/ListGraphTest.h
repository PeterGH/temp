#pragma once
#include "..\Algorithm\ListGraph.h"
#include "..\Algorithm\TestClass.h"
class ListGraphTest : public Test::TestClass {
public:
	ListGraphTest(Test::Log & log) : Test::TestClass(log) {}
	~ListGraphTest(void) {}
	void Init(void);
};

