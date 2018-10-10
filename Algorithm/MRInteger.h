#pragma once

#include <stdexcept>
#include "String.h"

using namespace std;

namespace Test {
	// Multi-Radix Integer
	// Digits:
	//    d_{n-1} d_{n-2} ...... d_i ...... d_2 d_1 d_0
	// Bases:
	//    b_{n-1} b_{n-2} ...... b_i ...... b_2 b_1 b_0
	// 0 <= d_i < b_i
	class MRInteger {
	private:
		unsigned int * _bases;
		// 0 <= _digits[i] < _bases[i]
		unsigned int * _digits;
		// Number of digits
		unsigned int _length;
		// maximum number of integers can be represented
		unsigned long _max;
		// position: n-1, n-2, ..., 3, 2, 1, 0
		// Add one to the sub MRInteger containing digits from position to 0.
		// Return 1 if need to increase the digit at position+1 by 1,
		// and 0 otherwise.
		unsigned int AddOne(unsigned int position)
		{
			if (0 == position) {
				_digits[position] = (1 + _digits[position]) % _bases[position];
				return (0 == _digits[position]) ? 1 : 0;
			} else {
				if (1 == AddOne(position - 1)) {
					_digits[position] = (1 + _digits[position]) % _bases[position];
					return (0 == _digits[position]) ? 1 : 0;
				} else {
					return 0;
				}
			}
		}

	public:
		__declspec(dllexport) MRInteger(const unsigned int * bases, unsigned int length)
			: _bases(nullptr), _digits(nullptr), _length(0), _max(0)
		{
			if (bases == nullptr) throw invalid_argument("bases is nullptr");
			if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
			for (unsigned int i = 0; i < length; i++) {
				if (bases[i] <= 0) {
					throw invalid_argument(String::Format("bases[%d] %d is invalid", i, bases[i]));
				}
			}

			_bases = new unsigned int[length];
			_digits = new unsigned int[length];
			_length = length;
			_max = 1;
			for (unsigned int i = 0; i < length; i++) {
				_bases[i] = bases[i];
				_digits[i] = 0;
				_max = _max * bases[i];
			}
		}

		__declspec(dllexport) MRInteger(const unsigned int * bases, const unsigned int * digits, unsigned int length)
			: _bases(nullptr), _digits(nullptr), _length(0), _max(0)
		{
			if (bases == nullptr) throw invalid_argument("bases is nullptr");
			if (digits == nullptr) throw invalid_argument("digits is nullptr");
			if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
			for (unsigned int i = 0; i < length; i++) {
				if (bases[i] <= 0) {
					throw invalid_argument(String::Format("bases[%d] %d is invalid", i, bases[i]));
				}
			}

			_bases = new unsigned int[length];
			_digits = new unsigned int[length];
			_length = length;
			_max = 1;
			for (unsigned int i = 0; i < length; i++) {
				_bases[i] = bases[i];
				_digits[i] = digits[i] % _bases[i];
				_max = _max * bases[i];
			}
		}

		// Copy constructor
		__declspec(dllexport) MRInteger(const MRInteger & mrint)
			: _bases(nullptr), _digits(nullptr), _length(0), _max(0)
		{
			if (_bases != nullptr) {
				delete[] _bases;
				_bases = nullptr;
			}

			if (_digits != nullptr) {
				delete[] _digits;
				_digits = nullptr;
			}

			_bases = new unsigned int[mrint._length];
			_digits = new unsigned int[mrint._length];
			_length = mrint._length;
			_max = mrint._max;
			for (unsigned int i = 0; i < _length; i++) {
				_bases[i] = mrint._bases[i];
				_digits[i] = mrint._digits[i];
			}
		}

		// Move constructor
		__declspec(dllexport) MRInteger(MRInteger && mrint)
			: _bases(nullptr), _digits(nullptr), _length(0), _max(0)
		{
			_bases = mrint._bases;
			mrint._bases = nullptr;
			_digits = mrint._digits;
			mrint._digits = nullptr;
			_length = mrint._length;
			mrint._length = 0;
			_max = mrint._max;
			mrint._max = 0;
		}

		__declspec(dllexport) ~MRInteger(void)
		{
			if (_bases != nullptr) {
				delete[] _bases;
				_bases = nullptr;
			}

			if (_digits != nullptr) {
				delete[] _digits;
				_digits = nullptr;
			}

			_length = 0;
			_max = 0;
		}

		// Set this MRInteger using the given digits array.
		__declspec(dllexport) void Set(const unsigned int * digits, unsigned int length)
		{
			// The number of elements to use from the digits array
			// is the minimum of the length and the MRInteger length.
			unsigned int l = length < this->_length ? length : this->_length;

			for (unsigned int i = 0; i < l; i++) {
				_digits[i] = digits[i] % _bases[i];
			}

			for (unsigned int i = l; i < this->_length; i++) {
				_digits[i] = 0;
			}
		}

		__declspec(dllexport) void Reset(void)
		{
			for (unsigned int i = 0; i < _length; i++) {
				_digits[i] = 0;
			}
		}

		// Copy asignment
		__declspec(dllexport) const MRInteger & operator=(const MRInteger & mrint)
		{
			if (this != &mrint) {
				delete[] _bases;
				_bases = new unsigned int[mrint._length];
				delete[] _digits;
				_digits = new unsigned int[mrint._length];
				_length = mrint._length;
				_max = mrint._max;
				for (unsigned int i = 0; i < _length; i++) {
					_bases[i] = mrint._bases[i];
					_digits[i] = mrint._digits[i];
				}
			}

			return *this;
		}

		// Move assignment
		__declspec(dllexport) const MRInteger & operator=(MRInteger && mrint)
		{
			if (this != &mrint) {
				delete[] _bases;
				_bases = mrint._bases;
				mrint._bases = nullptr;
				delete[] _digits;
				_digits = mrint._digits;
				mrint._digits = nullptr;
				_length = mrint._length;
				mrint._length = 0;
				_max = mrint._max;
				mrint._max = 0;
			}

			return *this;
		}

		// ++ MRInteger
		__declspec(dllexport) const MRInteger & operator++(void)
		{
			AddOne(_length - 1);
			return *this;
		}

		// MRInteger ++
		__declspec(dllexport) const MRInteger operator++(int)
		{
			MRInteger mrint(*this);
			++ *this;
			return mrint;
		}

		__declspec(dllexport) bool operator==(const MRInteger & mrint) const
		{
			int minLength = (int)this->_length;
			if (this->_length > mrint._length) {
				minLength = mrint._length;
				for (int i = (int)this->_length - 1; i >= (int)mrint._length; i--) {
					if (this->_digits[i] != 0) {
						// this has more digits and one of them is not zero
						return false;
					}
				}
			} else if (this->_length < mrint._length) {
				for (int i = (int)mrint._length - 1; i >= (int)this->_length; i--) {
					if (mrint._digits[i] != 0) {
						// mrint has more digits and one of them is not zero
						return false;
					}
				}
			}

			// Now this and mrint either have the same length,
			// or have different lengh but the extra digits are zeros.
			for (int i = minLength - 1; i >= 0; i--) {
				if (this->_digits[i] != mrint._digits[i]) {
					// this != mrint
					return false;
				}
			}

			return true;
		}

		__declspec(dllexport) bool operator!=(const MRInteger & mrint) const { return !((*this) == mrint); }

		__declspec(dllexport) bool operator<(const MRInteger & mrint) const
		{
			int minLength = (int)this->_length;
			if (this->_length > mrint._length) {
				minLength = mrint._length;
				for (int i = (int)this->_length - 1; i >= (int)mrint._length; i--) {
					if (this->_digits[i] > 0) {
						// this has more digits and one of them is greater than zero
						return false;
					}
				}
			} else if (this->_length < mrint._length) {
				for (int i = (int)mrint._length - 1; i >= (int)this->_length; i--) {
					if (mrint._digits[i] > 0) {
						// mrint has more digits and one of them is greater than zero
						return true;
					}
				}
			}

			for (int i = minLength - 1; i >= 0; i--) {
				if (this->_digits[i] > mrint._digits[i]) {
					// this > mrint
					return false;
				} else if (this->_digits[i] < mrint._digits[i]) {
					// this < mrint
					return true;
				}
			}

			// this == mrint
			return false;
		}

		__declspec(dllexport) bool operator>=(const MRInteger & mrint) const { return !((*this) < mrint); }

		__declspec(dllexport) bool operator>(const MRInteger & mrint) const
		{
			int minLength = (int)this->_length;
			if (this->_length > mrint._length) {
				minLength = mrint._length;
				for (int i = (int)this->_length - 1; i >= (int)mrint._length; i--) {
					if (this->_digits[i] > 0) {
						// this has more digits and one of them is greater than zero
						return true;
					}
				}
			} else if (this->_length < mrint._length) {
				for (int i = (int)mrint._length - 1; i >= (int)this->_length; i--) {
					if (mrint._digits[i] > 0) {
						// mrint has more digits and one of them is greater than zero
						return false;
					}
				}
			}

			for (int i = minLength - 1; i >= 0; i--) {
				if (this->_digits[i] < mrint._digits[i]) {
					// this < mrint
					return false;
				} else if (this->_digits[i] > mrint._digits[i]) {
					// this > mrint
					return true;
				}
			}

			// this == mrint
			return false;
		}

		__declspec(dllexport) bool operator<=(const MRInteger & mrint) const { return !((*this) > mrint); }

		// maximum number of integers can be represented
		__declspec(dllexport) const unsigned long Max(void) const { return _max; }

		__declspec(dllexport) const unsigned int Length(void) const { return _length; }

		__declspec(dllexport) const unsigned int operator[](unsigned int index) const
		{
			return _digits[index];
		}

		__declspec(dllexport) void Random(void)
		{
			for (unsigned int i = 0; i < this->_length; i++) {
				this->_digits[i] = rand() % this->_bases[i];
			}
		}
	};
}