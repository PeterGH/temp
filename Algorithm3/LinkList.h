#pragma once

#include <iostream>
#include <fstream>
using namespace std;

template<class T> class SingleLinkNode {
	template<class T> friend class SingleLinkList;
public:
	SingleLinkNode(T);
	~SingleLinkNode(void);
private:
	T _data;
	SingleLinkNode * _next;
};

template<class T> class SingleLinkList {
	// The overloaded operator << is a template
	// Another valid form is: friend ostream& operator<<<>(ostream &, SingleLinkList<T> &);
	friend ostream& operator<<<T>(ostream &, SingleLinkList<T> &);
public:
	SingleLinkList(void);
	~SingleLinkList(void);
	void Insert(T);
	void Reverse(void);
	T Middle(void);
	void Print(ostream &);

private:
	SingleLinkNode<T> * _head, * _tail;
};

template<class T> SingleLinkNode<T>::SingleLinkNode(T data)
{
	_data = data;
	_next = NULL;
}

template<class T> SingleLinkNode<T>::~SingleLinkNode(void)
{
	_next = NULL;
}

template<class T> SingleLinkList<T>::SingleLinkList(void)
{
	_head = NULL;
	_tail = NULL;
}

template<class T> SingleLinkList<T>::~SingleLinkList(void)
{
	SingleLinkNode<T> * p;
	while (NULL != _head) {
		p = _head;
		_head = p->_next;
		delete p;
	}
}

template<class T> void SingleLinkList<T>::Insert(T data)
{
	SingleLinkNode<T> * node = new SingleLinkNode<T>(data);
	if (NULL == _head) {
		// the list is empty, so initialize the list with the node.
		_head = node;
		_tail = node;
	} else {
		// the list is not empty, so add the node to the end.
		_tail->_next = node;
		_tail = node;
	}
}

template<class T> void SingleLinkList<T>::Reverse(void)
{
	SingleLinkNode<T> *p, *n;

	// The list is empty or contains only one node.
	if (NULL == _head || NULL == _head->_next) return;

	// Initialize the variables.
	// p to previous node.
	p = _head;
	// header to the middle node.
	_head = _head->_next;
	// n to the next node.
	n = _head->_next;
	// The last node of the reversed list should point to nothing.
	p->_next = NULL;
	// tail points to the last node of the reversed list.
	_tail = p;

	while (NULL != n) {
		// Reverse the link between the previous node and the middle node.
		_head->_next = p;
		// Move forward.
		p = _head;
		_head = n;
		n = _head->_next;
	}
	// n is NULL, header points to the last node of the original list.
	// Reverst the last link.
	_head->_next = p;
}

// The middle node is the n-th node, no matter if the list contain (2n-1) nodes or 2n nodes.
template<class T> T SingleLinkList<T>::Middle(void)
{
	SingleLinkNode<T> *middle, *p;

	// The list is empty.
	if (NULL == _head) return -1;

	// Start from the first node.
	middle = _head;
	p = _head;

	while (NULL != p->_next && NULL != p->_next->_next) {
		// p visits the (2n-1)-th node.
		p = p->_next->_next;
		// middle visits the n-th node.
		middle = middle->_next;
	}

	return middle->_data;
}

template<class T> void SingleLinkList<T>::Print(ostream & os)
{
	SingleLinkNode<T> * p = _head;
	os << "Head->";
	while (NULL != p) {
		os << p->_data << "->";
		p = p->_next;
	}
	os << "NULL" << endl;
}

template<class T> ostream& operator<<(ostream & os, SingleLinkList<T> & list)
{
	list.Print(os);
	return os;
}

template __declspec(dllexport) class SingleLinkNode<int>;
template __declspec(dllexport) class SingleLinkList<int>;