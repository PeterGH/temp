#pragma once

#include <ppl.h>
#include "Heap.h"
#include "SingleNode.h"

using namespace concurrency;

namespace Test {
	class _declspec(dllexport) MergeSort {
	public:
		template<class T> static void Merge(SingleNode<T> * & first, SingleNode<T> * second);

		template<class T> static void Sort(SingleNode<T> * & list);
	};

	// Merge two sorted single link lists
	template<class T> void MergeSort::Merge(SingleNode<T> * & first, SingleNode<T> * second)
	{
		if (second == nullptr) return;

		if (first == nullptr) {
			first = second;
			return;
		}

		SingleNode<T> * p;
		if (second->Value() < first->Value()) {
			p = second->Next();
			second->Next() = first;
			first = second;
			second = p;
		}

		// Now first->Value() <= second->Value()

		p = first;
		while (p != nullptr && second != nullptr) {
			while (p->Next() != nullptr && p->Next()->Value() <= second->Value()) {
				p = p->Next();
			}

			// Now p->Value() <= second->Value()

			if (p->Next() == nullptr) {
				// first list is done, append rest of second to first
				p->Next() = second;
				break;
			} else {
				// Insert second between p and p->Next()
				SingleNode<T> * q = second->Next();
				second->Next() = p->Next();
				p->Next() = second;
				p = second;
				second = q;
			}
		}
	}

	// Sort a single link list or a circular list
	template<class T> void MergeSort::Sort(SingleNode<T> * & list)
	{
		if (list == nullptr || list->Next() == nullptr || list->Next() == list) return;

		SingleNode<T> * m = list;
		SingleNode<T> * p = list;

		while (p->Next() != nullptr && p->Next() != list
			&& p->Next()->Next() != nullptr && p->Next()->Next() != list) {
			// p visits the (2n-1)-th node.
			p = p->Next()->Next();
			// middle visits the n-th node.
			m = m->Next();
		}

		bool circular = false;
		if (p->Next() == list) {
			circular = true;
			p->Next() = nullptr;
		} else if (p->Next() != nullptr && p->Next()->Next() == list) {
			circular = true;
			p->Next()->Next() = nullptr;
		}

		SingleNode<T> * second = m->Next();
		m->Next() = nullptr;
		Sort(list);
		Sort(second);
		Merge(list, second);

		if (circular) {
			p = list;
			while (p->Next() != nullptr) {
				p = p->Next();
			}
			p->Next() = list;
		}
	}
}