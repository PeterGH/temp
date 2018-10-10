#pragma once
#include <set>
#include "BinaryNode.h"
using namespace std;
namespace Test {
	template<class T> class BinaryNodeWithParent : public BinaryNode<T> {
	public:
		BinaryNodeWithParent(const T & v) : BinaryNode<T>(v)
		{
			this->Neighbor(2) = nullptr;
		}

		virtual ~BinaryNodeWithParent(void) {}

		// Get the reference of parent pointer
		BinaryNodeWithParent * & Parent(void) { return (BinaryNodeWithParent * &)this->Neighbor(2); }
		// Set the parent pointer
		virtual void Parent(BinaryNode * parent) { this->Neighbor(2) = parent; }

		// Create a random binary tree
		// Return nullptr if input is empty
		static BinaryNodeWithParent * RandomTree2(vector<T> & values);
		// May return nullptr
		static BinaryNodeWithParent * RandomTree2(size_t maxSize);

		// Non-recursive without stack
		static void PreOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f);
		void PreOrderWalkWithOutStack(function<void(T)> f) { PreOrderWalkWithOutStack(this, f); }

		// Non-recursive without stack
		static void InOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f);
		void InOrderWalkWithOutStack(function<void(T)> f) { InOrderWalkWithOutStack(this, f); }

		// Non-recursive without stack
		static void PostOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f);
		void PostOrderWalkWithOutStack(function<void(T)> f) { PostOrderWalkWithOutStack(this, f); }

		static BinaryNodeWithParent<T> * LowestCommonAncestor(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second);
		static BinaryNodeWithParent<T> * LowestCommonAncestor2(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second);

		// Count height of tree rooted at node
		// Non-recursive
		static int Height2(BinaryNodeWithParent * node);
		int Height2(void) { return Height2(this); }

		// Count the distance of node from the root
		static int Depth(BinaryNodeWithParent * node);
		int Depth(void) { return Depth(this); }

		static BinaryNodeWithParent * Clone2(BinaryNode * node);
		BinaryNodeWithParent * Clone2(void) { return Clone2(this); }

		// Find the lagest binary search tree in a binary tree. http://leetcode.com/2010/11/largest-binary-search-tree-bst-in_22.html
		static BinaryNodeWithParent * MaxSearchTreeInBinaryTree(BinaryNode<T> * binaryTree);
		static BinaryNodeWithParent * MaxSearchTreeInBinaryTree2(BinaryNode<T> * binaryTree);

		// Find the lagest binary search sub tree in a binary tree. http://leetcode.com/2010/11/largest-binary-search-tree-bst-in.html
		static BinaryNodeWithParent * MaxSubSearchTreeInBinaryTree(BinaryNode<T> * binaryTree);
		static BinaryNodeWithParent * MaxSubSearchTreeInBinaryTree2(BinaryNode<T> * binaryTree);

		//
		// Binary Search Tree
		//

		static BinaryNodeWithParent<T> * SearchTreeSuccessor(BinaryNodeWithParent<T> * node);
		static BinaryNodeWithParent<T> * SearchTreePredecessor(BinaryNodeWithParent<T> * node);

		// Delete a node from a binary search tree. Return the root of tree.
		static BinaryNodeWithParent<T> * SearchTreeDelete(BinaryNodeWithParent<T> * tree, BinaryNodeWithParent<T> * node);
	};

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::RandomTree2(vector<T> & values)
	{
		if (values.size() == 0) return nullptr;

		BinaryNode<T> * n = RandomTreeFromInOrder(values);
		BinaryNodeWithParent<T> * node = Clone2(n);
		DeleteTree(n);
		return node;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::RandomTree2(size_t maxSize)
	{
		vector<T> values;
		int size = rand() % (maxSize + 1);
		for (int i = 0; i < size; i++) {
			values.push_back(rand());
		}
		BinaryNodeWithParent<T> * node = RandomTree2(values);
		return node;
	}

	// Non-recursive without stack
	template<class T> void BinaryNodeWithParent<T>::PreOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		BinaryNodeWithParent * prev = node;
		while (node != nullptr) {
			if (prev == node->Right()) {
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				f(node->Value());
				prev = node;
				node = (BinaryNodeWithParent<T> *)node->Left();
			} else {
				if (node->Left() == nullptr) f(node->Value());
				prev = node;
				if (node->Right() == nullptr) node = node->Parent();
				else node = (BinaryNodeWithParent<T> *)node->Right();
			}
		}
	}

	// Non-recursive without stack
	template<class T> void BinaryNodeWithParent<T>::InOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		BinaryNodeWithParent * prev = node;
		while (node != nullptr) {
			if (prev == node->Right()) {
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				prev = node;
				node = (BinaryNodeWithParent<T> *)node->Left();
			} else {
				f(node->Value());
				prev = node;
				if (node->Right() == nullptr) node = node->Parent();
				else node = (BinaryNodeWithParent<T> *)node->Right();
			}
		}
	}

	template<class T> void BinaryNodeWithParent<T>::PostOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		BinaryNodeWithParent * prev = node;
		while (node != nullptr) {
			if (prev == node->Right()) {
				f(node->Value());
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				prev = node;
				node = (BinaryNodeWithParent<T> *)node->Left();
			} else {
				prev = node;
				if (node->Right() == nullptr) {
					f(node->Value());
					node = node->Parent();
				} else {
					node = (BinaryNodeWithParent<T> *)node->Right();
				}
			}
		}
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::LowestCommonAncestor(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second)
	{
		if (first == nullptr || second == nullptr) return nullptr;
		set<BinaryNodeWithParent<T> *> visited;
		pair<set<BinaryNodeWithParent<T> *>::iterator, bool> result;
		auto checkAndMoveUp = [&](BinaryNodeWithParent<T> ** p) -> bool {
			if (*p != nullptr) {
				// set.insert returns a pair, where the second value is a bool indicating
				// whether the first value points to a new element or an existing element.
				result = visited.insert(*p);
				if (!result.second) {
					// Insert failed because the same element already exists
					return true;
				}
				*p = (*p)->Parent();
			}
			return false;
		};

		while (first != nullptr || second != nullptr) {
			if (checkAndMoveUp(&first)) return first;
			if (checkAndMoveUp(&second)) return second;
		}
		return nullptr;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::LowestCommonAncestor2(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second)
	{
		if (first == nullptr || second == nullptr) return nullptr;
		int df = first->Depth();
		int ds = second->Depth();
		int dd = df > ds ? df - ds : ds - df;
		BinaryNodeWithParent<T> * h = df < ds ? first : second;
		BinaryNodeWithParent<T> * l = df < ds ? second : first;
		for (int i = 0; i < dd; i++) {
			l = l->Parent();
		}
		while (h != nullptr && l != nullptr) {
			if (h == l) return h;
			h = h->Parent();
			l = l->Parent();
		}
		return nullptr;
	}

	// Count height of tree rooted at node
	// Non-recursive
	template<class T> int BinaryNodeWithParent<T>::Height2(BinaryNodeWithParent * node)
	{
		if (node == nullptr) return 0;
		BinaryNodeWithParent * prev = node;
		// Track the maximum height while traversing the tree
		int max = 0;
		// Track the height of current node
		int h = 0;
		while (node != nullptr) {
			if (prev == node->Right()) {
				// h is the height of right
				// Minus one to get the height of node
				h--;
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				// h is the height of node
				// Plus one to get the height of left child
				h++;
				if (h > max) max = h;
				prev = node;
				node = (BinaryNodeWithParent *)node->Left();
			} else {
				if (node->Left() == prev) {
					// h is the height of left
					// Minus one to get the height of node
					h--;
				} else if (node->Left() == nullptr) {
					// h is the height of parent
					// Plus one to get the height of node
					h++;
					if (h > max) max = h;
				}

				prev = node;
				if (node->Right() == nullptr) node = node->Parent();
				else node = (BinaryNodeWithParent *)node->Right();
			}
		}
		return max;
	}

	// Count the distance of node from the root
	template<class T> int BinaryNodeWithParent<T>::Depth(BinaryNodeWithParent * node)
	{
		int d = 0;
		while (node != nullptr) {
			d++;
			node = node->Parent();
		}
		return d;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::Clone2(BinaryNode<T> * node)
	{
		if (node == nullptr) return nullptr;
		BinaryNodeWithParent * newNode = new BinaryNodeWithParent(node->Value());
		BinaryNodeWithParent * left = Clone2(node->Left());
		if (left != nullptr) {
			newNode->Left() = left;
			left->Parent() = newNode;
		}
		BinaryNodeWithParent * right = Clone2(node->Right());
		if (right != nullptr) {
			newNode->Right() = right;
			right->Parent() = newNode;
		}
		return newNode;
	}

	// Bottom-up recursively to find the max search tree
	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::MaxSearchTreeInBinaryTree(BinaryNode<T> * binaryTree)
	{
		// Given a binary search tree, find the first node less than or equal to a value
		function<BinaryNodeWithParent<T> * (BinaryNodeWithParent<T> *, T)>
		firstNodeLessThanOrEqual = [&](BinaryNodeWithParent<T> * n, T v) -> BinaryNodeWithParent<T> * {
			while (n != nullptr) {
				if (n->Value() <= v) {
					// Implicitly, n is its parent's left child. Otherwise,
					// its parent should be returned.
					return n;
				}
				if (n->Left() != nullptr) n = (BinaryNodeWithParent<T> *)n->Left();
				else n = (BinaryNodeWithParent<T> *)n->Right();
			}
			return n;
		};

		// Given a binary search tree, find the first node greater than a value
		function<BinaryNodeWithParent<T> * (BinaryNodeWithParent<T> *, T)>
		firstNodeGreaterThan = [&](BinaryNodeWithParent<T> * n, T v) -> BinaryNodeWithParent<T> * {
			while (n != nullptr) {
				if (n->Value() > v) {
					// Implicitly, n is its parent's right child. Otherwise,
					// its parent should be returned.
					return n;
				}
				if (n->Right() != nullptr) n = (BinaryNodeWithParent<T> *)n->Right();
				else n = (BinaryNodeWithParent<T> *)n->Left();
			}
			return n;
		};

		// Merge the binary search tree in left subtree with current node to form a new binary search tree
		function<void(BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> *, int)>
		mergeLeft = [&](BinaryNodeWithParent<T> * & node, int & count, BinaryNodeWithParent<T> * left, int leftCount) {
			BinaryNodeWithParent<T> * clone = Clone2(left);
			BinaryNodeWithParent<T> * invalid = firstNodeGreaterThan(clone, node->Value());
			int invalidSize = invalid == nullptr ? 0 : Size(invalid);
			node->Left() = clone;
			clone->Parent() = node;
			count += (leftCount - invalidSize);
			if (invalid != nullptr) {
				BinaryNodeWithParent<T> * p = invalid->Parent();
				p->Right() = nullptr;
				DeleteTree(invalid);
			}
		};

		// Merge the binary search tree in right subtree with current node to form a new binary search tree
		function<void(BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> *, int)>
		mergeRight = [&](BinaryNodeWithParent<T> * & node, int & count, BinaryNodeWithParent<T> * right, int rightCount) {
			BinaryNodeWithParent<T> * clone = Clone2(right);
			BinaryNodeWithParent<T> * invalid = firstNodeLessThanOrEqual(clone, node->Value());
			int invalidSize = invalid == nullptr ? 0 : Size(invalid);
			node->Right() = clone;
			clone->Parent() = node;
			count += (rightCount - invalidSize);
			if (invalid != nullptr) {
				BinaryNodeWithParent<T> * p = invalid->Parent();
				p->Left() = nullptr;
				DeleteTree(invalid);
			}
		};

		function<void(BinaryNode<T> *, BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> * &, int &)>
		search = [&](
			BinaryNode<T> * node,                // current node from input binary tree
			BinaryNodeWithParent<T> * & current, // root of current search tree
			int & currentCount,                  // node count of current search tree
			BinaryNodeWithParent<T> * & last,    // root of last max search tree. can be current or different.
			int & lastCount                      // node count of last max search tree.
			)
		{
			if (node == nullptr) {
				current = nullptr;
				currentCount = 0;
				last = nullptr;
				lastCount = 0;
				return;
			}

			BinaryNodeWithParent<T> * left;
			int leftCount;
			BinaryNodeWithParent<T> * leftLast;
			int leftLastCount;
			search(node->Left(), left, leftCount, leftLast, leftLastCount);

			BinaryNodeWithParent<T> * right;
			int rightCount;
			BinaryNodeWithParent<T> * rightLast;
			int rightLastCount;
			search(node->Right(), right, rightCount, rightLast, rightLastCount);

			current = new BinaryNodeWithParent<T>(node->Value());
			currentCount = 1;

			if (left != nullptr && left->Value() <= current->Value()) {
				mergeLeft(current, currentCount, left, leftCount);
			}

			if (right != nullptr && right->Value() > current->Value()) {
				mergeRight(current, currentCount, right, rightCount);
			}

			if (leftLastCount >= rightLastCount) {
				last = leftLast;
				lastCount = leftLastCount;
			} else {
				last = rightLast;
				lastCount = rightLastCount;
			}

			if (currentCount >= lastCount) {
				last = current;
				lastCount = currentCount;
			}

			if (left != last) DeleteTree(left);
			if (right != last) DeleteTree(right);
			if (leftLast != last && leftLast != left) DeleteTree(leftLast);
			if (rightLast != last && rightLast != right) DeleteTree(rightLast);
		};

		BinaryNodeWithParent<T> * node;
		int count;
		BinaryNodeWithParent<T> * last;
		int lastCount;
		search(binaryTree, node, count, last, lastCount);

		if (node != last) {
			if (count >= lastCount) {
				DeleteTree(last);
				last = node;
			} else {
				DeleteTree(node);
			}
		}
		return last;
	}

	// This implementation follows http://leetcode.com/2010/11/largest-binary-search-tree-bst-in_22.html
	// However, the algorithm is wrong. The algorithm uses the node value to define a range to search sub solutions in its children.
	// But the range may rule out possible solutions containing nodes outside of the range. Some examples are shown in test.
	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::MaxSearchTreeInBinaryTree2(BinaryNode<T> * binaryTree)
	{
		T binaryTreeMin = Min(binaryTree)->Value();
		T binaryTreeMax = Max(binaryTree)->Value();

		function<void(BinaryNode<T> *, T, T, BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> * &, int &)>
		search = [&](
			BinaryNode<T> * node,                // current node from input binary tree
			T min,                               // lower bound of node value
			T max,                               // upper bound of node value
			BinaryNodeWithParent<T> * & current, // root of current search tree
			int & currentCount,                  // node count of current search tree
			BinaryNodeWithParent<T> * & last,    // root of last max search tree. can be current or different.
			int & lastCount                      // node count of last max search tree.
			)
		{
			if (node == nullptr) {
				current = nullptr;
				currentCount = 0;
				last = nullptr;
				lastCount = 0;
				return;
			}

			if (min < node->Value() && node->Value() <= max) {
				BinaryNodeWithParent<T> * left;
				int leftCount;
				BinaryNodeWithParent<T> * leftLast;
				int leftLastCount;
				search(node->Left(), min, node->Value(), left, leftCount, leftLast, leftLastCount);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				BinaryNodeWithParent<T> * rightLast;
				int rightLastCount;
				search(node->Right(), node->Value(), max, right, rightCount, rightLast, rightLastCount);

				current = new BinaryNodeWithParent<T>(node->Value());
				currentCount = 1;

				if (left != nullptr) {
					current->Left() = left;
					left->Parent() = current;
					currentCount += leftCount;
				}

				if (right != nullptr) {
					current->Right() = right;
					right->Parent() = current;
					currentCount += rightCount;
				}

				if (leftLastCount >= rightLastCount) {
					last = leftLast;
					lastCount = leftLastCount;
				} else {
					last = rightLast;
					lastCount = rightLastCount;
				}

				if (currentCount >= lastCount) {
					last = current;
					lastCount = currentCount;
				}

				if (left != current->Left() && left != last) DeleteTree(left);
				if (right != current->Right() && right != last) DeleteTree(right);
				if (leftLast != last && leftLast != left) DeleteTree(leftLast);
				if (rightLast != last && rightLast != right) DeleteTree(rightLast);
			} else {
				search(node, binaryTreeMin - 1, binaryTreeMax + 1, current, currentCount, last, lastCount);
				current = nullptr;
				currentCount = 0;
			}
		};

		BinaryNodeWithParent<T> * node;
		int count;
		BinaryNodeWithParent<T> * last;
		int lastCount;
		search(binaryTree, binaryTreeMin - 1, binaryTreeMax + 1, node, count, last, lastCount);

		if (node != last) {
			if (count >= lastCount) {
				DeleteTree(last);
				last = node;
			} else {
				DeleteTree(node);
			}
		}
		return last;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::MaxSubSearchTreeInBinaryTree(BinaryNode<T> * binaryTree)
	{
		function<void(BinaryNode<T> * &, BinaryNodeWithParent<T> * &, int &, T &, T &)>
		search = [&](
			BinaryNode<T> * & node,              // current node from input binary tree. updated to the node corresponding to current.
			BinaryNodeWithParent<T> * & current, // root of current search tree
			int & currentCount,                  // node count of current search tree
			T & currentMin,                      // min of current search tree
			T & currentMax                       // max of current search tree
			)
		{
			if (node == nullptr) {
				current = nullptr;
				currentCount = 0;
				return;
			}

			BinaryNode<T> * leftChild = node->Left();
			BinaryNodeWithParent<T> * left;
			int leftCount;
			T leftMin;
			T leftMax;
			search(leftChild, left, leftCount, leftMin, leftMax);

			BinaryNode<T> * rightChild = node->Right();
			BinaryNodeWithParent<T> * right;
			int rightCount;
			T rightMin;
			T rightMax;
			search(rightChild, right, rightCount, rightMin, rightMax);

			if ((left == nullptr || (leftChild == node->Left() && leftMax <= node->Value()))
				&& (right == nullptr || (rightChild == node->Right() && rightMin > node->Value()))) {
				// Left sub search tree and right sub search tree are both children of node. Merge them.
				current = new BinaryNodeWithParent<T>(node->Value());
				current->Left() = left;
				if (left != nullptr) left->Parent() = current;
				current->Right() = right;
				if (right != nullptr) right->Parent() = current;
				currentCount = 1 + leftCount + rightCount;
				currentMin = left == nullptr ? node->Value() : leftMin;
				currentMax = right == nullptr ? node->Value() : rightMax;
			} else {
				if (leftCount >= rightCount) {
					// Set node to the left sub search tree. It will be bottomed up to check if a merge at its parent is possible.
					node = leftChild;
					current = left;
					currentCount = leftCount;
					currentMin = leftMin;
					currentMax = leftMax;
					if (right != nullptr) DeleteTree(right);
				} else {
					// Set node to the right sub search tree. It will be bottomed up to check if a merge at its parent is possible.
					node = rightChild;
					current = right;
					currentCount = rightCount;
					currentMin = rightMin;
					currentMax = rightMax;
					if (left != nullptr) DeleteTree(left);
				}
			}
		};

		BinaryNodeWithParent<T> * node;
		int count;
		T min;
		T max;
		search(binaryTree, node, count, min, max);
		return node;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::MaxSubSearchTreeInBinaryTree2(BinaryNode<T> * binaryTree)
	{
		// Record subtrees already verified to avoid re-verification
		map<BinaryNode<T> *, int> subtrees;

		function<bool(BinaryNode<T> *, T &, T &, int &)>
		isSearchTree = [&](BinaryNode<T> * node, T & min, T & max, int & count) -> bool {
			count = 0;
			if (node == nullptr) return true;
			min = node->Value();
			max = node->Value();
			if (subtrees.find(node) != subtrees.end()) {
				count = subtrees[node];
				return count >= 0;
			}

			T leftMin;
			T leftMax;
			int leftCount;
			bool leftTrue = isSearchTree(node->Left(), leftMin, leftMax, leftCount);

			T rightMin;
			T rightMax;
			int rightCount;
			bool rightTrue = isSearchTree(node->Right(), rightMin, rightMax, rightCount);

			if (!leftTrue
				|| !rightTrue
				|| (node->Left() != nullptr && leftMax > node->Value())
				|| (node->Right() != nullptr && rightMin <= node->Value())) {
				subtrees[node] = -1;
				return false;
			}

			min = node->Left() == nullptr ? node->Value() : leftMin;
			max = node->Right() == nullptr ? node->Value() : rightMax;
			count += (1 + leftCount + rightCount);
			subtrees[node] = count;
			return true;
		};

		function<void(BinaryNode<T> *, BinaryNodeWithParent<T> * &, int &)>
		search = [&](
			BinaryNode<T> * node,                // current node from input binary tree
			BinaryNodeWithParent<T> * & current, // root of current search tree
			int & currentCount                   // node count of current search tree
			)
		{
			if (node == nullptr) {
				current = nullptr;
				currentCount = 0;
				return;
			}

			T min;
			T max;
			if (isSearchTree(node, min, max, currentCount)) {
				current = BinaryNodeWithParent<T>::Clone2(node);
			} else {
				BinaryNodeWithParent<T> * left;
				int leftCount;
				search(node->Left(), left, leftCount);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				search(node->Right(), right, rightCount);

				if (leftCount >= rightCount) {
					current = left;
					currentCount = leftCount;
					if (right != nullptr) DeleteTree(right);
				} else {
					current = right;
					currentCount = rightCount;
					if (left != nullptr) DeleteTree(left);
				}
			}
		};

		BinaryNodeWithParent<T> * node;
		int count;
		search(binaryTree, node, count);
		return node;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::SearchTreeSuccessor(BinaryNodeWithParent<T> * node)
	{
		if (node == nullptr) return node;
		//  (A)
		//  / \
		// () (B)
		// The successor of A is the minimum node of subtree B
		if (node->Right() != nullptr) return (BinaryNodeWithParent<T> *)SearchTreeMin(node->Right());
		//    (B)
		//   /
		// (C)
		//   \
		//    ()
		//      \
		//      (A)
		//      / \
		//     () NULL
		// The successor of A is the lowest ancestor B whose left child C contains A in its right substree
		BinaryNodeWithParent<T> * parent = node->Parent();
		while (parent != nullptr && node == parent->Right()) {
			node = parent;
			parent = parent->Parent();
		}
		// parent could be NULL if node is the maximum node of tree, i.e.,
		//
		//  (A)
		//  / \
		// () NULL
		//
		// or
		//
		// ()
		//   \
		//   (A)
		//   / \
		//  () NULL
		return parent;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::SearchTreePredecessor(BinaryNodeWithParent<T> * node)
	{
		if (node == nullptr) return nullptr;
		//   (A)
		//   /
		// (B)
		// The predecessor of A is the maximum node of subtree B
		if (node->Left() != nullptr) return (BinaryNodeWithParent<T> *)SearchTreeMax(node->Left());
		//     (B)
		//       \
		//       (C)
		//       /
		//      ()
		//     /
		//   (A)
		//   / \
		// NULL ()
		// The predecessor of A is the lowest ancestor B whose right child C contains A in its left substree
		BinaryNodeWithParent<T> * parent = node->Parent();
		while (parent != nullptr && node == parent->Left()) {
			node = parent;
			parent = parent->Parent();
		}
		// parent could be NULL if node is the minimum node of tree, i.e.,
		//
		//   (A)
		//   / \
		// NULL ()
		//
		// or
		//
		//      ()
		//     /
		//   (A)
		//   / \
		// NULL ()
		return parent;
	}

	// Delete a node from a binary search tree. Return the root of tree.
	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::SearchTreeDelete(BinaryNodeWithParent<T> * tree, BinaryNodeWithParent<T> * node)
	{
		if (tree == nullptr || node == nullptr) return tree;

		// Replace the subtree at dst with the subtree at src. Return dst.
		auto transplant = [&](BinaryNodeWithParent<T> * dst, BinaryNodeWithParent<T> * src) -> BinaryNodeWithParent<T> * {
			if (dst == nullptr) return dst;
			if (dst->Parent() == nullptr) {
				// src becomes the new root
				if (src != nullptr) src->Parent() = nullptr;
				return dst;
			}
			if (dst == dst->Parent()->Left()) dst->Parent()->Left() = src;
			else dst->Parent()->Right() = src;
			if (src != nullptr) src->Parent() = dst->Parent();
			return dst;
		};

		if (node->Left() == nullptr) {
			//   ()
			//    |
			//   (A)
			//   /  \
			// NULL (B)
			BinaryNodeWithParent<T> * r = (BinaryNodeWithParent<T> *)node->Right();
			transplant(node, r);
			node->Right() = nullptr;
			if (tree == node) {
				// r is the new root
				tree = r;
			}
			delete node;
			node = nullptr;
			return tree;
		}

		if (node->Right() == nullptr) {
			//   ()
			//    |
			//   (A)
			//   /  \
			// (B) NULL
			BinaryNodeWithParent<T> * l = (BinaryNodeWithParent<T> *)node->Left();
			transplant(node, l);
			node->Left() = nullptr;
			if (tree == node) {
				// l is the new root
				tree = l;
			}
			delete node;
			node = nullptr;
			return tree;
		}

		BinaryNodeWithParent<T> * successor = (BinaryNodeWithParent<T> *)SearchTreeMin(node->Right());

		if (successor->Parent() != node) {
			//     ()
			//     |
			//    (A)
			//    / \
			//   ()  (D)
			//        \
			//         ()
			//        /
			//      (B)
			//      / \
			//    NULL (C)
			transplant(successor, (BinaryNodeWithParent<T> *)successor->Right());
			//     ()
			//     |
			//    (A)
			//    / \
			//   () (D)
			//        \
			//         ()
			//        /
			//      (C)           (B)
			successor->Right() = node->Right();
			((BinaryNodeWithParent<T> *)successor->Right())->Parent() = successor;
			//     ()
			//     |
			//    (A)
			//    /
			//   ()
			//       (B)
			//         \
			//         (D)
			//           \
			//            ()
			//           /
			//         (C)
		}

		transplant(node, successor);
		successor->Left() = node->Left();
		((BinaryNodeWithParent<T> *)successor->Left())->Parent() = successor;

		if (tree == node) {
			// successor is the new root
			tree = successor;
		}

		node->Left() = nullptr;
		node->Right() = nullptr;
		delete node;
		node = nullptr;

		return tree;
	}
}