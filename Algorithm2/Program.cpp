// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ArrayTest.h"
#include "StringTest.h"
#include "Argument.h"
#include "ArgumentTest.h"
#include "SingleLinkListTest.h"
#include "PathTest.h"
#include "MaskTest.h"
#include "MRNumberTest.h"
#include "PermutationTest.h"

class ExampleTest : public My::TestClass {
public:
	ExampleTest(void) {}
	~ExampleTest(void) {}
	void Init(void);
};

void ExampleTest::Init(void)
{
	Add("Test1", []() {
		cout << "This is Test1." << endl;
		throw My::AssertError("My Test1 failed.");
	});

	Add("Assert1", [&]() {
		Assert1(1 > 2);
	});

	Add("ASSERT1", [&]() {
		ASSERT1(1 > 2);
	});

	Add("Assert2", [&]() {
		Assert2(1 > 2, "1 is smaller than 2");
	});

	Add("ASSERT2", [&]() {
		ASSERT2(1 > 2, "1 is smaller than 2");
	});
}

int main(int argc, char * argv[])
{
	My::Argument<char> arg(argc, argv);
	
	My::TestSuite suite;
	suite.Add(new ArrayTest());
	suite.Add(new StringTest());	
	suite.Add(new ArgumentTest());
	suite.Add(new SingleLinkListTest());
	suite.Add(new PathTest());
	suite.Add(new MaskTest());
	suite.Add(new MRNumberTest());
	suite.Add(new PermutationTest());
	suite.Add(new ExampleTest());
	
	if (arg.Has("l")) {
		cout << "Available tests are:" << endl;
		suite.List();
		return 0;
	}

	if (arg.CountIndexedArgs() > 1) {
		suite.Run(arg[1]);
	} else {
		suite.Run();
	}

	suite.Report();

	return 0;
}

