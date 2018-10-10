#pragma once

#include <iostream>
#include <fstream>
using namespace std;

class Mask
{
	__declspec(dllexport) friend ostream& operator<<(ostream &, const Mask &);

public:
	__declspec(dllexport) Mask(void);
	__declspec(dllexport) Mask(int);
	__declspec(dllexport) Mask(const Mask &);
	__declspec(dllexport) ~Mask(void);

	__declspec(dllexport) void Reset(void);
	__declspec(dllexport) void Set(int);
	__declspec(dllexport) void Clear(int);
	__declspec(dllexport) void Toggle(int);
	__declspec(dllexport) bool IsSet(int);

private:
	void Position(int, int *, int *);

	int *_mask;
	int _len;
};
