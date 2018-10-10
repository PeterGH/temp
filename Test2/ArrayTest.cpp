#include "ArrayTest.h"

void ArrayTest::Init(void)
{
	Add("Array1D", [&]() {
		My::Array1D<int> A(4);
		A.Print();
		A.SetValue(1, 101);
		A.Print();
		int v = A.GetValue(1);
		ASSERT1(101 == v);
		A[3] = 303;
		A.Print();
		v = A[3];
		ASSERT1(303 == v);
	});

	Add("Array2D", [&]() {
		My::Array2D<int> B(3, 4);
		B.Print();
		B.SetValue(1, 2, 101);
		B.Print();
		int v = B.GetValue(1, 2);
		ASSERT1(101 == v);
		B.Element(2, 3) = 202;
		B.Print();
		v = B.Element(2, 3);
		ASSERT1(202 == v);
	});

	Add("PartialSum", [&]() {
		vector<int> input(10);

		generate(input.begin(), input.end(), rand);
		for (size_t i = 0; i < input.size(); i ++)	{
			printf("%d ", input[i]);
		}

		printf("\n");

		printf("input\t");
		for_each (input.begin(), input.end(), [](int& x)->void { x = x % 20;});
		for (size_t i = 0; i < input.size(); i ++)	{
			printf("%d ", input[i]);
		}

		printf("\n");

		vector<int> output1 = My::Array::PartialSum(input);
		printf("output1\t");
		for (size_t i = 0; i < output1.size(); i ++)	{
			printf("%d ", output1[i]);
		}

		printf("\n");

		vector<int> output2 = My::Array::PartialSum(input, input.size());
		printf("output2\t");
		for (size_t i = 0; i < output2.size(); i ++)	{
			printf("%d ", output2[i]);
		}

		printf("\n");

		vector<int> output3 = My::Array::PartialSum2(input, input.size());
		printf("output3\t");
		for (size_t i = 0; i < output3.size(); i ++)	{
			printf("%d ", output3[i]);
		}

		printf("\n");

		My::Array::PartialSum3(input, input.size());
		printf("input\t");
		for (size_t i = 0; i < input.size(); i ++)	{
			printf("%d ", input[i]);
		}

		printf("\n");

		for (size_t i = 0; i < output1.size(); i ++)	{
			ASSERT1(output1[i] == output2[i]);
			ASSERT1(output2[i] == output3[i]);
			ASSERT1(output3[i] == input[i]);
		}
	});

	Add("PartialSum2", [&]() {
		vector<int> input(10);

		generate(input.begin(), input.end(), rand);
		for (size_t i = 0; i < input.size(); i ++)	{
			printf("%d ", input[i]);
		}

		printf("\n");

		printf("input\t");
		for_each (input.begin(), input.end(), [](int& x)->void { x = x % 20;});
		for (size_t i = 0; i < input.size(); i ++)	{
			printf("%d ", input[i]);
		}

		printf("\n");

		vector<int> output2 = My::Array::PartialSum(input, input.size() >> 1);
		printf("output2\t");
		for (size_t i = 0; i < output2.size(); i ++)	{
			printf("%d ", output2[i]);
		}

		printf("\n");

		vector<int> output3 = My::Array::PartialSum2(input, input.size() >> 1);
		printf("output3\t");
		for (size_t i = 0; i < output3.size(); i ++)	{
			printf("%d ", output3[i]);
		}

		printf("\n");

		for (size_t i = 0; i < output2.size(); i ++)	{
			ASSERT1(output2[i] == output3[i]);
		}

		My::Array::PartialSum3(input, input.size() >> 1);
		printf("input\t");
		for (size_t i = 0; i < input.size(); i ++)	{
			printf("%d ", input[i]);
		}

		printf("\n");

		for (size_t i = 0; i < output2.size(); i ++)	{
			ASSERT1(output3[i] == input[i]);
		}
	});

	Add("Transpose", [&](){
		int A[15];
		int B[15];
		for (int i = 0; i < 15; i++) {
			A[i] = i;
			B[i] = i;
		}

		My::Array::Print(A, 15, 5);
		My::Array::Transpose(B, 15, 5);
		My::Array::Print(B, 15, 3);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 5; j++) {
				int s = i * 5 + j;
				int t = j * 3 + i;
				ASSERT1(A[s] == B[t]);
			}
		}
	});
}
