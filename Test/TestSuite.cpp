#include "TestSuite.h"

namespace Test {

	bool TestSuite::Has(const string & name)
	{
		return _tests.find(name) != _tests.end();
	}

	void TestSuite::Run(map<string, TestClass *>::iterator & it)
	{
		cout << " ==== " << it->first << " ==== " << endl;
		it->second->Run();
		it->second->Report();
		_pass += it->second->PassCount();
		_fail += it->second->FailCount();
	}

	void TestSuite::Run(map<string, TestClass *>::iterator & it, const string & method)
	{
		cout << " ==== " << it->first << " ==== " << endl;
		it->second->Run(method);
		it->second->Report();
		_pass += it->second->PassCount();
		_fail += it->second->FailCount();
	}

	TestSuite::~TestSuite(void)
	{
		// Make sure all allocated objects are freed
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
			delete it->second;
			it->second = nullptr;
		}
	}

	void TestSuite::Add(TestClass * test)
	{
		string name = test->Name();
		if (!Has(name)) {
			test->Init();
			_tests.insert(pair<string, TestClass *>(name, test));
		}
	}

	void TestSuite::List(void)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
			cout << "\t" << it->first << endl;
		}
	}

	void TestSuite::List(const string & test)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
			if (String::Contains(it->first, test)) {
				cout << "Available test methods of " << it->first << " are:" << endl;
				it->second->List();
			}
		}
	}
	
	void TestSuite::Run()
	{
		// for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
		// 	Run(it);
		// }

		combinable<long> pass;
		combinable<long> fail;

		parallel_for_each(_tests.begin(), _tests.end(), [&](pair<string, TestClass *> it) {
			cout << " ==== " << it.first << " ==== " << endl;
			it.second->Run();
			it.second->Report();
			pass.local() += it.second->PassCount();
			fail.local() += it.second->FailCount();
		});

		_pass = pass.combine(plus<long>());
		_fail = fail.combine(plus<long>());
	}

	void TestSuite::Run(const string & test)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
			if (String::StartsWith(it->first, test)) {
				Run(it);
			}
		}
	}

	void TestSuite::Run(const string & test, const string & method)
	{
		for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
			if (String::StartsWith(it->first, test)) {
				Run(it, method);
			}
		}
	}
	
	void TestSuite::Report(void) const
	{
		cout << " ==== Summary ==== " << endl;
		cout << _pass << " passed, " << _fail << " failed." << endl;
	}
}