#pragma once

#include <stdlib.h>
#include <string>

using namespace std;

namespace My {

	// Standard C++ Library contains a class bitset<N> to manipulate a set of bits.
	// The difference is bitset<N> requires N to be set explicitly during compile time 
	// while Mask can be defined during runtime.
	// Like bitset, every method of Mask manipulating a bit takes an input parameter representing a zero-based position.
	class Mask
	{
		__declspec(dllexport) friend ostream& operator<<(ostream &, const Mask &);

	public:
		__declspec(dllexport) Mask(int);
		__declspec(dllexport) Mask(const Mask &);
		__declspec(dllexport) ~Mask(void);

		__declspec(dllexport) void Reset(void);
		__declspec(dllexport) void Reset(size_t);
		__declspec(dllexport) void Set(void);
		__declspec(dllexport) void Set(size_t);
		__declspec(dllexport) void Flip(void);
		__declspec(dllexport) void Flip(size_t);
		
		__declspec(dllexport) bool All(void) const;
		__declspec(dllexport) bool Any(void) const;
		__declspec(dllexport) size_t Count(void) const;
		__declspec(dllexport) bool Test(size_t) const;

	private:
		void Position(int, int *, int *) const;

		// Number of bits managed by this class
		int _lenBit;
		// Int array storing the managed bits
		int * _mask;
		// Length of int array
		int _lenInt;
		// Number of bits an integer can store
		static const int IntBits = 8 * sizeof(int);
	};


}

