#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <ppl.h>
#include <queue>
#include <stack>
#include <vector>
#include "Node.h"
#include "SingleNode.h"
#include "String.h"
#include "UpperTriangularMatrix.h"
using namespace concurrency;
using namespace std;

namespace Test {
	template<class T> class BinaryNode : public Node<T> {
	public:
		BinaryNode(const T & v) : Node<T>(v, 2) {}
		virtual ~BinaryNode(void) {}

		// Delete a rooted binary tree
		static void DeleteTree(BinaryNode * node);
		virtual void DeleteTree(void) { DeleteTree(this); }

		// Create a random binary tree
		// Return nullptr if input is empty
		static BinaryNode * RandomTreeFromPreOrder(vector<T> & values);
		static BinaryNode * RandomTreeFromInOrder(vector<T> & values);
		static BinaryNode * RandomTreeFromPostOrder(vector<T> & values);
		static BinaryNode * RandomTree(vector<T> & values);
		// May return nullptr
		static BinaryNode * RandomTree(size_t maxSize);

		// Create all unique binary trees that can be built with a sequence
		static vector<BinaryNode *> UniqueTreesFromPreOrder(vector<T> & values);
		static vector<BinaryNode *> UniqueTreesFromInOrder(vector<T> & values);
		static vector<BinaryNode *> UniqueTreesFromPostOrder(vector<T> & values);

		// Given a pre-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
		// count unique binary trees that can be built with the n numbers
		static unsigned long long CountUniqueTreesFromPreOrderOfSize(int n);
		// Given an in-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
		// count unique binary trees that can be built with the n numbers
		static unsigned long long CountUniqueTreesFromInOrderOfSize(int n);
		// Given a post-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
		// count unique binary trees that can be built with the n numbers
		static unsigned long long CountUniqueTreesFromPostOrderOfSize(int n);

		// Create a complete binary tree
		static BinaryNode * ToCompleteTree(vector<T> & values);
		// Fill missing nodes to make a complete tree
		static BinaryNode * FillToComplete(BinaryNode * node, vector<T> & values);
		// May return nullptr
		static BinaryNode * RandomCompleteTree(size_t maxSize);
		static bool IsCompleteTree(BinaryNode * node);
		// Insert a new value using BFS
		static BinaryNode * Insert(BinaryNode * node, T value);

		// Create a balanced tree from a single link list
		static BinaryNode * ToBalancedTree(SingleNode<T> * list);
		static BinaryNode * ToBalancedTree2(SingleNode<T> * list);

		// Return 0 if two trees are equal
		static int Compare(BinaryNode * first, BinaryNode * second);
		static int Compare2(BinaryNode * first, BinaryNode * second);

		// Recursive
		static int Height(BinaryNode * node);
		virtual int Height(void) { return Height(this); }

		// Get the reference of left child pointer
		virtual BinaryNode * & Left(void) { return (BinaryNode * &)this->Neighbor(0); }
		// Set the left child pointer
		virtual void Left(BinaryNode * left) { this->Neighbor(0) = left; }

		// Get the reference of right child pointer
		virtual BinaryNode * & Right(void) { return (BinaryNode * &)this->Neighbor(1); }
		// Set the right child pointer
		virtual void Right(BinaryNode * right) { this->Neighbor(1) = right; }

		static int Size(BinaryNode * node);
		virtual int Size(void) { return Size(this); }

		static stringstream & ToString(BinaryNode * node, stringstream & output);
		static stringstream & ToString2(BinaryNode * node, stringstream & output);

		void Print(void);
		void Print2(void);

		static void Serialize(BinaryNode * node, ostream & output);
		static BinaryNode * Deserialize(istream & input);

		// Recursive
		static void PreOrderWalk(BinaryNode * node, function<void(T)> f);
		void PreOrderWalk(function<void(T)> f) { PreOrderWalk(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack(BinaryNode * node, function<void(T)> f);
		void PreOrderWalkWithStack(function<void(T)> f) { PreOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack2(BinaryNode * node, function<void(T)> f);
		void PreOrderWalkWithStack2(function<void(T)> f) { PreOrderWalkWithStack2(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack3(BinaryNode * node, function<void(T)> f);
		void PreOrderWalkWithStack3(function<void(T)> f) { PreOrderWalkWithStack3(this, f); }

		// Recursive
		static void InOrderWalk(BinaryNode * node, function<void(T)> f);
		void InOrderWalk(function<void(T)> f) { InOrderWalk(this, f); }
		
		// Non-recursive with stack
		static void InOrderWalkWithStack(BinaryNode * node, function<void(T)> f);
		void InOrderWalkWithStack(function<void(T)> f) { InOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void InOrderWalkWithStack2(BinaryNode * node, function<void(T)> f);
		void InOrderWalkWithStack2(function<void(T)> f) { InOrderWalkWithStack2(this, f); }

		// Recursive
		static void PostOrderWalk(BinaryNode * node, function<void(T)> f);
		void PostOrderWalk(function<void(T)> f) { PostOrderWalk(this, f); }
				
		// Non-recursive with stack
		static void PostOrderWalkWithStack(BinaryNode * node, function<void(T)> f);
		void PostOrderWalkWithStack(function<void(T)> f) { PostOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void PostOrderWalkWithStack2(BinaryNode * node, function<void(T)> f);
		void PostOrderWalkWithStack2(function<void(T)> f) { PostOrderWalkWithStack2(this, f); }

		static BinaryNode * BuildTreePreOrderInOrder(T * preOrder, int preLength, T * inOrder, int inLength);
		static BinaryNode * BuildTreePreOrderInOrder2(T * preOrder, int preLength, T * inOrder, int inLength);
		static BinaryNode * BuildTreeInOrderPostOrder(T * inOrder, int inLength, T * postOrder, int postLength);
		static BinaryNode * BuildTreeInOrderPostOrder2(T * inOrder, int inLength, T * postOrder, int postLength);

		// Visit level by level, left to right
		// Breadth-first search
		static void LevelOrderWalk(BinaryNode * node, function<void(T)> f);
		virtual void LevelOrderWalk(function<void(T)> f) { LevelOrderWalk(this, f); }

		// Visit level by level, left to right
		// Depth-first search
		static void LevelOrderWalk2(BinaryNode * node, function<void(T)> f);
		virtual void LevelOrderWalk2(function<void(T)> f) { LevelOrderWalk2(this, f); }

		// Visit nodes level by level from bottom up and left to right
		static void LevelOrderWalkBottomUp(BinaryNode * node, function<void(T)> f);
		void LevelOrderWalkBottomUp(function<void(T)> f) { LevelOrderWalkBottomUp(this, f); }

		// The boundary values include left-most nodes, leaf nodes and right-most nodes.
		// A left-most node may be the right child of its parent if its parent is left-most and has no left child.
		// Same goes to the right-most nodes.
		static void GetBoundaryValues(BinaryNode * node, vector<T> & values);
		void GetBoundaryValues(vector<T> & values) { GetBoundaryValues(this, values); }

		static BinaryNode * Search(BinaryNode * node, const T & v);
		static BinaryNode * Min(BinaryNode * node);
		static BinaryNode * Max(BinaryNode * node);

		static BinaryNode * LowestCommonAncestor(BinaryNode * node, BinaryNode * first, BinaryNode * second);
		static BinaryNode * LowestCommonAncestor2(BinaryNode * node, BinaryNode * first, BinaryNode * second);

		// http://leetcode.com/2010/09/printing-binary-tree-in-zig-zag-level_18.html
		// Breadth-first-search using stack
		void PrintZigZag(void);

		// Convert a binary tree to a linked list so that the list nodes
		// are linked by the left and right pointers and are in pre-order of original tree.
		// e.g.
		//      1
		//     / \
		//    2   5
		//   / \   \
		//  3   4   6
		// to
		//  1-2-3-4-5-6
		// This version builds a double-link list by setting node->left also.
		// If need a single-link list, just remove the statements setting node->left.
		static BinaryNode * ToPreOrderLinkList(BinaryNode * node);
		// Convert a binary tree to a linked list so that the list nodes
		// are linked by the left and right pointers and are in in-order of original tree.
		// e.g.
		//      1
		//     / \
		//    2   5
		//   / \   \
		//  3   4   6
		// to
		//  3-2-4-1-5-6
		// This version builds a double-link list by setting node->left also.
		// If need a single-link list, just remove the statements setting node->left.
		static BinaryNode * ToInOrderLinkList(BinaryNode * node);
		// Convert a binary tree to a linked list so that the list nodes
		// are linked by the left and right pointers and are in post-order of original tree.
		// e.g.
		//      1
		//     / \
		//    2   5
		//   / \   \
		//  3   4   6
		// to
		//  3-4-2-6-5-1
		// This version builds a double-link list by setting node->left also.
		// If need a single-link list, just remove the statements setting node->left.
		static BinaryNode * ToPostOrderLinkList(BinaryNode * node);

		// A tree is balanced if the heights of its left tree and right tree differs no more than 1.
		static bool IsBalanced(BinaryNode * node);
		bool IsBalanced(void) { return IsBalanced(this); }

		// A tree is balanced if the heights of its left tree and right tree differs no more than 1.
		// This algorithm is wrong.
		static bool IsBalanced2(BinaryNode * node);
		bool IsBalanced2(void) { return IsBalanced2(this); }

		// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
		// For example, this binary tree is symmetric:
		//    1
		//   / \
		//  2   2
		// / \ / \
		// 3 4 4 3
		// But the following is not:
		//   1
		//  / \
		// 2   2
		//  \   \
		//   3   3
		static bool IsSymmetric(BinaryNode * node);
		bool IsSymmetric(void) { return IsSymmetric(this); }

		// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
		// For example, this binary tree is symmetric:
		//    1
		//   / \
		//  2   2
		// / \ / \
		// 3 4 4 3
		// But the following is not:
		//   1
		//  / \
		// 2   2
		//  \   \
		//   3   3
		static bool IsSymmetric2(BinaryNode * node);
		bool IsSymmetric2(void) { return IsSymmetric2(this); }

		// Swap values of two nodes
		static void SwapValues(BinaryNode * first, BinaryNode * second);

		static BinaryNode * Clone1(BinaryNode * node);

		//
		// BinarySearchTree
		//

		// Create a random binary search tree
		// Return nullptr if input is empty
		static BinaryNode * SearchTreeRandom(vector<T> & values);
		// May return nullptr
		static BinaryNode * SearchTreeRandom(size_t maxSize);

		// Insert a new value to binary search tree
		static BinaryNode * SearchTreeInsert(BinaryNode * node, T value);
		static BinaryNode * SearchTreeInsert2(BinaryNode * node, T value);

		// Verify if a tree is a binary search tree
		static bool SearchTreeVerify(BinaryNode * node);
		static bool SearchTreeVerify2(BinaryNode * node);
		static bool SearchTreeVerify3(BinaryNode * node);

		// Search a node in binary search tree
		static BinaryNode * SearchTreeSearch(BinaryNode * node, T value);
		static BinaryNode * SearchTreeSearch2(BinaryNode * node, T value);

		// Find the minimum node
		static BinaryNode * SearchTreeMin(BinaryNode * node);
		// Find the maximum node
		static BinaryNode * SearchTreeMax(BinaryNode * node);

		// Assume first and second exist in the tree
		static BinaryNode * SearchTreeLowestCommonAncestor(BinaryNode * node, const T & first, const T & second);

		// Serialize a binary search tree
		static void SearchTreeSerialize(BinaryNode * node, ostream & output);

		// Deserialize a binary search tree
		static BinaryNode * SearchTreeDeserialize(istream & input);
		static BinaryNode * SearchTreeDeserialize2(istream & input);
		static BinaryNode * SearchTreeDeserialize3(istream & input);

		// Two elements of a binary search tree are swapped by mistake.
		// Recover the tree without changing its structure.
		// If we traverse a binary search tree in-order, we will get an increasing
		// sequence, e.g.,
		//    1, 2, 3, 4, 5, 6, 7, .......
		// If two neighboring elements are swapped, we will have one inversion, e.g.,
		//    1, 2, 4, 3, 5, 6, 7, .......
		// If two non-neighboring elements are swapped, we will have two inversions, e.g.,
		//    1, 2, 3, 6, 5, 4, 7, ....... , or
		//    1, 2, 6, 4, 5, 3, 7, .......
		static BinaryNode * SearchTreeRecover(BinaryNode * node);
		static BinaryNode * SearchTreeRecover2(BinaryNode * node);
	};

	template<class T> void BinaryNode<T>::DeleteTree(BinaryNode * node)
	{
		if (node == nullptr) return;
		DeleteTree(node->Left());
		DeleteTree(node->Right());
		delete node;
		node = nullptr;
	}

	// Create a random binary tree from a pre-order sequence
	template<class T> BinaryNode<T> * BinaryNode<T>::RandomTreeFromPreOrder(vector<T> & values)
	{
		if (values.size() == 0) return nullptr;

		function<BinaryNode<T> * (vector<T> &, int, int)>
		create = [&](vector<T> & v, int i, int j) -> BinaryNode<T> * {
			if (i > j) return nullptr;
			BinaryNode<T> * n = new BinaryNode<T>(v[i]);
			int k = i + 1 + (rand() % (j - i + 1));
			n->Left() = create(v, i + 1, k - 1);
			n->Right() = create(v, k, j);
			return n;
		};

		BinaryNode<T> * node = create(values, 0, values.size() - 1);
		return node;
	}

	// Create a random binary tree from an in-order sequence
	template<class T> BinaryNode<T> * BinaryNode<T>::RandomTreeFromInOrder(vector<T> & values)
	{
		if (values.size() == 0) return nullptr;

		function<BinaryNode<T> * (vector<T> &, int, int)>
		create = [&](vector<T> & v, int i, int j) -> BinaryNode<T> * {
			if (i > j) return nullptr;
			int k = i + (rand() % (j - i + 1));
			BinaryNode<T> * n = new BinaryNode<T>(v[k]);
			n->Left() = create(v, i, k - 1);
			n->Right() = create(v, k + 1, j);
			return n;
		};

		BinaryNode<T> * node = create(values, 0, values.size() - 1);
		return node;
	}

	// Create a random binary tree from a post-order sequence
	template<class T> BinaryNode<T> * BinaryNode<T>::RandomTreeFromPostOrder(vector<T> & values)
	{
		if (values.size() == 0) return nullptr;

		function<BinaryNode<T> * (vector<T> &, int, int)>
		create = [&](vector<T> & v, int i, int j) -> BinaryNode<T> * {
			if (i > j) return nullptr;
			BinaryNode<T> * n = new BinaryNode<T>(v[j]);
			int k = i - 1 + (rand() % (j - i + 1));
			n->Left() = create(v, i, k);
			n->Right() = create(v, k + 1, j - 1);
			return n;
		};

		BinaryNode<T> * node = create(values, 0, values.size() - 1);
		return node;
	}

	// Create a random binary tree
	template<class T> BinaryNode<T> * BinaryNode<T>::RandomTree(vector<T> & values)
	{
		if (values.size() == 0) return nullptr;

		function<BinaryNode<T> * (vector<T> &, int, int)>
		create = [&](vector<T> & v, int i, int j) -> BinaryNode<T> * {
			if (i > j) return nullptr;
			BinaryNode<T> * n = nullptr;
			int k = rand() % 3;
			switch (k) {
			case 0:
				n = new BinaryNode<T>(v[i]);
				k = i + 1 + (rand() % (j - i + 1));
				n->Left() = create(v, i + 1, k - 1);
				n->Right() = create(v, k, j);
				break;
			case 1:
				k = i + (rand() % (j - i + 1));
				n = new BinaryNode<T>(v[k]);
				n->Left() = create(v, i, k - 1);
				n->Right() = create(v, k + 1, j);
				break;
			case 2:
				n = new BinaryNode<T>(v[j]);
				k = i - 1 + (rand() % (j - i + 1));
				n->Left() = create(v, i, k);
				n->Right() = create(v, k + 1, j - 1);
				break;
			}
			return n;
		};

		BinaryNode<T> * node = create(values, 0, values.size() - 1);
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::RandomTree(size_t maxSize)
	{
		vector<T> values;
		int size = rand() % (maxSize + 1);
		for (int i = 0; i < size; i++) {
			values.push_back(rand());
		}
		BinaryNode<T> * node = RandomTree(values);
		return node;
	}

	template<class T> vector<BinaryNode<T> *> BinaryNode<T>::UniqueTreesFromPreOrder(vector<T> & values)
	{
		function<vector<BinaryNode *>(int, int)>
		create = [&](int i, int j)->vector<BinaryNode *>{
			vector<BinaryNode *> trees;

			if (i > j) return trees;

			if (i == j) {
				trees.push_back(new BinaryNode(values[i]));
				return trees;
			}

			vector<BinaryNode *> firstTrees = create(i+1, j);
			for_each (firstTrees.begin(), firstTrees.end(), [&](BinaryNode * f){
				BinaryNode * n = new BinaryNode(values[i]);
				n->Left() = Clone1(f);
				trees.push_back(n);
			});

			for_each (firstTrees.begin(), firstTrees.end(), [&](BinaryNode * f){
				BinaryNode * n = new BinaryNode(values[i]);
				n->Right() = Clone1(f);
				trees.push_back(n);
			});

			for_each (firstTrees.begin(), firstTrees.end(), [&](BinaryNode * f){
				DeleteTree(f);
			});

			for (int k = i+2; k <= j; k++) {
				vector<BinaryNode *> leftTrees = create(i+1, k-1);
				vector<BinaryNode *> rightTrees = create(k, j);
				for_each (leftTrees.begin(), leftTrees.end(), [&](BinaryNode * l){
					for_each (rightTrees.begin(), rightTrees.end(), [&](BinaryNode * r){
						BinaryNode * n = new BinaryNode(values[i]);
						n->Left() = Clone1(l);
						n->Right() = Clone1(r);
						trees.push_back(n);
					});
				});

				for_each (leftTrees.begin(), leftTrees.end(), [&](BinaryNode * l){
					DeleteTree(l);
				});
				for_each (rightTrees.begin(), rightTrees.end(), [&](BinaryNode * r){
					DeleteTree(r);
				});
			}

			return trees;
		};

		return create(0, values.size() - 1);
	}

	template<class T> vector<BinaryNode<T> *> BinaryNode<T>::UniqueTreesFromInOrder(vector<T> & values)
	{
		function<vector<BinaryNode *>(int, int)>
		create = [&](int i, int j)->vector<BinaryNode *>{
			vector<BinaryNode *> trees;

			if (i > j) return trees;

			if (i == j) {
				trees.push_back(new BinaryNode(values[i]));
				return trees;
			}

			if (i + 1 == j) {
				BinaryNode * n = new BinaryNode(values[j]);
				n->Left() = new BinaryNode(values[i]);
				trees.push_back(n);
				n = new BinaryNode(values[i]);
				n->Right() = new BinaryNode(values[j]);
				trees.push_back(n);
				return trees;
			}

			vector<BinaryNode *> firstTrees = create(i+1, j);
			for_each (firstTrees.begin(), firstTrees.end(), [&](BinaryNode * f){
				BinaryNode * n = new BinaryNode(values[i]);
				n->Right() = f;
				trees.push_back(n);
			});

			vector<BinaryNode *> lastTrees = create(i, j-1);
			for_each (lastTrees.begin(), lastTrees.end(), [&](BinaryNode * l){
				BinaryNode * n = new BinaryNode(values[j]);
				n->Left() = l;
				trees.push_back(n);
			});

			for (int k = i+1; k < j; k++) {
				vector<BinaryNode *> leftTrees = create(i, k-1);
				vector<BinaryNode *> rightTrees = create(k+1, j);
				for_each (leftTrees.begin(), leftTrees.end(), [&](BinaryNode * l){
					for_each (rightTrees.begin(), rightTrees.end(), [&](BinaryNode * r){
						BinaryNode * n = new BinaryNode(values[k]);
						n->Left() = Clone1(l);
						n->Right() = Clone1(r);
						trees.push_back(n);
					});
				});

				for_each (leftTrees.begin(), leftTrees.end(), [&](BinaryNode * l){
					DeleteTree(l);
				});
				for_each (rightTrees.begin(), rightTrees.end(), [&](BinaryNode * r){
					DeleteTree(r);
				});
			}

			return trees;
		};

		return create(0, values.size() - 1);
	}

	template<class T> vector<BinaryNode<T> *> BinaryNode<T>::UniqueTreesFromPostOrder(vector<T> & values)
	{
		function<vector<BinaryNode *>(int, int)>
		create = [&](int i, int j)->vector<BinaryNode *>{
			vector<BinaryNode *> trees;

			if (i > j) return trees;

			if (i == j) {
				trees.push_back(new BinaryNode(values[i]));
				return trees;
			}

			vector<BinaryNode *> firstTrees = create(i, j-1);
			for_each (firstTrees.begin(), firstTrees.end(), [&](BinaryNode * f){
				BinaryNode * n = new BinaryNode(values[j]);
				n->Left() = Clone1(f);
				trees.push_back(n);
			});

			for_each (firstTrees.begin(), firstTrees.end(), [&](BinaryNode * f){
				BinaryNode * n = new BinaryNode(values[j]);
				n->Right() = Clone1(f);
				trees.push_back(n);
			});

			for_each (firstTrees.begin(), firstTrees.end(), [&](BinaryNode * f){
				DeleteTree(f);
			});

			for (int k = i; k < j - 1; k++) {
				vector<BinaryNode *> leftTrees = create(i, k);
				vector<BinaryNode *> rightTrees = create(k+1, j-1);
				for_each (leftTrees.begin(), leftTrees.end(), [&](BinaryNode * l){
					for_each (rightTrees.begin(), rightTrees.end(), [&](BinaryNode * r){
						BinaryNode * n = new BinaryNode(values[j]);
						n->Left() = Clone1(l);
						n->Right() = Clone1(r);
						trees.push_back(n);
					});
				});

				for_each (leftTrees.begin(), leftTrees.end(), [&](BinaryNode * l){
					DeleteTree(l);
				});
				for_each (rightTrees.begin(), rightTrees.end(), [&](BinaryNode * r){
					DeleteTree(r);
				});
			}

			return trees;
		};

		return create(0, values.size() - 1);
	}

	// Given a pre-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
	// count unique binary trees that can be built with the n numbers
	// Let C[i,j] be the count of unique binary trees using numbers i to j
	// Then chose a k between i+1 and j and solve sub problems
	// C[i,j] = 2 * C[i+1, j]
	//        + C[i+1, k-1] * C[k, j]
	template<class T> unsigned long long BinaryNode<T>::CountUniqueTreesFromPreOrderOfSize(int n)
	{
		if (n <= 0) return 0;

		UpperTriangularMatrix<unsigned long long> count(n, n);

		for (int i = 0; i < n; i++) {
			count(i, i) = 1;
		}

		for (int l = 1; l < n; l++) {
			for (int i = 0; i < n - l; i++) {
				int j = i + l;
				count(i, j) = count(i+1, j) << 1;
				for (int k = i+2; k <= j; k++) {
					count(i, j) += count(i+1, k-1) * count(k, j);
				}
			}
		}

		return count(0, n-1);
	}

	// Given an in-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
	// count unique binary trees that can be built with the n numbers
	// Let C[i,j] be the count of unique binary trees using numbers i to j
	// Then chose a k between i and j and solve sub problems
	// C[i,j] = C[i+1, j]
	//        + C[i, j-1]
	//        + C[i, k-1] * C[k+1, j]
	template<class T> unsigned long long BinaryNode<T>::CountUniqueTreesFromInOrderOfSize(int n)
	{
		if (n <= 0) return 0;

		UpperTriangularMatrix<unsigned long long> count(n, n);

		for (int i = 0; i < n; i++) {
			count(i, i) = 1;
		}

		for (int l = 1; l < n; l++) {
			for (int i = 0; i < n - l; i++) {
				int j = i + l;
				count(i, j) = count(i+1, j) + count(i, j-1);
				for (int k = i+1; k < j; k++) {
					count(i, j) += count(i, k-1) * count(k+1, j);
				}
			}
		}

		return count(0, n-1);
	}

	// Given a post-order sequence of n numbers (e.g., 1, 2, 3, ..., n)
	// count unique binary trees that can be built with the n numbers
	// Let C[i,j] be the count of unique binary trees using numbers i to j
	// Then chose a k between i+1 and j and solve sub problems
	// C[i,j] = 2 * C[i, j-1]
	//        + C[i, k] * C[k+1, j-1]
	template<class T> unsigned long long BinaryNode<T>::CountUniqueTreesFromPostOrderOfSize(int n)
	{
		if (n <= 0) return 0;

		UpperTriangularMatrix<unsigned long long> count(n, n);

		for (int i = 0; i < n; i++) {
			count(i, i) = 1;
		}

		for (int l = 1; l < n; l++) {
			for (int i = 0; i < n - l; i++) {
				int j = i + l;
				count(i, j) = count(i, j-1) << 1;
				for (int k = i; k < j-1; k++) {
					count(i, j) += count(i, k) * count(k+1, j-1);
				}
			}
		}

		return count(0, n-1);
	}

	// Create a complete binary tree
	template<class T> BinaryNode<T> * BinaryNode<T>::ToCompleteTree(vector<T> & values)
	{
		if (values.size() == 0) return nullptr;
		BinaryNode<T> * node = new BinaryNode<T>(values[0]);
		queue<BinaryNode<T> *> q;
		q.push(node);
		size_t i = 1;
		BinaryNode<T> * n;
		while (!q.empty() && i < values.size()) {
			n = q.front();
			q.pop();
			n->Left() = new BinaryNode<T>(values[i++]);
			if (i == values.size()) break;
			q.push(n->Left());
			n->Right() = new BinaryNode<T>(values[i++]);
			if (i == values.size()) break;
			q.push(n->Right());
		}
		return node;
	}

	// Fill missing nodes to make a complete tree
	template<class T> BinaryNode<T> * BinaryNode<T>::FillToComplete(BinaryNode * node, vector<T> & values)
	{
		if (values.size() == 0) return node;
		size_t i = 0;
		if (node == nullptr) node = new BinaryNode<T>(values[i++]);
		queue<BinaryNode<T> *> q;
		q.push(node);
		BinaryNode<T> * n;
		while (!q.empty() && i < values.size()) {
			n = q.front();
			q.pop();
			if (n->Left() == nullptr) {
				n->Left() = new BinaryNode<T>(values[i++]);
				if (i == values.size()) break;
			}
			q.push(n->Left());
			if (n->Right() == nullptr) {
				n->Right() = new BinaryNode<T>(values[i++]);
				if (i == values.size()) break;
			}
			q.push(n->Right());
		}
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::RandomCompleteTree(size_t maxSize)
	{
		int size = rand() % (maxSize + 1);
		if (size == 0) return nullptr;
		BinaryNode<T> * node = new BinaryNode<T>(rand());
		queue<BinaryNode<T> *> q;
		q.push(node);
		int i = 1;
		BinaryNode<T> * n;
		while (!q.empty() && i < size) {
			n = q.front();
			q.pop();
			n->Left() = new BinaryNode<T>(rand());
			i++;
			if (i == size) break;
			q.push(n->Left());
			n->Right() = new BinaryNode<T>(rand());
			i++;
			if (i == size) break;
			q.push(n->Right());
		}
		return node;
	}

	template<class T> bool BinaryNode<T>::IsCompleteTree(BinaryNode * node)
	{
		if (node == nullptr) return true;
		queue<BinaryNode<T> *> q;
		q.push(node);
		bool end = false;
		while (!q.empty()) {
			node = q.front();
			q.pop();
			if (node->Left() == nullptr) {
				if (!end) end = true;
			} else {
				if (end) return false;
				else q.push(node->Left());
			}
			if (node->Right() == nullptr) {
				if (!end) end = true;
			} else {
				if (end) return false;
				else q.push(node->Right());
			}
		}
		return true;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::Insert(BinaryNode * node, T value)
	{
		if (node == nullptr) return new BinaryNode<T>(value);
		queue<BinaryNode<T> *> q;
		q.push(node);
		BinaryNode<T> * n;
		while (!q.empty()) {
			n = q.front();
			q.pop();
			if (n->Left() == nullptr) {
				n->Left() = new BinaryNode<T>(value);
				break;
			}
			q.push(n->Left());
			if (n->Right() == nullptr) {
				n->Right() = new BinaryNode<T>(value);
				break;
			}
			q.push(n->Right());
		}
		return node;
	}

	// Create a balanced tree from a single link list
	template<class T> BinaryNode<T> * BinaryNode<T>::ToBalancedTree(SingleNode<T> * list)
	{
		if (list == nullptr) return nullptr;

		function<BinaryNode<T> * (SingleNode<T> *)>
		convert = [&](SingleNode<T> * head) -> BinaryNode<T> * {
			if (head == nullptr) return nullptr;

			if (head->Next() == nullptr) {
				BinaryNode<T> * tree = new BinaryNode<T>(head->Value());
				delete head;
				return tree;
			}

			SingleNode<T> * first = head;
			SingleNode<T> * second = head->Next();
			while (second->Next() != nullptr && second->Next()->Next() != nullptr) {
				first = first->Next();
				second = second->Next();
				second = second->Next();
			}

			SingleNode<T> * node = first->Next();
			first->Next() = nullptr;
			first = node->Next();
			node->Next() = nullptr;

			BinaryNode<T> * tree = new BinaryNode<T>(node->Value());

			parallel_invoke(
				[&convert, &tree, head] { tree->Left() = convert(head); },
				[&convert, &tree, first] { tree->Right() = convert(first); }
			);

			delete node;
			return tree;
		};

		return convert(list);
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::ToBalancedTree2(SingleNode<T> * list)
	{
		if (list == nullptr) return nullptr;

	    function<BinaryNode<T> * (SingleNode<T> * &, int, int)>
		convert = [&](SingleNode<T> * & head, int begin, int end) -> BinaryNode<T> * {
			if (head == nullptr || begin > end) return nullptr;

			// Choose the median one if there are odd numbers in [begin, end]
			// Choose the upper median if there are even numbers in [begin, end]
			int middle = begin + ((1 + end - begin) >> 1);

		    BinaryNode<T> * left = convert(head, begin, middle - 1);
			BinaryNode<T> * node = new BinaryNode<T>(head->Value());
			node->Left() = left;

			SingleNode<T> * p = head;
			head = head->Next();
			delete p;

			node->Right() = convert(head, middle + 1, end);

			return node;
		};

		SingleNode<T> * p = list;
		int i = 0;
		while (p != nullptr) {
			p = p->Next();
			i++;
		}

		return convert(list, 0, i-1);
	}

	template<class T> int BinaryNode<T>::Compare(BinaryNode * first, BinaryNode * second)
	{
		if (first == nullptr && second == nullptr) return 0;
		if (first == nullptr && second != nullptr) return -1;
		if (first != nullptr && second == nullptr) return 1;
		if (first->Value() < second->Value()) return -1;
		if (first->Value() > second->Value()) return 1;
		int v = Compare(first->Left(), second->Left());
		if (v == 0) v = Compare(first->Right(), second->Right());
		return v;
	}

	template<class T> int BinaryNode<T>::Compare2(BinaryNode * first, BinaryNode * second)
	{
		if (first == nullptr && second == nullptr) return 0;
		if (first == nullptr && second != nullptr) return -1;
		if (first != nullptr && second == nullptr) return 1;
		if (first->Value() < second->Value()) return -1;
		if (first->Value() > second->Value()) return 1;
		deque<BinaryNode *> q;
		q.push_front(first);
		q.push_back(second);
		while (!q.empty()) {
			first = q.front();
			q.pop_front();
			second = q.back();
			q.pop_back();
			if (first->Right() == nullptr && second->Right() != nullptr) return -1;
			if (first->Right() != nullptr && second->Right() == nullptr) return 1;
			if (first->Right() != nullptr && second->Right() != nullptr) {
				if (first->Right()->Value() < second->Right()->Value()) return -1;
				if (first->Right()->Value() > second->Right()->Value()) return 1;
				q.push_front(first->Right());
				q.push_back(second->Right());
			}
			if (first->Left() == nullptr && second->Left() != nullptr) return -1;
			if (first->Left() != nullptr && second->Left() == nullptr) return 1;
			if (first->Left() != nullptr && second->Left() != nullptr) {
				if (first->Left()->Value() < second->Left()->Value()) return -1;
				if (first->Left()->Value() > second->Left()->Value()) return 1;
				q.push_front(first->Left());
				q.push_back(second->Left());
			}
		}
		return 0;
	}

	template<class T> int BinaryNode<T>::Height(BinaryNode * node)
	{
		if (node == nullptr) return 0;
		int left = Height(node->Left());
		int right = Height(node->Right());
		return 1 + std::max<int>(left, right);
	}

	template<class T> int BinaryNode<T>::Size(BinaryNode * node)
	{
		if (node == nullptr) return 0;
		int left = Size(node->Left());
		int right = Size(node->Right());
		return 1 + left + right;
	}

	template<class T> stringstream & BinaryNode<T>::ToString(BinaryNode * node, stringstream & output)
	{
		function<void(BinaryNode *, int, vector<int> &)>
		toString = [&](
			BinaryNode * n, // Current node to print
			int x,          // Current node position
			vector<int> & y // Positions of unprinted right branch starting points
			)
		{
			if (n == nullptr) return;

			static string link = "____";
			string c = String::ToString(n->Value());
			output << " " << c;
			x += (1 + c.length());

			if (n->Right() != nullptr) {
				// Record current x coordinate,
				// so it can be used to draw '|'
				y.push_back(x);
			}

			if (n->Left() != nullptr) {
				output << link;
				toString(n->Left(), x + link.length(), y);
			}

			if (n->Right() != nullptr) {
				output << endl;

				for (size_t i = 0; i < y.size(); i++) {
					int len = i == 0 ? y[i] : y[i] - y[i - 1];
					string blank(len - 1, ' ');
					output << blank << '|';
				}

				output << link;

				// The right child is ready to print
				// Remove its coordinate because it is not needed any more
				y.pop_back();

				toString(n->Right(), x + link.length(), y);
			}
		};

		vector<int> y;
		toString(node, 0, y);
		output << endl;
		return output;
	}

	template<class T> stringstream & BinaryNode<T>::ToString2(BinaryNode * node, stringstream & output)
	{
		function<void(stringstream *, int, char)>
			printChar = [&](stringstream * s, int n, char c) {
			if (n > 0) {
				string chars(n, c);
				*s << chars;
			}
		};

		function<void(BinaryNode *, unsigned int, int &, int &, vector<stringstream *> &)>
		toString = [&](
			BinaryNode * n,             // current node to print
			unsigned int y,             // current node level
			int & x,                    // x-axis position of root of last printed sub tree
			int & r,                    // x-axis position of right-most boundary of last printed sub tree
			vector<stringstream *> & ss // output streams, one per level
			)
		{
			if (n == nullptr) return;

			if (ss.size() <= y) {
				ss.push_back(new stringstream());
			}

			// print left tree, update x and r accordingly
			toString(n->Left(), y + 1, x, r, ss);

			stringstream * s = ss[y];

			int l = (int)(s->str().length());
			if (l < x) {
				printChar(s, x - l, ' ');
			}

			if (n->Left() != nullptr && r > x) {
				*s << '/';
				printChar(s, r - x - 1, '-');
			}

			string nc = String::ToString(n->Value());
			*s << nc;

			x = (r + (nc.length() >> 1));
			r = r + nc.length();

			int rx = r;
			int rr = r;
			toString(n->Right(), y + 1, rx, rr, ss);

			if (n->Right() != nullptr && rx >= r) {
				printChar(s, rx - r - 1, '-');
				*s << '\\';
			}

			// Update the right most boundary
			r = rr;
		};

		vector<stringstream *> streams;
		int x = 0;
		int r = 0;
		toString(node, 0, x, r, streams);

		for_each (streams.begin(), streams.end(), [&](stringstream * s) {
			output << s->str() << endl;
			delete s;
		});

		return output;
	}

	template<class T> void BinaryNode<T>::Print(void)
	{
		stringstream ss;
		ToString(this, ss);
		cout << ss.str();
	}

	template<class T> void BinaryNode<T>::Print2(void)
	{
		stringstream ss;
		ToString2(this, ss);
		cout << ss.str();
	}

	template<class T> void BinaryNode<T>::Serialize(BinaryNode * node, ostream & output)
	{
		function<void(BinaryNode<T> *)> serialize = [&](BinaryNode<T> * n){
			if (n == nullptr) {
				output << '#';
			} else {
				output << n->Value() << ' ';
				serialize(n->Left());
				serialize(n->Right());
			}
		};

		serialize(node);
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::Deserialize(istream & input)
	{
		function<void(BinaryNode<T> * &)> deserialize = [&](BinaryNode<T> * & n) {
			char c = input.peek();
			if (c == ' ') {
				// Two cases: ' '#, or ' 'number
				// Skip ' ' using seekg. Using input >> c does not work
				// because the >> operator actually skips ' ' and reads
				// next charactor, which is either '#' or a digit.
				input.seekg(1, ios_base::cur);
				c = input.peek();
			}

			if (c == '#') {
				// Eat '#'
				input >> c;
				return;
			}

			T value;
			// The istream >> operator reads a value and leaves
			// the next ' ' character in the stream.
			input >> value;
			n = new BinaryNode<T>(value);
			deserialize(n->Left());
			deserialize(n->Right());
		};

		BinaryNode<T> * node;
		deserialize(node);
		return node;
	}

	template<class T> void BinaryNode<T>::PreOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		f(node->Value());
		PreOrderWalk(node->Left(), f);
		PreOrderWalk(node->Right(), f);
	}

	template<class T> void BinaryNode<T>::PreOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		while (!path.empty() || node != nullptr) {
			if (node != nullptr) {
				f(node->Value());
				path.push(node);
				node = node->Left();
			} else {
				node = path.top()->Right();
				path.pop();
			}
		}
	}

	template<class T> void BinaryNode<T>::PreOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		while (!path.empty()) {
			BinaryNode * top = path.top();
			path.pop();
			f(top->Value());
			if (top->Right() != nullptr) path.push(top->Right());
			if (top->Left() != nullptr) path.push(top->Left());
		}
	}

	template<class T> void BinaryNode<T>::PreOrderWalkWithStack3(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		BinaryNode * prev = node;
		while (!path.empty()) {
			node = path.top();
			if (prev == node->Right()) {
				path.pop();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				f(node->Value());
				path.push(node->Left());
			} else {
				if (node->Left() != prev) f(node->Value());
				if (node->Right() == nullptr) path.pop();
				else path.push(node->Right());
			}
			prev = node;
		}
	}

	template<class T> void BinaryNode<T>::InOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		InOrderWalk(node->Left(), f);
		f(node->Value());
		InOrderWalk(node->Right(), f);
	}

	template<class T> void BinaryNode<T>::InOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		while (!path.empty() || node != nullptr) {
			if (node != nullptr) {
				path.push(node);
				node = node->Left();
			} else {
				node = path.top();
				path.pop();
				f(node->Value());
				node = node->Right();
			}
		}
	}

	template<class T> void BinaryNode<T>::InOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		BinaryNode * prev = nullptr;
		while (!path.empty()) {
			node = path.top();
			if (prev == node->Right()) {
				path.pop();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				path.push(node->Left());
			} else {
				f(node->Value());
				if (node->Right() == nullptr) path.pop();
				else path.push(node->Right());
			}
			prev = node;
		}
	}

	template<class T> void BinaryNode<T>::PostOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		PostOrderWalk(node->Left(), f);
		PostOrderWalk(node->Right(), f);
		f(node->Value());
	}

	template<class T> void BinaryNode<T>::PostOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		BinaryNode * prev = nullptr;
		while (!path.empty() || node != nullptr) {
			if (node != nullptr) {
				path.push(node);
				node = node->Left();
			} else {
				BinaryNode * top = path.top();
				if (top->Right() != nullptr && top->Right() != prev) {
					node = top->Right();
				} else {
					path.pop();
					f(top->Value());
					prev = top;
				}
			}
		}
	}

	template<class T> void BinaryNode<T>::PostOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		BinaryNode * prev = node;
		while (!path.empty()) {
			node = path.top();
			if (prev == node->Right()) {
				f(node->Value());
				path.pop();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				path.push(node->Left());
			} else {
				if (node->Right() != nullptr) path.push(node->Right());
				else {
					f(node->Value());
					path.pop();
				}
			}
			prev = node;
		}
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::BuildTreePreOrderInOrder(T * preOrder, int preLength, T * inOrder, int inLength)
	{
		if (inOrder == nullptr || preOrder == nullptr || inLength <= 0 || preLength <= 0 || inLength != preLength) return nullptr;

		T value = preOrder[0];

		int index = -1;
		for (int i = 0; i < inLength; i++) {
			if (inOrder[i] == value) {
				index = i;
				break;
			}
		}

		if (index == -1) return nullptr;

		BinaryNode<T> * node = new BinaryNode<T>(value);

		node->Left() = BuildTreePreOrderInOrder(preOrder + 1, index, inOrder, index);
		node->Right() = BuildTreePreOrderInOrder(preOrder + index + 1, preLength - 1 - index, inOrder + index + 1, inLength - 1 - index);

		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::BuildTreePreOrderInOrder2(T * preOrder, int preLength, T * inOrder, int inLength)
	{
		if (preOrder == nullptr || preLength <= 0 || inOrder == nullptr || inLength <= 0 || preLength != inLength) return nullptr;

		stack<BinaryNode<T> *> path;

		int i = 0; // index current element in preOrder
		int j = 0; // index current element in inOrder
		int f = 0; // flag to insert to left or right

		// Root
		BinaryNode<T> * node = new BinaryNode<T>(preOrder[i]);
		path.push(node);

		// Current insertion point
		BinaryNode<T> * t = node;
		i++;

		while (i < preLength) {
			if (!path.empty() && path.top()->Value() == inOrder[j]) {
				// Done with a left substree, start to insert the right subtree
				t = path.top();
				path.pop();
				f = 1;
				j++;
			} else {
				if (f == 0) {
					t->Left() = new BinaryNode<T>(preOrder[i]);
					t = t->Left();
				} else {
					f = 0;
					t->Right() = new BinaryNode<T>(preOrder[i]);
					t = t->Right();
				}
				path.push(t);
				i++;
			}
		}

		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::BuildTreeInOrderPostOrder(T * inOrder, int inLength, T * postOrder, int postLength)
	{
		if (inOrder == nullptr || postOrder == nullptr || inLength <= 0 || postLength <= 0 || inLength != postLength) return nullptr;

		T value = postOrder[postLength - 1];

		int index = -1;
		for (int i = 0; i < inLength; i++) {
			if (inOrder[i] == value) {
				index = i;
				break;
			}
		}

		if (index == -1) return nullptr;

		BinaryNode<T> * node = new BinaryNode<T>(value);

		node->Left() = BuildTreeInOrderPostOrder(inOrder, index, postOrder, index);
		node->Right() = BuildTreeInOrderPostOrder(inOrder + index + 1, inLength - 1 - index, postOrder + index, postLength - 1 - index);

		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::BuildTreeInOrderPostOrder2(T * inOrder, int inLength, T * postOrder, int postLength)
	{
		if (inOrder == nullptr || inLength <= 0 || postOrder == nullptr || postLength <= 0 || inLength != postLength) return nullptr;

		stack<BinaryNode<T> *> path;

		int i = postLength - 1; // index current element in postOrder
		int j = inLength - 1;   // index current element in inOrder
		int f = 0; // flag to insert to left or right

		// Root
		BinaryNode<T> * node = new BinaryNode<T>(postOrder[i]);
		path.push(node);

		// Current insertion point
		BinaryNode<T> * t = node;
		i--;

		while (i >= 0) {
			if (!path.empty() && path.top()->Value() == inOrder[j]) {
				// Done with a right subtree, start to insert the left subtree
				t = path.top();
				path.pop();
				f = 1;
				j--;
			} else {
				if (f == 0) {
					t->Right() = new BinaryNode<T>(postOrder[i]);
					t = t->Right();
				} else {
					f = 0;
					t->Left() = new BinaryNode<T>(postOrder[i]);
					t = t->Left();
				}
				path.push(t);
				i--;
			}
		}

		return node;
	}

	template<class T> void BinaryNode<T>::LevelOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		queue<BinaryNode *> q;
		q.push(node);
		while (!q.empty()) {
			node = q.front();
			q.pop();
			f(node->Value());
			if (node->Left() != nullptr) q.push(node->Left());
			if (node->Right() != nullptr) q.push(node->Right());
		}
	}

	template<class T> void BinaryNode<T>::LevelOrderWalk2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;

		vector<vector<T> *> levels;

		function<void(BinaryNode *, unsigned int)> preOrder = [&](BinaryNode * n, unsigned int l) {
			if (n == nullptr) return;

			if (levels.size() <= l) {
				levels.push_back(new vector<T>());
			}

			vector<T> * level = levels[l];
			level->push_back(n->Value());

			preOrder(n->Left(), l + 1);
			preOrder(n->Right(), l + 1);
		};

		preOrder(node, 0);

		for_each (levels.begin(), levels.end(), [&](vector<T> * level){
			for_each (level->begin(), level->end(), [&](T c){
				f(c);
			});
			delete level;
		});
	}

	template<class T> void BinaryNode<T>::LevelOrderWalkBottomUp(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;

		vector<vector<T>> levels;
		levels.push_back(vector<T> { node->Value() });

		queue<BinaryNode *> q[2];
		q[0].push(node);

		int l = 0;
		while (!q[0].empty() || !q[1].empty()) {
			queue<BinaryNode *> & current = q[l & 0x1];
			queue<BinaryNode *> & next = q[(1+l) & 0x1];
			vector<T> level;
			while (!current.empty()) {
				node = current.front();
				current.pop();
				if (node->Left() != nullptr) {
					level.push_back(node->Left()->Value());
					next.push(node->Left());
				}
				if (node->Right() != nullptr) {
					level.push_back(node->Right()->Value());
					next.push(node->Right());
				}
			}
			if (level.size() > 0) levels.insert(levels.begin(), level);
			l++;
		}

		for_each (levels.begin(), levels.end(), [&](vector<T> & level){
			for_each (level.begin(), level.end(), [&](T c){
				f(c);
			});
		});
	}

	template<class T> void BinaryNode<T>::GetBoundaryValues(BinaryNode<T> * node, vector<T> & values)
	{
		if (node == nullptr) return;

		values.push_back(node->Value());

		function<void(BinaryNode<T> *, bool)>
		searchLeft = [&](BinaryNode<T> * n, bool include) {
			if (n == nullptr) return;

			if (include
				|| n->Left() == nullptr && n->Right() == nullptr) {
				values.push_back(n->Value());
			}

			if (n->Left() != nullptr) searchLeft(n->Left(), include);

			if (n->Right() != nullptr) {
				// include the right child only if
				// its parent is included and has no left child
				searchLeft(n->Right(), include && n->Left() == nullptr);
			}
		};

		function<void(BinaryNode<T>*, bool)>
		searchRight = [&](BinaryNode<T> * n, bool include) {
			if (n == nullptr) return;

			if (n->Left() != nullptr) {
				// include the left child only if
				// its parent is included and has no right child
				searchRight(n->Left(), include && n->Right() == nullptr);
			}

			if (n->Right() != nullptr) searchRight(n->Right(), include);

			if (include
				|| n->Left() == nullptr && n->Right() == nullptr) {
				values.push_back(n->Value());
			}
		};

		searchLeft(node->Left(), true);
		searchRight(node->Right(), true);
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::Search(BinaryNode * node, const T & v)
	{
		if (node == nullptr || node->Value() == v) return node;
		BinaryNode<T> * left = Search(node->Left(), v);
		if (left != nullptr) return left;
		else return Search(node->Right(), v);
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::Min(BinaryNode * node)
	{
		if (node == nullptr) return node;
		BinaryNode<T> * left = Min(node->Left());
		BinaryNode<T> * right = Min(node->Right());
		BinaryNode<T> * min = node;
		if (left != nullptr && left->Value() < min->Value()) min = left;
		if (right != nullptr && right->Value() < min->Value()) min = right;
		return min;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::Max(BinaryNode * node)
	{
		if (node == nullptr) return node;
		BinaryNode<T> * left = Max(node->Left());
		BinaryNode<T> * right = Max(node->Right());
		BinaryNode<T> * max = node;
		if (left != nullptr && left->Value() > max->Value()) max = left;
		if (right != nullptr && right->Value() > max->Value()) max = right;
		return max;
	}
	
	// TODO: PostOrder with DP
	template<class T> BinaryNode<T> * BinaryNode<T>::LowestCommonAncestor(BinaryNode * node, BinaryNode * first, BinaryNode * second)
	{
		if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
		if (node == first || node == second) return node;

		function<int(BinaryNode<T> *, BinaryNode<T> *, BinaryNode<T> *)>
		hits = [&](BinaryNode<T> * n, BinaryNode<T> * f, BinaryNode<T> * s) -> int {
			if (n == nullptr) return 0;
			int h = hits(n->Left(), f, s) + hits(n->Right(), f, s);
			if (n == f || n == s) return 1 + h;
			else return h;
		};

		int h = hits(node->Left(), first, second);
		if (h == 1) return node;
		else if (h == 2) return LowestCommonAncestor(node->Left(), first, second);
		else return LowestCommonAncestor(node->Right(), first, second);
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::LowestCommonAncestor2(BinaryNode * node, BinaryNode * first, BinaryNode * second)
	{
		if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
		if (node == first || node == second) return node;
		BinaryNode<T> * left = LowestCommonAncestor2(node->Left(), first, second);
		BinaryNode<T> * right = LowestCommonAncestor2(node->Right(), first, second);
		if (left != nullptr && right != nullptr) return node;
		if (left != nullptr) return left;
		else return right;
	}

	// http://leetcode.com/2010/09/printing-binary-tree-in-zig-zag-level_18.html
	// Breadth-first-search using stack
	template<class T> void BinaryNode<T>::PrintZigZag(void)
	{
		stack<BinaryNode *> level[2];
		int l = 0;
		level[0].push(this);
		while (true) {
			stack<BinaryNode *> & current = level[l % 2];
			stack<BinaryNode *> & next = level[(l+1) % 2];
			while (!current.empty()) {
				BinaryNode * p = current.top();
				current.pop();
				cout << p->Value() << ' ';
				if (l % 2 == 0) {
					if (p->Left() != nullptr) next.push(p->Left());
					if (p->Right() != nullptr) next.push(p->Right());
				} else {
					if (p->Right() != nullptr) next.push(p->Right());
					if (p->Left() != nullptr) next.push(p->Left());
				}
			}
			cout << endl;
			if (next.empty()) break;
			l++;
		}
	}

	// Convert a binary tree to a linked list so that the list nodes
	// are linked by the left and right pointers and are in pre-order of original tree.
	// e.g.
	//      1
	//     / \
	//    2   5
	//   / \   \
	//  3   4   6
	// to
	//  1-2-3-4-5-6
	// This version builds a double-link list by setting node->left also.
	// If need a single-link list, just remove the statements setting node->left.
	template<class T> BinaryNode<T> * BinaryNode<T>::ToPreOrderLinkList(BinaryNode * node)
	{
		if (node == nullptr) return node;

		function<void(BinaryNode *, BinaryNode * &)>
		convert = [&](BinaryNode * head, BinaryNode * & tail){
			if (head == nullptr) {
				tail = nullptr;
				return;
			}

			if (head->Left() == nullptr && head->Right() == nullptr) {
				tail = head;
				return;
			}

			BinaryNode * leftTail = nullptr;
			convert(head->Left(), leftTail);

			BinaryNode * rightTail = nullptr;
			convert(head->Right(), rightTail);

			if (head->Left() != nullptr) {
				head->Left()->Left() = head;
				leftTail->Right() = head->Right();
				head->Right() = head->Left();
				head->Left() = nullptr;
				if (leftTail->Right() == nullptr) {
					tail = leftTail;
				} else {
					leftTail->Right()->Left() = leftTail;
					tail = rightTail;
				}
			} else {
				head->Right()->Left() = head;
				tail = rightTail;
			}
		};

		BinaryNode * tail;
		convert(node, tail);
		return node;
	}

	// Convert a binary tree to a linked list so that the list nodes
	// are linked by the left and right pointers and are in in-order of original tree.
	// e.g.
	//      1
	//     / \
	//    2   5
	//   / \   \
	//  3   4   6
	// to
	//  3-2-4-1-5-6
	// This version builds a double-link list by setting node->left also.
	// If need a single-link list, just remove the statements setting node->left.
	template<class T> BinaryNode<T> * BinaryNode<T>::ToInOrderLinkList(BinaryNode * node)
	{
		if (node == nullptr) return node;

		function<void(BinaryNode *, BinaryNode * &, BinaryNode * &)>
		convert = [&](BinaryNode * n, BinaryNode * & h, BinaryNode * & t) {
			h = nullptr;
			t = nullptr;
			if (n == nullptr) return;

			BinaryNode * leftHead = nullptr;
			BinaryNode * leftTail = nullptr;
			convert(n->Left(), leftHead, leftTail);

			BinaryNode * rightHead = nullptr;
			BinaryNode * rightTail = nullptr;
			convert(n->Right(), rightHead, rightTail);

			if (leftTail == nullptr) {
				leftHead = n;
				leftTail = n;
			} else {
				leftTail->Right() = n;
				n->Left() = leftTail;
			}

			if (rightHead == nullptr) {
				rightHead = n;
				rightTail = n;
			} else {
				rightHead->Left() = n;
				n->Right() = rightHead;
			}

			h = leftHead;
			t = rightTail;
		};

		BinaryNode<T> * head = nullptr;
		BinaryNode<T> * tail = nullptr;
		convert(node, head, tail);
		return head;
	}

	// Convert a binary tree to a linked list so that the list nodes
	// are linked by the left and right pointers and are in post-order of original tree.
	// e.g.
	//      1
	//     / \
	//    2   5
	//   / \   \
	//  3   4   6
	// to
	//  3-4-2-6-5-1
	// This version builds a double-link list by setting node->left also.
	// If need a single-link list, just remove the statements setting node->left.
	template<class T> BinaryNode<T> * BinaryNode<T>::ToPostOrderLinkList(BinaryNode * node)
	{
		if (node == nullptr) return node;

		function<void(BinaryNode * &, BinaryNode *)>
		convert = [&](BinaryNode * & head, BinaryNode * tail){
			if (tail == nullptr) {
				head = nullptr;
				return;
			}

			if (tail->Left() == nullptr && tail->Right() == nullptr) {
				head = tail;
				return;
			}

			BinaryNode * leftHead = nullptr;
			convert(leftHead, tail->Left());

			BinaryNode * rightHead = nullptr;
			convert(rightHead, tail->Right());

			if (tail->Right() != nullptr) {
				tail->Right()->Right() = tail;
				rightHead->Left() = tail->Left();
				tail->Left() = tail->Right();
				tail->Right() = nullptr;
				if (rightHead->Left() == nullptr) {
					head = rightHead;
				} else {
					rightHead->Left()->Right() = rightHead;
					head = leftHead;
				}
			} else {
				tail->Left()->Right() = tail;
				head = leftHead;
			}
		};

		BinaryNode * head;
		convert(head, node);
		return head;
	}

	template<class T> bool BinaryNode<T>::IsBalanced(BinaryNode * node)
	{
		if (node == nullptr) return true;

		function<bool(BinaryNode *, int &)>
		balanced = [&](BinaryNode * n, int & h)->bool{
			if (n == nullptr) {
				h = 0;
				return true;
			}

			if (n->Left() == nullptr && n->Right() == nullptr) {
				h = 1;
				return true;
			}

			int lh;
			bool l = balanced(n->Left(), lh);
			if (l == false) return false;

			int rh;
			bool r = balanced(n->Right(), rh);
			if (r == false) return false;

			if (lh - rh > 1 || rh - lh > 1) return false;

			h = 1 + (lh >= rh ? lh : rh);
			return true;
		};

		int height;
		bool isBalanced = balanced(node, height);
		return isBalanced;
	}

	// A tree is balanced if the heights of its left tree and right tree differs no more than 1.
	// This algorithm is wrong. A failed example is:
	//         1
	//     2       2
	//   3   3   3   3
	//  4 4 4 4 4 4
	// 5 5
	template<class T> bool BinaryNode<T>::IsBalanced2(BinaryNode * node)
	{
		if (node == nullptr) return true;

		int minDepth = INT_MAX;
		bool foundMinDepth = false;
		int depth = 0;
		queue<BinaryNode *> q[2];
		q[0].push(node);
		while (!q[0].empty() || !q[1].empty()) {
			queue<BinaryNode *> & current = q[depth & 0x1];
			queue<BinaryNode *> & next = q[(depth + 1) & 0x1];
			while (!current.empty()) {
				node = current.front();
				current.pop();
				if (node->Left() == nullptr && node->Right() == nullptr && !foundMinDepth) {
					foundMinDepth = true;
					minDepth = depth;
				}

				if (node->Left() != nullptr && node->Right() == nullptr) {
					if (node->Left()->Left() != nullptr || node->Left()->Right() != nullptr) return false;
				}

				if (node->Left() == nullptr && node->Right() != nullptr) {
					if (node->Right()->Left() != nullptr || node->Right()->Right() != nullptr) return false;
				}

				if (foundMinDepth && depth - minDepth > 1) return false;

				if (node->Left() != nullptr) next.push(node->Left());
				if (node->Right() != nullptr) next.push(node->Right());
			}

			depth++;
		}
		return true;
	}

	// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
	// For example, this binary tree is symmetric:
	//    1
	//   / \
	//  2   2
	// / \ / \
	// 3 4 4 3
	// But the following is not:
	//   1
	//  / \
	// 2   2
	//  \   \
	//   3   3
	template<class T> bool BinaryNode<T>::IsSymmetric(BinaryNode * node)
	{
		function<bool(BinaryNode *, BinaryNode *)>
		isSymmetric = [&](BinaryNode * left, BinaryNode * right) -> bool {
			if (left == nullptr && right == nullptr) return true;
			if (left != nullptr && right == nullptr
				|| left == nullptr && right != nullptr) return false;
			if (left->Value() != right->Value()) return false;
			if (!isSymmetric(left->Left(), right->Right())) return false;
			return isSymmetric(left->Right(), right->Left());
		};

		return isSymmetric(node, node);
	}

	// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
	// For example, this binary tree is symmetric:
	//    1
	//   / \
	//  2   2
	// / \ / \
	// 3 4 4 3
	// But the following is not:
	//   1
	//  / \
	// 2   2
	//  \   \
	//   3   3
	template<class T> bool BinaryNode<T>::IsSymmetric2(BinaryNode * node)
	{
		if (node == nullptr) return true;
		if (node->Left() == nullptr && node->Right() == nullptr) return true;
		if (node->Left() != nullptr && node->Right() == nullptr
			|| node->Left() == nullptr && node->Right() != nullptr) return false;
		if (node->Left()->Value() != node->Right()->Value()) return false;
		deque<BinaryNode *> q;
		q.push_front(node->Left());
		q.push_back(node->Right());
		while (!q.empty()) {
			BinaryNode * left = q.front();
			q.pop_front();
			BinaryNode * right = q.back();
			q.pop_back();
			if (left->Right() != nullptr && right->Left() == nullptr
				|| left->Right() == nullptr && right->Left() != nullptr) return false;
			if (left->Right() != nullptr && right->Left() != nullptr) {
				if (left->Right()->Value() != right->Left()->Value()) return false;
				q.push_front(left->Right());
				q.push_back(right->Left());
			}
			if (left->Left() != nullptr && right->Right() == nullptr
				|| left->Left() == nullptr && right->Right() != nullptr) return false;
			if (left->Left() != nullptr && right->Right() != nullptr) {
				if (left->Left()->Value() != right->Right()->Value()) return false;
				q.push_front(left->Left());
				q.push_back(right->Right());
			}
		}
		return true;
	}

	template<class T> void BinaryNode<T>::SwapValues(BinaryNode * first, BinaryNode * second)
	{
		if (first == nullptr || second == nullptr) return;
		T t = first->Value();
		first->Value() = second->Value();
		second->Value() = t;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::Clone1(BinaryNode * node)
	{
		if (node == nullptr) return nullptr;
		BinaryNode * newNode = new BinaryNode(node->Value());
		newNode->Left() = Clone1(node->Left());
		newNode->Right() = Clone1(node->Right());
		return newNode;
	}

	// Create a random binary search tree
	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeRandom(vector<T> & values)
	{
		if (values.size() == 0) return nullptr;
		sort(values.begin(), values.end());
		BinaryNode<T> * node = RandomTreeFromInOrder(values);
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeRandom(size_t maxSize)
	{
		vector<T> values;
		int size = rand() % (maxSize + 1);
		for (int i = 0; i < size; i++) {
			values.push_back(rand());
		}
		BinaryNode<T> * node = SearchTreeRandom(values);
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeInsert(BinaryNode * node, T value)
	{
		BinaryNode<T> * newNode = new BinaryNode<T>(value);
		if (node == nullptr) return newNode;
		BinaryNode<T> * parent = node;
		BinaryNode<T> * current = node;
		while (current != nullptr) {
			parent = current;
			if (value <= current->Value()) current = current->Left();
			else current = current->Right();
		}
		if (value <= parent->Value()) parent->Left() = newNode;
		else parent->Right() = newNode;
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeInsert2(BinaryNode * node, T value)
	{
		BinaryNode<T> * newNode = new BinaryNode<T>(value);
		if (node == nullptr) return newNode;
		BinaryNode<T> * current = node;
		while (true) {
			if (value <= current->Value()) {
				if (current->Left() == null) {
					current->Left() = newNode;
					break;
				} else {
					current = current->Left();
				}
			} else {
				if (current->Right() == null) {
					current->Right() = newNode;
					break;
				} else {
					current = current->Right();
				}
			}
		}
		return node;
	}

	// Verify if a subtree at node is a valid binary search tree.
	template<class T> bool BinaryNode<T>::SearchTreeVerify(BinaryNode<T> * node)
	{
		if (node == nullptr) return true;

		// ensure min < n->Value() <= max
		function<bool(BinaryNode<T> *, T, T)> between = [&](BinaryNode<T> * n, T min, T max) -> bool {
			if (n == nullptr) return true;
			if (n->Value() <= min || n->Value() > max) return false;
			return between(n->Left(), min, n->Value()) && between(n->Right(), n->Value(), max);
		};

		// ensure n->Value() <= max
		function<bool(BinaryNode<T> *, T)> less = [&](BinaryNode<T> * n, T max) -> bool {
			if (n == nullptr) return true;
			if (n->Value() > max) return false;
			return less(n->Left(), n->Value()) && between(n->Right(), n->Value(), max);
		};

		// ensure min < n->Value()
		function<bool(BinaryNode<T> *, T)> greater = [&](BinaryNode<T> * n, T min) -> bool {
			if (n == nullptr) return true;
			if (n->Value() <= min) return false;
			return greater(n->Right(), n->Value()) && between(n->Left(), min, n->Value());
		};

		return less(node->Left(), node->Value()) && greater(node->Right(), node->Value());
	}

	template<class T> bool BinaryNode<T>::SearchTreeVerify2(BinaryNode<T> * node)
	{
		function<bool(BinaryNode<T> *, T &, T &)>
		verify = [&](BinaryNode<T> * n, T & min, T & max) -> bool {
			if (n == nullptr) return true;
			if (n->Left() == nullptr && n->Right() == nullptr) {
				min = n->Value();
				max = n->Value();
				return true;
			}

			if (n->Left() == nullptr) {
				min = n->Value();
			} else {
				T leftMin;
				T leftMax;
				if (!verify(n->Left(), leftMin, leftMax)) return false;
				if (leftMax > n->Value()) return false;
				min = leftMin;
			}

			if (n->Right() == nullptr) {
				max = n->Value();
			} else {
				T rightMin;
				T rightMax;
				if (!verify(n->Right(), rightMin, rightMax)) return false;
				if (rightMin <= n->Value()) return false;
				max = rightMax;
			}

			return true;
		};

		T min;
		T max;
		return verify(node, min, max);
	}

	template<class T> bool BinaryNode<T>::SearchTreeVerify3(BinaryNode<T> * node)
	{
		if (node == nullptr) return true;
		stack<BinaryNode<T> *> path;
		path.push(node);
		BinaryNode<T> * prev = nullptr; // InOrder previous node
		BinaryNode<T> * lastVisited = nullptr;
		while (!path.empty()) {
			node = path.top();
			if (node->Right() != nullptr && node->Right() == lastVisited) {
				path.pop();
			} else if (node->Left() != nullptr && node->Left() != lastVisited) {
				path.push(node->Left());
			} else {
				if (prev != nullptr) {
					if (prev->Right() == node) {
						if (prev->Value() >= node->Value()) return false;
					} else {
						if (prev->Value() > node->Value()) return false;
					}
				}
				prev = node;
				if (node->Right() == nullptr) path.pop();
				else path.push(node->Right());
			}
			lastVisited = node;
		}
		return true;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeSearch(BinaryNode * node, T value)
	{
		if (node == nullptr || node->Value() == value) return node;
		if (value <= node->Value()) return SearchTreeSearch(node->Left(), value);
		else return SearchTreeSearch(node->Right(), value);
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeSearch2(BinaryNode * node, T value)
	{
		if (node == nullptr || node->Value() == value) return node;
		while (node != nullptr && node->Value() != value) {
			if (value <= node->Value())	node = node->Left();
			else node = node->Right();
		}
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeMin(BinaryNode * node)
	{
		if (node == nullptr) return nullptr;
		while (node->Left() != nullptr) node = node->Left();
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeMax(BinaryNode * node)
	{
		if (node == nullptr) return node;
		while (node->Right() != nullptr) node = node->Right();
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeLowestCommonAncestor(BinaryNode<T> * node, const T & first, const T & second)
	{
		if (node == nullptr) return nullptr;
		while (node != nullptr) {
			if (node->Value() > std::max(first, second))
				node = node->Left();
			else if (node->Value() < std::min(first, second))
				node = node->Right();
			else
				break;
		}
		return node;
	}

	template<class T> void BinaryNode<T>::SearchTreeSerialize(BinaryNode * node, ostream & output)
	{
		function<void(T)> serialize = [&](T v) { output << v << ' '; };
		PreOrderWalk(node, serialize);
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeDeserialize(istream & input)
	{
		function<void(T, T, T &, BinaryNode<T> * &)>
		deserialize = [&](T l, T h, T & value, BinaryNode<T> * & node) {
			if (l < value && value <= h) {
				T v = value;
				node = new BinaryNode<T>(v);
				input >> value;
				if (input.good() && !input.eof()) {
					deserialize(l, v, value, node->Left());
					deserialize(v, h, value, node->Right());
				}
			}
		};

		function<void(T, T &, BinaryNode<T> * &)>
		deserializeLeft = [&](T p, T & value, BinaryNode<T> * & node) {
			if (value <= p) {
				T v = value;
				node = new BinaryNode<T>(v);
				input >> value;
				if (input.good() && !input.eof()) {
					deserializeLeft(v, value, node->Left());
					deserialize(v, p, value, node->Right());
				}
			}
		};

		function<void(T, T &, BinaryNode<T> * &)>
		deserializeRight = [&](T p, T & value, BinaryNode<T> * & node) {
			if (value > p) {
				T v = value;
				node = new BinaryNode<T>(v);
				input >> value;
				if (input.good() && !input.eof()) {
					deserialize(p, v, value, node->Left());
					deserializeRight(v, value, node->Right());
				}
			}
		};

		BinaryNode<T> * node = nullptr;
		T value;
		input >> value;
		if (input.good() && !input.eof()) {
			node = new BinaryNode<T>(value);
			input >> value;
			if (input.good() && !input.eof()) {
				deserializeLeft(node->Value(), value, node->Left());
				deserializeRight(node->Value(), value, node->Right());
			}
		}
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeDeserialize2(istream & input)
	{
		BinaryNode<T> * node = nullptr;
		T value;
		input >> value;
		while (input.good() && !input.eof()) {
			node = SearchTreeInsert(node, value);
			input >> value;
		}
		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeDeserialize3(istream & input)
	{
		BinaryNode<T> * node = nullptr;
		T value;
		input >> value;
		if(input.good() && !input.eof()) node = new BinaryNode<T>(value);
		else return node;
		stack<BinaryNode<T> *> path;
		path.push(node);
		BinaryNode<T> * prev = nullptr;
		while (true) {
			input >> value;
			if (!input.good() || input.eof()) break;
			BinaryNode<T> * n = new BinaryNode<T>(value);
			if (!path.empty() && value <= path.top()->Value()) {
				path.top()->Left() = n;
			} else {
				while (!path.empty() && path.top()->Value() < value) {
					prev = path.top();
					path.pop();
				}
				if (prev != nullptr) prev->Right() = n;
			}
			path.push(n);
		}
		return node;
	}

	// Two elements of a binary search tree are swapped by mistake.
	// Recover the tree without changing its structure.
	// If we traverse a binary search tree in-order, we will get an increasing
	// sequence, e.g.,
	//    1, 2, 3, 4, 5, 6, 7, .......
	// If two neighboring elements are swapped, we will have one inversion, e.g.,
	//    1, 2, 4, 3, 5, 6, 7, .......
	// If two non-neighboring elements are swapped, we will have two inversions, e.g.,
	//    1, 2, 3, 6, 5, 4, 7, ....... , or
	//    1, 2, 6, 4, 5, 3, 7, .......
	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeRecover(BinaryNode * node)
	{
		if (node == nullptr || node->Left() == nullptr && node->Right() == nullptr) return node;

		// Track the first inversion
		BinaryNode * n1 = nullptr;
		BinaryNode * n2 = nullptr;
		// Track the second inversion
		BinaryNode * n3 = nullptr;
		BinaryNode * n4 = nullptr;

		stack<BinaryNode *> path;
		path.push(node);

		// Track the in-order previous and current nodes
		BinaryNode * prev = nullptr;
		BinaryNode * current = nullptr;
		// Track the last visited node
		BinaryNode * lastVisited = nullptr;

		while (!path.empty()) {
			current = path.top();
			if (current->Right() != nullptr && current->Right() == lastVisited) {
				path.pop();
			} else if (current->Left() != nullptr && current->Left() != lastVisited) {
				path.push(current->Left());
			} else {
				if (prev != nullptr && prev->Value() > current->Value()) {
					if (n1 == nullptr && n2 == nullptr) {
						n1 = prev;
						n2 = current;
					} else {
						n3 = prev;
						n4 = current;
						break;
					}
				}
				prev = current;
				if (current->Right() == nullptr) path.pop();
				else path.push(current->Right());
			}
			lastVisited = current;
		}

		if (n3 == nullptr && n4 == nullptr
			&& n1 != nullptr && n2 != nullptr) {
			SwapValues(n1, n2);
		} else if (n3 != nullptr && n4 != nullptr
			&& n1 != nullptr && n2 != nullptr) {
			SwapValues(n1, n4);
		}

		return node;
	}

	template<class T> BinaryNode<T> * BinaryNode<T>::SearchTreeRecover2(BinaryNode * node)
	{
		if (node == nullptr || node->Left() == nullptr && node->Right() == nullptr) return node;

		function<void(BinaryNode *, BinaryNode * &, BinaryNode * &, BinaryNode * &, BinaryNode * &, BinaryNode * &)>
		search = [&](
			BinaryNode * current,
			BinaryNode * & prev,
			BinaryNode * & n1,
			BinaryNode * & n2,
			BinaryNode * & n3,
			BinaryNode * & n4)
		{
			if (current == nullptr) return;

			search(current->Left(), prev, n1, n2, n3, n4);

			if (prev != nullptr && prev->Value() > current->Value()) {
				if (n1 == nullptr && n2 == nullptr) {
					n1 = prev;
					n2 = current;
				} else {
					n3 = prev;
					n4 = current;
					return;
				}
			}

			prev = current;

			search(current->Right(), prev, n1, n2, n3, n4);
		};

		BinaryNode * prev = nullptr;
		BinaryNode * n1 = nullptr;
		BinaryNode * n2 = nullptr;
		BinaryNode * n3 = nullptr;
		BinaryNode * n4 = nullptr;
		search(node, prev, n1, n2, n3, n4);

		if (n3 == nullptr && n4 == nullptr
			&& n1 != nullptr && n2 != nullptr) {
			SwapValues(n1, n2);
		} else if (n3 != nullptr && n4 != nullptr
			&& n1 != nullptr && n2 != nullptr) {
			SwapValues(n1, n4);
		}

		return node;
	}
}