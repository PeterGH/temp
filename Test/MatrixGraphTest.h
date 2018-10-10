#pragma once
#include "..\Algorithm\MatrixGraph.h"
#include "..\Algorithm\TestClass.h"
class MatrixGraphTest : public Test::TestClass {
public:
	MatrixGraphTest(Test::Log & log) : Test::TestClass(log) {}
	~MatrixGraphTest(void) {}
	void Init(void);
};

