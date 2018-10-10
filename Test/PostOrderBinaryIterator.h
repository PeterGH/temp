#pragma once
#include "BinaryIterator.h"
#include <stack>
using namespace std;
namespace Test {
	template<class T, template<class T> class N> class PostOrderBinaryIterator : public BinaryIterator<T, N> {
	private:
		stack<N<T> *> path;
		N<T> * current;
		N<T> * prev;
	public:
		PostOrderBinaryIterator(N<T> * p) : BinaryIterator(p), current(p), prev(nullptr)
		{
			this->operator++();
		}

		PostOrderBinaryIterator(const PostOrderBinaryIterator & it) : BinaryIterator(it), current(it.pointer), prev(nullptr)
		{
			this->operator++();
		}

		PostOrderBinaryIterator(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			if (this->path.empty() && this->current == nullptr) {
				this->pointer = nullptr;
			}

			while (!this->path.empty() || this->current != nullptr) {
				if (this->current != nullptr) {
					this->path.push(this->current);
					this->current = (N<T>*)this->current->Left();
				} else {
					if (this->path.top()->Right() != nullptr && this->path.top()->Right() != this->prev) {
						this->current = (N<T>*)this->path.top()->Right();
					} else {
						this->pointer = this->path.top();
						this->path.pop();
						this->prev = this->pointer;
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