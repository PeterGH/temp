#pragma once

#include <Windows.h>
#include <assert.h>
#include <string>
#include <typeinfo>
#include <map>
#include <iostream>
#include <functional>
#include <ppl.h>

using namespace std;
using namespace Concurrency;

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

	// Use dllexport at method level instead of class level because there are private members we do not want to export
	class TestClass {
	private:
		long _pass;
		long _fail;
		map<string, function<void (void)>> _testMethods;
		bool Has(const string);
		void Run(map<string, function<void (void)>>::iterator & it);
	public:
		__declspec(dllexport) TestClass(void) : _pass(0), _fail(0) {}
		__declspec(dllexport) virtual ~TestClass(void) { }
		__declspec(dllexport) void Assert(bool result, const string & statement, const string & message, const string & file, long line);
		__declspec(dllexport) void Add(const string, const function<void (void)>);
		// Derived class to implement this method to add any test method
		__declspec(dllexport) virtual void Init(void) = 0;
		__declspec(dllexport) void Run(void);
		__declspec(dllexport) const string Name(void);
		__declspec(dllexport) long PassCount(void) const { return _pass; }
		__declspec(dllexport) long FailCount(void) const { return _fail; }
		__declspec(dllexport) void Report(void) const;
		__declspec(dllexport) inline void Assert1(bool statement) { Assert(statement, STRING(statment), "", __FILE__, __LINE__); }
		__declspec(dllexport) inline void Assert2(bool statement, string message) { Assert(statement, STRING(statment), message, __FILE__, __LINE__); }
	};
	
	// Use dllexport at method level instead of class level because there are private members we do not want to export
	class TestSuite {
	private:
		long _pass;
		long _fail;
		bool Has(const string);
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