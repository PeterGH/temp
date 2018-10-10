#include <iostream>
#include "Argument.h"
#include "Test.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc < 2) {
        cout << "Test.exe -l" << endl;
        cout << "\tList all tests." << endl;
        cout << "Test.exe Test -l" << endl;
        cout << "\tList all test methods of a test. The test name can be a partial name." << endl;
        cout << "Test.exe *" << endl;
        cout << "\tRun all tests." << endl;
        cout << "Test.exe Test" << endl;
        cout << "\tRun a specified test. The test name can be a partial name." << endl;
        cout << "Test.exe Test Method" << endl;
        cout << "\tRun a specified test method of a specific test. Both the test name and method name can be partial names." << endl;
        return -1;
    }

    // Note argc >= 1, argv[0] == "Test.exe"
    Argument<char> arg(argc, argv);

    LogLevel level = arg.Has("v") ? LogLevel::Verbose : LogLevel::Error;
    Log log(cout, level);
    TestSuite suite(log);

    suite.Add(new AlgorithmTest(log));
    suite.Add(new CppTest(log));
    suite.Add(new LeetCodeTest(log));

    if (arg.Has("l")) {
        if (arg.CountIndexedArgs() == 1) {
            cout << "Available tests are:" << endl;
            suite.List();
            return 0;
        } else if (arg.CountIndexedArgs() > 1) {
            suite.List(arg[1]);
            return 0;
        }
    } else if (arg.CountIndexedArgs() > 1) {
        if (arg[1] == "*") {
            suite.Run();
        } else if (arg.CountIndexedArgs() == 2) {
            suite.Run(arg[1]);
        } else {
            suite.Run(arg[1], arg[2]);
        }
    }

    suite.Report();
    return 0;
}