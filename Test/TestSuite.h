#pragma once

#include <iostream>
#include <map>
#include <ppl.h>
#include <string>
#include <Windows.h>
#include "Log.h"
#include "String.h"
#include "TestClass.h"

using namespace std;
using namespace concurrency;

namespace Test {
	class TestSuite final {
	private:
		// Count passed test methods for all test classes
		long _pass;
		
		// Count failed test methods for all test classes
		long _fail;

		// Each key is a test class and the value is the implementation
		map<string, TestClass *> _tests;

		Log & _log;
		
		// Check if a test class is implemented
		bool Has(const string & name);

		// Run test methods of a particular test class
		void Run(map<string, TestClass *>::iterator & it);

		// Run a test method of a particular test class
		// Input method can be a partial name
		void Run(map<string, TestClass *>::iterator & it, const string & method);
	public:
		__declspec(dllexport) TestSuite(Log & log = Log()) : _pass(0), _fail(0), _log(log) {}

		// Destructor to dispose all test class objects
		__declspec(dllexport) ~TestSuite(void);

		// Add a particular test class
		__declspec(dllexport) void Add(TestClass * test);

		// Print all test classes
		__declspec(dllexport) void List(void);

		// Print all methods of a test class
		__declspec(dllexport) void List(const string & test);
		
		// Run all test classes
		__declspec(dllexport) void Run(void);

		// Run all test classes whose name contains the specified test name
		__declspec(dllexport) void Run(const string & test);

		// Run the specified method in the specified test classes.
		// Input test and method can be partial names.
		__declspec(dllexport) void Run(const string & test, const string & method);
		
		// Print result of test run
		__declspec(dllexport) void Report(void) const;		
	};
}
