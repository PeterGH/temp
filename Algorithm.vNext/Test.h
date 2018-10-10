#pragma once

#include "Algorithm.h"
#include "TestClass.h"

using namespace Test;

class AlgorithmTest : public TestClass {
public:
	AlgorithmTest(Log & log) : TestClass(log) {}
	~AlgorithmTest(void) {}
	void Init(void);
};

class CppTest : public TestClass {
public:
	CppTest(Log & log) : TestClass(log) {}
	~CppTest(void) {}
	void Init(void);
};

class LogTest : public TestClass {
public:
	LogTest(Log & log) : TestClass(log) {}
	~LogTest(void) {}
	void Init(void);
};

class SmartPointerTest : public TestClass {
public:
	SmartPointerTest(Log & log) : TestClass(log) {}
	~SmartPointerTest(void) {}
	void Init(void);
};

class StringTest : public TestClass {
public:
	StringTest(Log & log) : TestClass(log) {}
	~StringTest(void) {}
	void Init(void);
};