#include "KnapsackTest.h"

void KnapsackTest::Init(void)
{
	Add("Knapsack", [&]() {
		unsigned int value[] = {60, 100, 120};
		unsigned int weight[] = {2, 4, 6};
		unsigned int capacity = 10;
		unsigned int matrix[3][11];
		My::Knapsack::ProgramValueMatrix(value, weight, 3, &matrix[0][0], 10);
		My::Knapsack::Print(value, weight, 3, &matrix[0][0], 10);
	});

	Add("Same weight", [&]() {
		unsigned int value[] = {60, 100, 120};
		unsigned int weight[] = {2, 2, 6};
		unsigned int capacity = 10;
		unsigned int matrix[3][11];
		My::Knapsack::ProgramValueMatrix(value, weight, 3, &matrix[0][0], 10);
		My::Knapsack::Print(value, weight, 3, &matrix[0][0], 10);
	});
}
