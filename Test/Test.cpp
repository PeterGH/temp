// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Algorithm\Argument.h"
#include "..\Algorithm\TestSuite.h"
#include "ArrayTest.h"
#include "AVLTreeTest.h"
#include "BinaryIteratorTest.h"
#include "BinaryNodeTest.h"
#include "BinarySearchTest.h"
#include "BitSetTest.h"
#include "BreakStringTest.h"
#include "CircularSingleLinkListTest.h"
#include "CoinChangeTest.h"
#include "CoinSelectTest.h"
#include "ColumnSortTest.h"
#include "CountingSortTest.h"
#include "CountTest.h"
#include "DestructorTest.h"
#include "DynamicProgrammingTest.h"
#include "FiniteAutomationTest.h"
#include "GraphTest.h"
#include "GeometryTest.h"
#include "HeapTest.h"
#include "InsertionSortTest.h"
#include "KnapsackTest.h"
#include "LeetCodeTest.h"
#include "ListGraphTest.h"
#include "LongestCommonSubsequenceTest.h"
#include "LongestIncreasingSubsequenceTest.h"
#include "LRUCacheTest.h"
#include "MathTest.h"
#include "MatrixChainTest.h"
#include "MatrixGraphTest.h"
#include "MatrixTest.h"
#include "MazeTest.h"
#include "MergeSortTest.h"
#include "MongeTest.h"
#include "MRIntegerTest.h"
#include "NodeGraphTest.h"
#include "NodeTest.h"
#include "PalindromeTest.h"
#include "PartitionTest.h"
#include "PermutationTest.h"
#include "QueueTest.h"
#include "QuickSortTest.h"
#include "RandomTest.h"
#include "RedBlackTreeTest.h"
#include "RodCutTest.h"
#include "SearchTest.h"
#include "SeamCarvingTest.h"
#include "SingleLinkListTest.h"
#include "SortedCircularSingleLinkListTest.h"
#include "SortedSingleLinkListTest.h"
#include "SortTest.h"
#include "StackTest.h"
#include "StringTest.h"
#include "TestClassTest.h"
#include "UnitTimeTaskSchedulerTest.h"
#include "YoungTableauTest.h"

int main(int argc, char * argv[])
{
	if (argc < 2) {
		cout << "Test.exe -l" << endl;
		cout << "\tList all tests." << endl;
		cout << "Test.exe Test -l" << endl;
		cout << "\tList all test methods of a test. The test name can be a partial name." << endl;
		cout << "Test.exe *" << endl;
		cout << "\tRun all tests." << endl;
		cout << "Test.exe Test" << endl;
		cout << "\tRun a specified test. The test name can be a partial name." << endl;
		cout << "Test.exe Test Method" << endl;
		cout << "\tRun a specified test method of a specific test. Both the test name and method name can be partial names." << endl;
		return 0;
	}

	// Note argc >= 1, argv[0] == "Test.exe"
	Test::Argument<char> arg(argc, argv);

	Test::LogLevel level = arg.Has("v") ? Test::LogLevel::Verbose : Test::LogLevel::Error;
	Test::Log log(cout, level);
	Test::TestSuite suite(log);

	suite.Add(new ArrayTest(log));
	suite.Add(new AVLTreeTest(log));
	suite.Add(new BinaryIteratorTest(log));
	suite.Add(new BinaryNodeTest(log));
	suite.Add(new BinarySearchTest(log));
	suite.Add(new BitSetTest(log));
	suite.Add(new BreakStringTest(log));
	suite.Add(new CircularSingleLinkListTest(log));
	suite.Add(new CoinChangeTest(log));
	suite.Add(new CoinSelectTest(log));
	suite.Add(new ColumnSortTest(log));
	suite.Add(new CountingSortTest(log));
	suite.Add(new CountTest(log));
	suite.Add(new DestructorTest(log));
	suite.Add(new DynamicProgrammingTest(log));
	suite.Add(new FiniteAutomationTest(log));
	suite.Add(new GraphTest(log));
	suite.Add(new GeometryTest(log));
	suite.Add(new HeapTest(log));
	suite.Add(new InsertionSortTest(log));
	suite.Add(new KnapsackTest(log));
	suite.Add(new LeetCodeTest(log));
	suite.Add(new ListGraphTest(log));
	suite.Add(new LongestCommonSubsequenceTest(log));
	suite.Add(new LongestIncreasingSubsequenceTest(log));
	suite.Add(new LRUCacheTest(log));
	suite.Add(new MathTest(log));
	suite.Add(new MatrixChainTest(log));
	suite.Add(new MatrixGraphTest(log));
	suite.Add(new MatrixTest(log));
	suite.Add(new MazeTest(log));
	suite.Add(new MergeSortTest(log));
	suite.Add(new MongeTest(log));
	suite.Add(new MRIntegerTest(log));
	suite.Add(new NodeGraphTest(log));
	suite.Add(new NodeTest(log));
	suite.Add(new PalindromeTest(log));
	suite.Add(new PartitionTest(log));
	suite.Add(new PermutationTest(log));
	suite.Add(new QueueTest(log));
	suite.Add(new QuickSortTest(log));
	suite.Add(new RandomTest(log));
	suite.Add(new RedBlackTreeTest(log));
	suite.Add(new RodCutTest(log));
	suite.Add(new SearchTest(log));
	suite.Add(new SeamCarvingTest(log));
	suite.Add(new SingleLinkListTest(log));
	suite.Add(new SortedCircularSingleLinkListTest(log));
	suite.Add(new SortedSingleLinkListTest(log));
	suite.Add(new SortTest(log));
	suite.Add(new StackTest(log));
	suite.Add(new StringTest(log));
	suite.Add(new TestClassTest(log));
	suite.Add(new UnitTimeTaskSchedulerTest(log));
	suite.Add(new YoungTableauTest(log));
	
	if (arg.Has("l")) {
		if (arg.CountIndexedArgs() == 1) {
			cout << "Available tests are:" << endl;
			suite.List();
			return 0;
		} else if (arg.CountIndexedArgs() > 1) {
			suite.List(arg[1]);
			return 0;
		}
	} else if (arg.CountIndexedArgs() > 1) {
		if (arg[1] == "*") {
			suite.Run();
		} else if (arg.CountIndexedArgs() == 2) {
			suite.Run(arg[1]);
		} else {
			suite.Run(arg[1], arg[2]);
		}
	}

	suite.Report();
	return 0;
}

