#include "QuickSortTest.h"

void QuickSortTest::Init(void)
{
	Add("Sort", [&](){
		int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
		int I2[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
		int I3[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
		int L = sizeof(I1)/sizeof(I1[0]);

		std::vector<int> V1;
		for (int i = 0; i < L; i++) {
			V1.push_back(I1[i]);
		}

		My::QuickSort<int>::Sort(I1, L);
		My::QuickSort<int>::ParallelSort(I2, L);
		My::QuickSort<int>::RandomSort(I3, L);

		std::sort(V1.begin(), V1.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V1[i] == I1[i]);
			ASSERT1(V1[i] == I2[i]);
			ASSERT1(V1[i] == I3[i]);
		}		
	});

	Add("Sort 2", [&](){
		int I1[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
		int L = sizeof(I1)/sizeof(I1[0]);

		std::vector<int> V1;
		for (int i = 0; i < L; i++) {
			V1.push_back(I1[i]);
		}

		My::QuickSort<int>::Sort(I1, L);

		std::sort(V1.begin(), V1.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V1[i] == I1[i]);
		}		
	});

	Add("Sort 3", [&](){
		int I1[] = {0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2};
		int L = sizeof(I1)/sizeof(I1[0]);

		std::vector<int> V1;
		for (int i = 0; i < L; i++) {
			V1.push_back(I1[i]);
		}

		My::QuickSort<int>::Sort(I1, L);

		std::sort(V1.begin(), V1.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V1[i] == I1[i]);
		}		
	});

	Add("Select", [&](){
		int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);
			int e = My::QuickSort<int>::RandomSelect(I1, L, 0);
			ASSERT1(1 == e);

			int I2[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I2, L, 1);
			ASSERT1(1 == e);

			int I3[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I3, L, 2);
			ASSERT1(3 == e);

			int I4[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I4, L, 3);
			ASSERT1(3 == e);

			int I5[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I5, L, 4);
			ASSERT1(7 == e);

			int I6[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I6, L, 5);
			ASSERT1(8 == e);

			int I7[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I7, L, 6);
			ASSERT1(34 == e);

			int I8[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I8, L, 7);
			ASSERT1(35 == e);

			int I9[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I9, L, 8);
			ASSERT1(42 == e);

			int I10[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I10, L, 9);
			ASSERT1(43 == e);

			int I11[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I11, L, 10);
			ASSERT1(64 == e);

			int I12[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I12, L, 11);
			ASSERT1(445 == e);

			int I13[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I13, L, 12);
			ASSERT1(3556 == e);

			int I14[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I14, L, 13);
			ASSERT1(8769 == e);

			int I15[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I15, L, 14);
			ASSERT1(96656532 == e);
	});

	Add("Select 2", [&](){
		int I1[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
		int L = sizeof(I1) / sizeof(I1[0]);

		for (int i = 0; i < L; i++) {
			int e = My::QuickSort<int>::RandomSelect(I1, L, i);
			ASSERT1(3 == e);
		}
	});
}