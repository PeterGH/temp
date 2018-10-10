#include "MyString.h"

namespace My {
	
	string StringA::ToString(char * input) 
	{
		size_t len = strlen(input);
		string output;
		for (unsigned int i = 0; i < len; i ++) {
			output.append(1, input[i]);
		}
		return output;
	}

	string StringA::ToLower(const string & input)
	{
		string output;
		for (size_t i = 0; i < input.length(); i ++) {
			output.append(1, tolower(input[i]));
		}
		return output;
	}

	const string StringA::Empty = "";
		
	wstring StringW::ToString(wchar_t * input) 
	{
		size_t len = wcslen(input);
		wstring output;
		for (unsigned int i = 0; i < len; i ++) {
			output.append(1, input[i]);
		}
		return output;
	}

	wstring StringW::ToLower(const wstring & input)
	{
		wstring output;
		for (size_t i = 0; i < input.length(); i ++) {
			output.append(1, towlower(input[i]));
		}
		return output;
	}
	
	const wstring StringW::Empty = L"";
}
