#include "CountingSortTest.h"
#include "..\Algorithm\Random.h"

void CountingSortTest::Init(void)
{
	Add("One", [&](){
		int A[] = {2, 5, 3, 0, 2, 3, 0, 3};
		int L = sizeof(A) / sizeof(A[0]);
		int B[8];
		My::CountingSort::Sort(A, L, B);

		cout << "A:\t" << A[0];
		for (int i = 1; i < L; i ++) {
			cout << "\t" << A[i];
		}

		cout << endl;

		cout << "B:\t" << B[0];
		for (int i = 1; i < L; i ++) {
			cout << "\t" << B[i];
			ASSERT1(B[i] >= B[i-1]);
		}

		cout << endl;

		My::CountingSort::Sort(A, L);

		cout << "A:\t" << A[0];
		for (int i = 1; i < L; i ++) {
			cout << "\t" << A[i];
			ASSERT1(A[i] >= A[i-1]);
		}

		cout << endl;
	});

	Add("Two", [&](){
		My::Random rnd;
		const int size = 1000;
		int A[size];
		for (int i = 0; i < size; i ++) {
			A[i] = rnd.Next(-50, 50);
		}

		My::CountingSort::Sort(A, size);

		cout << "A:\t" << A[0];
		for (int i = 1; i < size; i ++) {
			cout << "\t" << A[i];
			ASSERT1(A[i] >= A[i-1]);
		}

		cout << endl;
	});
}