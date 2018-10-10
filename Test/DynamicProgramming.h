#pragma once
namespace Test {
	class DynamicProgramming {
	public:
		DynamicProgramming();
		~DynamicProgramming();

		__declspec(dllexport) static void LongestStringWithKeystrokes(int n, unsigned long long length[]);
	};
}