#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include "BinaryNode.h"
using namespace std;
namespace Test {
	class Math {
	public:
		Math();
		~Math();

		
		
		__declspec(dllexport) static unsigned long long BinaryTreeSumBranches(BinaryNode<unsigned int> * node);
		__declspec(dllexport) static long long BinaryTreeMaxPathSum(BinaryNode<int> * root, vector<BinaryNode<int> *> & path);

		class Tree {
		public:
			//         0
			//    1          2
			//  3   4     5     6
			// 7 8 9 10 11 12 13 14
			// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
			// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
			__declspec(dllexport) static unsigned int Parent(unsigned int i) { return (i - 1) >> 1; }
			__declspec(dllexport) static unsigned int Left(unsigned int i) { return (i << 1) + 1; }
			__declspec(dllexport) static unsigned int Right(unsigned int i) { return (i << 1) + 2; }
			// Get the height of binary tree given count of nodes
			__declspec(dllexport) static unsigned int Height(unsigned int count);
			// d-ary heap
			//                                                  0
			//                   1                              2                    ...          d
			// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
			// (d^2+d+1) (d^2+d+2) ...
			// ......
			// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
			// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]
			// Return the index of the parent of node i
			__declspec(dllexport) static unsigned int Parent(unsigned int i, unsigned int d) { return (i - 1) / d; }
			// Return the index of the j-th child of node i. j is zero based.
			__declspec(dllexport) static unsigned int Child(unsigned int i, unsigned int j, unsigned int d) { return i * d + j + 1; }
			// Get the height of d-ary tree given count of nodes
			__declspec(dllexport) static unsigned int Height(unsigned int count, unsigned int d);
		};
	};

}

