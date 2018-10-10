#pragma once

#include "SingleLinkList.h"

namespace Test {
	template<class T> class SortedSingleLinkList : public SingleLinkList<T> {
	public:
		void Insert(const T & data);
	};

	template<class T> void SortedSingleLinkList<T>::Insert(const T & data)
	{
		SingleLinkList<T>::Node * node = new SingleLinkList<T>::Node(data);
		if (nullptr == head) {
			head = node;
			return;
		}

		if (head->data > data) {
			node->next = head;
			head = node;
			return;
		}

		SingleLinkList<T>::Node * p = head;
		while (nullptr != p->next && p->next->data <= data) {
			p = p->next;
		}

		node->next = p->next;
		p->next = node;		
	}
}