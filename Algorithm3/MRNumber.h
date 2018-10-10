#pragma once

#include <iostream>
#include <fstream>
using namespace std;

// Define a Mixed Radix number.
class MRNumber
{
	__declspec(dllexport) friend ostream & operator<<(ostream &, const MRNumber &);

private:
	int *_bases;
	// 0 <= _digits[i] < _bases[i]
	int *_digits;
	int _length;
	
	long _max;

	int AddOne(int);	

public:
	__declspec(dllexport) MRNumber(const int *, int);
	__declspec(dllexport) MRNumber(const MRNumber &);
	__declspec(dllexport) ~MRNumber(void);
	__declspec(dllexport) void Reset(void);
	__declspec(dllexport) const MRNumber & operator++(void);
	__declspec(dllexport) const MRNumber operator++(int);
	__declspec(dllexport) const long Max(void) const { return _max; }
	__declspec(dllexport) const int Length(void) const { return _length; }
	__declspec(dllexport) const int operator[](int) const;
	__declspec(dllexport) void Random(void);
};
