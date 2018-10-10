#include "ArrayTest.h"

void ArrayTest::Init(void)
{
	Add("Array1D", [&]() {
		Array1D<int> A(4);
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
		Array2D<int> B(3, 4);
		B.Print();
		B.SetValue(1, 2, 101);
		B.Print();
		int v = B.GetValue(1, 2);
		ASSERT1(101 == v);
		//*B.Element(2, 3) = 202;
		B.Element(2, 3) = 202;
		B.Print();
		//v = *B.Element(2, 3);
		v = B.Element(2, 3);
		ASSERT1(202 == v);
	});
}
