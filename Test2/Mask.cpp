#include "Mask.h"
#include "String.h"

namespace My {

	Mask::Mask(int maxBits)
	{
		if (maxBits > 0) {
			_lenBit = maxBits;
			_lenInt = _lenBit / IntBits;
			int y = _lenBit % IntBits;
			if (y > 0)  _lenInt ++;
			_mask = new int[_lenInt];
			memset(_mask, 0, _lenInt * sizeof(int));
		} else {
			throw invalid_argument(String::Format("Invalid argument [%d]", maxBits));
		}
	}

	Mask::Mask(const Mask & mask)
	{
		_lenBit = mask._lenBit;
		_lenInt = mask._lenInt;
		_mask = new int[mask._lenInt];
		memcpy(_mask, mask._mask, mask._lenInt * sizeof(int));		
	}

	Mask::~Mask(void)
	{
		if (nullptr != _mask) {
			delete _mask;
			_mask = nullptr;
		}
	}

	// Assume n = sizeof(int), then the int array mask represents a bit map like:
	//     | 0 1 ... (n-1) | n (n+1) ... (2n-1) | 2n  ... (3n-1) | 3n ...
	// x = | 0             | 1                  | 2              | 3  ...
	// y = | 0 1 ... (n-1) | 0 1     ... (n-1)  | 0 1 ... (n-1)  | 0  ...
	// position = x*n + y
	void Mask::Position(int position, int * x, int * y) const
	{
		if (position < 0 || position >=_lenBit) throw invalid_argument(String::Format("Invalid bit position [%d]", position));
		*x = position / IntBits;
		*y = position % IntBits;	
	}

	void Mask::Reset(void)
	{
		 memset(_mask, 0, _lenInt * sizeof(int));
	}

	void Mask::Reset(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_mask[x] &= ~(0x1 << y);
	}

	void Mask::Set(void)
	{
		memset(_mask, 0xFF, _lenInt * sizeof(int));
		int y = _lenBit % IntBits;
		if (y > 0) _mask[_lenInt - 1] &= (0x1 << y) - 1;
	}
	
	void Mask::Set(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_mask[x] |= 0x1 << y;
	}

	void Mask::Flip(void)
	{
		for (int i = 0; i < _lenInt; i++) {
			_mask[i] ^= 0xFFFFFFFF;
		}
		int y = _lenBit % IntBits;
		if (y > 0) _mask[_lenInt - 1] &= (0x1 << y) - 1;
	}
	
	void Mask::Flip(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_mask[x] ^= 0x1 << y;
	}

	
	bool Mask::All(void) const
	{
		int y = _lenBit % IntBits;
		
		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i ++) {
			if (_mask[i] != 0xFFFFFFFF) return false;
		}

		if (y > 0 && (((0x1 << y) - 1) ^ _mask[_lenInt - 1]) != 0) return false;

		return true;
	}

	bool Mask::Any(void) const
	{
		int y = _lenBit % IntBits;
		
		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i ++) {
			if (_mask[i] != 0) return true;
		}

		if (y > 0 && ((((0x1 << y) - 1) & _mask[_lenInt - 1]) != 0)) return true;

		return false;
	}

	size_t Mask::Count(void) const
	{
		size_t count = 0;
		int y = _lenBit % IntBits;
		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i ++) {
			for (int j = 0; j < IntBits; j ++) {
				count += 0x1 & (_mask[i] >> j);
			}
		}
		if (y > 0) {
			for (int i = 0; i < y; i ++) {
				count += 0x1 & (_mask[_lenInt - 1] >> i);
			}
		}
		return count;
	}

	bool Mask::Test(size_t position) const
	{
		int x, y;
		Position(position, &x, &y);
		return 0x1 & (_mask[x] >> y);
	}

	ostream& operator<<(ostream& os, const Mask& mask)
	{
		if (nullptr != mask._mask) {
			for (int i = mask._lenInt - 1; i >= 0; i --) {
				for (int j = 28; j >= 0; j -=4) {
					os << hex << (0xF & (mask._mask[i] >> j));
				}
			}
		}
		return os;
	}
}
