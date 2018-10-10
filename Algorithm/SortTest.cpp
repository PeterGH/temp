#include "Header.h"

void SortTest::Init(void)
{
	Add("RowSort", [&]() {
		{
			const int rows = 3;
			const int columns = 18;
			const int length = rows * columns;
			int A[length];
			for (int i = 0; i < length; i++) {
				A[i] = length - i;
			}

			Sort::RowSort::Sort<int>(A, length, columns);
			ASSERT1(Sort::RowSort::IsSorted(A, length, columns));
		}
		{
			for (int i = 0; i < 10; i++) {
				// srand((unsigned)time(NULL));
				const int rows = rand() % 100 + 1;
				const int columns = 2 * rows * rows;
				const int length = rows * columns;
				Logger().WriteInformation("Run %d: %d X %d\n", i, rows, columns);

				unique_ptr<int[]> A(new int[length]);
				Array::Random(A.get(), length);
				unique_ptr<int[]> B(new int[length]);
				memcpy_s(B.get(), length * sizeof(int), A.get(), length * sizeof(int));

				long tick = GetTickCount();
				bool sortedA = Sort::RowSort::IsSorted(A.get(), length, columns);
				Logger().WriteInformation("Serialized: %ssorted, %d ticks\n", sortedA ? "" : "not ", GetTickCount() - tick);
				tick = GetTickCount();
				Sort::RowSort::Sort<int>(A.get(), length, columns);
				Logger().WriteInformation("Serialized: sort took %d ticks\n", GetTickCount() - tick);
				tick = GetTickCount();
				sortedA = Sort::RowSort::IsSorted(A.get(), length, columns);
				Logger().WriteInformation("Serialized: %ssorted, %d ticks\n", sortedA ? "" : "not ", GetTickCount() - tick);

				tick = GetTickCount();
				bool sortedB = Sort::RowSort::ParallelIsSorted(B.get(), length, columns);
				Logger().WriteInformation("Parallel: %ssorted, %d ticks\n", sortedB ? "" : "not ", GetTickCount() - tick);
				tick = GetTickCount();
				Sort::RowSort::ParallelSort<int>(B.get(), length, columns);
				Logger().WriteInformation("Parallel: sort took %d ticks\n", GetTickCount() - tick);
				tick = GetTickCount();
				sortedB = Sort::RowSort::IsSorted(B.get(), length, columns);
				Logger().WriteInformation("Parallel: %ssorted, %d ticks\n", sortedB ? "" : "not ", GetTickCount() - tick);

				bool equal = Equal(A.get(), B.get(), length);
				ASSERT1(sortedA == true);
				ASSERT1(sortedB == true);
				ASSERT1(equal == true);
			}
		}
	});

	Add("CountingSort", [&]() {
		{
			int A[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
			int L = sizeof(A) / sizeof(A[0]);
			int B[8];
			Sort::CountingSort::Sort(A, L, B);
			Logger().WriteInformation("A:\t");
			Logger().Print(A, L);
			Logger().WriteInformation("B:\t");
			Logger().Print(B, L);
			ASSERT1(IsSorted(B, L));
			Sort::CountingSort::Sort(A, L);
			Logger().WriteInformation("A:\t");
			Logger().Print(A, L);
			ASSERT1(IsSorted(A, L));
		}
		{
			for (int i = 0; i < 100; i++) {
				int size = 1 + rand() % 1000;
				int range = rand() % 100;
				Logger().WriteInformation("Run %d %d elements in [-%d, %d]\n", i, size, range, range);
				unique_ptr<int[]> A(new int[size]);
				Array::Random(A.get(), size, -range, range);
				Sort::CountingSort::Sort(A.get(), size);
				ASSERT1(IsSorted(A.get(), size));
			}
		}
	});
}