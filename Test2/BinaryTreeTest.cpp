#include "BinaryTreeTest.h"

void BinaryTreeTest::Init(void)
{
	Add("Insert", [&](){
		My::BinaryTree<int> tree;

		for (int i = 0; i < 10; i++) {
			tree.Insert(i);
		}

		tree.Print();
		cout << endl;
	});
}
