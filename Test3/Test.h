#pragma once

#include <assert.h>
#include <string>
#include <typeinfo>
#include <map>
#include <iostream>
#include <functional>

using namespace std;

namespace My {

#define ASSERT2(statement, message) \
	Assert(statement, #statement, message, __FILE__, __LINE__)

#define ASSERT1(statement) \
	Assert(statement, #statement, "", __FILE__, __LINE__)

	class AssertError : public domain_error {
	public:
		AssertError(const string & message) : domain_error(message) { }
	};

	class TestClass {
	private:
		map<wstring, function<void (void)>> _testMethods;
		void Run(map<wstring, function<void (void)>>::iterator & it);
	protected:
		TestClass(void) : _pass(0), _fail(0) { }
		long _pass;
		long _fail;
	public:
		virtual ~TestClass(void) { }
		void Assert(bool result, const string & statement, const string & message, const string & file, long line);
		void Add(const wstring, const function<void (void)>);
		// Derived class to implement this method to add any test method
		virtual void Init(void) = 0;
		void Run(void);
		wstring Name(void);
		long PassCount(void) { return _pass; }
		long FailCount(void) { return _fail; }
		void Report(void);
	};
	
	class TestSuite {
	private:
		map<wstring, TestClass *> _tests;
		long _pass;
		long _fail;
		void Run(map<wstring, TestClass *>::iterator & it);
	public:
		TestSuite(void) : _pass(0), _fail(0) { }
		~TestSuite(void);
		void Add(TestClass * test);
		void Run(void);
		void Run(wstring & test);
		void Report(void);
	};

}

class MyTest : public My::TestClass {
public:
	MyTest(void) {}
	~MyTest(void) {}
	void Init(void);
};