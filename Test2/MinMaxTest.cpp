#include "MinMaxTest.h"

void MinMaxTest::Init(void)
{
	Add("One", [&](){
		int A[] = {1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 1, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 0);
	});

	Add("Two Same", [&](){
		int A[] = {2, 2};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 2, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 1);
	});

	Add("Two One", [&](){
		int A[] = {1, 2};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 2, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 1);
	});

	Add("Two Two", [&](){
		int A[] = {2, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 2, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 0);
	});

	Add("Tree Same", [&](){
		int A[] = {2, 2, 2};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("Tree one", [&](){
		int A[] = {1, 2, 2};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("Tree two", [&](){
		int A[] = {2, 1, 2};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 2);
	});

	Add("Tree three", [&](){
		int A[] = {2, 2, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 1);
	});

	Add("Tree four", [&](){
		int A[] = {1, 1, 2};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("Tree four", [&](){
		int A[] = {1, 2, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 1);
	});

	Add("Tree five", [&](){
		int A[] = {2, 1, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 0);
	});

	Add("Tree Six", [&](){
		int A[] = {1, 2, 3};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("Tree Seven", [&](){
		int A[] = {3, 2, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 0);
	});

	Add("Four Same", [&](){
		int A[] = {4, 4, 4, 4};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("Four one", [&](){
		int A[] = {1, 4, 4, 4};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("Four two", [&](){
		int A[] = {4, 1, 4, 4};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 3);
	});

	Add("Four three", [&](){
		int A[] = {4, 4, 1, 4};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 3);
	});

	Add("Four four", [&](){
		int A[] = {4, 4, 4, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 3);
		ASSERT1(maxIndex == 2);
	});

	Add("Four five", [&](){
		int A[] = {1, 1, 4, 4};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("Four six", [&](){
		int A[] = {1, 4, 1, 4};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("Four seven", [&](){
		int A[] = {4, 1, 4, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 2);
	});

	Add("Four eight", [&](){
		int A[] = {4, 4, 1, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 1);
	});

	Add("Four nine", [&](){
		int A[] = {4, 3, 2, 1};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 3);
		ASSERT1(maxIndex == 0);
	});

	Add("Four ten", [&](){
		int A[] = {1, 3, 2, 4};
		int minIndex;
		int maxIndex;
		My::MinMax<int>::Get(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});
}