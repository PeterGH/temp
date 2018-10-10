#include "RedBlackTreeTest.h"


void RedBlackTreeTest::Init(void)
{
	Add("Insert", [&](){
		int I[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64,70};
		int L = sizeof(I)/sizeof(I[0]);

		//           7(B)
		//          /    \
		//         /      \
		//        /        \
		//       /          \
		//     3(B)         64(B)
		//    / \          /    \
		//   /   \        /      \
		// 1(B)  3(B)  42(R)     3556(R)
		//   \         /   \      /    \
		//   1(R)    34(B) 43(B) 445(B) 8769(B)
		//           / \          /         \
		//         8(R) 35(R)    70(R)      96656532(R)
		My::RedBlackTree<int> * tree = new My::RedBlackTree<int>();
		for (int i = 0; i < L; i ++) {
			tree->Insert(I[i]);
			cout << i << ": " << I[i] << ": ";
			tree->Print();
			cout << endl;
		}
		cout << "It is " << (tree->Verify() ? "" : "not ") << "a RedBlackTree." << endl;
		cout << "Its BlackHeight is " << tree->BlackHeight() << "." << endl;
		delete tree;
	});
}

