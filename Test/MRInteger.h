#pragma once

#include "Random.h"

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
		unsigned int AddOne(unsigned int position);
	public:
		__declspec(dllexport) MRInteger(const unsigned int * bases, unsigned int length);
		__declspec(dllexport) MRInteger(const unsigned int * bases, const unsigned int * digits, unsigned int length);
		// Copy constructor
		__declspec(dllexport) MRInteger(const MRInteger & mrint);
		// Move constructor
		__declspec(dllexport) MRInteger(MRInteger && mrint);
		__declspec(dllexport) ~MRInteger(void);
		// Set this MRInteger using the given digits array.
		__declspec(dllexport) void Set(const unsigned int * digits, unsigned int length);
		__declspec(dllexport) void Reset(void);
		// Copy asignment
		__declspec(dllexport) const MRInteger & operator=(const MRInteger & mrint);
		// Move assignment
		__declspec(dllexport) const MRInteger & operator=(MRInteger && mrint);
		// ++ MRInteger
		__declspec(dllexport) const MRInteger & operator++(void);
		// MRInteger ++
		__declspec(dllexport) const MRInteger operator++(int);
		__declspec(dllexport) bool operator==(const MRInteger & mrint) const;
		__declspec(dllexport) bool operator!=(const MRInteger & mrint) const { return !((*this) == mrint); }
		__declspec(dllexport) bool operator<(const MRInteger & mrint) const;
		__declspec(dllexport) bool operator>=(const MRInteger & mrint) const { return !((*this) < mrint); }
		__declspec(dllexport) bool operator>(const MRInteger & mrint) const;
		__declspec(dllexport) bool operator<=(const MRInteger & mrint) const { return !((*this) > mrint); }
		// maximum number of integers can be represented
		__declspec(dllexport) const unsigned long Max(void) const { return _max; }
		__declspec(dllexport) const unsigned int Length(void) const { return _length; }
		__declspec(dllexport) const unsigned int operator[](unsigned int) const;
		__declspec(dllexport) void Random(void);
	};
}

