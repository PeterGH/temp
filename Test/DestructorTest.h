#pragma once
#include <iostream>
#include "..\Algorithm\TestClass.h"
using namespace std;
class DestructorTest : public Test::TestClass {
public:
	DestructorTest(Test::Log & log) : Test::TestClass(log) {}
	~DestructorTest(void) {}
	void Init(void);
};

