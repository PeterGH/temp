#pragma once

#include <iostream>
#include <sstream>
#include "Log.h"
#include "String.h"

using namespace std;

namespace Test {

	// Standard C++ Library contains a class bitset<N> to manipulate a set of bits.
	// The difference is bitset<N> requires N to be set explicitly during compile time 
	// while BitSet can be defined during runtime.
	// Like bitset, every method of BitSet manipulating a bit takes an input parameter representing a zero-based position.
	class BitSet {
		__declspec(dllexport) friend ostream & operator<<(ostream &, const BitSet &);
		__declspec(dllexport) friend Log & operator<<(Log &, const BitSet &);
	private:
		// Number of bits an integer can store
		static const int IntBits = 8 * sizeof(int); 
		
		// Number of bits managed by this class
		int _lenBit;
		
		// Length of int array to store bits
		int _lenInt;

		// Int array storing the managed bits
		int * _ints;

		// Logical shift to the left with a distance
		void LeftShiftInternal(size_t distance);

		// Given a zero-based bit position, calculate the index x of integer and the index y of bit in the integer.
		void Position(int position, int * x, int * y) const;
	public:
		// Create a BitSet object to manage bits upto maxBits.
		__declspec(dllexport) BitSet(int maxBits);
		__declspec(dllexport) BitSet(const BitSet & mask);
		__declspec(dllexport) ~BitSet(void);

		// Test if all bits are set
		__declspec(dllexport) bool All(void) const;

		// Test if any bit is set
		__declspec(dllexport) bool Any(void) const;

		// Count the bits have been set
		__declspec(dllexport) size_t Count(void) const;

		// Flip all bits
		__declspec(dllexport) void Flip(void);

		// Flip one bit position
		__declspec(dllexport) void Flip(size_t position);

		// Test if the bit set represent an integer of power of 2
		__declspec(dllexport) bool IsPower2(void);

		// Logical shift to the left with a distance
		__declspec(dllexport) void LeftShift(size_t distance);

		// Reset all bits to zero
		__declspec(dllexport) void Reset(void);

		// Reset one bit position to zero
		__declspec(dllexport) void Reset(size_t position);

		// Reverse bits of an unsigned integer
		__declspec(dllexport) static void Reverse(unsigned int & bits);

		// Reverse bits
		__declspec(dllexport) void Reverse(void);

		// Set all bits to one
		__declspec(dllexport) void Set(void);

		// Set one bit position to one
		__declspec(dllexport) void Set(size_t position);

		// Test if one bit position is set
		__declspec(dllexport) bool Test(size_t position) const;

		__declspec(dllexport) string ToString(void);
	};
}

