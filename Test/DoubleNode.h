#pragma once
#include "Node.h"
namespace Test {
	template<class T> class DoubleNode : public Node<T> {
		template<class T> friend ostream & operator<<(ostream &, DoubleNode<T> *);
	public:
		DoubleNode(const T & v) : Node<T>(v, 2) {}
		virtual ~DoubleNode(void) {}

		// Get the reference of previous node pointer
		DoubleNode * & Prev(void) { return (DoubleNode * &)this->Neighbor(0); }
		// Set the previous node pointer
		void Prev(DoubleNode * prev) { this->Neighbor(0) = prev; }

		// Get the reference of next node pointer
		DoubleNode * & Next(void) { return (DoubleNode * &)this->Neighbor(1); }
		// Set the next node pointer
		void Next(DoubleNode * next) { this->Neighbor(1) = next; }

		// Delete a double link list. The list may be a cycle or not.
		static void DeleteList(DoubleNode * node);
	};

	template<class T> void DoubleNode<T>::DeleteList(DoubleNode * node)
	{
		if (node == nullptr) return;
		DoubleNode * p;
		while (node->Next() != nullptr && node->Next() != node) {
			p = node->Next();
			node->Next() = p->Next();
			if (p->Next() != nullptr) p->Next()->Prev() = node;
			delete p;
			p = nullptr;
		}
		delete node;
		node = nullptr;
	}

	template<class T> ostream & operator<<(ostream & os, DoubleNode<T> * list)
	{
		os << "head";
		if (list == nullptr) {
			os << "->nullptr" << endl;
			return os;
		}

		DoubleNode<T> * p = list;
		string s;
		int i = 4;
		do {
			s = to_string(p->Value());
			os << "->" << s;
			i = i + 2 + s.length();
			p = p->Next();
		} while (p != nullptr && p != list);

		if (p == nullptr) {
			os << "->nullptr" << endl;
			return os;
		}

		auto printChar = [&](int n, char c) {
			string chars(n, c);
			os << chars;
		};

		os << "-|" << endl;
		printChar(5, ' ');
		os << "|";
		printChar(i-5, '_');
		os << "|" << endl;
		return os;
	}
}