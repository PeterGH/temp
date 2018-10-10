#include "BinarySearchTreeTest.h"

void BinarySearchTreeTest::Init()
{
	Add("Node", [&](){
		int I[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64,70};
		int L = sizeof(I)/sizeof(I[0]);

		//    3
		//   /  \
		//  /    \
		// 1      43
		//  \    /  \
		//   1  42  3556
		//     /     /  \
		//    3    445 8769
		//     \   /      \
		//      7 64    96656532
		//       \  \
		//       34  70
		//       / \
		//      8  35
		My::BinarySearchTree<int>::Node * root = new My::BinarySearchTree<int>::Node(I[0]);
		for (int i = 1; i < L; i ++) {
			My::BinarySearchTree<int>::Node::Insert(root, I[i]);
		}
		cout << "root:";
		My::BinarySearchTree<int>::Node::PrintTree(root);
		cout << endl;

		cout << "Min:" ;
		root->Min()->PrintContent();
		cout << endl;

		cout << "Max:";
		root->Max()->PrintContent();
		cout << endl;

		cout << "PreOrder: ";
		root->PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });	
		cout << endl;
		cout << "InOrder: ";
		root->InOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Successor of 34:";
		root->Successor(root->Search(34))->PrintContent();
		cout << endl;
		cout << "Predecessor of 42:";
		root->Predecessor(root->Search(42))->PrintContent();
		cout << endl;
		cout << "PostOrder: ";
		root->PostOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;

		cout << "Empty()";
		root->Empty();
		cout << endl;

		cout << "PreOrder: ";
		root->PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });	
		cout << endl;
		cout << "InOrder: ";
		root->InOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "PostOrder: ";
		root->PostOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;

		root->Empty();
		delete root;

	});

	Add("Node::Delete", [&]() {
		int I[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64,70};
		int L = sizeof(I)/sizeof(I[0]);

		//    3
		//   /  \
		//  /    \
		// 1      43
		//  \    /  \
		//   1  42  3556
		//     /     /  \
		//    3    445 8769
		//     \   /      \
		//      7 64    96656532
		//       \  \
		//       34  70
		//       / \
		//      8  35
		My::BinarySearchTree<int>::Node root(I[0]);
		for (int i = 1; i < L; i ++) {
			root.Insert(I[i]);
		}
		cout << "root:";	
		root.PrintTree();
		cout << endl;

		cout << "PreOrder: ";
		root.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete min " << root.Min()->Content() << endl;
		root.Delete(root.Min());
		cout << "PreOrder: ";
		root.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete min " << root.Min()->Content() << endl;
		root.Delete(root.Min());
		cout << "PreOrder: ";
		root.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete max " << root.Max()->Content() << endl;
		root.Delete(root.Max());
		cout << "PreOrder: ";
		root.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;

		//    3
		//   /  \
		//  /    \
		// 1      43
		//  \    /  \
		//   1  42  3556
		//     /     /  \
		//    3    445 8769
		//     \   /      \
		//      7 64    96656532
		//       \  \
		//       34  70
		//       / \
		//      8  35
		My::BinarySearchTree<int>::Node root2(I[0]);
		for (int i = 1; i < L; i ++) {
			root2.Insert(I[i]);
		}
		cout << "root2:";	
		root2.PrintTree();
		cout << endl;

		cout << "PreOrder: ";
		root2.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete 7" << endl;
		root2.Delete(root2.Search(7));
		cout << "PreOrder: ";
		root2.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete 42" << endl;
		root2.Delete(root2.Search(42));
		cout << "PreOrder: ";
		root2.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete 3556" << endl;
		root2.Delete(root2.Search(3556));
		cout << "PreOrder: ";
		root2.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete 43" << endl;
		root2.Delete(root2.Search(43));
		cout << "PreOrder: ";
		root2.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;

		//    3
		//   /  \
		//  /    \
		// 1      43
		//  \    /  \
		//   1  42  3556
		//     /     /  \
		//    3    445 8769
		//     \   /      \
		//      7 64    96656532
		//       \  \
		//       34  70
		//       / \
		//      8  35
		My::BinarySearchTree<int>::Node root3(I[0]);
		for (int i = 1; i < L; i ++) {
			root3.Insert(I[i]);
		}
		cout << "root3:";	
		root3.PrintTree();
		cout << endl;

		cout << "PreOrder: ";
		root3.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
		cout << "Delete 43" << endl;
		root3.Delete(root3.Search(43));
		cout << "PreOrder: ";
		root3.PreOrderWalk([](My::BinarySearchTree<int>::Node * x){ x->PrintContent(); });
		cout << endl;
	});

	Add("BinarySearchTree", [&](){
		int I[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64,70};
		int L = sizeof(I)/sizeof(I[0]);

		My::BinarySearchTree<int> bst;
		for (int i = 0; i < L; i ++) {
			bst.Insert(I[i]);
		}

		cout << "Print:";
		bst.Print();
		cout << endl;

		cout << "Min:" << bst.Min() << endl;

		cout << "Max:" << bst.Max() << endl;

		cout << "PreOrder: ";
		bst.PreOrderWalk([](int x){ cout << x << " "; });	
		cout << endl;
		cout << "InOrder: ";
		bst.InOrderWalk([](int x){ cout << x << " "; });
		cout << endl;
		cout << "Successor of 34:" << bst.Successor(34) << endl;
		cout << "Predecessor of 42:" << bst.Predecessor(42) << endl;
		cout << "PostOrder: ";
		bst.PostOrderWalk([](int x){ cout << x << " "; });
		cout << endl;

		cout << "Empty" << endl;
		bst.Empty();

		cout << "PreOrder: ";
		bst.PreOrderWalk([](int x){ cout << x << " "; });	
		cout << endl;
		cout << "InOrder: ";
		bst.InOrderWalk([](int x){ cout << x << " "; });
		cout << endl;
		cout << "PostOrder: ";
		bst.PostOrderWalk([](int x){ cout << x << " "; });
		cout << endl;
	});
}