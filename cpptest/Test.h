#pragma once

#include <set>
#include <vector>
#include "Algorithm.h"
#include "LeetCode.h"
#include "TestSuite.h"
#include "Util.h"

using namespace Test;

class AlgorithmTest : public TestClass
{
public:
    AlgorithmTest(Log & log) : TestClass(log) {}
    AlgorithmTest(void) {}
    void Init(void);
};

class CppTest : public TestClass
{
public:
    CppTest(Log & log) : TestClass(log) {}
    ~CppTest(void) {}
    void Init(void);
};

class LeetCodeTest : public TestClass
{
public:
    LeetCodeTest(Log & log) : TestClass(log) {}
    ~LeetCodeTest(void) {}
    void Init(void);
};