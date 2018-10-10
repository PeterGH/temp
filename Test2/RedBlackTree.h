#pragma once
#include <algorithm>

namespace My {
	template<class T> class RedBlackTree {
	public:
		typedef enum {
			RED,
			BLACK
		} Color;

		class Node {
			template<class T> friend class RedBlackTree;
		private:
			T content;
			Node * parent;
			Node * left;
			Node * right;
			Color color;
		public:
			Node(T c) : content(c), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
			// Not delete its children
			~Node(void)
			{
				auto f = [](Node * p) { if (p != nullptr) { p = nullptr;} };
				f(this->left);
				f(this->right);
				f(this->parent);
			}
			T Content() { return this->content; }
			void PrintContent() { cout << this->content << "(" << (this->color == RED ? "R" : "B") << ") "; }
			//        y               x
			//       / \             / \
			//      x       <====       y
			//     / \                 / \
			//
			static Node * LeftRotate(Node * node)
			{
				if (node == nullptr) return nullptr;
				Node * right = node->right;
				if (right == nullptr) return nullptr;

				node->right = right->left;
				if (right->left != nullptr) right->left->parent = node;

				right->parent = node->parent;
				if (node->parent != nullptr) {
					if (node == node->parent->left) node->parent->left = right;
					else node->parent->right = right;
				}

				right->left = node;
				node->parent = right;
				return right;
			}
			//        y               x
			//       / \             / \
			//      x       ====>       y
			//     / \                 / \
			//
			static Node * RightRotate(Node * node)
			{
				if (node == nullptr) return nullptr;
				Node * left = node->left;
				if (left == nullptr) return nullptr;

				node->left = left->right;
				if (left->right != nullptr) left->right->parent = node;

				left->parent = node->parent;
				if (node->parent != nullptr) {
					if (node == node->parent->left) node->parent->left = left;
					else node->parent->right = left;
				}

				left->right = node;
				node->parent = left;
				return left;
			}
			static void FixUp(Node * node)
			{
				if (node == nullptr || node->color == BLACK) return;

				while (node->parent != nullptr && node->parent->color == RED) {
					// So node and node->parent are both RED, we need to fix it.

					if (node->parent->parent == nullptr) {
						// node->parent is the root
						node->parent->color = BLACK;
						return;
					}

					// Now node->parent->parent exists and it is BLACK by definition of RedBlackTree.
					if (node->parent == node->parent->parent->left) {
						Node * uncle = node->parent->parent->right;
						if (uncle == nullptr || uncle->color == BLACK) {
							if (node == node->parent->right) {
								//          (B)              (B)
								//          / \             /   \
								//        (R)       or    (R)   (B)
								//        / \             / \   / \
								//          (R)             (R)
								//          / \             / \
								//
								node = node->parent;
								LeftRotate(node);
							}
							//          (B)              (B)
							//          / \             /   \
							//        (R)       or    (R)   (B)
							//        / \             / \   / \
							//      (R)             (R)
							//      / \             / \
							//
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							//          (R)              (R)
							//          / \             /   \
							//        (B)       or    (B)   (B)
							//        / \             / \   / \
							//      (R)             (R)
							//      / \             / \
							//
							RightRotate(node->parent->parent);
							//          (B)              (B)
							//          / \             /   \
							//        (R) (R)   or    (R)   (R)
							//        / \ / \         / \   / \
							//                                (B)
							//                                / \
							//
						} else {
							//           (B)
							//          /   \
							//        (R)   (R)
							//         |
							//        (R)
							node->parent->color = BLACK;
							uncle->color = BLACK;
							node->parent->parent->color = RED;
							//           (R)
							//          /   \
							//        (B)   (B)
							//         |
							//        (R)							
							node = node->parent->parent;
						}
					} else if (node->parent == node->parent->parent->right) {
						Node * uncle = node->parent->parent->left;
						if (uncle == nullptr || uncle->color == BLACK) {
							if (node == node->parent->left) {
								//          (B)              (B)
								//          / \             /   \
								//            (R)    or   (B)   (R)
								//            / \         / \   / \
								//          (R)               (R)
								//          / \               / \
								//
								node = node->parent;
								RightRotate(node);
							}
							//          (B)              (B)
							//          / \             /   \
							//            (R)    or   (B)   (R)
							//            / \         / \   / \
							//              (R)               (R)
							//              / \               / \
							//
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							//          (R)              (R)
							//          / \             /   \
							//            (B)    or   (B)   (B)
							//            / \         / \   / \
							//              (R)               (R)
							//              / \               / \
							//
							LeftRotate(node->parent->parent);
							//          (B)              (B)
							//          / \             /   \
							//        (R) (R)    or   (R)   (R)
							//        / \ / \         / \   / \
							//                      (B)
							//                      / \
							//
						} else {
							//           (B)
							//          /   \
							//        (R)   (R)
							//               |
							//              (R)
							node->parent->color = BLACK;
							uncle->color = BLACK;
							node->parent->parent->color = RED;
							//           (R)
							//          /   \
							//        (B)   (B)
							//               |
							//              (R)
							node = node->parent->parent;
						}
					}
				}
				if (node->parent == nullptr) {
					// node is the root
					node->color = BLACK;
				}
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
			static int BlackHeight(Node * node)
			{
				if (node == nullptr) return 0;
				int left = BlackHeight(node->left);
				int right = BlackHeight(node->right);
				return std::max<int>(left, right) + (node->color == BLACK ? 1 : 0);
			}
			int BlackHeight(void) { return BlackHeight(this); }
			static bool Verify(Node * node)
			{
				if (node->parent == nullptr && node->color != BLACK)
				{
					// Root is not BLACK
					return false;
				}
				if (node->color == RED) {
					if ((node->left != nullptr && node->left->color == RED)
						|| (node->right != nullptr && node->right->color == RED)) {
							// A RED node cannot have a RED child
							return false;
					}
				}
				int left = BlackHeight(node->left);
				int right = BlackHeight(node->right);
				if (left != right) {
					// Both children must have the same number of BLACK nodes
					return false;
				}
				bool result = true;
				if (node->left != nullptr) result &= Verify(node->left);
				if (node->right != nullptr) result &= Verify(node->right);
				return result;
			}
			bool Verify(void) { return Verify(this); }
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
#if NULL
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

			//
			// THIS IS NOT FINISHED !!!
			//
			static void Delete(Node * node)
			{
				if (node == nullptr) return;
				Node * moved = node;
				Color original = node->color;
				if (node->left == nullptr) {
					//   () 
					//    |
					//   (A)
					//   /  \
					// NULL (B)
					moved = node->right;
					Transplant(node, node->right);
					// delete node will not delete its children
					delete node;					
				} else if (node->right == nullptr) {
					//   ()
					//    |
					//   (A)
					//   /  \
					// (B) NULL
					moved = node->left;
					Transplant(node, node->left);
					// delete node will not delete its children
					delete node;
				} else {
					Node * successor = Min(node->right);
					original = successor->color;
					moved = successor->right;

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
					successor->color = node->color;
					delete node;
				}
				if (original == BLACK) {

				}
			}
#endif
			static void PrintTree(Node * node)
			{
				auto f = [](Node * x){ x->PrintContent(); };
				InOrderWalk(node, f);
			}
			void PrintTree(void) { PrintTree(this); }
		};

	private:
		Node * root;

	public:

		RedBlackTree(void) : root(nullptr) {}

		void Empty(void)
		{
			if (this->root != nullptr) {
				Node::Empty(this->root);
				delete this->root;
				this->root = nullptr;
			}
		}

		~RedBlackTree() { Empty(); }

		void Insert(T content)
		{
			Node * newNode = new Node(content);

			if (this->root == nullptr) {
				// The new node becomes the root.
				// The root must be BLACK in a RedBlackTree.
				this->root = newNode;
				this->root->color = BLACK;
				return;
			}

			Node * parent = this->root;
			Node * current = this->root;
			while (current != nullptr) {
				parent = current;
				if (newNode->content < current->content) current = current->left;
				else current = current->right;
			}
			newNode->parent = parent;
			if (newNode->content < parent->content) {
				parent->left = newNode;
			} else {
				parent->right = newNode;
			}

			if (parent->color == BLACK) {
				// Nothing else
				return;
			} else if (parent->color == RED) {
				// Both newNode and parent are RED
				if (parent->parent == nullptr) {
					// parent is root
					parent->color = BLACK;
				} else {
					// parent is not root
					Node::FixUp(newNode);
					while (this->root->parent != nullptr) {
						this->root = this->root->parent;
					}
				}
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

		int BlackHeight(void) { return Node::BlackHeight(this->root); }
		bool Verify(void) {
			if (this->root != nullptr) {
				return this->root->Verify();
			}
			return true;
		}

		void Print()
		{
			if (this->root != nullptr) {
				Node::PrintTree(this->root);
			}
		}

	};

	template __declspec(dllexport) class RedBlackTree<int>;
}