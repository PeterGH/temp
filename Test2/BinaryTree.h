#pragma once

#include <iostream>
#include <functional>
#include <stack>
using namespace std;

namespace My {

	template<class T> class  BinaryTree {
	public:
		class Node {
			template<class T> friend class BinaryTree;
		private:
			T content;
			Node * parent;
			Node * left;
			Node * right;	
		public:
			Node(const T & c) : content(c), parent(nullptr), left(nullptr), right(nullptr) {}
			// Not delete its children
			~Node(void)
			{
				auto f = [](Node * p) { if (p != nullptr) { p = nullptr;} };
				f(this->left);
				f(this->right);
				f(this->parent);
			}
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
			T Content() { return this->content; }
			void PrintContent() { cout << this->content << " "; }
			static void PrintTree(Node * node)
			{
				auto f = [](Node * x){ x->PrintContent(); };
				InOrderWalk(node, f);
			}
			void PrintTree(void) { PrintTree(this); }
			
		};

	private:
		Node * root;
		int count;

	public:

		BinaryTree(void) : root(nullptr), count(0) {}

		void Empty(void)
		{
			if (this->root != nullptr) {
				Node::Empty(this->root);
				delete this->root;
				this->root = nullptr;
				this->count = 0;
			}
		}

		~BinaryTree(void) { Empty(); }

		//         0
		//    1          2
		//  3   4     5     6
		// 7 8 9 10 11 12 13 14
		// Given Height, the number of nodes are in [2^(Height - 1), 2^Height - 1]
		// The indices of nodes at Height are in [2^(Height - 1) - 1, 2^Height - 2]
		// Given node index, its children are 2*index+1 and 2*index+2
		void Insert(T content)
		{
			Node * newNode = new Node(content);
			if (this->root == nullptr) {
				this->root = newNode;
				this->root->parent = nullptr;
				this->count = 1;
			} else {
				// this->count equals to the index for the new node
				stack<int> branch;
				int index = this->count;
				while (index > 0) {
					if (index % 2 == 1) {
						// index is an odd number, meaning it is the left child of its parent
						// Encode it as 0
						branch.push(0);
					} else {
						// index is an even number, meaning it is the left child of its parent
						// Encode it as 1
						branch.push(1);
					}

					index = (index - 1) >> 1;
				}

				Node * current = this->root;
				while (branch.size() > 1) {
					if (branch.top() == 0 && current->left != nullptr) {
						current = current->left;
					} else if (branch.top() == 1 && current->right != nullptr) {
						current = current->right;
					}

					branch.pop();
				}

				if (branch.top() == 0 && current->left == nullptr) {
					current->left = newNode;
				} else if (branch.top() == 1 && current->right == nullptr) {
					current->right = newNode;
				}

				branch.pop();
				this->count++;
			}
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

		void Print()
		{
			if (this->root != nullptr) {
				Node::PrintTree(this->root);
			}
		}
	};
}