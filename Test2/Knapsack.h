#pragma once
namespace My {
	class __declspec(dllexport) Knapsack {
	public:
		Knapsack(void) {}
		~Knapsack(void) {}

		static void ProgramValueMatrix(unsigned int * value, unsigned int * weight, unsigned int length, unsigned int * matrix, unsigned int capacity);
		static void Print(unsigned int * value, unsigned int * weight, unsigned int length, unsigned int * matrix, unsigned int capacity);
	};
}

