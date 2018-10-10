#pragma once

#include <functional>
#include <vector>

using namespace std;

namespace Test {
	template<class T> class AVLTree {
	private:
		class Node {
			template<class T> friend class AVLTree;
		private:
			T content;
			Node * parent;
			Node * left;
			Node * right;
			int height;

		public:
			Node(const T & c) : content(c), parent(nullptr), left(nullptr), right(nullptr), height(1) {}
			// Not delete its children
			~Node(void)
			{
				auto f = [](Node * & p) { if (p != nullptr) { p = nullptr; } };
				f(this->left);
				f(this->right);
				f(this->parent);
			}

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

			static void Empty(Node* node)
			{
				PostOrderWalk(node->left, [](Node * x){ delete x; });
				PostOrderWalk(node->right, [](Node * x){ delete x; });
				node->left = nullptr;
				node->right = nullptr;
			}

			static bool Verify(Node * node)
			{
				if (node == nullptr) return true;
				if (node->left == nullptr && node->right == nullptr) {
					if (node->height != 1) return false;
				}

				if (node->left == nullptr && node->right != nullptr) {
					if (node->right->height != 1) return false;
					if (node->height != 2) return false;
				}

				if (node->left != nullptr && node->right == nullptr) {
					if (node->left->height != 1) return false;
					if (node->height != 2) return false;
				}
				
				if (node->left != nullptr && node->right != nullptr) {
					if (node->left->height - node->right->height > 1) return false;
					if (node->right->height - node->left->height > 1) return false;
					if (node->height != 1 + std::max(node->left->height, node->right->height)) return false;
				}

				if (node->left != nullptr && !Verify(node->left)) return false;

				if (node->right != nullptr && !Verify(node->right)) return false;

				return true;
			}

			static stringstream & ToString(stringstream & ss, Node * node, int x, vector<int> & y)
			{
				static string link = "____";
				string c = String::Format("%d:%d", node->height, node->content);
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
		//        z               z
		//
		// Rotate at x
		Node * LeftRotate(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * y = node->right;
			if (y == nullptr) return nullptr;

			node->right = y->left;
			if (y->left != nullptr) y->left->parent = node;

			y->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = y;
			} else {
				if (node == node->parent->left) node->parent->left = y;
				else node->parent->right = y;
			}

			y->left = node;
			node->parent = y;
			return y;
		}

		//        x               y
		//       / \             / \
		//      y       ====>       x
		//     / \                 / \
		//        z               z
		//
		// Rotate at x
		Node * RightRotate(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * y = node->left;
			if (y == nullptr) return nullptr;

			node->left = y->right;
			if (y->right != nullptr) y->right->parent = node;

			y->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = y;
			} else {
				if (node == node->parent->left) node->parent->left = y;
				else node->parent->right = y;
			}

			y->right = node;
			node->parent = y;
			return y;
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

		//        z                 x
		//       / \               / \
		//      x   y     <====       y
		//     / \ / \               / \
		//                          z
		//                         / \
		// Transplant at x
		Node * LeftTransplant(Node * node)
		{
			if (node == nullptr) return nullptr;

			Node * y = node->right;
			if (y == nullptr) return nullptr;

			Node * z = y->left;
			if (z == nullptr) return nullptr;

			y->left = z->right;
			if (z->right != nullptr) z->right->parent = y;

			node->right = z->left;
			if (z->left != nullptr) z->left->parent = node;

			z->right = y;
			y->parent = z;

			z->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = z;
			} else {
				if (node == node->parent->left)
					node->parent->left = z;
				else
					node->parent->right = z;
			}

			z->left = node;
			node->parent = z;

			return z;
		}

		//        x                 z
		//       / \               / \
		//      y       ====>     y   x
		//     / \               / \ / \
		//        z
		//       / \
		// Transplant at x
		Node * RightTransplant(Node * node)
		{
			if (node == nullptr) return nullptr;

			Node * y = node->left;
			if (y == nullptr) return nullptr;

			Node * z = y->right;
			if (z == nullptr) return nullptr;

			y->right = z->left;
			if (z->left != nullptr) z->left->parent = y;

			node->left = z->right;
			if (z->right != nullptr) z->right->parent = node;

			z->left = y;
			y->parent = z;

			z->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = z;
			} else {
				if (node == node->parent->left)
					node->parent->left = z;
				else
					node->parent->right = z;
			}

			z->right = node;
			node->parent = z;

			return z;
		}

		// Case 1
		//        ( )
		//        / \
		//     N(h) ( )
		//     / \  / \
		//
		// Case 2
		//     ( )
		//     / \
		//   ( ) N(h)
		//   / \ / \
		//
		// The subtree at node is a valid AVL tree.
		// Need to fix the height of node's ancestors and siblings.
		void InsertFix(Node * node)
		{
			if (node == nullptr) return;
			while (node->parent != nullptr) {
				Node * parent = node->parent;
				if (parent->height == node->height + 1) {
					//       P(h+1)       P(h+1)
					//       /   \        /   \
					//     N(h)  (h)    (h)   N(h)
					//     / \   / \    / \   / \
					//
					break;
				}
				
				// Now parent->height == node->height

				if (node == parent->left) {
					if (parent->right == nullptr) {
						if (parent->height == 1) {
							//       P(1)
							//       /
							//     N(1)
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->right) {
								//     (2)
								//     / \
								//       P(1)
								//       /
								//     N(1)
								//
								RightRotate(parent);
								//     (2)
								//     / \
								//       N(1)
								//         \
								//         P(1)
								//
								node->height++;
								//     (2)
								//     / \
								//       N(2)
								//         \
								//         P(1)
								//
								continue;
							} else {
								//         (2)
								//         / \
								//       P(1)
								//       /
								//     N(1)
								//
								parent->height++;
								node = parent;
								//         (2)
								//         / \
								//       N(2)
								//       /
								//     (1)
								//
								continue;
							}
						}

						//       P(2)
						//       /
						//     N(2)
						//     / \
						//
						if (node->left == nullptr) {
							//       P(2)
							//       /
							//     N(2)
							//       \
							//       (1)
							LeftRotate(node);
							//       P(2)
							//       /
							//     (1)
							//     /
							//   N(2)
							node->height--;
							node = node->parent;
							node->height++;
							//       P(2)
							//       /
							//     N(2)
							//     /
							//   (1)
						}

						if (node->right == nullptr) {
							//       P(2)
							//       /
							//     N(2)
							//     /
							//   (1)
							RightRotate(parent);
							//     N(2)
							//     /  \
							//   (1)  P(2)
							parent->height = node->height - 1;
							//     N(2)
							//     /  \
							//   (1)  P(1)								
							break;
						} else {
							//       P(2)
							//       /
							//     N(2)
							//     /  \
							//   (1)  (1)
							RightRotate(parent);
							//     N(2)
							//     /  \
							//   (1)  P(2)
							//        /
							//      (1)
							node->height++;
							//     N(3)
							//     /  \
							//   (1)  P(2)
							//        /
							//      (1)
							continue;
						}
					} else if (parent->right != nullptr) {
						if (parent->right->height == node->height - 1) {
							//       P(h)
							//       /   \
							//     N(h) (h-1)
							//     / \   / \
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->left) {
								//         ( )
								//         /
								//       P(h)
								//       /   \
								//     N(h) (h-1)
								//     / \   / \
								//
								parent->height++;
								node = parent;
								//         ( )
								//         /
								//       N(h+1)
								//       /   \
								//     (h)  (h-1)
								//     / \   / \
								//
								continue;
							} else {
								//      ( )
								//        \
								//       P(h)
								//       /   \
								//     N(h) (h-1)
								//     / \   / \
								//
								RightRotate(parent);
								//      ( )
								//        \
								//       N(h)
								//       /   \
								//           P(h)
								//           / \
								//             (h-1)
								node->height++;
								//      ( )
								//        \
								//       N(h+1)
								//       /   \
								//           P(h)
								//           / \
								//             (h-1)
								continue;
							}
						}

						// Now parent->right->height == node->height - 2

						//       P(h)              P(h)              P(h)
						//       /   \            /    \            /    \
						//     N(h) (h-2)       N(h)   (h-2)      N(h)   (h-2)
						//     /     / \       /  \     / \      /  \     /  \
						//                  (h-1)(h-2)        (h-1)(h-1) 
						//
						RightRotate(parent);
						//       N(h)             N(h)                N(h)
						//       /   \            /   \               /   \
						//          P(h)       (h-1)  P(h)         (h-1)  P(h)
						//           / \             /   \               /    \
						//            (h-2)       (h-2)  (h-2)         (h-1) (h-2)
						//
						if (parent->left != nullptr && parent->height == parent->left->height + 1) {
							node = parent;
							continue;
						} else {
							parent->height--;
							break;
						}
						//       N(h)             N(h)                  (h)
						//       /   \            /   \               /   \
						//          P(h-1)     (h-1) P(h-1)         (h-1) N(h)
						//           / \             /   \               /    \
						//            (h-2)       (h-2)  (h-2)         (h-1) (h-2)
						//							
					}
				} else if (node == parent->right) {
					if (parent->left == nullptr) {
						if (parent->height == 1) {
							//       P(1)
							//         \
							//        N(1)
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->left) {
								//     (2)
								//     / \
								//   P(1)
								//     \
								//     N(1)
								//
								LeftRotate(parent);
								//     (2)
								//     / \
								//   N(1)
								//   /
								// P(1)
								//
								node->height++;
								//     (2)
								//     / \
								//   N(2)
								//   /
								// P(1)
								//
								continue;
							} else {
								//    (2)
								//    / \
								//      P(1)
								//        \
								//        N(1)
								//
								parent->height++;
								node = parent;
								//    (2)
								//    / \
								//      N(2)
								//        \
								//        (1)
								//
								continue;
							}
						}

						//       P(2)
						//          \
						//          N(2)
						//           / \
						//
						if (node->right == nullptr) {
							//       P(2)
							//          \
							//          N(2)
							//           /
							//         (1)
							RightRotate(node);
							//       P(2)
							//          \
							//          (1)
							//            \
							//           N(2)
							node->height--;
							node = node->parent;
							node->height++;
							//       P(2)
							//          \
							//          N(2)
							//            \
							//            (1)
						}

						if (node->left == nullptr) {
							//       P(2)
							//          \
							//          N(2)
							//            \
							//            (1)
							LeftRotate(parent);
							//       N(2)
							//       /   \
							//     P(2)  (1)
							parent->height = node->height - 1;
							//       N(2)
							//       /   \
							//     P(1)  (1)
							break;
						} else {
							//       P(2)
							//          \
							//          N(2)
							//          /  \
							//         (1) (1)
							LeftRotate(parent);
							//       N(2)
							//       /   \
							//     P(2)  (1)
							//        \
							//        (1)
							node->height++;
							//       N(3)
							//       /   \
							//     P(2)  (1)
							//        \
							//        (1)
							continue;
						}
					} else if (parent->left != nullptr) {
						if (parent->left->height == node->height - 1) {
							//       P(h)
							//       /   \
							//    (h-1) N(h)
							//     / \   / \
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->right) {
								//     ( )
								//       \
								//       P(h)
								//       /   \
								//    (h-1) N(h)
								//     / \   / \
								//
								parent->height++;
								node = parent;
								//     ( )
								//       \
								//       N(h+1)
								//       /   \
								//    (h-1)  (h)
								//     / \   / \
								//
								continue;
							} else {
								//         ( )
								//         /
								//       P(h)
								//       /   \
								//    (h-1) N(h)
								//     / \   / \
								//
								LeftRotate(parent);
								//         ( )
								//         /
								//       N(h)
								//       /   \
								//     P(h)
								//     / \
								//  (h-1)
								node->height++;
								//         ( )
								//         /
								//       N(h+1)
								//       /   \
								//     P(h)
								//     / \
								//  (h-1)
								continue;
							}
						}

						// Now parent->left->height == node->height - 2
						
						//		 P(h)              P(h)              P(h)
						//       /   \            /    \            /    \
						//    (h-2)  N(h)      (h-2)   N(h)      (h-2)   N(h)
						//     / \     \       /  \     / \      /  \     /  \
						//                           (h-2)(h-1)        (h-1) (h-1)
						//
						LeftRotate(parent);
						//       N(h)             N(h)                N(h)
						//       /   \            /   \               /   \
						//     P(h)            P(h)  (h-1)          P(h) (h-1)
						//     / \             /   \               /    \
						//  (h-2)           (h-2)  (h-2)         (h-2) (h-1)
						//
						if (parent->right != nullptr && parent->height == parent->right->height + 1) {
							node = parent;
							continue;
						} else {
							parent->height--;
							break;
						}
						//       N(h)             N(h)                 (h)
						//       /   \            /   \               /   \
						//    P(h-1)          P(h-1) (h-1)           N(h) (h-1)
						//     / \             /   \               /    \
						//  (h-2)           (h-2)  (h-2)         (h-2) (h-1)
						//
					}
				}
			}
		}

		// Node height is one less than its original value.
		// Need to fix it way up.
		void DeleteFix(Node * node)
		{
			if (node == nullptr || node->parent == nullptr) return;

			while (node->parent != nullptr) {
				Node * parent = node->parent;

				if (node == parent->left) {
					//      P( )
					//      /   \
					//   N(h)   ( )
					Node * sibling = parent->right;

					if (sibling->height == node->height) {
						//      P(h+2)
						//      /   \
						//   N(h)   S(h)
						parent->height = node->height + 1;
						node = parent;
						//      N(h+1)
						//      /   \
						//    (h)   S(h)
						continue;
					}

					if (sibling->height == node->height + 1) {
						//      P(h+2)
						//      /   \
						//   N(h)   S(h+1)
						break;
					}

					if (sibling->height == node->height + 2) {
						//      P(h+3)
						//      /   \
						//   N(h)   S(h+2)
						//           /  \
						//
						if (sibling->right->height == node->height) {
							//      P(h+3)
							//      /   \
							//   N(h)   S(h+2)
							//           /  \
							//        (h+1) (h)
							//         / \
							//
							LeftTransplant(parent);
							//         (h+1)
							//         /    \
							//      P(h+3)  S(h+2)
							//      /   \    /  \
							//   N(h)           (h)
							parent->height = node->height + 1;
							sibling->height = node->height + 1;
							sibling->parent->height = node->height + 2;
							node = sibling->parent;
							//         N(h+2)
							//         /    \
							//      P(h+1)  S(h+1)
							//      /   \    /  \
							//    (h)           (h)
							continue;
						}

						if (sibling->left->height == node->height) {
							//      P(h+3)
							//      /   \
							//   N(h)   S(h+2)
							//           /  \
							//         (h) (h+1)
							LeftRotate(parent);
							//         S(h+2)
							//         /    \
							//      P(h+3)  (h+1)
							//      /   \
							//   N(h)   (h)
							parent->height = node->height + 1;
							node = sibling;
							//         N(h+2)
							//         /    \
							//      P(h+1)  (h+1)
							//      /   \
							//    (h)   (h)
							continue;
						}

						if (sibling->left->height == node->height + 1) {
							//      P(h+3)
							//      /   \
							//   N(h)   S(h+2)
							//           /  \
							//        (h+1) (h+1)
							LeftRotate(parent);
							//         S(h+2)
							//         /    \
							//      P(h+3)  (h+1)
							//      /   \
							//   N(h)   (h+1)
							parent->height = node->height + 2;
							sibling->height = node->height + 3;
							//         S(h+3)
							//         /    \
							//      P(h+2)  ( )
							//      /   \
							//   N(h)   (h+1)
							break;
						}
					}
				}

				if (node == parent->right) {
					//      P( )
					//      /   \
					//    ( )  N(h)
					Node * sibling = parent->left;

					if (sibling->height == node->height) {
						//      P(h+2)
						//      /   \
						//   S(h)   N(h)
						parent->height = node->height + 1;
						node = parent;
						//      N(h+1)
						//      /   \
						//    S(h)   (h)
						continue;
					}

					if (sibling->height == node->height + 1) {
						//      P(h+2)
						//      /   \
						//  S(h+1)  N(h)
						break;
					}

					if (sibling->height == node->height + 2) {
						//      P(h+3)
						//      /   \
						//  S(h+2)   N(h)
						//   /  \
						//
						if (sibling->left->height == node->height) {
							//      P(h+3)
							//      /   \
							//  S(h+2)   N(h)
							//   /  \
							// (h)  (h+1)
							RightTransplant(parent);
							//         (h+1)
							//         /    \
							//      S(h+2)  P(h+3)
							//      /   \    /  \
							//    (h)           N(h)
							parent->height = node->height + 1;
							sibling->height = node->height + 1;
							sibling->parent->height = node->height + 2;
							node = sibling->parent;
							//         N(h+2)
							//         /    \
							//      S(h+1)  P(h+1)
							//      /   \    /  \
							//    (h)           (h)
							continue;
						}

						if (sibling->right->height == node->height) {
							//      P(h+3)
							//      /   \
							//  S(h+2)   N(h)
							//   /  \
							// (h+1) (h)
							RightRotate(parent);
							//         S(h+2)
							//         /    \
							//      (h+1)  P(h+3)
							//              /   \
							//            (h)   N(h)
							parent->height = node->height + 1;
							node = sibling;
							//         N(h+2)
							//         /    \
							//      (h+1) P(h+1)
							//              /   \
							//            (h)   (h)
							continue;
						}

						if (sibling->right->height == node->height + 1) {
							//      P(h+3)
							//      /   \
							//  S(h+2)   N(h)
							//   /  \
							//(h+1) (h+1)
							RightRotate(parent);
							//         S(h+2)
							//         /    \
							//      (h+1) P(h+3)
							//              /   \
							//           (h+1)   N(h)
							parent->height = node->height + 2;
							sibling->height = node->height + 3;
							//         S(h+3)
							//         /    \
							//      (h+1)  P(h+2)
							//              /   \
							//           (h+1)   N(h)
							break;
						}
					}
				}
			}
		}

		//     N( )
		//     /
		//
		//     N( )
		//        \
		// Node has one leaf child deleted.
		// Need to fix the node tree.
		void DeleteFixLeafTree(Node * node)
		{
			if (node == nullptr) return;
			if (node->left == nullptr && node->right == nullptr) {
				if (node->height != 1) {
					node->height = 1;
					DeleteFix(node);
				}

				return;
			}

			if (node->left != nullptr && node->right != nullptr) {
				// Should not be a valid input,
				// but handle it anyway.
				int h = 1 + node->left->height > node->right->height ? node->left->height : node->right->height;
				if (node->height != h) {
					node->height = h;
					DeleteFix(node);
				}

				return;
			}

			if (node->left != nullptr) {
				if (node->left->height == 1) {
					//     N(2)
					//     /
					//	 (1)
					return;
				} else {
					Node * left = node->left;
					if (left->right == nullptr) {
						//     N(3)
						//     /
						//	 L(2)
						//   /
						// (1)
						RightRotate(node);
						//	 L(2)
						//   /  \
						// (1) N(3)
						node->height = 1;
						//	 L(2)
						//   /  \
						// (1) N(1)
						DeleteFix(left);
						return;
					} else {
						//     N(3)
						//     /
						//	 L(2)
						//   / \
						//     (1)
						RightTransplant(node);
						//      (1)
						//     /  \
						//	 L(2) N(3)
						//   /
						//
						if (left->left == nullptr) {
							//      (1)
							//     /  \
							//	 L(2) N(3)
							left->height = 1;
							left->parent->height = 2;
							node->height = 1;
							//      (2)
							//     /  \
							//	 L(1) N(1)
							DeleteFix(left->parent);
							return;
						} else {
							//      (1)
							//     /  \
							//	 L(2) N(3)
							//   /
							// (1)
							left->parent->height = 3;
							node->height = 1;
							//      (3)
							//     /  \
							//	 L(2) N(1)
							//   /
							// (1)
							return;
						}
					}
				}
			}

			if (node->right != nullptr) {
				if (node->right->height == 1) {
					//     N(2)
					//        \
					//	      (1)
					return;
				} else {
					Node * right = node->right;
					if (right->left == nullptr) {
						//     N(3)
						//        \
						//	      R(2)
						//          \
						//          (1)
						LeftRotate(node);
						//	     R(2)
						//       /  \
						//     N(3) (1)
						node->height = 1;
						//	     R(2)
						//       /  \
						//     N(1) (1)
						DeleteFix(right);
						return;
					} else {
						//     N(3)
						//        \
						//	      R(2)
						//        /  \
						//      (1)
						LeftTransplant(node);
						//      (1)
						//     /   \
						//	 N(3) R(2)
						//           \
						//
						if (right->right == nullptr) {
							//      (1)
							//     /   \
							//	 N(3) R(2)
							right->height = 1;
							right->parent->height = 2;
							node->height = 1;
							//      (2)
							//     /   \
							//	 N(1) R(1)
							DeleteFix(right->parent);
							return;
						} else {
							//      (1)
							//     /   \
							//	 N(3) R(2)
							//           \
							//           (1)
							right->parent->height = 3;
							node->height = 1;
							//      (3)
							//     /   \
							//	 N(1) R(2)
							//           \
							//           (1)
							return;
						}
					}
				}
			}
		}

	public:

		AVLTree(void) : root(nullptr) {}

		~AVLTree()
		{ 
			if (this->root != nullptr) {
				Node::Empty(this->root);
				delete this->root;
				this->root = nullptr;
			}
		}

		void Insert(const T & content)
		{
			Node * newNode = new Node(content);

			if (this->root == nullptr) {
				// The new node becomes the root.
				this->root = newNode;
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

			InsertFix(newNode);
		}

		void Delete(const T & content)
		{
			Node * node = Node::Search(this->root, content);
			if (node == nullptr) return;

			if (node->left == nullptr && node->right == nullptr) {
				if (node->parent == nullptr) {
					this->root = nullptr;
					delete node;
					return;
				}

				Node * parent = node->parent;
				if (node == parent->left) parent->left = nullptr;
				else if (node == parent->right) parent->right = nullptr;
				delete node;
				DeleteFixLeafTree(parent);
				return;
			}

			if (node->left == nullptr) {
				//    N(2)
				//       \
				//       (1)
				Node * right = node->right;
				Transplant(node, right);
				delete node;
				//    (1)
				if (right->parent != nullptr) DeleteFix(right);
				return;
			}

			if (node->right == nullptr) {
				//    N(2)
				//    /
				//  (1)
				Node * left = node->left;
				Transplant(node, left);
				delete node;
				//    (1)
				if (left->parent != nullptr) DeleteFix(left);
				return;
			}

			// Now node->left and node-right exist

			//    N( )
			//    /  \
			//  ( )  ( )

			Node * successor = Node::Min(node->right);

			if (successor == node->right && successor->right == nullptr) {
				//    N( )
				//    /  \
				//  ( )  S(1)
				//  / \
				//
				Transplant(node, successor);
				successor->height = node->height;
				successor->left = node->left;
				node->left->parent = successor;
				delete node;
				//    S( )
				//    /
				//  ( )
				//  / \
				//
				DeleteFixLeafTree(successor);
				return;
			}

			if (successor == node->right && successor->right != nullptr) {
				//    N( )
				//    /  \
				//  ( )  S(2)
				//  / \     \
				//          (1)
				Transplant(node, successor);
				successor->height = node->height;
				successor->left = node->left;
				node->left->parent = successor;
				delete node;
				//    S( )
				//    /  \
				//  ( )  (1)
				//  / \
				//
				DeleteFix(successor->right);
				return;
			}

			// Now successor != node->right
			//     N( )
			//    /   \
			//  ( )   ( )
			//  / \   /  \
			//      ( )
			//      / \
			//    S( )
			//       \

			if (successor->right != nullptr) {
				//     N( )
				//    /   \
				//  ( )   ( )
				//  / \   /  \
				//      ( )
				//      / \
				//    S(2)
				//       \
				//       (1)
				Node * right = successor->right;
				Transplant(successor, right);
				successor->right = node->right;
				node->right->parent = successor;
				//     N( )
				//    /   \
				//  ( )
				//  / \   S(2)
				//           \
				//           ( )
				//          /  \
				//        ( )
				//        / \
				//      R(1)
				//
				Transplant(node, successor);
				successor->height = node->height;
				successor->left = node->left;
				node->left->parent = successor;
				delete node;
				//     S( )
				//    /   \
				//  ( )   ( )
				//  / \   /  \
				//      ( )
				//      / \
				//    R(1)
				DeleteFix(right);
				return;
			}

			if (successor->right == nullptr) {
				//     N( )
				//    /   \
				//  ( )   ( )
				//  / \   /  \
				//      ( )
				//      / \
				//    S(1)
				Node * parent = successor->parent;
				parent->left = nullptr;
				successor->right = node->right;
				node->right->parent = successor;
				//     N( )
				//    /   \
				//  ( )
				//  / \   S(1)
				//           \
				//           ( )
				//          /  \
				//        P( )
				//           \
				//
				Transplant(node, successor);
				successor->height = node->height;
				successor->left = node->left;
				node->left->parent = successor;
				delete node;
				//     S( )
				//    /   \
				//  ( )   ( )
				//  / \   /  \
				//      P( )
				//         \
				//
				DeleteFixLeafTree(parent);
				return;
			}
		}

		bool Verify(void)
		{
			return Node::Verify(this->root);
		}

		void Print(void)
		{
			if (this->root != nullptr) this->root->Print();
		}
	};
}
