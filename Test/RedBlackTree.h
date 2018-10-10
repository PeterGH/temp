#pragma once
#include <algorithm>
#include <functional>
#include <vector>
#include "String.h"

using namespace std;

namespace Test {
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
			Node(const T & c) : content(c), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
			// Not delete its children
			~Node(void)
			{
				auto f = [](Node * p) { if (p != nullptr) { p = nullptr; } };
				f(this->left);
				f(this->right);
				f(this->parent);
			}

			T Content() { return this->content; }
			
			static Node * Search(Node * node, const T & content)
			{
				if (node == nullptr || node->content == content) return node;
				while (node != nullptr && content != node->content) {
					if (content < node->content)
						node = node->left;
					else
						node = node->right;
				}

				return node;
			}

			static Node * Min(Node * node)
			{
				if (node == nullptr) return node;
				while (node->left != nullptr) node = node->left;
				return node;
			}

			static void PostOrderWalk(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				PostOrderWalk(node->left, f);
				PostOrderWalk(node->right, f);
				f(node);
			}

			static int BlackHeight(Node * node)
			{
				if (node == nullptr) {
					// NULL is BLACK by definition
					return 1;
				}

				int left = BlackHeight(node->left);
				int right = BlackHeight(node->right);
				return std::max<int>(left, right) + (node->color == BLACK ? 1 : 0);
			}

			static int BlackHeight2(Node * node)
			{
				if (node == nullptr) {
					// NULL is BLACK by definition
					return 1;
				}

				Node * prev = node;
				int max = 0;
				int h = 0;
				while (node != nullptr) {
					if (prev == node->right) {
						if (node->right->color == BLACK) h--;
						prev = node;
						node = node->parent;
					} else if (node->left != nullptr && prev != node->left) {
						if (node->color == BLACK) h++;
						prev = node;
						node = node->left;
					} else {
						if (node->left == nullptr) {
							if (node->color == BLACK) h++;
							if (h + 1 > max) max = h + 1;
						} else if (prev == node->left) {
							if (node->left->color == BLACK) h--;
						}

						prev = node;

						if (node->right == nullptr) {
							if (h + 1 > max) max = h + 1;
							node = node->parent;
						} else {
							node = node->right;
						}
					}
				}

				return max;
			}

			static bool Verify(Node * node)
			{
				if (node == nullptr) return true;

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

				int left = BlackHeight2(node->left);
				int right = BlackHeight2(node->right);
				if (left != right) {
					// Both children must have the same BLACK height
					return false;
				}

				if (node->left != nullptr && !Verify(node->left)) return false;
				if (node->right != nullptr && !Verify(node->right)) return false;
				return true;
			}

			static void Empty(Node* node)
			{
				PostOrderWalk(node->left, [](Node * x){ delete x; });
				PostOrderWalk(node->right, [](Node * x){ delete x; });
				node->left = nullptr;
				node->right = nullptr;
			}

			void Empty(void) { Empty(this); }

			static stringstream & ToString(stringstream & ss, Node * node, int x, vector<int> & y)
			{
				static string link = "____";
				string c = String::Format("%s%d", node->color == RED ? "R" : "B", node->content);
				ss << c;
				x += c.length();

				if (node->right != nullptr) {
					// Record current x coordinate,
					// so it can be used to draw '|'
					y.push_back(x);
				}

				if (node->left != nullptr) {
					ss << link;
					ToString(ss, node->left, x + link.length(), y);
				}

				if (node->right != nullptr) {
					ss << endl;

					for (size_t i = 0; i < y.size(); i++) {
						int len = i == 0 ? y[i] : y[i] - y[i - 1];
						string blank(len - 1, ' ');
						ss << blank << '|';
					}

					ss << link;

					// The right child is ready to print
					// Remove its coordinate because it is not needed any more
					y.pop_back();

					ToString(ss, node->right, x + link.length(), y);
				}

				return ss;
			}

			void Print(void)
			{
				stringstream ss;
				vector<int> y;
				ToString(ss, this, 0, y);
				ss << endl;
				cout << ss.str();
			}

		} * root;

		//        y               x
		//       / \             / \
		//      x       <====       y
		//     / \                 / \
		//
		// Rotate at x
		Node * LeftRotate(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * right = node->right;
			if (right == nullptr) return nullptr;

			node->right = right->left;
			if (right->left != nullptr) right->left->parent = node;
			
			right->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = right;
			} else {
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
		// Rotate at y
		Node * RightRotate(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * left = node->left;
			if (left == nullptr) return nullptr;

			node->left = left->right;
			if (left->right != nullptr) left->right->parent = node;

			left->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = left;
			} else {
				if (node == node->parent->left) node->parent->left = left;
				else node->parent->right = left;
			}

			left->right = node;
			node->parent = left;
			return left;
		}

		void InsertFixUp(Node * node)
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
							//        (R)       or    (R)    (B)
							//        / \             / \    / \
							//          N(R)            N(R)
							//          / \             / \
							//
							node = node->parent;
							LeftRotate(node);
						}
						//          (B)              (B)
						//          / \             /   \
						//        (R)       or    (R)   (B)
						//        / \             / \   / \
						//      N(R)           N(R)
						//      / \             / \
						//
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						//          (R)              (R)
						//          / \             /   \
						//        (B)       or    (B)   (B)
						//        / \             / \   / \
						//     N(R)            N(R)
						//      / \             / \
						//
						RightRotate(node->parent->parent);
						//          (B)              (B)
						//          / \             /   \
						//       N(R) (R)   or   N(R)   (R)
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
							//         N(R)               N(R)
							//          / \               / \
							//
							node = node->parent;
							RightRotate(node);
						}
						//          (B)              (B)
						//          / \             /   \
						//            (R)    or   (B)   (R)
						//            / \         / \   / \
						//              N(R)               N(R)
						//              / \               / \
						//
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						//          (R)              (R)
						//          / \             /   \
						//            (B)    or   (B)   (B)
						//            / \         / \   / \
						//              N(R)              N(R)
						//              / \               / \
						//
						LeftRotate(node->parent->parent);
						//          (B)              (B)
						//          / \             /   \
						//        (R) N(R)    or   (R)  N(R)
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

		// Replace the subtree at dst with the subtree at src
		// Update root if dst is the original root
		// src may be NULL, then dst is removed from its parent but not deleted.
		void Transplant(Node * dst, Node * src)
		{
			if (dst == nullptr) return;
			if (dst->parent == nullptr) {
				// src becomes the new root
				this->root = src;
			} else if (dst == dst->parent->left) {
				dst->parent->left = src;
			} else {
				dst->parent->right = src;
			}

			if (src != nullptr) src->parent = dst->parent;
		}

		//      N(B)
		//     /   \
		//         (R)
		//         / \
		//
		//       N(B)
		//       /   \
		//     (R)
		//     / \
		//
		// Subtree at node has BLACK height one less than its sibling
		// Need to fix it
		void DeleteFixUp(Node * node)
		{
			if (node == nullptr) return;

			while (node->parent != nullptr && node->color == BLACK) {
				if (node == node->parent->left) {
					//      ( )
					//     /   \
					//   N(B)  ( )
					//
					Node * sibling = node->parent->right;
					
					if (sibling->color == RED) {
						// sibling is RED and its children are BLACK
						//          ( )
						//         /   \
						//       N(B)  S(R)
						//             / \
						//           (B) (B)
						//
						sibling->color = BLACK;
						node->parent->color = RED;
						//          (R)
						//         /   \
						//       N(B)  S(B)
						//             / \
						//           (B) (B)
						//
						// Now node's BLACK height is two less than its sibling's
						//
						LeftRotate(node->parent);
						//          S(B)
						//         /   \
						//       (R)  (B)
						//       / \
						//    N(B) (B)
						//
						sibling = node->parent->right;
						//          (B)
						//         /   \
						//       (R)  (B)
						//       / \
						//    N(B) S(B)
						//
						// Now node's BLACK height is one less than its new sibling's
					}

					//      ( )
					//     /   \
					//   N(B) S(B)
					//
					// Now sibling is BLACK, and node's BLACK height is one less than its sibling's

					if (sibling->left != nullptr && sibling->left->color == RED
						|| sibling->right != nullptr && sibling->right->color == RED) {
						//       ( )               ( )              ( )
						//       / \               / \              / \
						//    N(B) S(B)         N(B) S(B)        N(B) S(B)
						//         / \               / \              / \
						//       (R) (B)           (B) (R)          (R) (R)
						//
						
						if (sibling->right != nullptr && sibling->right->color == BLACK) {
							//       ( )
							//       / \
							//    N(B) S(B)
							//         / \
							//       (R) (B)
							//       / \
							//     (B) (B)
							//
							sibling->left->color = BLACK;
							sibling->color = RED;
							//       ( )
							//       / \
							//    N(B) S(R)
							//         / \
							//       (B) (B)
							//       / \
							//     (B) (B)
							//
							RightRotate(sibling);
							//       ( )
							//       / \
							//    N(B) (B)
							//         / \
							//       (B) S(R)
							//           / \
							//         (B) (B)
							//
							sibling = node->parent->right;
							//       ( )
							//       / \
							//    N(B) S(B)
							//         / \
							//       (B) (R)
							//           / \
							//         (B) (B)
							//
							// node's BLACK height is still one less than its sibling's,
							// and its sibling->right is RED
						}
						
						// Now sibling->right is RED and has two BLACK children
						//       ( )
						//       / \
						//    N(B) S(B)
						//         / \
						//       ( ) (R)
						//           / \
						//         (B) (B)
						//
						sibling->color = node->parent->color;
						node->parent->color = BLACK;
						sibling->right->color = BLACK;
						//       (B)
						//       / \
						//    N(B) S( )
						//          / \
						//        ( ) (B)
						//            / \
						//          (B) (B)
						//
						LeftRotate(node->parent);
						//       S( )
						//       /   \
						//     (B)    (B)
						//    /  \     / \
						//  N(B) ( ) (B) (B)
						//
						// Now node is fixed.
						node = this->root;
						break;
					} else  {
						// sibling must have at least one child
						//       ( )               ( )              ( )
						//       / \               / \              / \
						//    N(B) S(B)         N(B) S(B)        N(B) S(B)
						//           \               /                / \
						//           (B)           (B)              (B) (B)
						sibling->color = RED;
						node = node->parent;
						//      N( )              N( )             N( )
						//       / \               / \              / \
						//     (B) S(R)          (B) S(R)         (B) S(R)
						//           \               /                / \
						//           (B)           (B)              (B) (B)
						// Now node children trees have the same BLACK heights. 
						// But node itself still has its BLACK height one less than its sibling's
					}
				} else {
					//      ( )
					//     /   \
					//   ( )  N(B)
					//
					Node * sibling = node->parent->left;

					if (sibling->color == RED) {
						// sibling is RED and its children are BLACK
						//          ( )
						//         /   \
						//       S(R)  N(B)
						//       / \
						//     (B) (B)
						//
						sibling->color = BLACK;
						node->parent->color = RED;
						//          (R)
						//         /   \
						//       S(B)  N(B)
						//       / \
						//     (B) (B)
						//
						// Now node's BLACK height is two less than its sibling's
						//
						RightRotate(node->parent);
						//          S(B)
						//         /   \
						//       (B)   (R)
						//             / \
						//           (B) N(B)
						//
						sibling = node->parent->left;
						//          (B)
						//         /   \
						//       (B)   (R)
						//             / \
						//          S(B) N(B)
						//
						// Now node's BLACK height is one less than its new sibling's
					}

					//      ( )
					//     /   \
					//   S(B) N(B)
					//
					// Now sibling is BLACK, and node's BLACK height is one less than its sibling's
					
					if (sibling->left != nullptr && sibling->left->color == RED
						|| sibling->right != nullptr && sibling->right->color == RED) {
						//       ( )               ( )              ( )
						//       / \               / \              / \
						//    S(B) N(B)         S(B) N(B)        S(B) N(B)
						//     / \               / \              / \
						//   (R) (B)           (B) (R)          (R) (R)
						//
						if (sibling->left != nullptr && sibling->left->color == BLACK) {
							//       ( )
							//       / \
							//    S(B) N(B)
							//     / \
							//   (B) (R)
							//       / \
							//     (B) (B)
							//
							sibling->right->color = BLACK;
							sibling->color = RED;
							//       ( )
							//       / \
							//    S(R) N(B)
							//     / \
							//   (B) (B)
							//       / \
							//     (B) (B)
							//
							LeftRotate(sibling);
							//       ( )
							//       / \
							//     (B) N(B)
							//     / \
							//   S(R) (B)
							//   / \
							// (B) (B)
							//
							sibling = node->parent->left;
							//       ( )
							//       / \
							//     S(B) N(B)
							//     / \
							//   (R) (B)
							//   / \
							// (B) (B)
							//
							// node's BLACK height is still one less than its sibling's,
							// and its sibling->right is RED
						}

						// Now sibling->left is RED and has two BLACK children
						//       ( )
						//       / \
						//     S(B) N(B)
						//     / \
						//   (R) ( )
						//   / \
						// (B) (B)
						//
						sibling->color = node->parent->color;
						node->parent->color = BLACK;
						sibling->left->color = BLACK;
						//       (B)
						//       / \
						//     S( ) N(B)
						//     / \
						//   (B) ( )
						//   / \
						// (B) (B)
						//
						RightRotate(node->parent);
						//       S( )
						//       /   \
						//     (B)    (B)
						//     / \    / \
						//   (B) (B) ( ) N(B)
						//
						// Now node is fixed.
						node = this->root;
						break;
					} else {
						// sibling must have at least one child
						//       ( )               ( )              ( )
						//       / \               / \              / \
						//    S(B) N(B)         S(B) N(B)        S(B) N(B)
						//     /                  \               / \
						//   (B)                  (B)           (B) (B)
						sibling->color = RED;
						node = node->parent;
						//       N( )              N( )             N( )
						//       / \               / \              / \
						//    S(R) (B)         S(R)  (B)        S(R)  (B)
						//     /                  \               / \
						//   (B)                  (B)           (B) (B)
						// Now node children trees have the same BLACK heights. 
						// But node itself still has its BLACK height one less than its sibling's
					}
				}
			}

			node->color = BLACK;
		}

		// Case 3
		//      P( )          P( )
		//     /   \         /   \
		//   N(B)  (B)     (B)  N(B)
		//   / \   / \     / \   / \
		//        () ()   () ()
		// where () could be NULL or (R)
		//
		// Case 4
		//      P(B)               P(B)
		//     /   \              /   \
		//   N(B)  (R)          (R)  N(B)
		//   / \   / \          / \   / \
		//       (B) (B)      (B) (B)
		//      / \   / \    / \   / \
		//     () () () ()  () () () ()
		// where () could be NULL or (R)
		//
		// node points to the BLACK node been deleted
		// Need to fix the subtree at its parent node
		void DeleteFix(Node * parent, Node * node)
		{
			Node * sibling;
			if (node == parent->left) {
				sibling = parent->right;
				if (sibling->color == BLACK && parent->color == RED) {
					//      P(R)
					//     /   \
					//   N(B)  S(B)
					//   / \   / \
					//        () ()
					// where () could be NULL or (R)
					//
					if (sibling->left == nullptr) {
						//      P(R)
						//     /   \
						//   N(B)  S(B)
						//   / \   / \
						//           ()
						// where () could be NULL or (R)
						//
						// After N(B) is deleted,
						LeftRotate(parent);
						//      S(B)
						//     /   \
						//    P(R) ()
						//    / \
						//
						return;
					}

					if (sibling->left != nullptr) {
						//      P(R)
						//     /   \
						//   N(B)  S(B)
						//   / \   / \
						//       (R) ()
						// where () could be NULL or (R)
						//
						// After N(B) is deleted,
						Node * c = sibling->left;						
						sibling->left = nullptr;
						c->right = sibling;
						sibling->parent = c;
						// P(R)    C(R)
						//        /   \
						//            S(B)
						//            / \
						//              ()
						//
						Transplant(parent, c);
						parent->right = nullptr;
						c->left = parent;
						parent->parent = c;
						parent->color = BLACK;
						//         C(R)
						//        /   \
						//      P(B)   S(B)
						//      / \   / \
						//              ()
						//
						return;
					}
				}
				
				if (sibling->color == BLACK && parent->color == BLACK) {
					//      P(B)
					//     /   \
					//   N(B)  S(B)
					//   / \   / \
					//        () ()
					// where () could be NULL or (R)
					//
					if (sibling->left == nullptr && sibling->right == nullptr) {
						//      P(B)
						//     /   \
						//   N(B)  S(B)
						//   / \   / \
						//
						// After node is deleted,
						//      P(B)
						//     /   \
						//         S(B)
						//         / \
						//
						sibling->color = RED;
						DeleteFixUp(parent);
						return;
					}
					
					if (sibling->left == nullptr && sibling->right != nullptr) {
						//      P(B)
						//     /   \
						//   N(B)  S(B)
						//   / \   / \
						//           (R)
						//
						// After node is deleted,
						LeftRotate(parent);
						//      S(B)
						//     /   \
						//   P(B)  (R)
						//   / \   / \
						//
						sibling->right->color = BLACK;
						//      S(B)
						//     /   \
						//   P(B)   (B)
						//   / \   / \
						//
						return;
					}
					
					if (sibling->left != nullptr && sibling->left->color == RED) {
						//      P(B)
						//     /   \
						//   N(B)  S(B)
						//   / \   / \
						//       (R) ()
						// where () could be NULL or (R)
						//
						// After node is deleted,
						Node * c = sibling->left;
						Transplant(parent, c);
						sibling->left = nullptr;
						c->right = sibling;
						sibling->parent = c;
						//  P(B)     C(R)
						//          /   \
						//              S(B)
						//              / \
						//                ( )
						//
						parent->right = nullptr;
						c->left = parent;
						parent->parent = c;
						c->color = BLACK;
						//           C(B)
						//          /   \
						//        P(B)  S(B)
						//        / \   / \
						//                ( )
						//
						return;
					}
				}
			
				if (sibling->color == RED) {
					//      P(B)
					//     /   \
					//   N(B)  (R)
					//   / \   / \
					//       (B) (B)
					//      / \   / \
					//     () () () ()
					// where () could be NULL or (R)
					//
					if (sibling->left->left == nullptr && sibling->left->right == nullptr) {
						//      P(B)
						//     /   \
						//   N(B)  S(R)
						//   / \   / \
						//       (B) (B)
						//      / \   / \
						//           () ()
						// where () could be NULL or (R)
						//
						// After node is deleted,
						sibling->left->color = RED;
						//      P(B)
						//     /   \
						//         S(R)
						//         / \
						//       (R) (B)
						//      / \   / \
						//           () ()
						// where () could be NULL or (R)
						//
						LeftRotate(parent);
						//      S(R)
						//     /   \
						//   P(B)   (B)
						//   / \    / \
						//     (R) () ()
						//     / \
						//
						sibling->color = BLACK;
						//      S(B)
						//     /   \
						//   P(B)   (B)
						//   / \    / \
						//     (R) () ()
						//     / \
						//
						return;
					}
					
					if (sibling->left->right != nullptr) {
						//      P(B)
						//     /   \
						//   N(B)  S(R)
						//   / \   / \
						//       (B) (B)
						//      / \   / \
						//     () (R)() ()
						// where () could be NULL or (R)
						//
						// After node is deleted,
						sibling->left->right->color = BLACK;
						//      P(B)
						//     /   \
						//         S(R)
						//         / \
						//       (B)  (B)
						//      / \   / \
						//     () (B)() ()
						//
						RightRotate(sibling);
						//      P(B)
						//     /   \
						//         (B)
						//         / \
						//       ()   S(R)
						//            / \
						//          (B)  (B)
						//               / \
						//              () ()
						//
						LeftRotate(parent);
						//         (B)
						//        /   \
						//      P(B)   S(R)
						//      / \    /  \
						//        () (B)  (B)
						//                / \
						//               () ()
						//
						return;
					}
					
					if (sibling->left->left != nullptr && sibling->left->right == nullptr) {
						//      P(B)
						//     /   \
						//   N(B)  S(R)
						//   / \   / \
						//       (B) (B)
						//      / \   / \
						//    (R)    () ()
						// where () could be NULL or (R)
						//
						// After node is deleted,
						Node * c = sibling->left->left;
						Transplant(parent, c);
						sibling->left->left = nullptr;
						c->right = sibling;
						sibling->parent = c;
						// P(B)    C(R)
						//        /   \
						//            S(R)
						//            / \
						//          (B)  (B)
						//         / \   / \
						//              () ()
						//
						parent->right = nullptr;
						c->left = parent;
						parent->parent = c;
						c->color = BLACK;
						//         C(B)
						//        /   \
						//      P(B)  S(R)
						//            / \
						//          (B)  (B)
						//          / \  / \
						//              () ()
						//
						return;
					}
				}
			}
			
			if (node == parent->right) {
				sibling = parent->left;
				if (sibling->color == BLACK && parent->color == RED) {
					//       P(R)
					//       /   \
					//     S(B)  N(B)
					//     / \   / \
					//    () ()
					// where () could be NULL or (R)
					//
					if (sibling->right == nullptr) {
						//       P(R)
						//       /   \
						//     S(B)  N(B)
						//     / \   / \
						//    ()
						// where () could be NULL or (R)
						//
						// After N(B) is deleted,
						RightRotate(parent);
						//        S(B)
						//       /   \
						//      ()   P(R)
						//           / \
						//
						return;
					}

					if (sibling->right != nullptr) {
						//       P(R)
						//       /   \
						//     S(B)  N(B)
						//     / \   / \
						//    () (R)
						// where () could be NULL or (R)
						//
						// After N(B) is deleted,
						Node * c = sibling->right;
						sibling->right = nullptr;
						c->left = sibling;
						sibling->parent = c;
						//         C(R)      P(R)
						//        /   \
						//      S(B)
						//      / \
						//     ()
						//
						Transplant(parent, c);
						parent->left = nullptr;
						c->right = parent;
						parent->parent = c;
						parent->color = BLACK;
						//         C(R)
						//        /   \
						//      S(B)  P(B)
						//      / \
						//     ()
						//
						return;
					}
				}
				
				if (sibling->color == BLACK && parent->color == BLACK) {
					//       P(B)
					//       /   \
					//     S(B)  N(B)
					//     / \   / \
					//    () ()
					// where () could be NULL or (R)
					//
					if (sibling->right == nullptr && sibling->left == nullptr) {
						//       P(B)
						//       /   \
						//     S(B) N(B)
						//     / \   / \
						//
						// After node is deleted,
						//       P(B)
						//       /   \
						//     S(B)
						//     / \
						//
						sibling->color = RED;
						DeleteFixUp(parent);
						return;
					}
					
					if (sibling->right == nullptr && sibling->left != nullptr) {
						//       P(B)
						//       /   \
						//     S(B) N(B)
						//     / \   / \
						//   (R)
						//
						// After node is deleted,
						RightRotate(parent);
						//        S(B)
						//       /   \
						//     (R)   P(B)
						//     / \   / \
						//
						sibling->left->color = BLACK;
						//        S(B)
						//       /   \
						//     (B)   P(B)
						//     / \   / \
						//
						return;
					}
					
					if (sibling->right != nullptr && sibling->right->color == RED) {
						//       P(B)
						//       /   \
						//     S(B)  N(B)
						//     / \   / \
						//    () (R)
						// where () could be NULL or (R)
						//
						// After node is deleted,
						Node * c = sibling->right;
						Transplant(parent, c);
						sibling->right = nullptr;
						c->left = sibling;
						sibling->parent = c;
						//         C(R)        P(B)
						//        /   \
						//      S(B)
						//      / \
						//    ()
						//
						parent->left = nullptr;
						c->right = parent;
						parent->parent = c;
						c->color = BLACK;
						//        C(B)
						//       /   \
						//     S(B)  P(B)
						//     / \   / \
						//    ()
						//
						return;
					}
				}
			
				if (sibling->color == RED) {
					//          P(B)
					//         /   \
					//       (R)  N(B)
					//       / \   / \
					//     (B) (B)
					//    / \   / \
					//   () () () ()
					// where () could be NULL or (R)
					//
					if (sibling->right->left == nullptr && sibling->right->right == nullptr) {
						//          P(B)
						//         /   \
						//       S(R)  N(B)
						//       / \   / \
						//     (B) (B)
						//    / \   / \
						//   () ()
						// where () could be NULL or (R)
						//
						// After node is deleted,
						sibling->right->color = RED;
						//          P(B)
						//         /   \
						//       S(R)
						//       / \
						//     (B) (R)
						//    / \   / \
						//   () ()
						RightRotate(parent);
						//           S(R)
						//          /   \
						//        (B)   P(B)
						//        / \   / \
						//       () () (R)
						//             / \
						//
						sibling->color = BLACK;
						//           S(B)
						//          /   \
						//        (B)   P(B)
						//        / \   / \
						//       () () (R)
						//             / \
						//
						return;
					}
					
					if (sibling->right->left != nullptr) {
						//          P(B)
						//         /   \
						//       S(R)  N(B)
						//       / \   / \
						//     (B) (B)
						//    / \   / \
						//   () ()(R) ()
						// where () could be NULL or (R)
						//
						// After node is deleted,
						sibling->right->left->color = BLACK;
						//          P(B)
						//         /   \
						//       S(R)
						//       / \
						//     (B) (B)
						//    / \   / \
						//   () ()(B) ()
						LeftRotate(sibling);
						//           P(B)
						//          /   \
						//        (B)
						//        / \
						//      S(R) ()
						//      / \
						//   (B)  (B)
						//   / \
						//  () ()
						//
						RightRotate(parent);
						//           (B)
						//          /   \
						//       S(R)   P(B)
						//       / \    / \
						//     (B) (B) ()
						//     / \
						//    () ()
						//
						return;
					}
					
					if (sibling->right->right != nullptr && sibling->right->left == nullptr) {
						//          P(B)
						//         /   \
						//       S(R)  N(B)
						//       / \   / \
						//     (B) (B)
						//    / \   / \
						//   () ()    (R)
						// where () could be NULL or (R)
						//
						// After node is deleted,
						Node * c = sibling->right->right;
						Transplant(parent, c);
						sibling->right->right = nullptr;
						c->left = sibling;
						sibling->parent = c;
						//           C(R)       P(B)
						//          /   \
						//        S(R)
						//        / \
						//     (B)  (B)
						//    / \   / \
						//   () ()    
						//
						parent->left = nullptr;
						c->right = parent;
						parent->parent = c;
						c->color = BLACK;
						//            C(B)
						//           /   \
						//         S(R)  P(B)
						//         / \
						//      (B)  (B)
						//     / \   / \
						//    () ()
						//
						return;
					}
				}
			}
		}

		void Delete(Node * node)
		{
			if (node == nullptr) return;

			Color original = node->color;

			if (node->left == nullptr && node->right == nullptr) {
				if (node == this->root) {
					// Case 0
					//    N( )
					//     / \
					//
					delete node;
					this->root = nullptr;
					return;
				}

				Node * sibling = nullptr;
				if (node == node->parent->left) {
					sibling = node->parent->right;
					node->parent->left = nullptr;
				} else {
					sibling = node->parent->left;
					node->parent->right = nullptr;
				}

				delete node;

				if (original == RED) {
					// Case 1
					//      (B)         (B)
					//     /   \       /   \
					//   N(R)             N(R)
					//   / \               / \
					//
					// Case 2
					//      (B)          (B)
					//     /   \        /   \
					//   N(R)  (R)    (R)  N(R)
					//   / \   / \    / \   / \
					//
					return;
				}
				
				if (original == BLACK) {
					// Case 3
					//      ( )           ( )
					//     /   \         /   \
					//   N(B)  (B)     (B)  N(B)
					//   / \   / \     / \   / \
					//        () ()   () ()
					// where () could be NULL or (R)
					//
					// Case 4
					//      (B)                (B)
					//     /   \              /   \
					//   N(B)  (R)          (R)  N(B)
					//   / \   / \          / \   / \
					//       (B) (B)      (B) (B)
					//      / \   / \    / \   / \
					//     () () () ()  () () () ()
					// where () could be NULL or (R)
					//
					// After node is deleted, its position becomes nullptr
					DeleteFix(sibling->parent, nullptr);
					return;
				}
			}
			
			if (node->left == nullptr) {
				// Case 5
				//   ( )
				//    |
				//   N(B)
				//   /  \
				//      (R)
				//      / \
				//
				Node * right = node->right;
				right->color = BLACK;
				Transplant(node, right);
				delete node;
				//   ( )
				//    |
				//   (B)
				//   / \
				//
				return;
			}
			
			if (node->right == nullptr) {
				// Case 6
				//    ( ) 
				//     |
				//    N(B)
				//    /  \
				//  (R)
				//  / \
				//
				Node * left = node->left;
				left->color = BLACK;
				Transplant(node, left);
				delete node;
				//    ( ) 
				//     |
				//    (B)
				//    / \
				//
				return;
			}
			
			Node * successor = Node::Min(node->right);
			original = successor->color;
				
			if (successor == node->right && successor->right == nullptr) {
				// Case 7
				//     ( ) 
				//      |
				//     N( )
				//     /  \
				//  ( )    S( )
				//  / \    / \
				//				
				Transplant(node, successor);
				successor->left = node->left;
				successor->left->parent = successor;
				original = successor->color;
				successor->color = node->color;
				delete node;
				//     ( ) 
				//      |
				//     S( )
				//     /  \
				//  ( )
				//  / \
				//				
				if (original == BLACK) {
					DeleteFix(successor, nullptr);
				}
				
				return;
			}
			
			if (successor == node->right && successor->right != nullptr) {
				// Case 8
				//     ( ) 
				//      |
				//     N( )
				//     /  \
				//  ( )    S(B)
				//  / \    / \
				//           (R)
				//
				Transplant(node, successor);
				successor->left = node->left;
				successor->left->parent = successor;
				successor->color = node->color;
				successor->right->color = BLACK;
				delete node;
				//     ( ) 
				//      |
				//     S( )
				//     /  \
				//  ( )    (B)
				//  / \
				//
				return;
			}
			
			if (successor != node->right && successor->right == nullptr) {
				// Case 9
				//     ( ) 
				//      |
				//     N( )
				//     /  \
				//  ( )    ( )
				//  / \    /  \
				//		 S( ) ( )
				//       / \
				//
				Node * parent = successor->parent;
				parent->left = nullptr;
				successor->right = node->right;
				successor->right->parent = successor;
				//     ( ) 
				//      |
				//     N( )
				//     /  \
				//   ( )
				//   / \   S( )
				//          / \  
				//            ( )
				//            /  \
				//		         ( )
				//
				Transplant(node, successor);
				successor->left = node->left;
				successor->left->parent = successor;
				original = successor->color;
				successor->color = node->color;
				delete node;
				if (original == BLACK) {
					DeleteFix(parent, nullptr);
				}
				
				return;
			}
			
			if (successor != node->right && successor->right != nullptr) {
				// Case 10
				//     ( ) 
				//      |
				//     N( )
				//     /  \
				//  ( )    ( )
				//  / \    /  \
				//		 S(B) ( )
				//       / \
				//         (R)
				//         / \
				//
				successor->right->color = BLACK;
				Transplant(successor, successor->right);
				//     ( ) 
				//      |
				//     N( )
				//     /  \
				//  ( )    ( )
				//  / \    /  \
				//		 (B) ( )       S(B)
				//       / \
				//
				successor->right = node->right;
				successor->right->parent = successor;
				//     ( ) 
				//      |
				//     N( )
				//     /  \
				//   ( )
				//   / \   S(B)
				//         / \  
				//           ( )
				//           /  \
				//         (B) ( )
				//         / \
				//
				Transplant(node, successor);
				successor->left = node->left;
				successor->left->parent = successor;
				successor->color = node->color;
				delete node;
				return;
			}
		}

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

		void Insert(const T & content)
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
					InsertFixUp(newNode);
					while (this->root->parent != nullptr) {
						this->root = this->root->parent;
					}
				}
			}
		}

		int BlackHeight(void)
		{
			return Node::BlackHeight(this->root);
		}

		int BlackHeight2(void)
		{
			return Node::BlackHeight2(this->root);
		}

		bool Verify(void)
		{
			return Node::Verify(this->root);
		}

		void Delete(const T & content)
		{
			Node * node = Node::Search(this->root, content);
			if (node == nullptr) return;
			Delete(node);
		}

		void Print(void)
		{
			if (this->root != nullptr) this->root->Print();
		}
	};

	template __declspec(dllexport) class RedBlackTree<int>;
}