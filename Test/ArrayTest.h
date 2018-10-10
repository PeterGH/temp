#pragma once

#include "..\Algorithm\Array.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class ArrayTest : public TestClass {
private:
	// Print a two dimensional matrix
	void Print(const int * input, const int length, const int columns); 
	void Test(int * A, int * B, int length, int columns, int rows);
public:
	ArrayTest(Log & log) : TestClass(log) {}
	~ArrayTest(void) {}
	void Init(void);
};

