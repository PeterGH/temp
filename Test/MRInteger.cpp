#include "MRInteger.h"

namespace Test {

	MRInteger::MRInteger(const unsigned int * bases, unsigned int length)
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

	MRInteger::MRInteger(const unsigned int * bases, const unsigned int * digits, unsigned int length)
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
	MRInteger::MRInteger(const MRInteger & mrint)
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
	MRInteger::MRInteger(MRInteger && mrint)
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

	MRInteger::~MRInteger(void)
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

	unsigned int MRInteger::AddOne(unsigned int position)
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

	void MRInteger::Set(const unsigned int * digits, unsigned int length)
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

	void MRInteger::Reset(void)
	{
		for (unsigned int i = 0; i < _length; i++) {
			_digits[i] = 0;
		}
	}

	const MRInteger & MRInteger::operator =(const MRInteger & mrint)
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

	const MRInteger & MRInteger::operator =(MRInteger && mrint)
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

	const MRInteger & MRInteger::operator ++(void)
	{
		AddOne(_length - 1);
		return *this;
	}

	const MRInteger MRInteger::operator ++(int)
	{
		MRInteger mrint(*this);
		++ *this;
		return mrint;
	}

	bool MRInteger::operator ==(const MRInteger & mrint) const
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

	bool MRInteger::operator <(const MRInteger & mrint) const
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

	bool MRInteger::operator >(const MRInteger & mrint) const
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

	const unsigned int MRInteger::operator [](unsigned int index) const
	{
		return _digits[index];
	}

	void MRInteger::Random(void)
	{
		for (unsigned int i = 0; i < this->_length; i++) {
			this->_digits[i] = Random::Next(this->_bases[i] - 1);
		}
	}
}