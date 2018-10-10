#pragma once
#include "BinaryIterator.h"
#include "BinaryNodeWithParent.h"
using namespace std;
namespace Test {
	template<class T> class PreOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent> {
	private:
		BinaryNodeWithParent<T> * current;
		BinaryNodeWithParent<T> * prev;
	public:
		PreOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> * p) : BinaryIterator(p), current(p), prev(p)
		{
			this->operator++();
		}

		PreOrderBinaryIteratorWithOutStack(const PreOrderBinaryIteratorWithOutStack & it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
		{
			this->operator++();
		}

		PreOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			while (this->current != nullptr) {
				if (this->prev == this->current->Right()) {
					this->prev = this->current;
					this->current = this->current->Parent();
				} else if (this->current->Left() != nullptr && this->prev != this->current->Left()) {
					this->pointer = this->current;
					this->prev = this->current;
					this->current = (BinaryNodeWithParent<T> *)this->current->Left();
					break;
				} else {					
					if (this->current->Left() == nullptr) {
						this->pointer = this->current;
					}

					this->prev = this->current;
					if (this->current->Right() != nullptr) {
						this->current = (BinaryNodeWithParent<T> *)this->current->Right();
					} else {
						this->current = this->current->Parent();
					}

					if (this->pointer == this->prev) {
						break;
					}
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