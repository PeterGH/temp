#pragma once
#include <algorithm>
#include "..\Algorithm\Random.h"
#include "..\Algorithm\SeamCarving.h"
#include "..\Algorithm\TestClass.h"
using namespace std;
using namespace Test;
class SeamCarvingTest : public TestClass {
public:
	SeamCarvingTest(Log & log) : TestClass(log) {}
	~SeamCarvingTest(void) {}
	void Init(void);
};

