#pragma once

#include "BinarySearch.h"
#include "SingleNode.h"

namespace Test {
	class __declspec(dllexport) InsertionSort {
	public:
		template<class T> static void Sort(SingleNode<T> * & list);
	};

	// Sort a single link list or a circular list
	template<class T> void InsertionSort::Sort(SingleNode<T> * & list)
	{
		if (list == nullptr || list->Next() == nullptr || list->Next() == list) return;

		bool circular = false;
		SingleNode<T> * e = list;
		while (e->Next() != nullptr && e->Next() != list) {
			e = e->Next();
		}
		if (e->Next() == list) circular = true;

		SingleNode<T> * q = list;
		while (q->Next() != nullptr && q->Next() != list) {
			if (q->Next()->Value() < list->Value()) {
				SingleNode<T> * t = q->Next();
				if (circular) {
					if (t->Next() != list) {
						q->Next() = t->Next();
						t->Next() = list;
						e->Next() = t;
					}
				} else {
					q->Next() = t->Next();
					t->Next() = list;
				}
				list = t;
			} else {
				SingleNode<T> * p = list;
				while (p != q && q->Next()->Value() >= p->Next()->Value()) {
					p = p->Next();
				}
				if (p == q) {
					q = q->Next();
				} else {
					SingleNode<T> * t = q->Next();
					q->Next() = t->Next();
					t->Next() = p->Next();
					p->Next() = t;
				}
			}
		}
	}
}