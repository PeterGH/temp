#pragma once

#include <iostream>
#include <fstream>
#include "MRNumber.h"
using namespace std;

template<class T> class Permutation
{
	// The overloaded operator << is a template
	// Another valid form is: friend ostream& operator<<<>(ostream &, const Permutation<T> &);
	friend ostream& operator<<<T>(ostream &, const Permutation<T> &);

private:
	MRNumber *_counter;
	T * _digits;
	T * _output;
	int _length;
	
	void Swap(int, int);

public:
	Permutation(T *, int);
	~Permutation(void);

	void Next(void);
	void Random(void);	
	const T operator[](int) const;
	const long Max(void) const { return _counter->Max(); }
};

template<class T> Permutation<T>::Permutation(T * digits, int length)
{
	int *bases = new int[length];
	_digits = new T[length];
	_output = new T[length];
	_length = length;
	for (int i = 0; i < length; i ++) {
		bases[i] = i + 1;
		_digits[i] = digits[i];
		_output[i] = 0;
	}
	_counter = new MRNumber(bases, _length);
	delete bases;
}

template<class T> Permutation<T>::~Permutation(void)
{
	delete _counter;
	delete _digits;
	delete _output;
}

// Swap data at two positions in the output buffer
template<class T> void Permutation<T>::Swap(int position1, int position2)
{
	if (position1 != position2) {
		T t = _output[position1];
		_output[position1] = _output[position2];
		_output[position2] = t;
	}
}

template<class T> void Permutation<T>::Next(void)
{
	// Initialize the output buffer
	memcpy(_output, _digits, _length * sizeof(T));
	for (int i = _length - 1; i >= 0; i --) {
		Swap(i, i - (*_counter)[i]);
	}
	// Prepare for the next permutation
	(*_counter) ++;
}

template<class T> void Permutation<T>::Random(void)
{
	memcpy(_output, _digits, _length * sizeof(T));
	for (int i = _length - 1; i >= 0; i --) {
		Swap(i, i - (*_counter)[i]);
	}
	(*_counter).Random();	
}

template<class T> const T Permutation<T>::operator[](int index) const
{
	return _output[index];
}

template<class T> ostream& operator<<(ostream& os, const Permutation<T> & permutation)
{
	for (int i = permutation._length - 1; i >= 0; i --) {
		os << "\t" << permutation[i];
	}
	os << endl;
	return os;
}

template __declspec(dllexport) class Permutation<int>;
template __declspec(dllexport) class Permutation<double>;