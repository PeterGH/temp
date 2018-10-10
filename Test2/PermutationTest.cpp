#include "PermutationTest.h"
#include "..\Algorithm\Permutation.h"

void PermutationTest::Init(void)
{
	Add("Permutation", [&]() {
		int data[] = {0, 1, 2, 3};
		My::Permutation<int> perm(data, 4);
		cout << "Ordered:" << endl;
		for (int i = 0; i < perm.Max(); i ++) {
			perm.Next();
			perm.Print();
		}
		cout << "Random:" << endl;
		for (int i = 0; i < perm.Max(); i ++) {
			perm.Random();
			perm.Print();
		}
	});
}