#pragma once

#include <iostream>
#include <functional>
using namespace std;

template<class T> class BinarySearchTreeNode
{
	template<class T> friend class BinarySearchTree;
private:
	T  _content;
	BinarySearchTreeNode * _parent;
	BinarySearchTreeNode * _left;
	BinarySearchTreeNode * _right;

public:
	BinarySearchTreeNode(T );
	~BinarySearchTreeNode(void);

	void Print() { cout << _content << " "; };
};

template<class T> BinarySearchTreeNode<T>::BinarySearchTreeNode(T content)
{
	_content = content;
	_parent = NULL;
	_left = NULL;
	_right = NULL;
}

template<class T> BinarySearchTreeNode<T>::~BinarySearchTreeNode(void)
{
	auto f = [](BinarySearchTreeNode<T> * p) { if (p != NULL) { p = NULL; }};
	f(_left);
	f(_right);
	f(_parent);	
}

template<class T> class BinarySearchTree
{
private:
	BinarySearchTreeNode<T> * _root;
	void PreOrderWalk(BinarySearchTreeNode<T> *, function<void (BinarySearchTreeNode<T> *)>);
	void InOrderWalk(BinarySearchTreeNode<T> *, function<void (BinarySearchTreeNode<T> *)>);
	void PostOrderWalk(BinarySearchTreeNode<T> *, function<void (BinarySearchTreeNode<T> *)>);
	BinarySearchTreeNode<T> * Search(BinarySearchTreeNode<T> *, T);
	BinarySearchTreeNode<T> * Min(BinarySearchTreeNode<T> *);
	BinarySearchTreeNode<T> * Max(BinarySearchTreeNode<T> *);

public:
	BinarySearchTree(void) { _root = NULL; };
	~BinarySearchTree(void);

	void Insert(T);
	void PreOrderWalk(function<void (BinarySearchTreeNode<T> *)> f) { PreOrderWalk(_root, f); };
	void InOrderWalk(function<void (BinarySearchTreeNode<T> *)> f) { InOrderWalk(_root, f); };
	void PostOrderWalk(function<void (BinarySearchTreeNode<T> *)> f) { PostOrderWalk(_root, f); };
	void Empty(void);
	BinarySearchTreeNode<T> * Search(T content) { return Search(_root, content); }
	BinarySearchTreeNode<T> * Min(void) { return Min(_root); }
	BinarySearchTreeNode<T> * Max(void) { return Max(_root); }
	BinarySearchTreeNode<T> * Successor(BinarySearchTreeNode<T> *);
	BinarySearchTreeNode<T> * Predecessor(BinarySearchTreeNode<T> *);
	void Print();
};

template<class T> BinarySearchTree<T>::~BinarySearchTree(void)
{
	Empty();
}

template<class T> void BinarySearchTree<T>::Empty(void)
{
	PostOrderWalk(_root, [](BinarySearchTreeNode<T> *x){ delete x;});
	_root = NULL;
}

template<class T> void BinarySearchTree<T>::Insert(T content)
{
	BinarySearchTreeNode<T> * node = new BinarySearchTreeNode<T>(content);
	BinarySearchTreeNode<T> * parent = NULL;
	BinarySearchTreeNode<T> * current = _root;
	while (current != NULL) {
		parent = current;
		if (node->_content < current->_content) {
			current = current->_left;
		} else {
			current = current->_right;
		}
	}
	node->_parent = parent;
	if (parent == NULL) {
		_root = node;
	} else if (node->_content < parent->_content) {
		parent->_left = node;
	} else {
		parent->_right = node;
	}
}

template<class T> void BinarySearchTree<T>::PreOrderWalk(BinarySearchTreeNode<T> * node, function<void (BinarySearchTreeNode<T> *)> f)
{
	if (node == NULL || f == NULL) return;
	f(node);
	PreOrderWalk(node->_left, f);
	PreOrderWalk(node->_right, f);	
}

template<class T> void BinarySearchTree<T>::InOrderWalk(BinarySearchTreeNode<T> * node, function<void (BinarySearchTreeNode<T> *)> f)
{
	if (node == NULL || f == NULL) return;
	InOrderWalk(node->_left, f);
	f(node);
	InOrderWalk(node->_right, f);	
}

template<class T> void BinarySearchTree<T>::PostOrderWalk(BinarySearchTreeNode<T> * node, function<void (BinarySearchTreeNode<T> *)> f)
{
	if (node == NULL || f == NULL) return;
	PostOrderWalk(node->_left, f);
	PostOrderWalk(node->_right, f);
	f(node);
}

template<class T> BinarySearchTreeNode<T> * BinarySearchTree<T>::Search(BinarySearchTreeNode<T> * node, T content)
{
	if (node == NULL || node->_content == content) return node;
	if (content < node->_content) return Search(node->_left, content);
	else return Search(node->_right, content);
}

template<class T> BinarySearchTreeNode<T> * BinarySearchTree<T>::Min(BinarySearchTreeNode<T> * node)
{
	if (node == NULL) return node;
	while (node->_left != NULL) node = node->_left;
	return node;
}

template<class T> BinarySearchTreeNode<T> * BinarySearchTree<T>::Max(BinarySearchTreeNode<T> * node)
{
	if (node == NULL) return node;
	while (node->_right != NULL) node = node->_right;
	return node;
}

template<class T> BinarySearchTreeNode<T> * BinarySearchTree<T>::Successor(BinarySearchTreeNode<T> * node)
{
	if (node == NULL) return NULL;
	if (node->_right != NULL) return Min(node->_right);
	BinarySearchTreeNode<T> * parent = node->_parent;
	while (parent != NULL && node == parent->_right) {
		node = parent;
		parent = parent->_parent;
	}
	return parent;
}

template<class T> BinarySearchTreeNode<T> * BinarySearchTree<T>::Predecessor(BinarySearchTreeNode<T> * node)
{
	if (node == NULL) return NULL;
	if (node->_left != NULL) return Max(node->_left);
	BinarySearchTreeNode<T> * parent = node->_parent;
	while (parent != NULL && node == parent->_left) {
		node = parent;
		parent = parent->_parent;
	}
	return parent;
}

template<class T> void BinarySearchTree<T>::Print()
{
	auto f = [](BinarySearchTreeNode<int> * x){ x->Print(); };
	PostOrderWalk(f);
}

template __declspec(dllexport) class BinarySearchTreeNode<int>;
template __declspec(dllexport) class BinarySearchTree<int>;