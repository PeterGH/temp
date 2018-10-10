#pragma once
#include "BinaryIterator.h"
#include <stack>
using namespace std;
namespace Test {
	template<class T, template<class T> class N> class PreOrderBinaryIterator : public BinaryIterator<T, N> {
	private:
		stack<N<T> *> path;
		N<T> * current;
	public:
		PreOrderBinaryIterator(N<T> * p) : BinaryIterator(p), current(p)
		{
			this->operator++();
		}

		PreOrderBinaryIterator(const PreOrderBinaryIterator & it) : BinaryIterator(it), current(it.pointer)
		{
			this->operator++();
		}

		PreOrderBinaryIterator(void) : BinaryIterator(), current(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			while (!this->path.empty() || this->current != nullptr) {
				if (this->current != nullptr) {
					this->pointer = this->current;
					path.push(this->current);
					this->current = (N<T>*)this->current->Left();
					break;
				} else {
					this->current = (N<T>*)this->path.top()->Right();
					this->path.pop();
				}
			}

			if (this->path.empty() && this->current == nullptr) {
				this->pointer = nullptr;
			}

			return this->pointer != nullptr;
		}

		// Postfix increment
		// it ++
		bool operator++(int) { return operator++(); }
	};
}