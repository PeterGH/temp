#pragma once
#include "BinaryIterator.h"
#include "BinaryNodeWithParent.h"
using namespace std;
namespace Test {
	template<class T> class InOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent> {
	private:
		BinaryNodeWithParent<T> * current;
		BinaryNodeWithParent<T> * prev;
	public:
		InOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> * p) : BinaryIterator(p), current(p), prev(p)
		{
			this->operator++();
		}

		InOrderBinaryIteratorWithOutStack(const InOrderBinaryIteratorWithOutStack & it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
		{
			this->operator++();
		}

		InOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			while (this->current != nullptr) {
				if (this->prev == this->current->Right()) {
					this->prev = this->current;
					this->current = this->current->Parent();
				} else if (this->current->Left() != nullptr && this->prev != this->current->Left()) {
					this->prev = this->current;
					this->current = (BinaryNodeWithParent<T> *)this->current->Left();
				} else {
					this->pointer = this->current;
					this->prev = this->current;
					if (this->current->Right() != nullptr) {
						this->current = (BinaryNodeWithParent<T> *)this->current->Right();
					} else {
						this->current = this->current->Parent();
					}

					break;
				}
			}

			if (this->current == nullptr) {
				this->pointer = nullptr;
			}

			return this->pointer != nullptr;
		}

		// Postfix increment
		// it ++
		bool operator++(int) { return operator++(); }
	};
}