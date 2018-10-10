#include "HeapDTest.h"
#include "..\Algorithm\Random.h"
#include <vector>

void HeapDTest::Init(void)
{
	Add("Sort", [&](){
		int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
		int L = sizeof(I1)/sizeof(I1[0]);
		std::vector<int> V1;
		for (int i = 0; i < L; i++) {
			V1.push_back(I1[i]);
		}
		
		My::HeapD<int> heap(3);
		heap.Sort(I1, L);
		
		for (int i = 0; i < L; i++) {
			cout << "\t" << I1[i];
		}

		cout << endl;

		std::make_heap(V1.begin(), V1.end());
		std::sort_heap(V1.begin(), V1.end());

		for (int i = 0; i < L; i++) {
			cout << "\t" << V1[i];
		}

		cout << endl;

		for (int i = 0; i < L; i++) {
			ASSERT1(V1[i] == I1[i]);
		}
	});

	Add("Sort2", [&](){
		vector<int> V(100000);
		generate(V.begin(), V.end(), rand);

		int I[100000];

		for (int i = 0; i < 100000; i ++) {
			I[i] = V[i];
		}

		My::HeapD<int> heap(23);
		heap.Sort(I, 100000);
		
		std::make_heap(V.begin(), V.end());
		std::sort_heap(V.begin(), V.end());

		for (int i = 0; i < 100000; i++) {
			ASSERT1(V[i] == I[i]);
		}
	});
}
