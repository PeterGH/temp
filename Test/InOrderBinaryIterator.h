#pragma once
#include "BinaryIterator.h"
#include <stack>
using namespace std;
namespace Test {
	template<class T, template<class T> class N> class InOrderBinaryIterator : public BinaryIterator<T, N> {
	private:
		stack<N<T> *> path;
		N<T> * current;
	public:
		InOrderBinaryIterator(N<T> * p) : BinaryIterator(p), current(p)
		{
			this->operator++();
		}

		InOrderBinaryIterator(const InOrderBinaryIterator & it) : BinaryIterator(it), current(it.pointer)
		{
			this->operator++();
		}

		InOrderBinaryIterator(void) : BinaryIterator(), current(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			if (this->path.empty() && this->current == nullptr) {
				this->pointer = nullptr;
			}

			while (!this->path.empty() || this->current != nullptr) {
				if (this->current != nullptr) {
					path.push(this->current);
					this->current = (N<T>*)this->current->Left();
				} else {
					this->pointer = this->path.top();
					this->path.pop();
					this->current = (N<T>*)this->pointer->Right();
					break;
				}
			}

			return this->pointer != nullptr;
		}

		// Postfix increment
		// it ++
		bool operator++(int) { return operator++(); }
	};
}