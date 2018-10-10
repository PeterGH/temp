#pragma once

#include <functional>
#include <sstream>
#include <stack>
#include <vector>
#include "BitSet.h"
#include "BinaryTree.h"
using namespace std;

namespace Test {

	// Implement a complete unordered binary tree.
	// Every level except the last one is fully filled.
	template<class T, template<class T> class N> class CompleteBinaryTree : public BinaryTree<T, N> {
	private:
		// Total number of nodes
		int count;

	public:
		CompleteBinaryTree(void) : BinaryTree(), count(0) {}
		virtual ~CompleteBinaryTree(void)
		{
			this->count = 0;
		}

		//         0
		//    1          2
		//  3   4     5     6
		// 7 8 9 10 11 12 13 14
		// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
		// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
		// Given node index I, its children are 2*I+1 and 2*I+2
		static int Height(int index)
		{
			unsigned int c = (unsigned int)(index + 1);
			int h = 0;
			while (c > 0) {
				h++;
				c = c >> 1;
			}

			return h;
		}

		// Encode the link from a node to its left child as 0.
		// Encode the link from a node to its right child as 1.
		// The the path from the root to and node can be represented with a bit set.
		static BitSet BrachCode(int index)
		{
			int h = Height(index);
			BitSet branch(h);
			unsigned int c = (unsigned int)index;
			while (c > 0) {
				if (c % 2 == 1) {
					// index is an odd number, meaning it is the left child of its parent
					// Encode it as 0
					branch.Reset(h - 1);
				} else {
					// index is an even number, meaning it is the right child of its parent
					// Encode it as 1
					branch.Set(h - 1);
				}

				c = (c - 1) >> 1;
				h--;
			}

			return branch;
		}

		void Insert(T & content)
		{
			N<T> * node = new N<T>(content);
			if (this->root == nullptr) {
				this->root = node;
				this->count = 1;
			} else {
				// this->count equals to the index for the new node
				int height = Height(this->count);
				BitSet branch = BrachCode(this->count);

				N<T> * current = this->root;
				for (int h = 1; h < height; h++) {
					if (!branch.Test(h)) {
						if (current->Left() != nullptr) current = (N<T>*)current->Left();
						else current->Left() = node;
					} else if (branch.Test(h)) {
						if (current->Right() != nullptr) current = (N<T>*)current->Right();
						else current->Right() = node;
					}
				}

				this->count++;
			}
		}

		int Height(void)
		{
			return BinaryTree<T, N>::Height();
		}
	};
}