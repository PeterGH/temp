#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <ppl.h>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Log.h"
#include "String.h"

using namespace std;
using namespace concurrency;

namespace Test {

	// Base class to derive specific test classes.
	// Contain a set of test methods.
	class TestClass {
	private:
		long _pass; // Count passed test methods
		long _fail; // Count failed test methods

		Log & _log;

		// Each key is a test name and the value is the test implementation
		map<string, function<void(void)>> _testMethods;

		// Check if a test method is implemented
		bool Has(const string & name) const;

		// Run a particular test method
		void Run(map<string, function<void(void)>>::iterator & it);

	public:
		__declspec(dllexport) TestClass(Log & log = Log()) : _pass(0), _fail(0), _log(log) {}

		// Destructor. Make it virtual so that we can delete a pointer to a derived class object
		__declspec(dllexport) virtual ~TestClass(void) {}

		// Assert the result of statement is true. Otherwise,
		// throw an error message including the code file name and the code line number.
		__declspec(dllexport) void Assert(bool result, const string & statement, const string & message, const string & file, long line) const;

		// Add a test method
		__declspec(dllexport) void Add(const string & name, const function<void(void)> & test);

		// Derived class to implement this method.
		// All test methods should be added in this method.
		__declspec(dllexport) virtual void Init(void) = 0;

		// Print all test methods
		__declspec(dllexport) void List(void) const;

		// Get the log reference
		__declspec(dllexport) Log & Logger(void) const { return _log; }

		// This test class name
		__declspec(dllexport) const string Name(void) const;

		// Run all test methods
		__declspec(dllexport) void Run(void) const;

		// Run all test methods whose name starts with the input string
		__declspec(dllexport) void Run(const string & name);

		__declspec(dllexport) long PassCount(void) const { return _pass; }
		__declspec(dllexport) long FailCount(void) const { return _fail; }

		// Print a report of test run result
		__declspec(dllexport) void Report(void) const;

		__declspec(dllexport) LONGLONG TimedCall(const function<void(void)> & func) const;

		template<class T> static bool Equal(const vector<T> & left, const vector<T> & right);

		template<class T> static bool Equal(const T * left, const T * right, int length);

		template<class T> static bool IsSorted(const T * input, int length);
	};

	class AssertError : public domain_error {
	public:
		AssertError(const string & message) : domain_error(message) {}
	};

#define ASSERT2(statement, message) \
	Assert(statement, #statement, message, __FILE__, __LINE__)

#define ASSERT1(statement) \
	Assert(statement, #statement, "", __FILE__, __LINE__)

#define ASSERTERROR(statement, error) \
	try { \
		statement; \
	} catch (error &) {	\
		ASSERT1(true); \
	}

#define STRING(statement) #statement

	template<class T> bool TestClass::Equal(const vector<T> & left, const vector<T> & right)
	{
		if (left.size() != right.size()) return false;
		for (size_t i = 0; i < left.size(); i++) {
			if (left[i] != right[i]) return false;
		}
		return true;
	}

	template<class T> bool TestClass::Equal(const T * left, const T * right, int length)
	{
		if (left == nullptr && right == nullptr) return true;
		if (left == nullptr || right == nullptr) return false;
		for (int i = 0; i < length; i++) {
			if (left[i] != right[i]) return false;
		}
		return true;
	}

	template<class T> bool TestClass::IsSorted(const T * input, int length)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		for (int i = 0; i < length - 1; i++) {
			if (input[i] > input[i + 1]) return false;
		}

		return true;
	}
}