#include <cstdlib>
#include <cstring>
#include "Mask.h"

Mask::Mask(void)
{
	_len = 0;
	_mask = NULL;
}

Mask::Mask(int maxBits)
{
	if (maxBits) {
		//_len = maxBits / (8 * sizeof(int));
		_len = maxBits >> 5;
		//int y = maxBits % (8 * sizeof(int));
		int y = maxBits & 31;
		if (y)  _len ++;
		_mask = (int *)malloc( _len * sizeof(int) );
		memset(_mask, 0, _len * sizeof(int));
	} else {
		_len = 0;
		_mask = NULL;
	}
}

Mask::Mask(const Mask & mask)
{
	if (NULL != mask._mask) {
		_len = mask._len;
		_mask = (int *)malloc( mask._len * sizeof(int) );
		memcpy(_mask, mask._mask, mask._len * sizeof(int));
	} else {
		_len = 0;
		_mask = NULL;
	}
}

Mask::~Mask(void)
{
	if (NULL != _mask) {
		free(_mask);
		_mask = NULL;
	}
}

void Mask::Reset(void)
{
	if (NULL != _mask)  memset(_mask, 0, _len * sizeof(int));
}

//
// Assume n = sizeof(int), then the int array mask represents a bit map like:
//     | 0 1 ... (n-1) | n (n+1) ... (2n-1) | 2n  ... (3n-1) | 3n ...
// x = | 0             | 1                  | 2              | 3  ...
// y = | 0 1 ... (n-1) | 0 1     ... (n-1)  | 0 1 ... (n-1)  | 0  ...
// position = x*n + y
void Mask::Position(int position, int * x, int * y)
{
	//*x = position / (8 * sizeof(int));
	*x = position >> 5;
	//*y = position % (8 * sizeof(int));
	*y = position & 31;
}


void Mask::Set(int position)
{
	if (NULL != _mask) {
		int x, y;
		Position(position, &x, &y);
		_mask[x] |= 0x1 << y;
	}
}

void Mask::Clear(int position)
{
	if (NULL != _mask) {
		int x, y;
		Position(position, &x, &y);
		_mask[x] &= ~(0x1 << y);
	}
}

void Mask::Toggle(int position)
{
	if (NULL != _mask) {
		int x, y;
		Position(position, &x, &y);
		_mask[x] ^= 0x1 << y;
	}
}

bool Mask::IsSet(int position)
{
	if (NULL != _mask) {
		int x, y;
		Position(position, &x, &y);
		return 0x1 & (_mask[x] >> y);
	}
	return false;
}

ostream& operator<<(ostream& os, const Mask& mask)
{
	if (NULL != mask._mask) {
		for (int i = mask._len - 1; i >= 0; i --) {
			for (int j = 28; j >= 0; j -=4) {
				os << hex << (0xF & (mask._mask[i] >> j));
			}
		}
	}
	os << endl;
	return os;
}