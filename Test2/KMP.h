#pragma once
#include <vector>
using namespace std;
namespace My {
	class KMP {
	public:
		__declspec(dllexport) KMP(char * pattern);
		__declspec(dllexport) ~KMP(void);
		__declspec(dllexport) void Print(void);
		__declspec(dllexport) vector<int> SearchString(char * input, int length);
	private:
		char * pattern;
		int * prefix;
		int length;
	};
}

