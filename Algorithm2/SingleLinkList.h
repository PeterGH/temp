#pragma once

#include <iostream>
#include "MyString.h"

using namespace std;

namespace My {

	template<class T> class SingleLinkList
	{
	private:
		class Node {
		public:
			T data;
			Node * next;
			Node(T & d, Node * n) : data(d), next(n) {}
			Node(T & d) : data(d), next(NULL) {}
			~Node(void) { next = NULL; }
		} * _head, * _tail;
	public:
		SingleLinkList(void) : _head(NULL), _tail(NULL) {}
		~SingleLinkList(void);
		void Insert(T &);
		void Reverse(void);
		const T & Middle(void) const;
		void Print(void) const;
		const T & operator[](unsigned int index) const;

		class iterator;
		friend class iterator;
		class iterator {
		private:
			unsigned int _index;
			Node * _pointer;
			void Check(void) const { if (_pointer == NULL) throw invalid_argument(String::Format("SingleLinkList<%s>::iterator is not initialized", typeid(T).name())); }
		public:
			iterator(const SingleLinkList<T> & list) : _index(0), _pointer(list._head) {}
			iterator(const iterator & it) : _index(it._index), _pointer(it._pointer) {}
			iterator(void) : _index(0), _pointer(NULL) {}
			
			const unsigned int index(void) const { return _index; }

			bool operator++() {
				Check();
				if (_pointer->next) {
					_index ++;
					_pointer = _pointer->next;
				}
				else {
					_index = 0;
					_pointer = NULL;
				}
				return _pointer != NULL;
			}

			bool operator++(int) { return operator++(); }

			const T & current() const {
				Check();
				T & d = _pointer->data;
				return d;
			}

			// Return a pointer so that dereference is on the return type
			const Node * operator->() { Check(); return _pointer; }

			const T & operator*() const { return current(); }

			// Note: There is no return value
			operator bool() const { return _pointer != NULL; }

			bool operator==(const iterator & it) const { return _pointer == it._pointer; }
			bool operator!=(const iterator & it) const { return _pointer != it._pointer; }
		};

		iterator begin() const { return iterator(*this); }
		iterator end() const { return iterator(); }
	};

	template<class T> SingleLinkList<T>::~SingleLinkList(void)
	{
		Node * p;
		while (NULL != _head) {
			p = _head;
			_head = p->next;
			delete p;
		}
	}

	template<class T> void SingleLinkList<T>::Insert(T & data)
	{
		Node * node = new Node(data);
		if (NULL == _head) {
			// the list is empty, so initialize the list with the node.
			_head = node;
			_tail = node;
		} else {
			// the list is not empty, so add the node to the end.
			_tail->next = node;
			_tail = node;
		}
	}

	template<class T> void SingleLinkList<T>::Reverse(void)
	{
		Node *p, *n;
		
		// The list is empty or contains only one node.
		if (NULL == _head || NULL == _head->next) return;
		
		// Initialize the variables.

		//  ( )->( )->( )->......( )->NULL
		//   ^                    ^
		//   |                    |
		// _head                _tail

		// p to previous node.
		p = _head;
		
		//  ( )->( )->( )->......( )->NULL
		//   ^                    ^
		//   |                    |
		// _head=p              _tail

		// header to the middle node.
		_head = p->next;

		//  ( )->( )->( )->......( )->NULL
		//   ^    ^               ^
		//   |    |               |
		//   p  _head           _tail

		// n to the next node.
		n = _head->next;
		
		//  ( )->( )->( )->......( )->NULL
		//   ^    ^    ^          ^
		//   |    |    |          |
		//   p  _head  n        _tail

		// tail points to the last node of the reversed list.
		_tail = p;

		//  ( )->( )->( )->......( )->NULL
		//   ^    ^    ^
		//   |    |    |
		//   p  _head  n
		//  =_tail

		// The last node of the reversed list should point to nothing.
		_tail->next = NULL;
		
		// NULL<-( )  ( )->( )->......( )->NULL
		//        ^    ^    ^
		//        |    |    |
		//        p  _head  n
		//     =_tail

		while (NULL != n) {
			// Reverse the link between the previous node and the middle node.
			_head->next = p;
			
			// NULL<-( )<-( )  ( )->......( )->NULL
		    //        ^    ^    ^
		    //        |    |    |
		    //        p  _head  n
		    //     =_tail

			// Move forward.
			p = _head;

			// NULL<-( )<-( )  ( )->......( )->NULL
		    //        ^    ^    ^
		    //        |    |    |
		    //      _tail  p    n
		    //           =_head

			_head = n;

			// NULL<-( )<-( )  ( )->......( )->NULL
		    //        ^    ^    ^
		    //        |    |    |
		    //      _tail  p    n
		    //                =_head

			n = _head->next;

			// NULL<-( )<-( )  ( )->( )......( )->NULL
		    //        ^    ^    ^    ^
		    //        |    |    |    |
		    //      _tail  p  _head  n
		}
		
		// NULL<-( )<-( )......( )  ( )->NULL
		//        ^             ^    ^    ^
		//        |             |    |    |
		//      _tail           p  _head  n

		// n is NULL, header points to the last node of the original list.
		// Reverse the last link.
		_head->next = p;

		// NULL<-( )<-( )......( )<-( ) NULL
		//        ^             ^    ^    ^
		//        |             |    |    |
		//      _tail           p  _head  n
	}

	// The middle node is the n-th node, no matter if the list contain (2n-1) nodes or 2n nodes.
	template<class T> const T & SingleLinkList<T>::Middle(void) const
	{
		Node * middle, * p;
		
		// The list is empty.
		if (NULL == _head) throw invalid_argument("Empty list");
		
		// Start from the first node.
		middle = _head;
		p = _head;
		
		while (NULL != p->next && NULL != p->next->next) {
			// p visits the (2n-1)-th node.
			p = p->next->next;
			// middle visits the n-th node.
			middle = middle->next;
		}
		return middle->data;
	}

	template<class T> void SingleLinkList<T>::Print(void) const
	{
		Node * p = _head;
		cout << "Head->";
		while (NULL != p) {
			cout << p->data << "->";
			p = p->next;
		}
		cout << "NULL" << endl;
	}

	template<class T> const T & SingleLinkList<T>::operator[](unsigned int index) const
	{
		unsigned int i = 0;
		Node * p = _head;
		while (i < index && p != NULL) {
			p = p->next;
			i ++;
		}
		if (p != NULL) {
			// i == index
			return p->data;
		}

		throw invalid_argument(String::Format("Invalid index [%d]", index));
	}

}