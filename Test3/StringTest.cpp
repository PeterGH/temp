#include "StringTest.h"

void StringTest::Init(void)
{
	Add("ToLowerA", [&]() {
		string i = "AFf34z df  g3zds^(%98FSDSFE";
		string o = My::StringA::ToLower(i);
		ASSERT1(0 == o.compare("aff34z df  g3zds^(%98fsdsfe"));
	});

	Add("ToLowerW", [&]() {
		wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
		wstring o = My::StringW::ToLower(i);
		ASSERT1(0 == o.compare(L"aff34z df  g3zds^(%98fsdsfe"));
	});

	Add("ToStringA", [&]() {
		string i = "AFf34z df  g3zds^(%98FSDSFE";
		cout << i << ": len " << strlen(&i[0]) << endl;
		string o = My::StringA::ToString(&i[0]);
		ASSERT1(0 == o.compare(i));
	});

	Add("ToStringW", [&]() {
		wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
		wcout << i << ": len " << wcslen(&i[0]) << endl;
		wstring o = My::StringW::ToString(&i[0]);
		ASSERT1(0 == o.compare(i));
	});
}
