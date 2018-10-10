#include "ArrayTest.h"

void ArrayTest::Init(void)
{
	Add("Array1D", [&]() {
		My::Array1D<int> A(4);
		A.Print();
		A.SetValue(1, 101);
		A.Print();
		int v = A.GetValue(1);
		ASSERT2(101 == v, My::String::Format("v = %d", v));
		A[3] = 303;
		A.Print();
		v = A[3];
		ASSERT2(303 == v, My::String::Format("v = %d", v));
		v = A.Length();
		ASSERT2(4 == v, My::String::Format("v = %d", v));
	});

	Add("Array2D", [&]() {
		My::Array2D<int> A(3, 4);
		A.Print();
		A.SetValue(1, 2, 101);
		A.Print();
		int v = A.GetValue(1, 2);
		ASSERT2(101 == v, My::String::Format("v = %d", v));
		A.Element(2, 3) = 202;
		A.Print();
		v = A.Element(2, 3);
		ASSERT2(202 == v, My::String::Format("v = %d", v));
		v = A.CountRows();
		ASSERT2(3 == v, My::String::Format("v = %d", v));
		v = A.CountCols();
		ASSERT2(4 == v, My::String::Format("v = %d", v));
	});

	Add("Invalid Index", [&]() {
		My::Array1D<int> A(4);
		ASSERTERROR(A.GetValue(-1), std::invalid_argument);
	});

	Add("Invalid Indices", [&]() {
		My::Array2D<int> A(3, 4);
		ASSERTERROR(A.GetValue(-1, -1), std::invalid_argument);
	});

	//Add("ArrayMD", [&]() {
	//	My::ArrayMD<int> A(4, 2, 3, 4, 5);
	//	A.Print();
	//});
}
