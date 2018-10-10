#pragma once

namespace My {

	// Multi-Radix integer
	class MRInteger {
	private:
		unsigned int * _bases;
		// 0 <= _digits[i] < _bases[i]
		unsigned int * _digits;
		unsigned int _length;	
		unsigned long _max;
		unsigned int AddOne(unsigned int position);	
	public:		
		__declspec(dllexport) MRInteger(const unsigned int * bases, unsigned int length);
		__declspec(dllexport) MRInteger(const unsigned int * bases, const unsigned int * digits, unsigned int length);
		__declspec(dllexport) MRInteger(const MRInteger & mrint);
		__declspec(dllexport) MRInteger(MRInteger && mrint);
		__declspec(dllexport) ~MRInteger(void);
		__declspec(dllexport) void Set(const unsigned int * digits, unsigned int length);
		__declspec(dllexport) void Reset(void);
		__declspec(dllexport) const MRInteger & operator=(const MRInteger & mrint);
		__declspec(dllexport) const MRInteger & operator=(MRInteger && mrint);
		__declspec(dllexport) const MRInteger & operator++(void);
		__declspec(dllexport) const MRInteger operator++(int);
		__declspec(dllexport) bool operator==(const MRInteger & mrint) const;
		__declspec(dllexport) bool operator!=(const MRInteger & mrint) const { return !((*this) == mrint); }
		__declspec(dllexport) bool operator<(const MRInteger & mrint) const;
		__declspec(dllexport) bool operator>=(const MRInteger & mrint) const { return !((*this) < mrint); }
		__declspec(dllexport) bool operator>(const MRInteger & mrint) const;
		__declspec(dllexport) bool operator<=(const MRInteger & mrint) const { return !((*this) > mrint); }
		__declspec(dllexport) const unsigned long Max(void) const { return _max; }
		__declspec(dllexport) const unsigned int Length(void) const { return _length; }
		__declspec(dllexport) const unsigned int operator[](unsigned int) const;
		__declspec(dllexport) void Random(void);
	};
}

