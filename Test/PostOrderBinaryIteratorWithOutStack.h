#pragma once
#include "BinaryIterator.h"
#include "BinaryNodeWithParent.h"
using namespace std;
namespace Test {
	template<class T> class PostOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent> {
	private:
		BinaryNodeWithParent<T> * current;
		BinaryNodeWithParent<T> * prev;
	public:
		PostOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> * p) : BinaryIterator(p), current(p), prev(p)
		{
			this->operator++();
		}

		PostOrderBinaryIteratorWithOutStack(const PostOrderBinaryIteratorWithOutStack & it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
		{
			this->operator++();
		}

		PostOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			if (this->current == nullptr) {
				this->pointer = nullptr;
			}

			while (this->current != nullptr) {
				if (this->prev == this->current->Right()) {
					this->pointer = this->current;
					this->prev = this->current;
					this->current = this->current->Parent();
					break;
				} else if (this->current->Left() != nullptr && this->prev != this->current->Left()) {
					this->prev = this->current;
					this->current = (BinaryNodeWithParent<T> *)this->current->Left();
				} else {
					this->prev = this->current;
					if (this->current->Right() != nullptr) {
						this->current = (BinaryNodeWithParent<T> *)this->current->Right();
					} else {
						this->pointer = this->current;
						this->current = this->current->Parent();
						break;
					}
				}
			}

			return this->pointer != nullptr;
		}

		// Postfix increment
		// it ++
		bool operator++(int) { return operator++(); }
	};
}