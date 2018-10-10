#include "ArgumentTest.h"

void ArgumentTest::Init(void)
{
	Add("Argument_char", [&]() {
		int argc = 9;
		char * argv[9] = {"Test.exe", "I1", "I2", "-K1", "V1", "-K2", "-K3", "V3", "I3"};
		My::Argument<char> arg(argc, argv);
		cout << arg.ToString() << endl;
		ASSERT2(arg.CountNamedArgs() == 3, My::String::Format("arg.CountNamedArgs() = %d", arg.CountNamedArgs()));
		ASSERT2(arg.CountIndexedArgs() == 4, My::String::Format("arg.CountIndexedArgs() = %d", arg.CountIndexedArgs()));
		ASSERT2(arg.Count() == 7, My::String::Format("arg.Count() == %d", arg.Count()));
		ASSERT1(arg.Has(3));
		ASSERT2(arg[3] == "I3", My::String::Format("arg[s] = %s", arg[3]));
		ASSERT1(!arg.Has(4));
		ASSERTERROR(arg[4], std::invalid_argument);
		ASSERT1(arg.Has("K2"));
		ASSERT2(arg["K2"] == "", My::String::Format("arg[\"K2\"] = %s", arg["K2"]));
		ASSERT1(arg.Has("K3"));
		ASSERT2(arg["K3"] == "V3", My::String::Format("arg[\"K3\"] = %s", arg["K3"]));
		ASSERT1(!arg.Has("K4"));
		ASSERTERROR(arg["K4"], invalid_argument);
	});

	Add("Keys_char", [&]() {
		int argc = 9;
		char * argv[9] = {"Test.exe", "I1", "I2", "-K1", "V1", "-K2", "-K3", "V3", "I3"};
		My::Argument<char> arg(argc, argv);
		cout << arg.ToString() << endl;
		set<string> keys = arg.Keys();
		ASSERT2(keys.size() == 3, My::String::Format("keys.size() = %d", keys.size()));
		set<string>::iterator it;
		string k[] = {"k1", "k2", "k3"};
		for (unsigned int i = 0; i < 3; i ++) {
			ASSERT1(arg.Has(k[i]));
			it = keys.find(k[i]);
			ASSERT2(it != keys.end(), My::String::Format("%s is not found", k[i]));
		}
	});

	Add("Argument_wchar_t", [&]() {
		int argc = 9;
		wchar_t * argv[9] = {L"Test.exe", L"I1", L"I2", L"-K1", L"V1", L"-K2", L"-K3", L"V3", L"I3"};
		My::Argument<wchar_t> arg(argc, argv);
		wcout << arg.ToString() << endl;
		ASSERT2(arg.CountNamedArgs() == 3, My::String::Format("arg.CountNamedArgs() = %d", arg.CountNamedArgs()));
		ASSERT2(arg.CountIndexedArgs() == 4, My::String::Format("arg.CountIndexedArgs() = %d", arg.CountIndexedArgs()));
		ASSERT2(arg.Count() == 7, My::String::Format("arg.Count() == %d", arg.Count()));
		ASSERT1(arg.Has(3));
		wcout << arg[3] << endl;
		ASSERT1(arg[3] == L"I3");
		ASSERT1(!arg.Has(4));
		ASSERTERROR(arg[4], std::invalid_argument);
		ASSERT1(arg.Has(L"K2"));
		wcout << L"arg[L\"K2\"] = " << arg[L"K2"] << endl;
		ASSERT1(arg[L"K2"] == L"");
		ASSERT1(arg.Has(L"K3"));
		wcout << L"arg[L\"K3\"] = " << arg[L"K2"] << endl;
		ASSERT1(arg[L"K3"] == L"V3");
		ASSERT1(!arg.Has(L"K4"));
		ASSERTERROR(arg[L"K4"], invalid_argument);
	});

	Add("Keys_wchar_t", [&]() {
		int argc = 9;
		wchar_t * argv[9] = {L"Test.exe", L"I1", L"I2", L"-K1", L"V1", L"-K2", L"-K3", L"V3", L"I3"};
		My::Argument<wchar_t> arg(argc, argv);
		wcout << arg.ToString() << endl;
		set<wstring> keys = arg.Keys();
		ASSERT2(keys.size() == 3, My::String::Format("keys.size() = %d", keys.size()));
		set<wstring>::iterator it;
		wstring k[] = {L"k1", L"k2", L"k3"};
		for (unsigned int i = 0; i < 3; i ++) {
			ASSERT1(arg.Has(k[i]));
			it = keys.find(k[i]);
			ASSERT2(it != keys.end(), My::String::Format("%s is not found", k[i]));
		}
	});

}
