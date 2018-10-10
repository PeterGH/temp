#pragma once
#include <bitset>
#include <stdarg.h>
#include <string>
using namespace std;

namespace My {
	
	class String {
	private:
		static const size_t MaxLength = 1024;
	public:
		String(void) {}
		~String(void) {}

		template<class T> __declspec(dllexport) static basic_string<T> Empty()
		{
			basic_string<T> empty;
			return empty;
		}

		// Convert an input string into an output string of different encoding.
		// Template arguments I and O can be char or wchar_t.
		template<class O, class I> __declspec(dllexport) static basic_string<O> ToString(const basic_string<I> & input)
		{ 
			basic_string<O> output(input.begin(), input.end()); 
			return output; 
		}

		template<class T> __declspec(dllexport) static string ToString(const basic_string<T> & input) 
		{ 
			string output(input.begin(), input.end()); 
			return output; 
		}

		template<class T> __declspec(dllexport) static wstring ToWString(const basic_string<T> & input)
		{
			wstring output(input.begin(), input.end());
			return output; 
		}

		__declspec(dllexport) static string ToString(const wchar_t * input) 
		{ 
			wstring s(input); 
			return ToString(s); 
		}

		__declspec(dllexport) static wstring ToWString(const char * input) 
		{ 
			string s(input); 
			return ToWString(s); 
		}	
		
		// Check if string input1 starts with string input2
		template<class T> __declspec(dllexport) static bool StartsWith(const basic_string<T> & input1, const basic_string<T> & input2) 
		{ 
			return 0 == ToLower(input1).compare(0, input2.size(), ToLower(input2)); 
		}

		// Check if string input1 ends with string input2
		template<class T> __declspec(dllexport) static bool EndsWith(const basic_string<T> & input1, const basic_string<T> & input2) 
		{ 
			return (input1.size() - input2.size()) == ToLower(input1).rfind(ToLower(input2), input1.size()); 
		}

		// Check if string input1 contains string input2
		template<class T> __declspec(dllexport) static bool Contains(const basic_string<T> & input1, const basic_string<T> & input2) 
		{ 
			return basic_string<T>::npos != ToLower(input1).find(ToLower(input2)); 
		}

		__declspec(dllexport) static string Format(const char * format, ...);
		__declspec(dllexport) static wstring Format(const wchar_t * format, ...);

		template<class T> __declspec(dllexport) static basic_string<T> ToLower(const basic_string<T> & input);

		template<class T> __declspec(dllexport) static basic_string<T> TrimStart(const basic_string<T> & input, const T * characters);
		template<class T> __declspec(dllexport) static basic_string<T> TrimEnd(const basic_string<T> & input, const T * characters);
		template<class T> __declspec(dllexport) static basic_string<T> Trim(const basic_string<T> & input, const T * characters);

		// Remove duplicate characters from string input.
		// Return the number of unique characters left in string input.
		__declspec(dllexport) static int RemoveDuplicateChars(char * input, int length);
	};

	template<class T> basic_string<T> String::ToLower(const basic_string<T> & input)
	{
		basic_string<T> output;
		for (size_t i = 0; i < input.length(); i ++) {
			output.append(1, tolower(input[i]));
		}

		return output;
	}

	template<class T> basic_string<T> String::TrimStart(const basic_string<T> & input, const T * characters)
	{
		if (input.length() == 0) return input;
		size_t index = input.find_first_not_of(characters);
		if (index == basic_string<T>::npos) return Empty<T>();
		return input.substr(index);
	}

	template<class T> basic_string<T> String::TrimEnd(const basic_string<T> & input, const T * characters)
	{
		if (input.length() == 0) return input;
		size_t index = input.find_last_not_of(characters);
		if (index == basic_string<T>::npos) return Empty<T>();
		return input.substr(0, index + 1);
	}

	template<class T> basic_string<T> String::Trim(const basic_string<T> & input, const T * characters)
	{
		if (input.length() == 0) return input;
		size_t f = input.find_first_not_of(characters);
		size_t l = input.find_last_not_of(characters);
		if (f == basic_string<T>::npos) return Empty<T>();
		return input.substr(f, l - f + 1);
	}
}

