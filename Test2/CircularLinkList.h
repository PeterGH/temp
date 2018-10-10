#include <iostream>
#include "String.h"
using namespace std;
namespace My {

	// Sorted elements linked into a circular list
	template<class T> class CircularLinkList {
	private:
		class Node {
		public:
			T data;
			Node * next;
			Node(const T & d, Node * n) : data(d), next(n) {}
			Node(const T & d) : data(d), next(nullptr) {}
			~Node(void) { next = nullptr; }
		} * head;
	public:
		CircularLinkList(void) : head(nullptr) {}
		~CircularLinkList(void);
		void Insert(const T & data);
		void Print(void) const;
	};

	template<class T> CircularLinkList<T>::~CircularLinkList(void)
	{
		if (this->head == nullptr) return;

		Node * p = this->head->next;
		while (p != this->head) {
			this->head->next = p->next;
			p->next = nullptr;
			delete p;
			p = this->head->next;
		}

		this->head->next = nullptr;
		delete this->head;
		this->head = nullptr;
	}

	template<class T> void CircularLinkList<T>::Insert(const T & data)
	{
		Node * newNode = new Node(data);

		if (this->head == nullptr) {
			this->head = newNode;
			newNode->next = this->head;
		} else {
			Node * p = this->head;
			Node * q = this->head->next;
			
			do {
				if (p->data <= newNode->data && newNode->data <= q->data) {
					// Case: p->data < q->data, and newNode is in between 
					// Case: p->data == q->data, and newNode is the same
					// Insert
					p->next = newNode;
					newNode->next = q;
					this->head = newNode;
					return;
				} else if (p->data > q->data && (p->data <= newNode->data || newNode->data <= q->data)) {
					// Case: p->data > q->data, and newNode is in between
					// Insert
					p->next = newNode;
					newNode->next = q;
					this->head = newNode;
					return;
				} else {
					p = q;
					q = p->next;
				}
			} while (p != this->head);

			// Now we know all nodes are equal
			// Case: p->data == q->data, and newNode is different from all nodes
			// Insert between p and q
			p->next = newNode;
			newNode->next = q;
			this->head = newNode;
		}
	}

	template<class T> void CircularLinkList<T>::Print(void) const
	{
		if (this->head == nullptr) return;

		Node * p = this->head;
		cout << "Head->";
		do {
			cout << p->data << "->";
			p = p->next;
		} while (p != this->head);

		cout << "Head" << endl;
	}
}