#pragma once

namespace My {
	class __declspec(dllexport) Rotation {
	public:
		Rotation(void) {}
		~Rotation(void) {}
		static void Left(char * input, int length, int distance);
		static void Right(char * input, int length, int distance);
	private:
		static void Swap(char * first, char * second, int count);
	};
}
