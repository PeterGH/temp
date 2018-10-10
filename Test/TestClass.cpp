#include "TestClass.h"

namespace Test {

	bool TestClass::Has(const string & name)
	{ 
		return _testMethods.find(name) != _testMethods.end(); 
	}

	void TestClass::Run(map<string, function<void(void)>>::iterator & it)
	{
		try {
			it->second();
			_pass++;
		} catch (AssertError & e) {
			_fail++;
			_log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(), e.what());
		} catch (exception & e) {
			_fail++;
			_log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(), e.what());
		} catch (...) {
			_fail++;
			_log.WriteError("%s\n", it->first.c_str());
		}
	}

	void TestClass::Assert(bool result, const string & statement, const string & message, const string & file, long line)
	{
		if (!result) {
			string error(message);
			error += "\n";
			error += file;
			error += ", ";
			error += String::Format("%ld", line);
			error += ": ";
			error += statement;
			throw AssertError(error);
		}
	}

	void TestClass::Add(const string & name, const function<void(void)> & test)
	{
		if (!Has(name)) _testMethods.insert(pair<string, function<void(void)>>(name, test));
	}

	void TestClass::List(void)
	{
		for (map<string, function<void(void)>>::iterator it = _testMethods.begin(); it != _testMethods.end(); it++) {
			cout << "\t" << it->first << endl;
		}
	}

	const string TestClass::Name(void)
	{
		string name = typeid(*this).name();
		return name.substr(6);
	}

	void TestClass::Run(void)
	{
		// for (map<string, function<void(void)>>::iterator it = _testMethods.begin(); it != _testMethods.end(); it++) {
		// 	Run(it);
		// }

		parallel_for_each(_testMethods.begin(), _testMethods.end(), [&](pair<string, function<void(void)>> it) {
			try {
				it.second();
				InterlockedIncrement64((long long *)&_pass);
			} catch (AssertError & e) {
				InterlockedIncrement64((long long *)&_fail);
				_log.WriteError("%s: %s, %s\n", it.first.c_str(), typeid(e).name(), e.what());
			} catch (exception & e) {
				InterlockedIncrement64((long long *)&_fail);
				_log.WriteError("%s: %s, %s\n", it.first.c_str(), typeid(e).name(), e.what());
			}
		});
	}

	void TestClass::Run(const string & test)
	{
		for (map<string, function<void(void)>>::iterator it = _testMethods.begin(); it != _testMethods.end(); it++) {
			if (String::StartsWith(it->first, test)) {
				Run(it);
			}
		}
	}

	void TestClass::Report() const
	{
		cout << _pass << " passed, " << _fail << " failed." << endl;
	}

	LONGLONG TestClass::TimedCall(const function<void(void)> & func)
	{
		function<LONGLONG(void)> GetTicks = [&](void)->LONGLONG{
			LARGE_INTEGER t;
			if (!QueryPerformanceCounter(&t)) t.QuadPart = 0;
			return t.QuadPart;
		};

		LONGLONG ticks = GetTicks();
		func();
		ticks = GetTicks() - ticks;
		return ticks;
	}
}