#include "Header.h"

void ArrayTest::Init(void)
{
	Add("MinMax", [&]() {
		auto check = [&](int * input, int length) {
			int minIndex;
			int maxIndex;
			Array::MinMax(input, length, minIndex, maxIndex);
			int minI = Array::Min(input, length, true);
			int maxI = Array::Max(input, length, false);
			ASSERT1(minIndex == minI);
			ASSERT1(maxIndex == maxI);
		};
		auto check2 = [&](vector<int> input) {
			auto inputs = Permutation::All(input);
			int len = (int)input.size();
			for_each(inputs.begin(), inputs.end(), [&](vector<int> & it) {
				unique_ptr<int[]> A(new int[len]);
				Array::ToArray(it, A.get());
				check(A.get(), len);
			});
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			vector<int> A = { 1, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			vector<int> A = { 1, 2, 2 };
			check2(A);
		}
		{
			vector<int> A = { 1, 1, 2 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 3 };
			check2(A);
		}
		{
			int A[] = { 4, 4, 4, 4 };
			check(A, 4);
		}
		{
			vector<int> A = { 1, 4, 4, 4 };
			check2(A);
		}
		{
			vector<int> A = { 1, 1, 4, 4 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 3, 4 };
			check2(A);
		}
		{
			for (int i = 0; i < 100; i++) {
				int length = 1 + rand() % 100;
				unique_ptr<int[]> input(new int[length]);
				for (int j = 0; j < length; j++) {
					input[j] = rand();
				}
				check(input.get(), length);
			}
		}
	});

	Add("Rotate", [&]() {
		auto check = [&](int length) {
			unique_ptr<int[]> input(new int[length]);
			Array::Random(input.get(), length);
			unique_ptr<int[]> input2(new int[length]);
			Array::Duplicate<int>(input.get(), input2.get(), length);
			for (int i = 0; i <= 2 * length; i++) {
				Array::RotateLeft(input.get(), length, i);
				Array::RotateLeft2(input2.get(), length, i);
				Logger().Print(input.get(), length);
				Logger().Print(input2.get(), length);
				ASSERT1(true == Equal(input.get(), input2.get(), length));
				Array::RotateRight(input.get(), length, i);
				Array::RotateRight2(input2.get(), length, i);
				Logger().Print(input.get(), length);
				Logger().Print(input2.get(), length);
				ASSERT1(true == Equal(input.get(), input2.get(), length));
			}
		};
		for (int i = 1; i < 20; i++) {
			check(i);
		}
	});

	Add("Transpose", [&]() {
		auto check = [&](int length, int columns) {
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Array::Sequential(A.get(), length);
			Array::Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			Array::Transpose(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = j * rows + i;
					ASSERT1(A[s] == B[t]);
				}
			}
			Array::Transpose<int>(B.get(), length, rows);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		};
		check(1, 1);
		check(5, 5);
		check(5, 1);
		check(15, 5);
		check(60, 6);
		check(64, 8);
	});

	Add("RowsColumns", [&](){
		{
			int length = 64;
			int columns = 8;
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Array::Sequential(A.get(), length);
			Array::Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			Array::TransposeRowsToColumns<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = j * rows + i;
					ASSERT1(A[s] == B[t]);
				}
			}
			Array::TransposeColumnsToRows<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		}
		{
			int length = 16;
			int columns = 8;
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Array::Sequential(A.get(), length);
			Array::Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			Array::TransposeRowsToColumns<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			// Transpose element (m,n) to ((n % M), (k(m-1) + n/M)) means the index i = Nm + n is mapped to j = (n % M)N + k(m-1) + n/M
			int k = columns / rows;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = (j % rows) * columns + k * i + j / rows;
					ASSERT1(A[s] == B[t]);
				}
			}
			Array::TransposeColumnsToRows<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		}
		{
			int length = 27;
			int columns = 3;
			int rows = length / columns;
			unique_ptr<int[]> A(new int[length]);
			unique_ptr<int[]> B(new int[length]);
			Array::Sequential(A.get(), length);
			Array::Sequential(B.get(), length);
			Logger().Print(A.get(), length, columns);
			Array::TransposeRowsToColumns<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			// Transpose element (m,n) to ((m%k)N + n, m/k)) means the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
			int k = rows / columns;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					int t = (i % k) * columns * columns + j * columns + i / k;
					ASSERT1(A[s] == B[t]);
				}
			}
			Array::TransposeColumnsToRows<int>(B.get(), length, columns);
			Logger().Print(B.get(), length, columns);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int s = i * columns + j;
					ASSERT1(A[s] == B[s]);
				}
			}
		}
	});
}