#pragma once

#include <assert.h>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ppl.h>
#include <string>
#include <typeinfo>
#include <Windows.h>
#include "String.h"

using namespace std;
using namespace concurrency;

namespace My {

#define ASSERT2(statement, message) \
	Assert(statement, #statement, message, __FILE__, __LINE__)

#define ASSERT1(statement) \
	Assert(statement, #statement, "", __FILE__, __LINE__)

#define ASSERTERROR(statement, error) \
	try { \
		statement; \
	} catch (error &) { \
		ASSERT1(true); \
	}

#define STRING(statement) #statement
	
	class AssertError : public domain_error {
	public:
		AssertError(const string & message) : domain_error(message) {}
	};

	class TestClass {
	private:
		long _pass;
		long _fail;
		map<string, function<void (void)>> _testMethods;
		bool Has(const string & name);
		void Run(map<string, function<void (void)>>::iterator & it);
	public:
		__declspec(dllexport) TestClass(void) : _pass(0), _fail(0) {}
		// Make the destructor virtual so that we can delete a pointer to a derived object
		__declspec(dllexport) virtual ~TestClass(void) {}
		__declspec(dllexport) void Assert(bool result, const string & statement, const string & message, const string & file, long line);
		__declspec(dllexport) void Add(const string, const function<void (void)>);
		// Derived class to implement this method to add any test method
		__declspec(dllexport) virtual void Init(void) = 0;
		__declspec(dllexport) void Run(void);
		__declspec(dllexport) const string Name(void);
		__declspec(dllexport) long PassCount(void) const { return _pass; }
		__declspec(dllexport) long FailCount(void) const { return _fail; }
		__declspec(dllexport) void Report(void) const;
	};

	class TestSuite final {
	private:
		long _pass;
		long _fail;
		bool Has(const string & name);
		// Seems unique_ptr has some problem casting from TestClass to specific derived class
		// map<string, unique_ptr<TestClass> &> _tests;
		map<string, TestClass *> _tests;
		void Run(map<string, TestClass *>::iterator & it);
	public:
		__declspec(dllexport) TestSuite(void) : _pass(0), _fail(0) {}
		__declspec(dllexport) ~TestSuite(void);
		__declspec(dllexport) void Add(TestClass * test);
		__declspec(dllexport) void Run(void);
		__declspec(dllexport) void Run(const string & test);
		__declspec(dllexport) void Report(void) const;
		__declspec(dllexport) void List(void);
	};
}

