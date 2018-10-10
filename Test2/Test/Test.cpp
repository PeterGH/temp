// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Algorithm\Argument.h"
#include "ArrayTest.h"
#include "BinarySearchTreeTest.h"
#include "BinaryTreeTest.h"
#include "CircularLinkListTest.h"
#include "CountingSortTest.h"
#include "HeapDTest.h"
#include "HeapTest.h"
#include "KnapsackTest.h"
#include "LongestCommonSubsequenceTest.h"
#include "MaskTest.h"
#include "MatrixChainTest.h"
#include "MergeSortTest.h"
#include "MinMaxTest.h"
#include "MRIntegerTest.h"
#include "PalindromeTest.h"
#include "PermutationTest.h"
#include "PowerSetTest.h"
#include "PriorityQueueTest.h"
#include "QuickSortTest.h"
#include "RandomTest.h"
#include "RedBlackTreeTest.h"
#include "RodCuttingTest.h"
#include "SetTest.h"
#include "SingleLinkListTest.h"
#include "SmartPointerTest.h"
#include "StringTest.h"
#include "VectorTest.h"
#include "YoungTableauTest.h"

int main(int argc, char * argv[])
{
	My::Argument<char> arg(argc, argv);
	My::TestSuite suite;
	suite.Add(new ArrayTest());
	suite.Add(new BinarySearchTreeTest());
	suite.Add(new BinaryTreeTest());
	suite.Add(new CircularLinkListTest());
	suite.Add(new CountingSortTest());
	suite.Add(new HeapDTest());
	suite.Add(new HeapTest());
	suite.Add(new KnapsackTest());
	suite.Add(new LongestCommonSubsequenceTest());
	suite.Add(new MaskTest());
	suite.Add(new MatrixChainTest());
	suite.Add(new MergeSortTest());
	suite.Add(new MinMaxTest());
	suite.Add(new MRIntegerTest());
	suite.Add(new PalindromeTest());
	suite.Add(new PermutationTest());
	suite.Add(new PowerSetTest());
	suite.Add(new PriorityQueueTest());
	suite.Add(new QuickSortTest());
	suite.Add(new RandomTest());
	suite.Add(new RedBlackTreeTest());
	suite.Add(new RodCuttingTest());
	suite.Add(new SetTest());
	suite.Add(new SingleLinkListTest());
	suite.Add(new SmartPointerTest());
	suite.Add(new StringTest());
	suite.Add(new VectorTest());
	suite.Add(new YoungTableauTest());

	if (arg.Has("l")) {
		cout << "Available tests are:" << endl;
		suite.List();
		return 0;
	}

	if (arg.CountIndexedArgs() > 1) {
		suite.Run(arg[1]);
	} else {
		suite.Run();
	}

	suite.Report();
	return 0;
}

