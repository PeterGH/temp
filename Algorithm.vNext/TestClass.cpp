#include "TestClass.h"

namespace Test {

	bool TestClass::Has(const string & name) const
	{
		return _testMethods.find(name) != _testMethods.end();
	}

	void TestClass::Run(map<string, function<void(void)>>::iterator & it)
	{
		try {
			it->second();
			_pass++;
		}
		catch (AssertError & e) {
			_fail++;
			_log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(), e.what());
		}
		catch (exception & e) {
			_fail++;
			_log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(), e.what());
		}
		catch (...) {
			_fail++;
			_log.WriteError("%s\n", it->first.c_str());
		}
	}

	void TestClass::Assert(bool result, const string & statement, const string & message, const string & file, long line) const
	{
		if (!result) {
			ostringstream error;
			error << message << "\n" << file << ", " << line << ": " << statement;
			throw AssertError(error.str());
		}
	}

	void TestClass::Add(const string & name, const function<void(void)> & test)
	{
		if (Has(name)) {
			ostringstream error;
			error << "TestMethod " << name << "already exists.";
			throw invalid_argument(error.str());
		}
		_testMethods.insert(pair<string, function<void(void)>>(name, test));
	}

	void TestClass::List(void) const
	{
		for (map<string, function<void(void)>>::const_iterator it = _testMethods.cbegin(); it != _testMethods.cend(); it++) {
			cout << "\t" << it->first << endl;
		}
	}

	const string TestClass::Name(void) const
	{
		string name = typeid(*this).name();
		return name.substr(6);
	}

	void TestClass::Run(void) const
	{
		parallel_for_each(_testMethods.begin(), _testMethods.end(), [&](pair<string, function<void(void)>> it) {
			try {
				it.second();
				InterlockedIncrement64((long long *)&_pass);
			}
			catch (AssertError & e) {
				InterlockedIncrement64((long long *)&_fail);
				_log.WriteError("%s: %s, %s\n", it.first.c_str(), typeid(e).name(), e.what());
			}
			catch (exception & e) {
				InterlockedIncrement64((long long *)&_fail);
				_log.WriteError("%s: %s, %s\n", it.first.c_str(), typeid(e).name(), e.what());
			}
			catch (...) {
				InterlockedIncrement64((long long *)&_fail);
				_log.WriteError("%s\n", it.first.c_str());
			}
		});
	}

	void TestClass::Run(const string & name)
	{
		for (map<string, function<void(void)>>::iterator it = _testMethods.begin(); it != _testMethods.end(); it++) {
			if (String::StartsWith(it->first, name)) {
				Run(it);
			}
		}
	}

	void TestClass::Report() const
	{
		cout << _pass << " passed, " << _fail << " failed." << endl;
	}

	LONGLONG TestClass::TimedCall(const function<void(void)> & func) const
	{
		function<LONGLONG(void)> GetTicks = [&](void)->LONGLONG {
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