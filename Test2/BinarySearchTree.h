#pragma once

#include <iostream>
#include <functional>
using namespace std;

namespace My {
	template<class T> class  BinarySearchTree {
	public:
		class Node {
			template<class T> friend class BinarySearchTree;
		private:
			T content;
			Node * parent;
			Node * left;
			Node * right;	
		public:
			Node(T c) : content(c), parent(nullptr), left(nullptr), right(nullptr) {}
			// Not delete its children
			~Node(void)
			{
				auto f = [](Node * p) { if (p != nullptr) { p = nullptr;} };
				f(this->left);
				f(this->right);
				f(this->parent);
			}

			T Content() { return this->content; }
			void PrintContent() { cout << this->content << " "; }

			// Insert a content to the subtree at node and return node.
			// If node is NULL, then return a new node with the content.
			static Node * Insert(Node * node, T content)
			{
				Node * newNode = new Node(content);
				Node * parent = node;
				Node * current = node;
				while (current != nullptr) {
					parent = current;
					if (newNode->content < current->content) current = current->left;
					else current = current->right;
				}

				newNode->parent = parent;

				if (parent == nullptr) {
					// This means node is NULL, i.e. it is an empty tree. 
					// Return the new node as it is the first node of a tree.
					return newNode;
				} else if (newNode->content < parent->content) {
					parent->left = newNode;
				} else {
					parent->right = newNode;
				}
				// The root of tree
				return node;
			}
			Node * Insert(T content) { return Insert(this, content); }
			static void PreOrderWalk(Node * node, function<void (Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				f(node);
				PreOrderWalk(node->left, f);
				PreOrderWalk(node->right, f);
			}
			void PreOrderWalk(function<void (Node *)> f) { PreOrderWalk(this, f); }
			static void InOrderWalk(Node * node, function<void (Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				InOrderWalk(node->left, f);
				f(node);
				InOrderWalk(node->right, f);
			}
			void InOrderWalk(function<void (Node *)> f) { InOrderWalk(this, f); }
			static void PostOrderWalk(Node * node, function<void (Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				PostOrderWalk(node->left, f);
				PostOrderWalk(node->right, f);
				f(node);
			}
			void PostOrderWalk(function<void (Node *)> f) { PostOrderWalk(this, f); }
			static void Empty(Node* node)
			{
				PostOrderWalk(node->left, [](Node * x){ delete x;});
				PostOrderWalk(node->right, [](Node * x){ delete x;});
				node->left = nullptr;
				node->right = nullptr;
			}
			void Empty(void) { Empty(this); }
			static Node * Search(Node * node, T content)
			{
				if (node == nullptr || node->content == content) return node;
				if (content < node->content) return Search(node->left, content);
				else return Search(node->right, content);
			}
			Node * Search(T content) { return Search(this, content); }
			static Node * Min(Node * node)
			{
				if (node == nullptr) return node;
				while (node->left != nullptr) node = node->left;
				return node;
			}
			Node * Min(void) { return Min(this); }
			static Node * Max(Node * node)
			{
				if (node == nullptr) return node;
				while (node->right != nullptr) node = node->right;
				return node;
			}
			Node * Max(void) { return Max(this); }
			static Node * Successor(Node * node)
			{
				if (node == nullptr) return node;

				//  (A)
				//  / \
				// () (B)
				// The successor of A is the minimum node of subtree B
				if (node->right != nullptr) return Min(node->right);

				//    (B)
				//   /
				// (C)
				//   \
				//    ()
				//      \
				//      (A)
				//      / \
				//     () NULL
				// The successor of A is the lowest ancestor B whos left child C contains A in its right substree
				Node * parent = node->parent;
				while (parent != nullptr && node == parent->right) {
					node = parent;
					parent = parent->parent;
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
			Node * Successor(void) { return Successor(this); }
			static Node * Predecessor(Node * node)
			{
				if (node == nullptr) return nullptr;

				//   (A)
				//   /
				// (B)
				// The predecessor of A is the maximum node of subtree B	
				if (node->left != nullptr) return Max(node->left);

				//     (B)
				//       \
				//       (C)
				//       /
				//      ()
				//     /
				//   (A)
				//   / \
				// NULL ()
				// The predecessor of A is the lowest ancestor B whos right child C contains A in its left substree
				Node * parent = node->parent;
				while (parent != nullptr && node == parent->left) {
					node = parent;
					parent = parent->parent;
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
			Node * Predecessor(void) { return Predecessor(this); }
			static void PrintTree(Node * node)
			{
				auto f = [](Node * x){ x->PrintContent(); };
				InOrderWalk(node, f);
			}
			void PrintTree(void) { PrintTree(this); }
			static Node * Transplant(Node * dst, Node * src)
			{
				if (dst == nullptr) return dst;

				if (dst->parent == nullptr) {
					// src becomes the new root
					if (src != nullptr) src->parent = nullptr;
					return dst;
				}

				if (dst == dst->parent->left) {
					dst->parent->left = src;
				} else {
					dst->parent->right = src;
				}

				if (src != nullptr) src->parent = dst->parent;

				return dst;
			}
			static void Delete(Node * node)
			{
				if (node == nullptr) return;

				if (node->left == nullptr) {
					//   () 
					//    |
					//   (A)
					//   /  \
					// NULL (B)
					Transplant(node, node->right);
					// delete node will not delete its children
					delete node;
					return;
				}

				if (node->right == nullptr) {
					//   ()
					//    |
					//   (A)
					//   /  \
					// (B) NULL
					Transplant(node, node->left);
					// delete node will not delete its children
					delete node;
					return;
				}

				Node * successor = Min(node->right);

				if (successor->parent != node) {
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
					Transplant(successor, successor->right);
					//     ()
					//     |
					//    (A)
					//    / \
					//   () (D)
					//        \
					//         ()
					//        /
					//      (C)           (B)
					successor->right = node->right;
					successor->right->parent = successor;
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

				Transplant(node, successor);
				successor->left = node->left;
				successor->left->parent = successor;
				delete node;
			}
		};

	private:
		Node * root;

	public:

		BinarySearchTree(void) : root(nullptr) {}

		void Empty(void)
		{
			this->root;
			if (this->root != nullptr) {
				Node::Empty(this->root);
				delete this->root;
				this->root = nullptr;
			}
		}

		~BinarySearchTree() { Empty(); }

		void Insert(T content)
		{
			if (this->root == nullptr) {
				this->root = new Node(content);
				this->root->parent = nullptr;
			}
			else Node::Insert(this->root, content);
		}

		void PreOrderWalk(function<void (T)> f)
		{
			if (this->root != nullptr) {
				auto fNode = [=](Node * x){ f(x->Content()); };
				Node::PreOrderWalk(this->root, fNode);
			}
		}

		void InOrderWalk(function<void (T)> f)
		{
			if (this->root != nullptr) {
				auto fNode = [=](Node * x){ f(x->Content()); };
				Node::InOrderWalk(this->root, fNode);
			}
		}

		void PostOrderWalk(function<void (T)> f)
		{
			if (this->root != nullptr) {
				auto fNode = [=](Node * x){ f(x->Content()); };
				Node::PostOrderWalk(this->root, fNode);
			}
		}

		T Min(void)
		{
			if (this->root != nullptr) return Node::Min(this->root)->Content();
			else return T(NULL);
		}

		T Max(void)
		{
			if (this->root != nullptr) return Node::Max(this->root)->Content();
			else return T(NULL);
		}

		T Successor(T content)
		{
			if (this->root != nullptr) {
				Node * p = Node::Search(this->root, content);
				if (p != nullptr && ((p = Node::Successor(p)) != nullptr)) return p->Content();
			}

			return T(NULL);
		}

		T Predecessor(T content)
		{
			if (this->root != nullptr) {
				Node * p = Node::Search(this->root, content);
				if (p != nullptr && ((p = Node::Predecessor(p)) != nullptr)) return p->Content();
			}

			return T(NULL);
		}

		void Print()
		{
			if (this->root != nullptr) {
				Node::PrintTree(this->root);
			}
		}
	};

	template __declspec(dllexport) class BinarySearchTree<int>;
}