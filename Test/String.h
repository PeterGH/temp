#pragma once

#include <bitset>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

namespace Test {

	class String {
	private:
		static const size_t MaxLength = 1024;
	public:
		String(void) {}
		~String(void) {}

		__declspec(dllexport) static int WordLadder(const string & start, const string & end, const unordered_set<string> & dictionary);
		__declspec(dllexport) static int WordLadder2(const string & start, const string & end, const unordered_set<string> & dictionary);
		__declspec(dllexport) static int WordLadder3(const string & start, const string & end, const unordered_set<string> & dictionary);

		__declspec(dllexport) static vector<vector<string>> WordLadders(const string & start, const string & end, const unordered_set<string> & dictionary);

		__declspec(dllexport) static int MatchSubsequence(const string & input, const string & pattern);
		__declspec(dllexport) static int MatchSubsequence2(const string & input, const string & pattern);

	};

}

