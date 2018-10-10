#include "Test.h"

namespace My {
	
	// Implemenation of TestClass

	bool TestClass::Has(const string & name)
	{
		map<string, function<void (void)>>::iterator it = _testMethods.find(name);
		if (it != _testMethods.end()) {
			return true;
		} else {
			return false;
		}
	}

	void TestClass::Run(map<string, function<void (void)>>::iterator & it)
	{
		cout << "  == " << it->first << " ==" << endl;
		try {
			it->second();
			_pass ++;
		} catch (AssertError & e) {
			_fail ++;
			cout << "Error: " << typeid(e).name() << ": " << e.what() << endl;
		} catch (exception & e) {
			_fail ++;
			cout << "Error: " << typeid(e).name() << ": " << e.what() << endl;
		}
	}

	void TestClass::Assert(bool result, const string & statement, const string & message, const string & file, long line)
	{
		if (! result) {
			string error(message);
			error += "\n";
			error += file;
			error += ", line ";
			error += String::Format("%ld", line);
			error += ": ";
			error += statement;
			throw AssertError(error);
		}
	}

	void TestClass::Add(const string name, const function<void (void)> fun)
	{
		if (!Has(name)) {
			_testMethods.insert(pair<string, function<void (void)>>(name, fun));
		}
	}

	void TestClass::Run(void)
	{
		for (map<string, function<void (void)>>::iterator it = _testMethods.begin(); it != _testMethods.end(); it ++) {
			Run(it);
		}
		
#if NULL
		parallel_for_each(_testMethods.begin(), _testMethods.end(), [&](pair<string, function<void (void)>> it) {
			cout << "  == " << it.first << " ==" << endl;
			try {
				it.second();
				InterlockedIncrement64((long long *)&_pass);
			} catch (AssertError & e) {
				InterlockedIncrement64((long long *)&_fail);
				cout << "Error: " << typeid(e).name() << ": " << e.what() << endl;
			} catch (exception & e) {
				InterlockedIncrement64((long long *)&_fail);
				cout << "Error: " << typeid(e).name() << ": " << e.what() << endl;
			}
		});
#endif
	}

	const string TestClass::Name(void) 
	{ 
		string name = typeid(*this).name();
		return name.substr(6);
	}

	void TestClass::Report() const
	{
		cout << _pass << " passed, " << _fail << " failed." << endl;
	}

	// Implementation of TestSuite

	bool TestSuite::Has(const string & name)
	{
		map<string, TestClass *>::iterator it = _tests.find(name);
		if (it != _tests.end()) {
			return true;
		} else {
			return false;
		}
	}

	void TestSuite::Run(map<string, TestClass *>::iterator & it)
	{
		cout << "==== " << it->first << " ====" << endl;
		it->second->Init();
		it->second->Run();
		it->second->Report();
		_pass += it->second->PassCount();
		_fail += it->second->FailCount();
	}

	TestSuite::~TestSuite(void)
	{
		// Make sure all allocated objects are freed
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it ++) {
			delete it->second;
			it->second = NULL;
		}
	}

	void TestSuite::Add(TestClass * test)
	{
		if (!Has(test->Name())) {
			_tests.insert(pair<string, TestClass *>(test->Name(), test));
		}
	}

	void TestSuite::Run()
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it ++) {
			Run(it);
		}
#if NULL
		combinable<long> pass;
		combinable<long> fail;

		parallel_for_each(_tests.begin(), _tests.end(), [&](pair<string, TestClass *> it) {
			cout << "==== " << it.first << " ====" << endl;
			it.second->Init();
			it.second->Run();
			it.second->Report();
			pass.local() += it.second->PassCount();
			fail.local() += it.second->FailCount();
		});

		_pass = pass.combine(plus<long>());
		_fail = fail.combine(plus<long>());
#endif
	}

	void TestSuite::Run(const string & test)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it ++) {
			//if (test.compare(it->first) == 0) {
			//if (String::ToLower(test) == String::ToLower(it->first)) {
			if (String::StartsWith(it->first, test)) {
				Run(it);
			}
		}
	}

	void TestSuite::Report(void) const
	{
		cout << "==== Summary ====" << endl;
		cout << _pass << " passed, " << _fail << " failed." << endl;
	}

	void TestSuite::List(void)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it ++) {
			cout << "\t" << it->first << endl;
		}
	}
}
