#include "stdafx.h"
#include <functional>
#include "ArrayTest.h"
#include "MaskTest.h"
#include "StringTest.h"
#include "Argument.h"

void MyTest::Init(void)
{
	Add("Test1", []() {
		cout << "This is Test1." << endl;
		throw My::AssertError("MyTest.Test1 failed.");
	});	
}

int _tmain(int argc, wchar_t * argv[])
{
	My::ArgumentW arg(argc, argv);
	wcout << arg.ToString() << endl;

	My::TestSuite suite;
	//suite.Add(new ArrayTest());
	//suite.Add(new MaskTest());
	//suite.Add(new MyTest());
	suite.Add(new StringTest());
	
	//if (arg.CountUnnamedArgs() > 1) {
	//	suite.Run(arg[1]);
	//} else {
		suite.Run();
	//}

	suite.Report();

	return 0;
}
