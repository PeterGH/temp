// Path.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include "Argument.h"
#include "MyPath.h"

using namespace std;

void Usage(wchar_t * argv[])
{
	wcout << L"Usage: " << argv[0] << L" [Path] [Wildchar] -Recursive" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	My::Argument<wchar_t> arg(argc, argv);
	if (arg.CountIndexedArgs() < 2) {
		Usage(argv);
		return -1;
	}

	wchar_t buffer[_MAX_PATH];
	if (_wfullpath(buffer, arg[1].c_str(), _MAX_PATH) == NULL) {
		Usage(argv);
		return -1;
	}

	wstring path(buffer);
	wcout << path << endl;

	wstring wildchar(L"*");
	if (arg.Has(2)) wildchar = wstring(arg[2]);

	bool recursive = arg.Has(L"recursive");

	wcout << "GetItems" << endl;

	vector<wstring> items;
	My::Path::GetDirectories(items, path, wildchar, recursive);
	My::Path::GetFiles(items, path, wildchar, recursive);

	for (vector<wstring>::iterator it = items.begin(); it != items.end(); it ++) {
		wcout << "  " << it->data() << endl;
	}

	wcout << "GetItemsP" << endl;

	concurrent_vector<wstring> itemsp;
	My::Path::GetDirectories(itemsp, path, wildchar, recursive);
	My::Path::GetFiles(itemsp, path, wildchar, recursive);

	for (concurrent_vector<wstring>::iterator it = itemsp.begin(); it != itemsp.end(); it ++) {
		wcout << "  " << it->data() << endl;
	}

	wcout << "GetItemsP: " << itemsp.size() << endl;

	wcout << "ProcessItems" << endl;

	auto p = [](wstring x) { wcout << "  " << x << endl; };

	My::Path::ProcessDirectories(path, p, wildchar, recursive);
	My::Path::ProcessFiles(path, p, wildchar, recursive);

	wcout << "GetItems: " << items.size() << endl;
	wcout << "GetItemsP: " << itemsp.size() << endl;
	return 0;
}

