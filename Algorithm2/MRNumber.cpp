#include "MRNumber.h"
#include <stdlib.h>
#include <time.h>

namespace My
{

	MRNumber::MRNumber(const int * bases, int length)
	{
		_bases = new int[length];
		_digits = new int[length];
		_length = length;
		_max = 1;
		for (int i = 0; i < length; i ++) {
			_bases[i] = bases[i];
			_digits[i] = 0;
			_max = _max * bases[i];
		}
		// Seed the random-number generator with the current time so that
		// the numbers will be different every time we run.
		srand((unsigned)time(NULL));
	}

	MRNumber::MRNumber(const MRNumber & mrnumber)
	{
		_bases = new int[mrnumber._length];
		_digits = new int[mrnumber._length];
		_length = mrnumber._length;
		_max = mrnumber._max;
		for (int i = 0; i < _length; i ++) {
			_bases[i] = mrnumber._bases[i];
			_digits[i] = mrnumber._digits[i];		
		}
		// Seed the random-number generator with the current time so that
		// the numbers will be different every time we run.
		srand((unsigned)time(NULL));
	}

	MRNumber::~MRNumber(void)
	{
		delete _bases;
		_bases = 0;
		delete _digits;
		_digits = 0;
		_length = 0;
		_max = 0;
	}

	// position: n-1, n-2, ..., 3, 2, 1, 0
	// Add one to the sub MRNumber containing digits from position to 0.
	// Return 1 if need to increase the digit at position+1 by 1,
	// and 0 otherwise.
	int MRNumber::AddOne(int position)
	{
		if (0 == position) {
			_digits[position] = (1 + _digits[position]) % _bases[position];
			return (0 == _digits[position]) ? 1 : 0;
		} else {
			if ( 1 == AddOne(position - 1) ) {
				_digits[position] = (1 + _digits[position]) % _bases[position];
				return (0 == _digits[position]) ? 1 : 0;
			} else {
				return 0;
			}
		}
	}

	void MRNumber::Reset(void)
	{
		for (int i = 0; i < _length; i ++) {
			_digits[i] = 0;
		}
	}

	// ++ MRNumber
	const MRNumber & MRNumber::operator ++(void) 
	{
		AddOne(_length - 1);
		return *this;
	}

	// MRNumber ++
	const MRNumber MRNumber::operator ++(int) 
	{
		MRNumber mrnumber(*this);
		++ *this;
		return mrnumber;
	}

	const int MRNumber::operator [](int index) const
	{
		return _digits[index];
	}

	void MRNumber::Random(void)
	{
		for (int i = 0; i < _length; i ++) {
			// The rand function returns a pseudorandom integer in the range 0 to RAND_MAX (32767). 
			_digits[i] = _bases[i] * rand() >> 15;
		}
	}

	ostream & operator<<(ostream & os, const MRNumber & mrnumber)
	{
		for (int i = mrnumber._length - 1; i >= 0; i --) {
			os << "\t" << mrnumber._digits[i];
		}
		os << endl;
		return os;
	}

}