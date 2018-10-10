#pragma once
#include <stdexcept>
#include "Node.h"
using namespace std;
namespace Test {
	template<class T> class SingleNode : public Node<T> {
		template<class T> friend ostream & operator<<(ostream &, SingleNode<T> *);
	public:
		SingleNode(const T & v) : Node<T>(v, 1) {}

		~SingleNode(void) {}

		// Delete the first node with value v
		void Delete(const T & v);

		// Delete the first node with value v. This list may contain a cycle or not.
		static SingleNode * Delete(SingleNode * list, const T & v);

		// Delete the list rooted at the node. This list may contain a cycle or not.
		void DeleteList(void);

		// Delete the list. This list may contain a cycle or not.
		static void DeleteList(SingleNode * list);

		// Find the beginning of cycle if exists
		static SingleNode * FindCycle(SingleNode * list);

		// Determine if the list has a cycle somewhere
		static bool HasCycle(SingleNode * list);

		// Insert a node or a list after this one. This list may contain a cycle or not.
		void InsertAfter(SingleNode * node);

		// Insert a node or a list at the end of this list. This list may contain a cycle or not.
		void InsertAtEnd(SingleNode * node);

		// Count list nodes. The list may contain a cycle or not.
		size_t Length(void);

		// Count list nodes. The list may contain a cycle or not.
		static size_t Length(SingleNode * list);

		// Return the n-th node when this list contains (2n-1) or 2n nodes.
		// The list may contain a cycle or not.
		SingleNode * Middle(void);

		// Return the n-th node when this list contains (2n-1) or 2n nodes.
		// The list may contain a cycle or not.
		static SingleNode * Middle(SingleNode * list);

		// Get the reference of next node pointer
		SingleNode * & Next(void)
		{
			return (SingleNode * &)this->Neighbor(0);
		}

		// Set the next node pointer
		void Next(SingleNode * next)
		{
			this->Neighbor(0) = next;
		}

		// Reorder single-link list
		// (1)  0 -> 1 -> 2 -> ...... -> n-1 -> n -> n+1 -> ...... 2n-1 -> nullptr
		//      0 -> 2n-1 -> 1 -> 2n-2 -> 2 -> ...... -> n-2 -> n+1 -> n-1 -> n -> nullptr
		// (2)  0 -> 1 -> 2 -> ...... -> n-1 -> n -> n+1 -> ...... 2n-1 -> 2n nullptr
		//      0 -> 2n -> 1 -> 2n-1 -> 2 -> ...... -> n+2 -> n-1 -> n+1 -> n -> nullptr
		static void Reorder(SingleNode * node);

		// Reverse this node and return the head of new list.
		// The list may be a cycle or not.
		SingleNode * Reverse(void);

		// Reverse this node and return the head of new list.
		// The list may contain a cycle or not.
		static SingleNode * Reverse(SingleNode * list);

		// Return the last node. The list may contain a cycle or not.
		static SingleNode * Tail(SingleNode * list);

		// Create a random list, no cycle
		static SingleNode * RandomList(size_t length);
	};

	template<class T> void SingleNode<T>::Delete(const T & v)
	{
		SingleNode * p = this;
		if (p->Value() == v) {
			// This node is what we are looking for, but
			// we cannot delete itself. So we copy next node value into this one,
			// which effectively "delete" this node.
			if (p->Next() == nullptr) throw invalid_argument("A SingleNode cannot delete itself");
			while (p->Next()->Next() != nullptr && p->Next()->Next() != this) {
				p->Value() = p->Next()->Value();
				p = p->Next();
			}
			p->Value() = p->Next()->Value();
			// Now p->Next() is useless and can be deleted
		} else {
			// TODO: handle the case when the list is a cycle and v is not found
			while (p->Next() != nullptr && p->Next()->Value() != v) {
				p = p->Next();
			}
			// Now p->Next() is what we are looking for
		}

		if (p->Next() != nullptr) {
			SingleNode * q = p->Next();
			p->Next() = q->Next();
			delete q;
		}
	}

	template<class T> SingleNode<T> * SingleNode<T>::Delete(SingleNode * list, const T & v)
	{
		if (list == nullptr) return nullptr;
		if (list->Value() == v && (list->Next() == nullptr || list->Next() == list)) {
			// list->v->null, or
			// list->v-|
			//      |__|
			delete list;
			return nullptr;
		}

		SingleNode * t = Tail(list);

		if (list->Value() == v) {
			if (t->Next() == list) {
				// list->v->...->t-|
				//      |__________|
				t->Next() = list->Next();
			}
			t = list->Next();
			delete list;
			return t;
		}

		SingleNode * p = list;
		while (p != t && p->Next()->Value() != v) p = p->Next();

		if (p == t) {
			// Not found
			return list;
		}

		if (p->Next() == t->Next()) {
			if (t->Next() == t) {
				// list->...->p->v-|
				//              |__|
				p->Next() = nullptr;
				delete t;
			} else {
				// list->...->p->v->...->t-|
				//              |__________|
				p->Next() = t->Next()->Next();
				p = t->Next();
				t->Next() = p->Next();
				delete p;
			}
		} else {
			// list->...->p->v->...->x->...->t-|
			//                      |__________|
			// list->...->x->...->p->v->...->t-|
			//           |_____________________|
			// list->x->...->p->v-|
			//      |_____________|
			// list->x->...->p->v->null
			t = p->Next();
			p->Next() = t->Next();
			delete t;
		}
		return list;
	}

	template<class T> void SingleNode<T>::DeleteList(void)
	{
		SingleNode<T> * p = Tail(this);
		if (p != nullptr) {
			// Break the cycle if there is one
			p->Next() = nullptr;
		}
		while (this->Next() != nullptr) {
			p = this->Next();
			this->Next() = p->Next();
			p->Next() = nullptr;
			delete p;
		}
	}

	template<class T> void SingleNode<T>::DeleteList(SingleNode * list)
	{
		if (list == nullptr) return;
		SingleNode<T> * p = Tail(list);
		if (p != nullptr) {
			// Break the cycle if there is one
			p->Next() = nullptr;
		}
		while (list != nullptr) {
			p = list;
			list = list->Next();
			p->Next() = nullptr;
			delete p;
		}
	}

	template<class T> SingleNode<T> * SingleNode<T>::FindCycle(SingleNode * list)
	{
		if (list == nullptr) return nullptr;

		SingleNode * t = Tail(list);
		if (t == nullptr) return nullptr;
		return t->Next();
	}

	template<class T> bool SingleNode<T>::HasCycle(SingleNode * list)
	{
		if (list == nullptr) return false;

		SingleNode * p = list;
		SingleNode * q = list;
		while (q->Next() != nullptr && q->Next()->Next() != nullptr) {
			p = p->Next();
			q = q->Next()->Next();
			if (p == q) return true;
		}

		return false;
	}

	template<class T> void SingleNode<T>::InsertAfter(SingleNode * node)
	{
		if (node == nullptr) throw invalid_argument("node is nullptr");

		SingleNode * p = Tail(node);
		// p->Next() == nullptr, if node contains no cycle
		// p->Next() != nullptr, if node contains a cycle
		// If node contains a cycle, it will be broken
		p->Next() = this->Next();
		this->Next() = node;
	}

	template<class T> void SingleNode<T>::InsertAtEnd(SingleNode * node)
	{
		if (node == nullptr) throw invalid_argument("node is nullptr");

		SingleNode * p = Tail(this);
		// p->Next() == nullptr, if this list contains no cycle
		// p->Next() != nullptr, if this list contains a cycle

		SingleNode * q = Tail(node);
		// q->Next() == nullptr, if node contains no cycle
		// q->Next() != nullptr, if node contains a cycle

		// If node contains a cycle, it will be broken
		// If this list contains a cycle, it will be maintained
		q->Next() = p->Next();
		p->Next() = node;
	}

	template<class T> size_t SingleNode<T>::Length(void)
	{
		size_t s = 1;
		SingleNode * t = Tail(this);
		SingleNode * p = this;
		while (p != t) {
			s++;
			p = p->Next();
		}
		return s;
	}

	template<class T> size_t SingleNode<T>::Length(SingleNode * list)
	{
		if (list == nullptr) return 0;

		SingleNode * p = list;
		size_t m = 0;
		SingleNode * q = list;
		size_t n = 0;
		while (q->Next() != nullptr && q->Next()->Next() != nullptr) {
			p = p->Next();
			m++;
			q = q->Next()->Next();
			n += 2;
			if (p == q) break;
		}

		if (q->Next() == nullptr) return n + 1;
		if (q->Next()->Next() == nullptr) return n + 2;

		// Multiple of cycle length
		m = n - m;

		p = list;
		q = list;
		for (size_t i = 0; i < m - 1; i++) {
			q = q->Next();
		}

		n = 0;
		while (p != q->Next()) {
			p = p->Next();
			q = q->Next();
			n++;
		}

		while (p != q) {
			p = p->Next();
			n++;
		}

		return n + 1;
	}

	template<class T> SingleNode<T> * SingleNode<T>::Middle(void)
	{
		return Middle(this);
	}

	template<class T> SingleNode<T> * SingleNode<T>::Middle(SingleNode * list)
	{
		if (list == nullptr) return nullptr;

		SingleNode * t = Tail(list);
		if (t == nullptr) return nullptr;

		// Start from the first (1-th) node.
		SingleNode * middle = list;
		SingleNode * p = list;

		while (p != t && p->Next() != t) {
			// p visits the (2n-1)-th node.
			p = p->Next()->Next();
			// middle visits the n-th node.
			middle = middle->Next();
		}

		return middle;
	}

	template<class T> SingleNode<T> * SingleNode<T>::Reverse(SingleNode * list)
	{
		if (list == nullptr || list->Next() == nullptr) return list;
		SingleNode * t = Tail(list);
		if (t == nullptr) return list;

		SingleNode * p = list;
		SingleNode * m = list->Next();
		SingleNode * n = m->Next();
		while (m != t) {
			m->Next() = p;
			p = m;
			m = n;
			n = n->Next();
		}
		m->Next() = p;
		list->Next() = n == list ? m : nullptr;
		return m;
	}

	template<class T> SingleNode<T> * SingleNode<T>::Reverse(void)
	{
		return Reverse(this);
	}

	// Reorder single-link list
	// (1)  0 -> 1 -> 2 -> ...... -> n-1 -> n -> n+1 -> ...... 2n-1 -> nullptr
	//      0 -> 2n-1 -> 1 -> 2n-2 -> 2 -> ...... -> n-2 -> n+1 -> n-1 -> n -> nullptr
	// (2)  0 -> 1 -> 2 -> ...... -> n-1 -> n -> n+1 -> ...... 2n-1 -> 2n nullptr
	//      0 -> 2n -> 1 -> 2n-1 -> 2 -> ...... -> n+2 -> n-1 -> n+1 -> n -> nullptr
	template<class T> void SingleNode<T>::Reorder(SingleNode * node)
	{
		if (node == nullptr) return;

		// Find the middle node
		SingleNode * m = node;
		SingleNode * p = node;
		while (p->Next() != nullptr && p->Next()->Next() != nullptr) {
			m = m->Next();
			p = p->Next()->Next();
		}

		if (m == node) {
			// Only one node or two nodes
			return;
		}

		// m's index is (n-1) or n, depending on whether the list has 2n or 2n+1 nodes

		// Break the list at the middle
		SingleNode * second = m->Next();
		m->Next() = nullptr;

		// Reverse the second half of list
		if (second->Next() != nullptr) {
			p = second;
			m = p->Next();
			SingleNode * q = m->Next();
			p->Next() = nullptr;
			while (m != nullptr && q != nullptr) {
				m->Next() = p;
				p = m;
				m = q;
				q = m->Next();
			}
			m->Next() = p;
			second = m;
		}

		// Merge two lists
		m = node;
		while (second != nullptr) {
			 p = second;
			 second = p->Next();
			 p->Next() = m->Next();
			 m->Next() = p;
			 m = p->Next();
		}
	}

	template<class T> SingleNode<T> * SingleNode<T>::Tail(SingleNode * list)
	{
		if (list == nullptr) return nullptr;

		SingleNode * p = list;
		size_t m = 0;
		SingleNode * q = list;
		size_t n = 0;
		while (q->Next() != nullptr && q->Next()->Next() != nullptr) {
			p = p->Next();
			m++;
			q = q->Next()->Next();
			n += 2;
			if (p == q) break;
		}

		if (q->Next() == nullptr) return q;
		if (q->Next()->Next() == nullptr) return q->Next();

		// Multiple of cycle length
		m = n - m;

		p = list;
		q = list;
		for (size_t i = 0; i < m - 1; i++) {
			q = q->Next();
		}

		while (p != q->Next()) {
			p = p->Next();
			q = q->Next();
		}

		return q;
	}

	template<class T> SingleNode<T> * SingleNode<T>::RandomList(size_t length)
	{
		if (length == 0) return nullptr;
		SingleNode<T> * list = new SingleNode<T>(rand());
		SingleNode<T> * p = list;
		for (size_t i = 1; i < length; i++) {
			p->Next() = new SingleNode<T>(rand());
			p = p->Next();
		}
		return list;
	}

	template<class T> ostream & operator<<(ostream & os, SingleNode<T> * list)
	{
		os << "head";
		if (list == nullptr) {
			os << "->nullptr" << endl;
			return os;
		}

		SingleNode<T> * c = SingleNode<T>::FindCycle(list);
		SingleNode<T> * p = list;
		string s;
		int i = 4;
		while (p != c) {
			s = to_string(p->Value());
			os << "->" << s;
			i = i + 2 + s.length();
			p = p->Next();
		}

		if (p == nullptr) {
			os << "->nullptr" << endl;
			return os;
		}

		int j = i;
		do {
			s = to_string(p->Value());
			os << "->" << s;
			j = j + 2 + s.length();
			p = p->Next();
		} while (p != c);

		auto printChar = [&](int n, char c) {
			string chars(n, c);
			os << chars;
		};

		os << "-|" << endl;
		j++;
		printChar(i+1, ' ');
		os << "|";
		printChar(j-i-2, '_');
		os << "|" << endl;
		return os;
	}
}