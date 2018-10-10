#include "Test.h"

void StringTest::Init(void)
{
	Add("Join", [&]() {
		{
			int i[] = { 0, 1, 2, 3 };
			string o1 = String::Join(i, 4, ":");
			Logger().WriteInformation("%s\n", o1.c_str());
			ASSERT1(0 == strcmp("0:1:2:3", o1.c_str()));

			wstring o2 = String::Join(i, 4, L":");
			Logger().WriteInformation("%S\n", o2.c_str());
			ASSERT1(0 == wcscmp(L"0:1:2:3", o2.c_str()));
		}
		{
			double i[] = { 0.1, 1.2, 2.3, 3.4 };
			string o1 = String::Join(i, 4, ":");
			Logger().WriteInformation("%s\n", o1.c_str());
			ASSERT1(0 == strcmp("0.1:1.2:2.3:3.4", o1.c_str()));

			wstring o2 = String::Join(i, 4, L":");
			Logger().WriteInformation("%S\n", o2.c_str());
			ASSERT1(0 == wcscmp(L"0.1:1.2:2.3:3.4", o2.c_str()));
		}
		{
			vector<int> i = { 0, 1, 2, 3 };
			string o1 = String::Join(i, ":");
			Logger().WriteInformation("%s\n", o1.c_str());
			ASSERT1(0 == strcmp("0:1:2:3", o1.c_str()));

			wstring o2 = String::Join(i, L":");
			Logger().WriteInformation("%S\n", o2.c_str());
			ASSERT1(0 == wcscmp(L"0:1:2:3", o2.c_str()));
		}
		{
			vector<double> i = { 0.1, 1.2, 2.3, 3.4 };
			string o1 = String::Join(i, ":");
			Logger().WriteInformation("%s\n", o1.c_str());
			ASSERT1(0 == strcmp("0.1:1.2:2.3:3.4", o1.c_str()));

			wstring o2 = String::Join(i, L":");
			Logger().WriteInformation("%S\n", o2.c_str());
			ASSERT1(0 == wcscmp(L"0.1:1.2:2.3:3.4", o2.c_str()));
		}
	});

	Add("Random", [&]() {
		{
			string a = "abcdefghijklmnopqrstuvwxyz";
			for (int i = 0; i < 100; i++) {
				size_t len = 1 + rand() % 100;
				string o = String::Random(a, len);
				Logger().WriteInformation("%s\n", o.c_str());
			}
		}
		{
			wstring a = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			for (int i = 0; i < 100; i++) {
				size_t len = 1 + rand() % 100;
				wstring o = String::Random(a, len);
				Logger().WriteInformation("%S\n", o.c_str());
			}
		}
	});
}