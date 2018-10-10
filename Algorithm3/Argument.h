#pragma once

#include <vector>
#include <map>
#include "MyString.h"

using namespace std;

namespace My {

	class ArgumentA {
	private:
		vector<string> _indexed;
		map<string, string> _named;
		__declspec(dllexport) void Parse(int argc, char * argv[]);
	public:
		__declspec(dllexport) ArgumentA(int argc, char * argv[]) { Parse(argc, argv); }
		__declspec(dllexport) ~ArgumentA(void) {}
		__declspec(dllexport) size_t CountNamedArgs(void) { return _named.size(); }
		__declspec(dllexport) size_t CountUnnamedArgs(void) { return _indexed.size(); }
		__declspec(dllexport) size_t Count(void) { return CountNamedArgs() + CountUnnamedArgs(); }
		__declspec(dllexport) bool Has(const string & key);
		__declspec(dllexport) bool Has(unsigned int index) { return index < _indexed.size(); }
		__declspec(dllexport) string & operator[](const string & key);
		__declspec(dllexport) string & operator[](unsigned int index);
		__declspec(dllexport) string ToString(void);
		
	};
		
	class ArgumentW {
	private:
		vector<wstring> _indexed;
		map<wstring, wstring> _named;
		__declspec(dllexport) void Parse(int argc, wchar_t * argv[]);
	public:
		__declspec(dllexport) ArgumentW(int argc, wchar_t * argv[]) { Parse(argc, argv); }
		__declspec(dllexport) ~ArgumentW(void) {}
		__declspec(dllexport) size_t CountNamedArgs(void) { return _named.size(); }
		__declspec(dllexport) size_t CountUnnamedArgs(void) { return _indexed.size(); }
		__declspec(dllexport) size_t Count(void) { return CountNamedArgs() + CountUnnamedArgs(); }
		__declspec(dllexport) bool Has(const wstring & key);
		__declspec(dllexport) bool Has(unsigned int index) { return index < _indexed.size(); }
		__declspec(dllexport) wstring & operator[](const wstring & key);
		__declspec(dllexport) wstring & operator[](unsigned int index);
		__declspec(dllexport) wstring ToString(void);
	};
	
}

