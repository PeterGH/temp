#pragma once
#include "..\Algorithm\LowerTriangularMatrix.h"
#include "..\Algorithm\Matrix.h"
#include "..\Algorithm\UpperTriangularMatrix.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class MatrixTest : public TestClass {
public:
	MatrixTest(Log & log) : TestClass(log) {}
	~MatrixTest(void) {}
	void Init(void);
};

