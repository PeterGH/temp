#pragma once
#include "String.h"
using namespace std;
namespace Test {
	template<class T, template<class T> class N> class BinaryIterator {
	protected:
		N<T> * pointer;

		void Check(void) const
		{
			if (this->pointer == nullptr)
			{
				throw invalid_argument(
					String::Format("BinaryIterator<%s, %s>::iterator is not initialized", typeid(T).name(), typeid(N).name()));
			}
		}

	public:
		BinaryIterator(N<T> * p) : pointer(p) {}
		BinaryIterator(const BinaryIterator & it) : pointer(it.pointer) {}
		BinaryIterator(void) : pointer(nullptr) {}

		// Get the value of current node
		const T & Current() const
		{
			Check();
			T & d = this->pointer->Value();
			return d;
		}

		// Return a pointer so that dereference is on the return type
		const N<T> * operator->() { Check(); return this->pointer; }

		const T & operator*() const { return Current(); }

		// Note: There is no return value
		// This allows to check if an iterator is valid by using
		//     if (it) { } else { }
		operator bool() const { return this->pointer != nullptr; }

		bool operator==(const BinaryIterator & it) const { return this->pointer == it.pointer; }
		bool operator!=(const BinaryIterator & it) const { return this->pointer != it.pointer; }

		// Prefix increment
		// ++ it
		virtual bool operator++() { return false; }

		// Postfix increment
		// it ++
		virtual bool operator++(int) { return false; }
	};
}