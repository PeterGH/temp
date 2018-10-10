#include "WinUnit.h"
#include "Mask.h"
#include "Misc.h"
#include "MRNumber.h"
#include "LinkList.h"
#include "Permutation.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "BitonicSort.h"
#include "BSTNode.h"
#include "RodCutting.h"
#include "MatrixChain.h"
#include "LCS.h"
#include "MyArray.h"
#include "Palindrome.h"
#include "Handle.h"

//template __declspec(dllimport) void InsertionSort(double *, int);
//template __declspec(dllimport) void PrintArray(double *, int);

BEGIN_TEST(Mask)
{
	Mask m(40);
	m.Set(0);
	WIN_ASSERT_TRUE(m.IsSet(0));
	m.Toggle(0);
	WIN_ASSERT_TRUE(! m.IsSet(0));
	m.Set(40);
	WIN_ASSERT_TRUE(m.IsSet(40));
	m.Clear(40);
	WIN_ASSERT_TRUE(! m.IsSet(40));
	m.Set(32);
	WIN_ASSERT_TRUE(m.IsSet(32));
	m.Reset();
	WIN_ASSERT_TRUE(! m.IsSet(32));
	Mask m2;
	WIN_ASSERT_TRUE(! m2.IsSet(0));
	Mask m3 = m2;
	WIN_ASSERT_TRUE(! m3.IsSet(0));
	Mask m4 = m;
	WIN_ASSERT_TRUE(! m4.IsSet(32));
}
END_TEST

BEGIN_TEST(RemoveDupChar)
{
	char *c;
	c = NULL;
	int l = RemoveDupChar(c, 0);
	WIN_ASSERT_NULL(c);
	WIN_ASSERT_EQUAL(-1, l);

	char c1[] = "Test";
	l = RemoveDupChar(c1, 4);
	WIN_ASSERT_STRING_EQUAL("Test", c1);
	WIN_ASSERT_EQUAL(4, l);

	char c2[] = "TTeesstt";
	l = RemoveDupChar(c2, 8);
	WIN_ASSERT_STRING_EQUAL("Test", c2);
	WIN_ASSERT_EQUAL(4, l);

	char c3[] = "TestTest";
	l = RemoveDupChar(c3, 8);
	WIN_ASSERT_STRING_EQUAL("Test", c3);
	WIN_ASSERT_EQUAL(4, l);

	char c4[] = "";
	l = RemoveDupChar(c4, 0);
	WIN_ASSERT_STRING_EQUAL("", c4);
	WIN_ASSERT_ZERO(l);
}
END_TEST

BEGIN_TEST(MyStrStr)
{
	WIN_ASSERT_NULL(MyStrStr(NULL, "Test"));
	WIN_ASSERT_NULL(MyStrStr("Test", NULL));
	WIN_ASSERT_NULL(MyStrStr("", "Test"));
	WIN_ASSERT_NULL(MyStrStr("Test", ""));
	WIN_ASSERT_NULL(MyStrStr("Test1", "Test2"));
	WIN_ASSERT_NULL(MyStrStr("TestLong", "TestS"));
	WIN_ASSERT_NULL(MyStrStr("TestS", "TestLong"));
	char str1[] = "TestLong";
	WIN_ASSERT_EQUAL(0, MyStrStr(str1, "Test") - str1);
	char str2[] = "1TestLong";
	WIN_ASSERT_EQUAL(1, MyStrStr(str2, "Test") - str2);
	char str3[] = "12TestTest";
	WIN_ASSERT_EQUAL(2, MyStrStr(str3, "Test") - str3);
}
END_TEST

BEGIN_TEST(MRNumber)
{
	int c[] = {1, 3, 2};
	MRNumber ctr(c, 3);
	WIN_ASSERT_EQUAL(6, ctr.Max());
	WIN_ASSERT_EQUAL(0, ctr[0]);
	WIN_ASSERT_EQUAL(0, ctr[1]);
	WIN_ASSERT_EQUAL(0, ctr[2]);
	ctr ++;
	WIN_ASSERT_EQUAL(0, ctr[0]);
	WIN_ASSERT_EQUAL(1, ctr[1]);
	WIN_ASSERT_EQUAL(0, ctr[2]);
	++ ctr;
	WIN_ASSERT_EQUAL(0, ctr[0]);
	WIN_ASSERT_EQUAL(2, ctr[1]);
	WIN_ASSERT_EQUAL(0, ctr[2]);
	MRNumber ctr2 = ctr;
	WIN_ASSERT_EQUAL(0, ctr2[0]);
	WIN_ASSERT_EQUAL(2, ctr2[1]);
	WIN_ASSERT_EQUAL(0, ctr2[2]);
	ctr2 ++;
	++ ctr2;
	WIN_ASSERT_EQUAL(0, ctr2[0]);
	WIN_ASSERT_EQUAL(1, ctr2[1]);
	WIN_ASSERT_EQUAL(1, ctr2[2]);
	ctr2 ++;
	++ ctr2;
	WIN_ASSERT_EQUAL(0, ctr2[0]);
	WIN_ASSERT_EQUAL(0, ctr2[1]);
	WIN_ASSERT_EQUAL(0, ctr2[2]);
	ctr2 ++;
	++ ctr2;
	WIN_ASSERT_EQUAL(0, ctr2[0]);
	WIN_ASSERT_EQUAL(2, ctr2[1]);
	WIN_ASSERT_EQUAL(0, ctr2[2]);
	ctr2.Reset();
	WIN_ASSERT_EQUAL(0, ctr2[0]);
	WIN_ASSERT_EQUAL(0, ctr2[1]);
	WIN_ASSERT_EQUAL(0, ctr2[2]);	
}
END_TEST


BEGIN_TEST(SingleLinkList)
{
	SingleLinkList<int> list;
	cout << list;
	cout << list.Middle() << endl;
	list.Reverse();
	cout << list;
	cout << list.Middle() << endl;
	list.Insert(0);
	cout << list;
	cout << list.Middle() << endl;
	list.Reverse();
	cout << list;
	cout << list.Middle() << endl;
	list.Insert(1);
	cout << list;
	cout << list.Middle() << endl;
	list.Reverse();
	cout << list;
	cout << list.Middle() << endl;
	list.Insert(2);
	cout << list;
	cout << list.Middle() << endl;
	list.Reverse();
	cout << list;
	cout << list.Middle() << endl;
	list.Insert(3);
	cout << list;
	cout << list.Middle() << endl;
	list.Reverse();
	cout << list;
	cout << list.Middle() << endl;
	list.Insert(4);
	cout << list;
	cout << list.Middle() << endl;
	list.Reverse();
	cout << list;
	cout << list.Middle() << endl;
	list.Insert(5);
	cout << list;
	cout << list.Middle() << endl;
	list.Reverse();
	cout << list;
	cout << list.Middle() << endl;
}
END_TEST

BEGIN_TEST(Permutation)
{
	int data[] = {0, 1, 2, 3};
	Permutation<int> perm(data, 4);
	cout << "Ordered:" << endl;
	for (int i = 0; i < perm.Max(); i ++) {
		perm.Next();
		cout << perm;
	}
	cout << "Random:" << endl;
	for (int i = 0; i < perm.Max(); i ++) {
		perm.Random();
		cout << perm;
	}
}
END_TEST


BEGIN_TEST(Sort)
{
	int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	int L = sizeof(I1)/sizeof(I1[0]);
	cout << "Original:\t";
	PrintArray<int>(I1, L);	
	InsertionSort<int>(I1, L);
	cout << "InsertionSort:\t";
	PrintArray<int>(I1, L);
	
	int I2[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	InsertionSortRecursively<int>(I2, L);
	cout << "InsertionSortRecursively:\t";
	PrintArray<int>(I2, L);
	WIN_ASSERT_TRUE(CompareArray(I1, I2, L));
	
	int I3[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	SelectionSort<int>(I3, L);
	cout << "SelectionSort:\t";
	PrintArray<int>(I3, L);
	WIN_ASSERT_TRUE(CompareArray(I1, I3, L));

	int I4[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	MergeSort<int>(I4, 0, L - 1);
	cout << "MergeSort:\t";
	PrintArray<int>(I4, L);
	WIN_ASSERT_TRUE(CompareArray(I1, I4, L));

	int I5[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	HeapSort<int> ihs(I5, L);
	ihs.Sort();
	cout << "HeapSort:\t";
	PrintArray<int>(I5, L);
	WIN_ASSERT_TRUE(CompareArray(I1, I5, L));

	int I6[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	QuickSort<int>::Sort(I6, L);
	cout << "QuickSort:\t";
	PrintArray<int>(I6, L);
	WIN_ASSERT_TRUE(CompareArray(I1, I6, L));

	int I7[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	QuickSort<int>::ParallelSort(I7, L);
	cout << "QuickSort[Parallel]:\t";
	PrintArray<int>(I7, L);
	WIN_ASSERT_TRUE(CompareArray(I1, I7, L));

	double F1[] ={3.2,43.334,42.313,1.00,3.20,3556.8586,7.345,34.85,8.23,8769.234,96656532.00,1,445,35.1,64};
	L = sizeof(F1)/sizeof(F1[0]);
	cout << "Original:\t";
	PrintArray<double>(F1, L);
	InsertionSort<double>(F1, L);
	cout << "InsertionSort:\t";
	PrintArray<double>(F1, L);
	
	double F2[] ={3.2,43.334,42.313,1.00,3.20,3556.8586,7.345,34.85,8.23,8769.234,96656532.00,1,445,35.1,64};
	InsertionSortRecursively<double>(F2, L);
	cout << "InsertionSortRecursively:\t";
	PrintArray<double>(F2, L);
	WIN_ASSERT_TRUE(CompareArray(F1, F2, L));

	double F3[] ={3.2,43.334,42.313,1.00,3.20,3556.8586,7.345,34.85,8.23,8769.234,96656532.00,1,445,35.1,64};
	SelectionSort<double>(F3, L);
	cout << "SelectionSort:\t";
	PrintArray<double>(F3, L);
	WIN_ASSERT_TRUE(CompareArray(F1, F3, L));

	double F4[] ={3.2,43.334,42.313,1.00,3.20,3556.8586,7.345,34.85,8.23,8769.234,96656532.00,1,445,35.1,64};
	MergeSort<double>(F4, 0, L - 1);
	cout << "MergeSort:\t";
	PrintArray<double>(F4, L);
	WIN_ASSERT_TRUE(CompareArray(F1, F4, L));

	double F5[] ={3.2,43.334,42.313,1.00,3.20,3556.8586,7.345,34.85,8.23,8769.234,96656532.00,1,445,35.1,64};
	HeapSort<double> fhs(F5, L);
	fhs.Sort();
	cout << "HeapSort:\t";
	PrintArray<double>(F5, L);
	WIN_ASSERT_TRUE(CompareArray(F1, F5, L));

	double F6[] ={3.2,43.334,42.313,1.00,3.20,3556.8586,7.345,34.85,8.23,8769.234,96656532.00,1,445,35.1,64};
	QuickSort<double>::Sort(F6, L);
	cout << "QuickSort:\t";
	PrintArray<double>(F6, L);
	WIN_ASSERT_TRUE(CompareArray(F1, F6, L));

	double F7[] ={3.2,43.334,42.313,1.00,3.20,3556.8586,7.345,34.85,8.23,8769.234,96656532.00,1,445,35.1,64};
	QuickSort<double>::ParallelSort(F7, L);
	cout << "QuickSort[Parallel]:\t";
	PrintArray<double>(F7, L);
	WIN_ASSERT_TRUE(CompareArray(F1, F7, L));

}
END_TEST

BEGIN_TEST(HeapSort)
{
	int I[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	int L = sizeof(I)/sizeof(I[0]);
	HeapSort<int> * hs = new HeapSort<int>(I, L);
	hs->Print(cout);
	hs->Sort();
	hs->Print(cout);
}
END_TEST

BEGIN_TEST(BitonicSort)
{
	//int I[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	int I[] = {2, 1, 0};
	int L = sizeof(I)/sizeof(I[0]);
	BitonicSort<int>::Sort(I, L);
}
END_TEST

BEGIN_TEST(Search)
{
	int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	int L = sizeof(I1)/sizeof(I1[0]);
	WIN_ASSERT_EQUAL(0, LinearSearch(3, I1, L));
	WIN_ASSERT_EQUAL(1, LinearSearch(43, I1, L));
	WIN_ASSERT_EQUAL(L - 1, LinearSearch(64, I1, L));
	WIN_ASSERT_EQUAL(-1, LinearSearch(222, I1, L));
	
	int I2[] = {1, 1, 3, 3, 7, 8, 34, 35, 42, 43, 64, 445, 3556, 8769, 96656532};
	L = sizeof(I2)/sizeof(I2[0]);
	WIN_ASSERT_EQUAL(0, BinarySearch(1, I2, 1));
	WIN_ASSERT_EQUAL(0, BinarySearchRecursively(1, I2, 0, 1));
	WIN_ASSERT_EQUAL(0, BinarySearch(1, I2, L));
	WIN_ASSERT_EQUAL(0, BinarySearchRecursively(1, I2, 0, L - 1));
	WIN_ASSERT_NOT_EQUAL(1, BinarySearch(1, I2, L));
	WIN_ASSERT_NOT_EQUAL(1, BinarySearchRecursively(1, I2, 0, L - 1));
	WIN_ASSERT_EQUAL(2, BinarySearch(3, I2, L));
	WIN_ASSERT_EQUAL(2, BinarySearchRecursively(3, I2, 0, L - 1));
	WIN_ASSERT_NOT_EQUAL(3, BinarySearch(3, I2, L));
	WIN_ASSERT_NOT_EQUAL(3, BinarySearchRecursively(3, I2, 0, L - 1));
	WIN_ASSERT_EQUAL(9, BinarySearch(43, I2, L));
	WIN_ASSERT_EQUAL(9, BinarySearchRecursively(43, I2, 0, L - 1));
	WIN_ASSERT_EQUAL(L - 1, BinarySearch(96656532, I2, L));
	WIN_ASSERT_EQUAL(L - 1, BinarySearchRecursively(96656532, I2, 0, L - 1));
	WIN_ASSERT_EQUAL(-1, BinarySearch(222, I2, L));
	WIN_ASSERT_EQUAL(-1, BinarySearchRecursively(222, I2, 0, L - 1));
}
END_TEST

BEGIN_TEST(BinarySearchTree)
{
	int I[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64,70};
	int L = sizeof(I)/sizeof(I[0]);

	BinarySearchTree<int> bst;
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

}
END_TEST

BEGIN_TEST(BSTNode)
{
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
	BSTNode<int> * root2 = new BSTNode<int>(I[0]);
	for (int i = 1; i < L; i ++) {
		root2->Insert(I[i]);
	}
	cout << "root2:";	
	root2->PrintTree();
	cout << endl;
	
	cout << "Min:" ;
	root2->Min()->PrintContent();
	cout << endl;

	cout << "Max:";
	root2->Max()->PrintContent();
	cout << endl;
		
	cout << "PreOrder: ";
	root2->PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });	
	cout << endl;
	cout << "InOrder: ";
	root2->InOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Successor of 34:";
	root2->Successor(root2->Search(34))->PrintContent();
	cout << endl;
	cout << "Predecessor of 42:";
	root2->Predecessor(root2->Search(42))->PrintContent();
	cout << endl;
	cout << "PostOrder: ";
	root2->PostOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;

	cout << "Empty()";
	root2->Empty();
	cout << endl;
	
	cout << "PreOrder: ";
	root2->PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });	
	cout << endl;
	cout << "InOrder: ";
	root2->InOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "PostOrder: ";
	root2->PostOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	
	delete root2;

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
	BSTNode<int> root3(I[0]);
	for (int i = 1; i < L; i ++) {
		root3.Insert(I[i]);
	}
	cout << "root3:";	
	root3.PrintTree();
	cout << endl;

	cout << "PreOrder: ";
	root3.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete " << root3.Min()->Content() << endl;
	root3.Delete(root3.Min());
	cout << "PreOrder: ";
	root3.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete " << root3.Min()->Content() << endl;
	root3.Delete(root3.Min());
	cout << "PreOrder: ";
	root3.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete " << root3.Max()->Content() << endl;
	root3.Delete(root3.Max());
	cout << "PreOrder: ";
	root3.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
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
	BSTNode<int> root4(I[0]);
	for (int i = 1; i < L; i ++) {
		root4.Insert(I[i]);
	}
	cout << "root4:";	
	root4.PrintTree();
	cout << endl;

	cout << "PreOrder: ";
	root4.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete 7" << endl;
	root4.Delete(root4.Search(7));
	cout << "PreOrder: ";
	root4.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete 42" << endl;
	root4.Delete(root4.Search(42));
	cout << "PreOrder: ";
	root4.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete 3556" << endl;
	root4.Delete(root4.Search(3556));
	cout << "PreOrder: ";
	root4.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete 43" << endl;
	root4.Delete(root4.Search(43));
	cout << "PreOrder: ";
	root4.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
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
	BSTNode<int> root5(I[0]);
	for (int i = 1; i < L; i ++) {
		root5.Insert(I[i]);
	}
	cout << "root5:";	
	root5.PrintTree();
	cout << endl;

	cout << "PreOrder: ";
	root5.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
	cout << "Delete 43" << endl;
	root5.Delete(root5.Search(43));
	cout << "PreOrder: ";
	root5.PreOrderWalk([](BSTNode<int> * x){ x->PrintContent(); });
	cout << endl;
}
END_TEST

BEGIN_TEST(FindPositionToInsert)
{
	int I[] = {1, 1, 3, 3, 7, 8, 34, 35, 42, 43, 64, 445, 3556, 8769, 96656532};
	int L = sizeof(I)/sizeof(I[0]);

	WIN_ASSERT_EQUAL(-1, FindPositionToInsert(0, I, 1));
	WIN_ASSERT_EQUAL(0, FindPositionToInsert(1, I, 1));
	WIN_ASSERT_EQUAL(0, FindPositionToInsert(2, I, 1));

	WIN_ASSERT_EQUAL(-1, FindPositionToInsert(0, I, 2));
	WIN_ASSERT_EQUAL(1, FindPositionToInsert(1, I, 2));
	WIN_ASSERT_EQUAL(1, FindPositionToInsert(2, I, 2));

	WIN_ASSERT_EQUAL(-1, FindPositionToInsert(0, I, 3));
	WIN_ASSERT_EQUAL(1, FindPositionToInsert(1, I, 3));
	WIN_ASSERT_EQUAL(1, FindPositionToInsert(2, I, 3));
	WIN_ASSERT_EQUAL(2, FindPositionToInsert(3, I, 3));
	WIN_ASSERT_EQUAL(2, FindPositionToInsert(4, I, 3));

	WIN_ASSERT_EQUAL(-1, FindPositionToInsert(0, I, L));
	WIN_ASSERT_EQUAL(1, FindPositionToInsert(1, I, L));
	WIN_ASSERT_EQUAL(3, FindPositionToInsert(3, I, L));
	WIN_ASSERT_EQUAL(9, FindPositionToInsert(43, I, L));
	WIN_ASSERT_EQUAL(9, FindPositionToInsert(44, I, L));
	WIN_ASSERT_EQUAL(L - 1, FindPositionToInsert(96656532, I, L));
	WIN_ASSERT_EQUAL(L - 1, FindPositionToInsert(96656533, I, L));	
}
END_TEST

BEGIN_TEST(Min)
{
	int data[] ={3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
	int length = sizeof(data)/sizeof(data[0]);

	WIN_ASSERT_EQUAL(3, Min(data, length));
}
END_TEST

BEGIN_TEST(Merge)
{
	int data1[] = {1, 3, 5, 2, 4, 6};
	PrintArray(data1, 6);
	Merge(data1, 0, 3, 5);
	PrintArray(data1, 6);
	
	int data2[] = {1, 2, 3, 4, 5, 6};
	PrintArray(data2, 6);
	Merge(data2, 0, 3, 5);
	PrintArray(data2, 6);
	
	int data3[] = {7, 2, 3, 4, 5, 6};
	PrintArray(data3, 6);
	Merge(data3, 0, 1, 5);
	PrintArray(data3, 6);
	
	int data4[] = {1, 2, 3, 4, 5, 0};
	PrintArray(data4, 6);
	Merge(data4, 0, 5, 5);
	PrintArray(data4, 6);

	int data5[] = {1, 3, 5, 1, 3, 5};
	PrintArray(data5, 6);
	Merge(data5, 0, 3, 5);
	PrintArray(data5, 6);

	int data6[] = {1, 1, 1, 1, 1, 1};
	PrintArray(data6, 6);
	Merge(data6, 0, 2, 5);
	PrintArray(data6, 6);	
}
END_TEST

BEGIN_TEST(MaximumSubArray)
{
	int A1[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int L = sizeof(A1)/sizeof(A1[0]);
	int l, r;
	long long sum;
	PrintArray(A1, L);
	MaximumSubArray(A1, L, l, r, sum);
	cout << "A1[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(7, l);
	WIN_ASSERT_EQUAL(10, r);
	WIN_ASSERT_EQUAL(43, sum);

	PrintArray(A1, 1);
	MaximumSubArray(A1, 1, l, r, sum);
	cout << "A1[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(0, l);
	WIN_ASSERT_EQUAL(0, r);
	WIN_ASSERT_EQUAL(13, sum);

	int A2[] = {13, 3, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 4, 7};
	PrintArray(A2, L);
	MaximumSubArray(A2, L, l, r, sum);
	cout << "A2[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(0, l);
	WIN_ASSERT_EQUAL(L - 1, r);
	WIN_ASSERT_EQUAL(213, sum);

	PrintArray(A2, 1);
	MaximumSubArray(A2, 1, l, r, sum);
	cout << "A2[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(0, l);
	WIN_ASSERT_EQUAL(0, r);
	WIN_ASSERT_EQUAL(13, sum);

	int A3[] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
	PrintArray(A3, L);
	MaximumSubArray(A3, L, l, r, sum);
	cout << "A3[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(1, l);
	WIN_ASSERT_EQUAL(1, r);
	WIN_ASSERT_EQUAL(-3, sum);

	PrintArray(A3, 1);
	MaximumSubArray(A3, 1, l, r, sum);
	cout << "A3[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(0, l);
	WIN_ASSERT_EQUAL(0, r);
	WIN_ASSERT_EQUAL(-13, sum);

	int A4[] = {0, 0, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
	PrintArray(A4, L);
	MaximumSubArray(A4, L, l, r, sum);
	cout << "A4[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(0, l);
	WIN_ASSERT_EQUAL(0, r);
	WIN_ASSERT_EQUAL(0, sum);

	PrintArray(A4, 2);
	MaximumSubArray(A4, 1, l, r, sum);
	cout << "A4[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(0, l);
	WIN_ASSERT_EQUAL(0, r);
	WIN_ASSERT_EQUAL(0, sum);

	int A5[] = {0, 0, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 0, 0};
	PrintArray(A5, L);
	MaximumSubArray(A5, L, l, r, sum);
	cout << "A5[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(2, l);
	WIN_ASSERT_EQUAL(13, r);
	WIN_ASSERT_EQUAL(186, sum);

	PrintArray(A5, 3);
	MaximumSubArray(A5, 1, l, r, sum);
	cout << "A5[" << l << ".." << r << "] = " << sum << endl;
	WIN_ASSERT_EQUAL(0, l);
	WIN_ASSERT_EQUAL(0, r);
	WIN_ASSERT_EQUAL(0, sum);

}
END_TEST

BEGIN_TEST(RodCutting)
{
	vector<double> utility;
	utility.push_back(1);
	utility.push_back(5);
	utility.push_back(8);
	utility.push_back(9);
	utility.push_back(10);
	utility.push_back(17);
	utility.push_back(17);
	utility.push_back(20);
	utility.push_back(24);
	utility.push_back(30);

	for (unsigned int i = 0; i < utility.size(); i ++) {
		cout << utility[i] << " ";
	}
	cout << endl;

	vector<double> maxUtility(utility.size());
	vector<int> firstCut(utility.size());

	RodCutting::ComputeFirstCut(utility, maxUtility, firstCut);

	for (unsigned int i = 0; i < utility.size(); i ++) {
		cout << i << "\t" << utility[i] << "\t" << maxUtility[i] << "\t" << firstCut[i] << endl;
	}

	vector<double> utility2;
	utility2.push_back(1);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(5);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(8);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(9);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(10);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(17);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(17);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(20);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(24);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
	utility2.push_back(30);
	cout << utility2.size() - 1 << ": ";
	RodCutting::PrintResult(utility2);
}
END_TEST

BEGIN_TEST(MatrixChain)
{
	int dimension[7] = {30, 35, 15, 5, 10, 20, 25};
	int count = 7;
	int cost[6][6];
	int split[6][6];

	memset(cost, 0, 36*sizeof(int));
	memset(split, 0, 36*sizeof(int));

	MatrixChain::ComputeCostTable(dimension, count, &cost[0][0], &split[0][0]);
	
	for (int i = 0; i < 6; i ++) {
		cout << "\t" << i;
	}
	cout << endl;

	for (int i = 0; i < 6; i ++) {
		cout << i;
		for (int j = 0; j < 6; j ++) {
			cout << "\t" << cost[i][j];
		}
		cout << endl;
	}

	cout << endl;
	
	for (int i = 0; i < 6; i ++) {
		cout << i;
		for (int j = 0; j < 6; j ++) {
			cout << "\t" << split[i][j];
		}
		cout << endl;
	}
}
END_TEST

BEGIN_TEST(LCS)
{
	string x = "ABCBDAB";
	string y = "BDCABA";

	LCS::PrintLCS(x, y);
}
END_TEST

BEGIN_TEST(Array1D)
{
	Array1D<int> A(4);

	A.Print();

	A.SetValue(1, 101);
	
	A.Print();

	int v = A.GetValue(1);

	WIN_ASSERT_EQUAL(101, v);

	A[3] = 303;

	A.Print();

	v = A[3];

	WIN_ASSERT_EQUAL(303, v);
}
END_TEST

BEGIN_TEST(Array2D)
{
	Array2D<int> A(3, 4);

	A.Print();

	A.SetValue(1, 2, 101);
	
	A.Print();

	int v = A.GetValue(1, 2);

	WIN_ASSERT_EQUAL(101, v);

	//*A.Element(2, 3) = 202;
	A.Element(2, 3) = 202;

	A.Print();

	//v = *A.Element(2, 3);
	v = A.Element(2, 3);

	WIN_ASSERT_EQUAL(202, v);
}
END_TEST

BEGIN_TEST(Palindrome)
{
	string s = "character";
	string t;
	string a;
	cout << "Input: " << s << endl;
	Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;

	s = "racecar";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;

	s = "raceecar";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;

	s = "ra";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;

	s = "rac";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;
}
END_TEST

//extern template class Handle<int>;

BEGIN_TEST(Handle)
{
	Handle<int> h;
	h.Set(10);
	int v = h.Get();
	cout << v << endl;
	WIN_ASSERT_EQUAL(10, v);
}
END_TEST