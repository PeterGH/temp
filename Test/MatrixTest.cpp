#include "MatrixTest.h"

void MatrixTest::Init()
{
	Add("Matrix", [&]() {
		Matrix<int> B(3, 4);
		Logger().Print(B);
		B(1, 2) = 101;
		Logger().Print(B, "%d", "\t");
		int v = B(1, 2);
		ASSERT1(101 == v);
		B(2, 3) = 202;
		auto p = [&](Log & l, int & x) { l.WriteInformation("%d", x); };
		Logger().Print<int>(B, p, "\t");
		v = B(2, 3);
		ASSERT1(202 == v);
		const int w = B(2, 3);
		ASSERT1(202 == w);
	});

	Add("LowerTriangularMatrix", [&]() {
		LowerTriangularMatrix<int> B(4, 3);
		Logger().Print(B);
		B(2, 1) = 101;
		Logger().Print(B, "%d", "\t");
		int v = B(2, 1);
		ASSERT1(101 == v);
		B(3, 2) = 202;
		auto p = [&](Log & l, int x) { l.WriteInformation("%d", x); };
		Logger().Print<int>(B, p, "\t");
		v = B(3, 2);
		ASSERT1(202 == v);
		const int w = B(3, 2);
		ASSERT1(202 == w);
		ASSERTERROR(B(0, 1) = 0, invalid_argument);
		const LowerTriangularMatrix<int> A(4, 3);
		ASSERT1(A(0, 1) == 0);
		LowerTriangularMatrix<int> C(4, 5);
		Logger().Print(C);
		C(2, 1) = 101;
		Logger().Print(C, "%d", "\t");
		v = C(2, 1);
		ASSERT1(101 == v);
		C(3, 2) = 202;
		Logger().Print<int>(C, p, "\t");
		v = C(3, 2);
		ASSERT1(202 == v);
		const int y = C(3, 2);
		ASSERT1(202 == y);
		ASSERTERROR(C(0, 1) = 0, invalid_argument);
		const LowerTriangularMatrix<int> D(4, 5);
		ASSERT1(D(0, 1) == 0);
	});

	Add("UpperTriangularMatrix", [&]() {
		UpperTriangularMatrix<int> B(3, 4);
		Logger().Print(B);
		B(1, 2) = 101;
		Logger().Print(B, "%d", "\t");
		int v = B(1, 2);
		ASSERT1(101 == v);
		B(2, 3) = 202;
		auto p = [&](Log & l, int x) { l.WriteInformation("%d", x); };
		Logger().Print<int>(B, p, "\t");
		v = B(2, 3);
		ASSERT1(202 == v);
		const int w = B(2, 3);
		ASSERT1(202 == w);
		ASSERTERROR(B(1, 0) = 0, invalid_argument);
		const UpperTriangularMatrix<int> A(3, 4);
		ASSERT1(A(1, 0) == 0);
		UpperTriangularMatrix<int> C(5, 4);
		Logger().Print(C);
		C(1, 2) = 101;
		Logger().Print(C, "%d", "\t");
		v = C(1, 2);
		ASSERT1(101 == v);
		C(2, 3) = 202;
		Logger().Print<int>(C, p, "\t");
		v = C(2, 3);
		ASSERT1(202 == v);
		const int y = C(2, 3);
		ASSERT1(202 == y);
		ASSERTERROR(C(1, 0) = 0, invalid_argument);
		const UpperTriangularMatrix<int> D(5, 4);
		ASSERT1(D(1, 0) == 0);
	});
}