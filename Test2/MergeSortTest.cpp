#include "MergeSortTest.h"


void MergeSortTest::Init(void)
{
	Add("Multiple inputs", [&](){

		int * inputs[3];
		size_t sizes[3];
		
		int a0[] = {0, 5, 9, 11};
		inputs[0] = a0;
		sizes[0] = 4;

		int a1[] = {0, 1, 2, 3, 5, 6};
		inputs[1] = a1;
		sizes[1] = 6;

		int a2[] = {6, 7, 8};
		inputs[2] = a2;
		sizes[2] = 3;

		vector<int> output;

		My::MergeSort<int>::Sort(inputs, sizes, (size_t)3, output);

		ASSERT1(is_sorted(output.begin(), output.end()));

		for_each(output.begin(), output.end(), [&](int e) -> void {
			cout << "\t" << e;
		});

		cout << endl;
	});
}
