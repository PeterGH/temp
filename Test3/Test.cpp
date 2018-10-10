#include "Test.h"
#include "MyString.h"

namespace My {

	void TestClass::Run(map<wstring, function<void (void)>>::iterator & it)
	{
		wcout << L"==== Begin Test Method " << it->first << L" ====" << endl;
		try {
			it->second();
			_pass ++;
		} catch (AssertError & e) {
			_fail ++;
			cout << e.what() << endl;
		} catch (exception & e) {
			_fail ++;
			cout << e.what() << endl;
		}
		wcout << L"==== End Test Method " << it->first << L" ====" << endl;
	}

	void TestClass::Assert(bool result, const string & statement, const string & message, const string & file, long line)
	{
		if (! result) {
			char sl[100];
			_ltoa_s(line, sl, 10);
			string error(message);
			error += "\n";
			error += file;
			error += ", line ";
			error += sl;
			error += ": ";
			error += statement;
			throw AssertError(error);
		}
	}

	void TestClass::Add(const wstring name, const function<void (void)> fun)
	{
		_testMethods.insert(pair<wstring, function<void (void)>>(name, fun));
	}

	void TestClass::Run(void)
	{
		for (map<wstring, function<void (void)>>::iterator it = _testMethods.begin(); it != _testMethods.end(); it ++) {
			Run(it);
		}
	}

	wstring TestClass::Name(void) 
	{ 
		wstring name = typeid(*this).name();
		return name.substr(6);
	}

	void TestClass::Report()
	{
		cout << _pass << " passed, " << _fail << " failed." << endl;
	}

	void TestSuite::Run(map<string, TestClass *>::iterator & it)
	{
		cout << "==== Begin Test Class " << it->first << " ====" << endl;
		it->second->Init();
		it->second->Run();
		it->second->Report();
		_pass += it->second->PassCount();
		_fail += it->second->FailCount();
		cout << "==== End Test Class " << it->first << " ====" << endl;
	}

	TestSuite::~TestSuite(void)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it ++) {
			delete it->second;
			it->second = NULL;
		}
	}

	void TestSuite::Add(TestClass * test)
	{
		_tests.insert(pair<string, TestClass *>(test->Name(), test));
	}

	void TestSuite::Run()
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it ++) {
			Run(it);
		}
	}

	void TestSuite::Run(string & test)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it ++) {
			//if (test.compare(it->first) == 0) {
			if (StringA::ToLower(test) == StringA::ToLower(it->first)) {
				Run(it);
			}
		}
	}

	void TestSuite::Report()
	{
		cout << "==== Summary ====" << endl;
		cout << _pass << " passed, " << _fail << " failed." << endl;
	}
}
