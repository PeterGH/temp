#pragma once

#include "SingleLinkList.h"

namespace Test {
	
	template<class T> class CircularSingleLinkList : public SingleLinkList<T> {
		template<class T> friend ostream & operator<<(ostream &, const CircularSingleLinkList<T> &);
		template<class T> friend Log & operator<<(Log &, const CircularSingleLinkList<T> &);
	protected:
		Node * Search(const T & data) const;
	public:
		~CircularSingleLinkList(void);
		bool Contain(const T & data) const;
		void Delete(const T & data);
		// Insert data between head and head->next, then set head to the new node
		virtual void Insert(const T & data);
		const T & operator[](unsigned int index) const;
	};

	template<class T> CircularSingleLinkList<T>::~CircularSingleLinkList(void)
	{
		if (nullptr == head) return;
		Node * p = head;
		head = p->next;
		p->next = nullptr;
		SingleLinkList<T>::~SingleLinkList();
	}

	template<class T> typename SingleLinkList<T>::Node * CircularSingleLinkList<T>::Search(const T & data) const
	{
		if (nullptr == head) return nullptr;
		
		Node * p = head;
		while (p->data != data && p->next != head) {
			p = p->next;
		}

		if (p->data == data) return p;		
		else return nullptr;
	}

	template<class T> bool CircularSingleLinkList<T>::Contain(const T & data) const
	{
		return nullptr != Search(data);
	}

	template<class T> void CircularSingleLinkList<T>::Delete(const T & data)
	{
		if (nullptr == head) return;
		
		Node * p = head;
		if (p->next == head) {
			if (p->data == data) {
				delete p;
				head = nullptr;
			}

			return;
		}

		while (p->next != head && p->next->data != data) {
			p = p->next;
		}

		if (p->next->data == data) {
			Node * t = p->next;
			p->next = t->next;
			if (t == head) head = t->next;
			delete t;
		}
	}

	template<class T> void CircularSingleLinkList<T>::Insert(const T & data)
	{
		Node * node = new Node(data);
		if (nullptr == head) {
			head = node;
			head->next = head;
		} else {
			node->next = head->next;
			head->next = node;
			head = node;
		}
	}

	template<class T> const T & CircularSingleLinkList<T>::operator[](unsigned int index) const
	{
		if (nullptr == head) throw invalid_argument("List is empty");

		unsigned int i = 0;
		Node * p = head;
		while (i < index) {
			p = p->next;
			i++;
		}

		return p->data;
	}

	template<class T> ostream & operator<<(ostream & os, const CircularSingleLinkList<T> & list)
	{
		SingleLinkList<T>::Node * p = list.head;
		cout << "Head->";
		if (list.head == nullptr) {
			cout << "nullptr" << endl;
			return;
		}

		do {
			cout << p->data << "->";
			p = p->next;
		} while (p != list.head);

		cout << "Head" << endl;
		return os;
	}

	template<class T> Log & operator<<(Log & log, const CircularSingleLinkList<T> & list)
	{
		SingleLinkList<T>::Node * p = list.head;
		log.WriteInformation("Head->");
		if (list.head == nullptr) {
			log.WriteInformation("nullptr\n");
			return log;
		}

		do {
			log.WriteInformation("%d->", p->data);
			p = p->next;
		} while (p != list.head);

		log.WriteInformation("Head\n");
		return log;
	}
}