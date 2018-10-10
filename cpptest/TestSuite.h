#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <sstream>
#include "Log.h"

using namespace std;

namespace Test {

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
    } catch (error &) {    \
        ASSERT1(true); \
    }

#define STRING(statement) #statement

    // Base class to derive specific test classes.
    // Contain a set of test methods.
    class TestClass {
    private:
        long _passCount; // Count passed test methods
        long _failCount; // Count failed test methods

        Log & _log;

        // Each key is a test name and the value is the test implementation
        map<string, function<void(void)>> _testMethods;

        // Check if a test method is implemented
        bool Has(const string & name) const
        {
            return _testMethods.find(name) != _testMethods.end();
        }

        // Run a particular test method
        void Run(map<string, function<void(void)>>::const_iterator & it)
        {
            try {
                it->second();
                _passCount++;
            } catch (AssertError & e) {
                _failCount++;
                _log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(), e.what());
            } catch (exception & e) {
                _failCount++;
                _log.WriteError("%s: %s, %s\n", it->first.c_str(), typeid(e).name(), e.what());
            }
            catch (...) {
                _failCount++;
                _log.WriteError("%s\n", it->first.c_str());
            }
        }

    public:
        TestClass(Log & log = Log()) : _passCount(0), _failCount(0), _log(log) {}

        // Destructor. Make it virtual so that we can delete a pointer to a derived class object
        virtual ~TestClass(void) {}

        // Assert the result of statement is true. Otherwise,
        // throw an error message including the code file name and the code line number.
        static void Assert(bool result, const string & statement, const string & message, const string & file, long line)
        {
            if (!result) {
                ostringstream error;
                error << message << "\n" << file << ", " << line << ": " << statement;
                throw AssertError(error.str());
            }
        }

        // Add a test method
        void Add(const string & name, const function<void(void)> & test)
        {
            if (Has(name)) {
                ostringstream error;
                error << "TestMethod " << name << "already exists.";
                throw invalid_argument(error.str());
            }
            _testMethods.insert(pair<string, function<void(void)>>(name, test));
        }

        // Derived class to implement this method.
        // All test methods should be added in this method.
        virtual void Init(void) = 0;

        // Print all test methods
        void List(void) const
        {
            for (map<string, function<void(void)>>::const_iterator it = _testMethods.cbegin(); it != _testMethods.cend(); it++) {
                cout << "\t" << it->first << endl;
            }
        }

        // Get the log reference
        Log & Logger(void) const { return _log; }

        // This test class name
        const string Name(void) const
        {
            string name = typeid(*this).name();
            return name.substr(6);
        }

        // Run all test methods
        void Run(void)
        {
            for (map<string, function<void(void)>>::const_iterator it = _testMethods.begin(); it != _testMethods.end(); it++) {
                Run(it);
            }
        }

        // Run all test methods whose name starts with the input string
        void Run(const string & name)
        {
            for (map<string, function<void(void)>>::iterator it = _testMethods.begin(); it != _testMethods.end(); it++) {
                if (0 == it->first.compare(0, name.size(), name)) {
                    Run(it);
                }
            }
        }

        long PassCount(void) const { return _passCount; }
        long FailCount(void) const { return _failCount; }

        // Print a report of test run result
        void Report(void) const
        {
            cout << _passCount << " passed, " << _failCount << " failed." << endl;
        }
    };
    
    class TestSuite final {
    private:
        long _passCount; // Count passed test methods for all test classes
        long _failCount; // Count failed test methods for all test classes
        map<string, TestClass *> _tests; // Each key is a test class and the value is the implementation

        Log & _log;

        // Check if a test class is implemented
        bool Has(const string & name) const
        {
            return _tests.find(name) != _tests.end();
        }

        // Run test methods of a particular test class
        void Run(map<string, TestClass *>::iterator & it)
        {
            cout << " ==== " << it->first << " ==== " << endl;
            it->second->Run();
            it->second->Report();
            _passCount += it->second->PassCount();
            _failCount += it->second->FailCount();
        }

        // Run a test method of a particular test class
        // Input method can be a partial name
        void Run(map<string, TestClass *>::iterator & it, const string & method)
        {
            cout << " ==== " << it->first << " ==== " << endl;
            it->second->Run(method);
            it->second->Report();
            _passCount += it->second->PassCount();
            _failCount += it->second->FailCount();
        }

    public:
        TestSuite(Log & log = Log()) : _passCount(0), _failCount(0), _log(log) {}

        // Destructor to dispose all test class objects
        ~TestSuite(void)
        {
            // Make sure all allocated objects are freed
            for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
                delete it->second;
                it->second = nullptr;
            }
        }

        // Add a particular test class
        void Add(TestClass * test)
        {
            string name = test->Name();
            if (Has(name)) {
                ostringstream error;
                error << "TestClass " << name << "already exists.";
                throw invalid_argument(error.str());
            }
            test->Init();
            _tests.insert(pair<string, TestClass *>(name, test));
        }

        // Print all test classes
        void List(void) const
        {
            for (map<string, TestClass *>::const_iterator it = _tests.cbegin(); it != _tests.cend(); it++) {
                cout << "\t" << it->first << endl;
            }
        }

        // Print all methods of a test class
        void List(const string & test) const
        {
            for (map<string, TestClass *>::const_iterator it = _tests.cbegin(); it != _tests.cend(); it++) {
                if (0 == it->first.compare(0, test.size(), test)) {
                    cout << "Available test methods of " << it->first << " are:" << endl;
                    it->second->List();
                }
            }
        }

        // Run all test classes
        void Run(void)
        {
            for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
                Run(it);
            }
        }

        // Run all test classes whose name starts with the specified test name
        void Run(const string & test)
        {
            for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
                if (0 == it->first.compare(0, test.size(), test)) {
                    Run(it);
                }
            }
        }

        // Run the specified method in the specified test classes.
        // Input test and method can be partial names.
        void Run(const string & test, const string & method)
        {
            for (map<string, TestClass *>::iterator it = _tests.begin(); it != _tests.end(); it++) {
                if (0 == it->first.compare(0, test.size(), test)) {
                    Run(it, method);
                }
            }
        }

        // Print result of test run
        void Report(void) const
        {
            cout << " ==== Summary ==== " << endl;
            cout << _passCount << " passed, " << _failCount << " failed." << endl;
        }
    };
}