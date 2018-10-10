#pragma once

#include <algorithm>
#include <Windows.h>
#include "..\Algorithm\BinarySearch.h"
#include "..\Algorithm\MergeSort.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\Sort.h"
#include "..\Algorithm\TestClass.h"

using namespace std;

class BinarySearchTest : public Test::TestClass {
public:
	BinarySearchTest(Test::Log & log) : Test::TestClass(log) {}
	~BinarySearchTest(void) {}
	void Init(void);
};

