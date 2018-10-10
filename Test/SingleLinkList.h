#pragma once

#include <iostream>
#include "Log.h"
#include "String.h"

using namespace std;

namespace Test {

	template<class T> class SingleLinkList {
		template<class T> friend ostream & operator<<(ostream &, const SingleLinkList<T> &);
		template<class T> friend Log & operator<<(Log &, const SingleLinkList<T> &);
	protected:
		class Node {
		public:
			T data;
			Node * next;
			Node(const T & d, Node * n) : data(d), next(n) {}
			Node(const T & d) : data(d), next(nullptr) {}
			~Node(void) { next = nullptr; }
		} * head;

		// Return the pointer to the first instance of input data
		virtual Node * Search(const T & data) const;
	public:
		SingleLinkList(void) : head(nullptr) {}
		virtual ~SingleLinkList(void);
		virtual bool Contain(const T & data) const;
		// Delete the first instance of input data
		virtual void Delete(const T & data);
		virtual void Insert(const T & data);
		const T & Middle(void) const;
		void Reverse(void);
		virtual const T & operator[](unsigned int index) const;

		class iterator;
		friend class iterator;
		class iterator {
		private:
			unsigned int index;
			Node * pointer;
			void Check(void) const { if (pointer == nullptr) throw invalid_argument(String::Format("SingleLinkList<%s>::iterator is not initialized", typeid(T).name())); }
		public:
			iterator(const SingleLinkList<T> & list) : index(0), pointer(list.head) {}
			iterator(const iterator & it) : index(it.index), pointer(it.pointer) {}
			iterator(void) : index(0), pointer(nullptr) {}

			const unsigned int Index(void) const { return this->index; }

			// Prefix increment
			// ++ it
			bool operator++() {
				Check();
				if (pointer->next) {
					index++;
					pointer = pointer->next;
				} else {
					index = 0;
					pointer = nullptr;
				}

				return pointer != nullptr;
			}

			// Postfix increment
			// it ++
			bool operator++(int) { return operator++(); }

			const T & current() const {
				Check();
				T & d = pointer->data;
				return d;
			}

			// Return a pointer so that dereference is on the return type
			const Node * operator->() { Check(); return pointer; }

			const T & operator*() const { return current(); }

			// Note: There is no return value
			// This allows to check if an iterator is valid by using
			//     if (it) { } else { }
			operator bool() const { return pointer != nullptr; }

			bool operator==(const iterator & it) const { return pointer == it.pointer; }
			bool operator!=(const iterator & it) const { return pointer != it.pointer; }
		};

		iterator begin() const { return iterator(*this); }
		iterator end() const { return iterator(); }
	};

	template<class T> SingleLinkList<T>::~SingleLinkList(void)
	{
		Node * p;
		while (nullptr != head) {
			p = head;
			head = p->next;
			delete p;
		}
	}

	template<class T> typename SingleLinkList<T>::Node * SingleLinkList<T>::Search(const T & data) const
	{
		Node * p = head;
		while (nullptr != p && p->data != data) {
			p = p->next;
		}

		// p == nullptr || p->data == data
		return p;
	}

	template<class T> bool SingleLinkList<T>::Contain(const T & data) const
	{
		return nullptr != Search(data);
	}

	template<class T> void SingleLinkList<T>::Delete(const T & data)
	{
		if (nullptr == head) return;

		Node * p = head;
		if (p->data == data) {
			head = p->next;
			delete p;
			return;
		}

		while (nullptr != p->next && p->next->data != data) {
			p = p->next;
		}

		if (nullptr != p->next) {
			Node * t = p->next;
			p->next = t->next;
			delete t;
		}
	}

	template<class T> void SingleLinkList<T>::Insert(const T & data)
	{
		Node * node = new Node(data);
		if (nullptr != head) {
			// The list is not empty. Insert it at front.
			node->next = head;
		}

		head = node;
	}

	// The middle node is the n-th node, no matter if the list contain (2n-1) nodes or 2n nodes.
	template<class T> const T & SingleLinkList<T>::Middle(void) const
	{
		Node * middle, *p;

		// The list is empty.
		if (nullptr == head) throw invalid_argument("Empty list");

		// Start from the first node.
		middle = head;
		p = head;

		while (nullptr != p->next && nullptr != p->next->next) {
			// p visits the (2n-1)-th node.
			p = p->next->next;
			// middle visits the n-th node.
			middle = middle->next;
		}

		return middle->data;
	}

	template<class T> void SingleLinkList<T>::Reverse(void)
	{
		Node *p, *n;

		// The list is empty or contains only one node.
		if (nullptr == head || nullptr == head->next) return;

		// Initialize the variables.

		//  ( )->( )->( )->......( )->nullptr
		//   ^
		//   |
		//  head

		// p to previous node.
		p = head;

		//  ( )->( )->( )->......( )->nullptr
		//   ^
		//   |
		//  head=p

		// head to the middle node.
		head = p->next;

		//  ( )->( )->( )->......( )->nullptr
		//   ^    ^
		//   |    |
		//   p   head

		// n to the next node.
		n = head->next;

		//  ( )->( )->( )->......( )->nullptr
		//   ^    ^    ^
		//   |    |    |
		//   p   head  n

		// The last node of the reversed list should point to nothing.
		p->next = nullptr;

		// nullptr<-( )  ( )->( )->......( )->nullptr
		//           ^    ^    ^
		//           |    |    |
		//           p  _head  n
		
		while (nullptr != n) {
			// Reverse the link between the previous node and the middle node.
			head->next = p;

			// nullptr<-( )<-( )  ( )->......( )->nullptr
			//           ^    ^    ^
			//           |    |    |
			//           p  head  n
			
			// Move forward.
			p = head;

			// nullptr<-( )<-( )  ( )->......( )->nullptr
			//                ^    ^
			//                |    |
			//                p    n
			//              = head

			head = n;

			// nullptr<-( )<-( )  ( )->......( )->nullptr
			//                ^    ^
			//                |    |
			//                p    n
			//                   = head

			n = head->next;

			// nullptr<-( )<-( )  ( )->( )......( )->nullptr
			//                ^    ^    ^
			//                |    |    |
			//                p   head  n
		}

		// nullptr<-( )<-( )......( )  ( )->nullptr
		//                         ^    ^    ^
		//                         |    |    |
		//                         p   head  n

		// n is nullptr, header points to the last node of the original list.
		// Reverse the last link.
		head->next = p;

		// nullptr<-( )<-( )......( )<-( ) nullptr
		//                         ^    ^    ^
		//                         |    |    |
		//                         p   head  n
	}

	template<class T> const T & SingleLinkList<T>::operator[](unsigned int index) const
	{
		unsigned int i = 0;
		Node * p = head;
		while (i < index && p != nullptr) {
			p = p->next;
			i++;
		}

		if (p != nullptr) {
			// i == index
			return p->data;
		}

		throw invalid_argument(String::Format("Invalid index [%d]", index));
	}

	template<class T> ostream & operator<<(ostream & os, const SingleLinkList<T> & list)
	{
		SingleLinkList<T>::Node * p = list.head;
		cout << "Head->";
		while (nullptr != p) {
			cout << p->data << "->";
			p = p->next;
		}

		cout << "nullptr" << endl;
		return os;
	}

	template<class T> Log & operator<<(Log & log, const SingleLinkList<T> & list)
	{
		SingleLinkList<T>::Node * p = list.head;
		log.WriteInformation("Head->");
		while (nullptr != p) {
			// This is not accurate as data may not be int type.
			log.WriteInformation("%d->", p->data);
			p = p->next;
		}

		log.WriteInformation("nullptr");
		return log;
	}
}