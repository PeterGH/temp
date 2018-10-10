#pragma once
#include "Node.h"
namespace Test {
	template<class T> class Node1 : public Node<T> {
	protected:
		Node * first;
	public:
		Node1(const T & v) : Node(v), first(nullptr) {}

		virtual ~Node1(void)
		{
			if (this->first != nullptr) {
				this->first = nullptr;
			}
		}

		virtual Node1 * Search(const T & v);
		virtual bool Contain(const T & v) { return nullptr != Search(v); }
	};

	template<class T> Node1<T> * Node1<T>::Search(const T & v)
	{
		Node1 * p = this;
		while (nullptr != p && p->value != v) {
			p = (Node1 *)p->first;
		}

		// p == nullptr || p->value == v
		return p;
	}
}