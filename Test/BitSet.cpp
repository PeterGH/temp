#include "BitSet.h"

namespace Test {

	ostream & operator<<(ostream & os, const BitSet & bitset)
	{
		if (nullptr != bitset._ints) {
			bool skip = true;
			int y = bitset._lenBit % bitset.IntBits;
			for (int j = 28; j >= 0; j -= 4) {
				unsigned int c = 0xF & (bitset._ints[bitset._lenInt - 1] >> j);
				if (skip && y > 0 && j >= y && c == 0) continue;
				skip = false;
				os << hex << c;
			}
			for (int i = bitset._lenInt - 2; i >= 0; i--) {
				for (int j = 28; j >= 0; j -= 4) {
					os << hex << (0xF & (bitset._ints[i] >> j));
				}
			}
		}

		return os;
	}

	Log & operator<<(Log & log, const BitSet & bitset)
	{
		if (nullptr != bitset._ints) {
			bool skip = true;
			int y = bitset._lenBit % bitset.IntBits;
			for (int j = 28; j >= 0; j -= 4) {
				unsigned int c = 0xF & (bitset._ints[bitset._lenInt - 1] >> j);
				if (skip && y > 0 && j >= y && c == 0) continue;
				skip = false;
				log.WriteInformation("%X", c);
			}
			for (int i = bitset._lenInt - 2; i >= 0; i--) {
				for (int j = 28; j >= 0; j -= 4) {
					log.WriteInformation("%X", (0xF & (bitset._ints[i] >> j)));
				}
			}
		}

		return log;
	}
	
	
	bool BitSet::All(void) const
	{
		int y = _lenBit % IntBits;

		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i++) {
			if (_ints[i] != 0xFFFFFFFF) return false;
		}

		// Test if the lower y bits of the last integer are all ones
		if (y > 0 && (((0x1 << y) - 1) ^ _ints[_lenInt - 1]) != 0) return false;

		return true;
	}

	bool BitSet::Any(void) const
	{
		int y = _lenBit % IntBits;

		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i++) {
			if (_ints[i] != 0) return true;
		}

		// Test if the lower y bits of the last integer are all zeros
		if (y > 0 && ((((0x1 << y) - 1) & _ints[_lenInt - 1]) != 0)) return true;

		return false;
	}

	size_t BitSet::Count(void) const
	{
		// http://leetcode.com/2010/09/number-of-1-bits.html
		auto countInt = [&](int n) -> size_t {
			int c = 0;
			while (n != 0) {
				// erase one bit from the lower end
				// 0x####0100 & 0x####00FF = 0x####0000
				n = n & (n - 1);
				c++;
			}
			return c;
		};

		size_t count = 0;
		int y = _lenBit % IntBits;
		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i++) {
			count += countInt(_ints[i]);
		}

		if (y > 0) {
			int last = _ints[_lenInt - 1] & ((0x1 << y) - 1);
			count += countInt(last);
		}

		return count;
	}

	void BitSet::Flip(void)
	{
		for (int i = 0; i < _lenInt; i++) {
			_ints[i] ^= 0xFFFFFFFF;
		}

		int y = _lenBit % IntBits;

		// The bits of the last integer have already been flipped.
		// Just reset its higher non-used bits to zero.
		if (y > 0) _ints[_lenInt - 1] &= (0x1 << y) - 1;
	}

	void BitSet::Flip(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_ints[x] ^= 0x1 << y;
	}

	bool BitSet::IsPower2(void)
	{
		return 1 == Count();
	}

	void BitSet::LeftShiftInternal(size_t distance)
	{
		if (distance == 0) return;

		int x, y;
		x = distance / IntBits;
		y = distance % IntBits;

		if (y == 0) {
			// +----+----+----+----+----+----+----+----+----+----+
			// 0    1         x-1  x         L-x            L-1
			// |<------- x ------->|         |<------- x ------->|
			for (int i = _lenInt - 1; i >= x; i--) {
				_ints[i] = _ints[i-x];
			}
		} else {
			// +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
			// 0        1                 x                                   L-x               L-1
			// |<----------- x ---------->|<-y->|                       |<-y->|<----------- x ---------->|
			unsigned int mask = (0x1 << y) - 1;
			for (int i = _lenInt - 1; i > x; i--) {
				_ints[i] = ((_ints[i-x] << y) & ~mask) + ((_ints[i-x-1] >> (IntBits - y)) & mask);
			}
			_ints[x] = (_ints[0] << y) & ~mask;
		}

		if (x > 0) {
			memset(_ints, 0, x * sizeof(int));
		}
	}

	void BitSet::LeftShift(size_t distance)
	{
		LeftShiftInternal(distance);
		// Reset the bits out of range
		int z = _lenBit % IntBits;
		if (z > 0) _ints[_lenInt - 1] &= (0x1 << z) - 1;
	}

	void BitSet::Reset(void)
	{
		memset(_ints, 0, _lenInt * sizeof(int));
	}

	void BitSet::Reset(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_ints[x] &= ~(0x1 << y);
	}

	void BitSet::Reverse(unsigned int & bits)
	{
		bits = ((bits & 0x55555555) << 1) | ((bits & 0xAAAAAAAA) >> 1);
		bits = ((bits & 0x33333333) << 2) | ((bits & 0xCCCCCCCC) >> 2);
		bits = ((bits & 0x0F0F0F0F) << 4) | ((bits & 0xF0F0F0F0) >> 4);
		bits = ((bits & 0x00FF00FF) << 8) | ((bits & 0xFF00FF00) >> 8);
		bits = ((bits & 0x0000FFFF) << 16) | ((bits & 0xFFFF0000) >> 16);
	}

	void BitSet::Reverse(void)
	{
		size_t d = _lenInt * IntBits - _lenBit;
		// 0YXXXXXXX
		// YXXXXXXX0
		LeftShiftInternal(d);
		int i = 0;
		int j = _lenInt - 1;
		while (j > i) {
			unsigned int u = _ints[i];
			unsigned int v = _ints[j];
			Reverse(u);
			Reverse(v);
			_ints[i] = v;
			_ints[j] = u;
			i++;
			j--;
		}

		if (j == i) {
			unsigned int t = _ints[i];
			Reverse(t);
			_ints[i] = t;
		}
	}

	void BitSet::Set(void)
	{
		memset(_ints, 0xFF, _lenInt * sizeof(int));
		int y = _lenBit % IntBits;
		
		// The bits of the last integer have already been flipped.
		// Just reset its higher non-used bits to zero.
		if (y > 0) _ints[_lenInt - 1] &= (0x1 << y) - 1;
	}

	void BitSet::Set(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_ints[x] |= 0x1 << y;
	}

	bool BitSet::Test(size_t position) const
	{
		int x, y;
		Position(position, &x, &y);
		return 0x1 & (_ints[x] >> y);
	}

	string BitSet::ToString(void)
	{
		ostringstream oss;
		oss << *this;
		return oss.str();
	}
}
