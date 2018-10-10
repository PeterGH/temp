#pragma once

#include "CircularSingleLinkList.h"

namespace Test {
	template<class T> class SortedCircularSingleLinkList : public CircularSingleLinkList<T> {
	public:
		// Insert data and update head to the smallest one
		void Insert(const T & data);
	};

	template<class T> void SortedCircularSingleLinkList<T>::Insert(const T & data)
	{
		SingleLinkList<T>::Node * node = new SingleLinkList<T>::Node(data);

		if (nullptr == head) {
			head = node;
			node->next = head;
			return;
		}
		
		Node * p = head;
		Node * q = head->next;
		
		do {
			if (p->data <= node->data && node->data < q->data) {
				// Case: p->data < q->data, and node is in between
				p->next = node;
				node->next = q;
				return;
			} 
			
			if (p->data > q->data && (p->data <= node->data || node->data <= q->data)) {
				// Case: p->data > q->data, and node is in between
				p->next = node;
				node->next = q;

				if (node->data <= q->data) {
					// node is the smallest one
					head = node;
				}

				return;
			} 
			
			p = q;
			q = p->next;
		} while (p != head);
		
		// Now we are back at head, and know all nodes are equal, 
		// because neither p->data < q->data or p->data > q->data has happened.
		// Case: p->data == q->data
		p->next = node;
		node->next = q;
		if (node->data < q->data) {
			head = node;
		} else if (node->data > q->data) {
			head = q;
		}
	}
}