#pragma once

#include <iostream>
#include <functional>
using namespace std;

template<class T> class BSTNode
{
	template<class T> friend class BinarySearchTree;

protected:
	T  _content;
	BSTNode * _parent;
	BSTNode * _left;
	BSTNode * _right;
	
	BSTNode<T> * Transplant(BSTNode<T> *, BSTNode<T> *);

public:
	BSTNode(T);
	~BSTNode(void);

	// Insert a content to the subtree at node and return node.
	// If node is NULL, then return a new node with the content.
	BSTNode<T> * Insert(BSTNode<T> * node, T content);
	void Insert(T content) { Insert(this, content); }
	
	void PreOrderWalk(BSTNode<T> *, function<void (BSTNode<T> *)>);
	void PreOrderWalk(function<void (BSTNode<T> *)> f) { PreOrderWalk(this, f); }
	
	void InOrderWalk(BSTNode<T> *, function<void (BSTNode<T> *)>);
	void InOrderWalk(function<void (BSTNode<T> *)> f) { InOrderWalk(this, f); }
	
	void PostOrderWalk(BSTNode<T> *, function<void (BSTNode<T> *)>);
	void PostOrderWalk(function<void (BSTNode<T> *)> f) { PostOrderWalk(this, f); }
	
	// Remove left and right subtrees at node
	void Empty(BSTNode<T> * node);
	void Empty() { Empty(this); }
	
	// Return the first decendent of node whose value equals to content
	BSTNode<T> * Search(BSTNode<T> * node, T content);
	BSTNode<T> * Search(T content) { return Search(this, content); }
	
	BSTNode<T> * Min(BSTNode<T> *);
	BSTNode<T> * Min() { return Min(this); }
	
	BSTNode<T> * Max(BSTNode<T> *);
	BSTNode<T> * Max() { return Max(this); }
	
	BSTNode<T> * Successor(BSTNode<T> *);
	BSTNode<T> * Successor() { return Successor(this); }
	
	BSTNode<T> * Predecessor(BSTNode<T> *);
	BSTNode<T> * Predecessor() { return Predecessor(this); }
	
	T Content() { return _content; }
	void PrintContent() { cout << _content << " "; }
	
	// Print tree at node in order
	void PrintTree(BSTNode<T> * node);
	void PrintTree() { PrintTree(this); }
		
	void Delete(BSTNode<T> *);
};

template<class T> BSTNode<T>::BSTNode(T content)
{
	_content = content;
	_parent = NULL;
	_left = NULL;
	_right = NULL;
}

template<class T> BSTNode<T>::~BSTNode(void)
{
	auto f = [](BSTNode<T> * p) { if (p != NULL) { p = NULL; }};
	f(_left);
	f(_right);
	f(_parent);	
}

template<class T> BSTNode<T> * BSTNode<T>::Insert(BSTNode<T> * node, T content)
{
	BSTNode<T> * newNode = new BSTNode<T>(content);
	BSTNode<T> * parent = node;
	BSTNode<T> * current = node;
	while (current != NULL) {
		parent = current;
		if (newNode->_content < current->_content) {
			current = current->_left;
		} else { // newNode->_content >= current->_content			
			current = current->_right;
		}
	}
	newNode->_parent = parent;
	if (parent == NULL) {
		// This means node is NULL, i.e. it is an empty tree. 
		// Return the new node as it is the first node of a tree.
		return newNode;
	} else if (newNode->_content < parent->_content) {
		parent->_left = newNode;
	} else {
		parent->_right = newNode;
	}
	// The root of tree.
	return node;
}

template<class T> void BSTNode<T>::PreOrderWalk(BSTNode<T> * node, function<void (BSTNode<T> *)> f)
{
	if (node == NULL || f == NULL) return;
	f(node);
	PreOrderWalk(node->_left, f);
	PreOrderWalk(node->_right, f);	
}

template<class T> void BSTNode<T>::InOrderWalk(BSTNode<T> * node, function<void (BSTNode<T> *)> f)
{
	if (node == NULL || f == NULL) return;
	InOrderWalk(node->_left, f);
	f(node);
	InOrderWalk(node->_right, f);	
}

template<class T> void BSTNode<T>::PostOrderWalk(BSTNode<T> * node, function<void (BSTNode<T> *)> f)
{
	if (node == NULL || f == NULL) return;
	PostOrderWalk(node->_left, f);
	PostOrderWalk(node->_right, f);
	f(node);
}

template<class T> void BSTNode<T>::Empty(BSTNode<T> * node)
{
	//PostOrderWalk(root, [](BSTNode<T> *x){ delete x;});
	PostOrderWalk(node->_left, [](BSTNode<T> *x){ delete x;});
	PostOrderWalk(node->_right, [](BSTNode<T> *x){ delete x;});
	node->_left = NULL;
	node->_right = NULL;
}

template<class T> BSTNode<T> * BSTNode<T>::Search(BSTNode<T> * node, T content)
{
	if (node == NULL || node->_content == content) return node;
	if (content < node->_content) return Search(node->_left, content);
	else return Search(node->_right, content);
}

template<class T> BSTNode<T> * BSTNode<T>::Min(BSTNode<T> * node)
{
	if (node == NULL) return node;
	while (node->_left != NULL) node = node->_left;
	return node;
}

template<class T> BSTNode<T> * BSTNode<T>::Max(BSTNode<T> * node)
{
	if (node == NULL) return node;
	while (node->_right != NULL) node = node->_right;
	return node;
}

template<class T> BSTNode<T> * BSTNode<T>::Successor(BSTNode<T> * node)
{
	if (node == NULL) return NULL;

	//  (A)
	//  / \
	// () (B)
	// The successor of A is the minimum node of subtree B
	if (node->_right != NULL) return Min(node->_right);

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
	BSTNode<T> * parent = node->_parent;
	while (parent != NULL && node == parent->_right) {
		node = parent;
		parent = parent->_parent;
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

template<class T> BSTNode<T> * BSTNode<T>::Predecessor(BSTNode<T> * node)
{
	if (node == NULL) return NULL;

	//   (A)
	//   /
	// (B)
	// The predecessor of A is the maximum node of subtree B	
	if (node->_left != NULL) return Max(node->_left);
	
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
	BSTNode<T> * parent = node->_parent;
	while (parent != NULL && node == parent->_left) {
		node = parent;
		parent = parent->_parent;
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

template<class T> void BSTNode<T>::PrintTree(BSTNode<T> * node)
{
	auto f = [](BSTNode<int> * x){ x->PrintContent(); };
	InOrderWalk(node, f);
}

template<class T> BSTNode<T> * BSTNode<T>::Transplant(BSTNode<T> * dst, BSTNode<T> * src)
{
	if (dst == NULL) return NULL;

	if (dst->_parent == NULL) {
		// src becomes the new root
		if (src != NULL) src->_parent = NULL;
		return dst;
	}

	if (dst == dst->_parent->_left) {
		dst->_parent->_left = src;
	} else {
		dst->_parent->_right = src;
	}

	if (src != NULL) src->_parent = dst->_parent;

	return dst;
}

template<class T> void BSTNode<T>::Delete(BSTNode<T> * node)
{
	if (node == NULL) return;

	if (node->_left == NULL) {
		//   () 
		//    |
		//   (A)
		//   /  \
		// NULL (B)
		Transplant(node, node->_right);
		delete node;
		return;
	}

	if (node->_right == NULL) {
		//   ()
		//    |
		//   (A)
		//   /  \
		// (B) NULL
		Transplant(node, node->_left);
		delete node;
		return;
	}

	BSTNode<T> * successor = Min(node->_right);

	if (successor->_parent != node) {
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
		Transplant(successor, successor->_right);
		//     ()
		//     |
		//    (A)
		//    / \
		//   () (D)
		//        \
		//         ()
	    //        /
	    //      (C)           (B)
		successor->_right = node->_right;
		successor->_right->_parent = successor;
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
	successor->_left = node->_left;
	successor->_left->_parent = successor;
	delete node;
}


template<class T> class BinarySearchTree
{
private:
	BSTNode<T> * _root;

public:
	BinarySearchTree(void) { _root = NULL; };
	~BinarySearchTree(void);

	void Insert(T);
	void PreOrderWalk(function<void (T)> f);
	void InOrderWalk(function<void (T)> f);
	void PostOrderWalk(function<void (T)> f);
	void Empty(void);
	T Min(void);
	T Max(void);
	T Successor(T);
	T Predecessor(T);
	void Print();
};

template<class T> BinarySearchTree<T>::~BinarySearchTree(void)
{
	Empty();
}

template<class T> void BinarySearchTree<T>::Insert(T content)
{
	if (_root == NULL) _root = new BSTNode<T>(content);
	else _root->Insert(content);
}

template<class T> void BinarySearchTree<T>::PreOrderWalk(function<void (T)> f)
{
	if (_root != NULL) {
		auto fNode = [=](BSTNode<T> * x){ f(x->Content()); };
		_root->PreOrderWalk(fNode);
	}
}

template<class T> void BinarySearchTree<T>::InOrderWalk(function<void (T)> f)
{
	if (_root != NULL) {
		auto fNode = [=](BSTNode<T> * x){ f(x->Content()); };
		_root->InOrderWalk(fNode);
	}
}

template<class T> void BinarySearchTree<T>::PostOrderWalk(function<void (T)> f)
{
	if (_root != NULL) {
		auto fNode = [=](BSTNode<T> * x){ f(x->Content()); };
		_root->PostOrderWalk(fNode);
	}
}

template<class T> void BinarySearchTree<T>::Empty(void)
{
	if (_root != NULL) {
		_root->Empty();
		_root = NULL;
	}
}

template<class T> T BinarySearchTree<T>::Min(void)
{
	if (_root != NULL) return _root->Min()->_content;
	else return NULL;
}

template<class T> T BinarySearchTree<T>::Max(void)
{
	if (_root != NULL) return _root->Max()->_content;
	else return NULL;
}

template<class T> T BinarySearchTree<T>::Successor(T content)
{
	if (_root != NULL) return _root->Search(content)->Successor()->_content;
	else return NULL;
}

template<class T> T BinarySearchTree<T>::Predecessor(T content)
{
	if (_root != NULL) return _root->Search(content)->Predecessor()->_content;
	else return NULL;
}

template<class T> void BinarySearchTree<T>::Print()
{
	if (_root != NULL) {
		_root->PrintTree();
	}
}

template __declspec(dllexport) class BSTNode<int>;
template __declspec(dllexport) class BinarySearchTree<int>;