#pragma once
#include "BinaryNode.h"
namespace Test {
	template<class T> class BinaryNodeWithRightSibling : public BinaryNode<T> {
	public:
		BinaryNodeWithRightSibling(const T & v) : BinaryNode<T>(v)
		{
			this->Neighbor(2) = nullptr;
		}

		virtual ~BinaryNodeWithRightSibling(void) {}

		// Get the reference of right sibling pointer
		BinaryNodeWithRightSibling * & RightSibling(void) { return (BinaryNodeWithRightSibling * &)this->Neighbor(2); }
		// Set the right sibling pointer
		void RightSibling(BinaryNode * p) { this->Neighbor(2) = p; }

		// This works for both complete and incomplete binary trees
		static void SetRightSibling(BinaryNodeWithRightSibling * node);
		void SetRightSibling(void) { SetRightSibling(this); }

		// DFS
		// This works for complete binary tree only
		static void SetRightSibling2(BinaryNodeWithRightSibling * node);
		void SetRightSibling2(void) { SetRightSibling2(this); }

		static BinaryNodeWithRightSibling * Clone2(BinaryNode * node);
		BinaryNodeWithRightSibling * Clone2(void) { return Clone2(this); }

		// Visit level by level, left to right
		// Breadth-first search
		static void LevelOrderWalk3(BinaryNodeWithRightSibling * node, function<void(T)> f);
		virtual void LevelOrderWalk3(function<void(T)> f) { LevelOrderWalk3(this, f); }
	};

	// This works for both complete and incomplete binary trees
	template<class T> void BinaryNodeWithRightSibling<T>::SetRightSibling(BinaryNodeWithRightSibling * node)
	{
		if (node == nullptr) return;

		while (node != nullptr) {
			// Track nodes at current level, which is already done with rightSibling setting
			BinaryNodeWithRightSibling * current = node;
			// Track the beginning of next level, which is to set with rightSibling
			node = (BinaryNodeWithRightSibling *)current->Left();
			// Find the beginning
			while (node == nullptr && current != nullptr) {
				node = (BinaryNodeWithRightSibling *)current->Left();
				if (node == nullptr) {
					// Current has no left child
					node = (BinaryNodeWithRightSibling *)current->Right();
				}
				if (node == nullptr) {
					// Current has no left and right children
					current = current->RightSibling();
				}
			}

			if (node == nullptr) {
				// No more nodes in the next level
				return;
			}

			BinaryNodeWithRightSibling * prev = node;
			if (prev == current->Left()) {
				if (current->Right() != nullptr) {
					prev->RightSibling() = (BinaryNodeWithRightSibling *)current->Right();
					prev = (BinaryNodeWithRightSibling *)current->Right();
				}
			}

			current = current->RightSibling();
			while (current != nullptr) {
				if (current->Left() != nullptr) {
					prev->RightSibling() = (BinaryNodeWithRightSibling *)current->Left();
					prev = (BinaryNodeWithRightSibling *)current->Left();
				}
				if (current->Right() != nullptr) {
					prev->RightSibling() = (BinaryNodeWithRightSibling *)current->Right();
					prev = (BinaryNodeWithRightSibling *)current->Right();
				}
				current = current->RightSibling();
			}
		}
	}

	// DFS
	// This works for complete binary tree only
	template<class T> void BinaryNodeWithRightSibling<T>::SetRightSibling2(BinaryNodeWithRightSibling * node)
	{
		if (node == nullptr) return;

		BinaryNodeWithRightSibling * p = (BinaryNodeWithRightSibling *)node->Left();
		if (p != nullptr) {
			p->RightSibling() = (BinaryNodeWithRightSibling *)node->Right();
		}

		if (node->Right() != nullptr) {
			p = (BinaryNodeWithRightSibling *)node->Right();
		}

		if (p != nullptr) {
			// For incomplete binary tree, the following search will fail,
			// because not all rightSibling of nodes at current level are set yet.
			BinaryNodeWithRightSibling * current = node->RightSibling();
			while (current != nullptr) {
				if (current->Left() != nullptr) {
					p->RightSibling() = (BinaryNodeWithRightSibling *)current->Left();
					break;
				}
				if (current->Right() != nullptr) {
					p->RightSibling() = (BinaryNodeWithRightSibling *)current->Right();
					break;
				}
				current = current->RightSibling();
			}
		}

		SetRightSibling2((BinaryNodeWithRightSibling *)node->Left());
		SetRightSibling2((BinaryNodeWithRightSibling *)node->Right());
	}

	template<class T> BinaryNodeWithRightSibling<T> * BinaryNodeWithRightSibling<T>::Clone2(BinaryNode<T> * node)
	{
		if (node == nullptr) return nullptr;
		BinaryNodeWithRightSibling * newNode = new BinaryNodeWithRightSibling(node->Value());
		BinaryNodeWithRightSibling * left = Clone2(node->Left());
		if (left != nullptr) {
			newNode->Left() = left;
		}
		BinaryNodeWithRightSibling * right = Clone2(node->Right());
		if (right != nullptr) {
			newNode->Right() = right;
		}

		return newNode;
	}

	// Visit level by level, left to right
	// Breadth-first search
	template<class T> void BinaryNodeWithRightSibling<T>::LevelOrderWalk3(BinaryNodeWithRightSibling * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		while (node != nullptr) {
			BinaryNodeWithRightSibling * p = node;
			while (p != nullptr) {
				f(p->Value());
				p = p->RightSibling();
			}

			while (p == nullptr && node != nullptr) {
				p = (BinaryNodeWithRightSibling *)node->Left();
				if (p == nullptr) p = (BinaryNodeWithRightSibling *)node->Right();
				if (p == nullptr) node = node->RightSibling();
			}

			node = p;
		}
	}

}