#pragma once

#include <string>

using namespace std;

namespace My {
	
	class StringA {
	public:
		StringA(void) {}
		~StringA(void) {}

		__declspec(dllexport) static string Format(const char * format, ...);
		__declspec(dllexport) static string ToString(char *);
		__declspec(dllexport) static string ToLower(const string &);
		__declspec(dllexport) static const string Empty;
	};

	class StringW {
	public:
		StringW(void) {}
		~StringW(void) {}
		__declspec(dllexport) static wstring ToString(wchar_t *);
		__declspec(dllexport) static wstring ToLower(const wstring &);
		__declspec(dllexport) static const wstring Empty;
	};

}

