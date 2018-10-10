#pragma once

//#include <iostream>
//#include <fstream>
#include "MRInteger.h"
#include <time.h>

using namespace std;

namespace My {

	template<class T> class Permutation	{
		// The overloaded operator << is a template
		// Another valid form is: friend ostream& operator<<<>(ostream &, const Permutation<T> &);
		// friend ostream& operator<<<T>(ostream &, const Permutation<T> &);

	private:
		// Keep the permutation state
		MRInteger * _counter;
		// Digits of type T to permute
		T * _digits;
		// Output buffer for permuted digits
		T * _output;
		unsigned int _length;

		bool _randInitialized;
	
		void Swap(unsigned int, unsigned int);

	public:
		Permutation(T * digits, unsigned int length);
		~Permutation(void);

		void Next(void);
		void Random(void);
		const T operator[](unsigned int index) const;
		const long Max(void) const { return _counter->Max(); }
		const void Print(void) const;
	};

	template<class T> Permutation<T>::Permutation(T * digits, unsigned int length)
	{
		unsigned int * bases = new unsigned int[length];
		_digits = new T[length];
		_output = new T[length];
		_length = length;
		for (unsigned int i = 0; i < length; i ++) {
			bases[i] = i + 1;
			_digits[i] = digits[i];
			_output[i] = 0;
		}

		_counter = new MRInteger(bases, _length);
		delete[] bases;

		_randInitialized = false;
	}

	template<class T> Permutation<T>::~Permutation(void)
	{
		delete _counter;
		delete[] _digits;
		delete[] _output;
	}

	// Swap data at two positions in the output buffer
	template<class T> void Permutation<T>::Swap(unsigned int position1, unsigned int position2)
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
		for (int i = (int)_length - 1; i >= 0; i --) {
			Swap(i, i - (*_counter)[i]);
		}
		// Prepare for the next permutation
		(*_counter) ++;
	}

	// Not thread safe, because no lock is used when initialize rand.
	template<class T> void Permutation<T>::Random(void)
	{
		if (_randInitialized == false) {
			// Seed the random-number generator with the current time so that
			// the numbers will be different every time we run.
			srand((unsigned)time(NULL));
			// Initialize the output buffer
			memcpy(_output, _digits, _length * sizeof(T));
			_randInitialized = true;
		}

		for (int i = _length - 1; i >= 0; i --) {
			// The rand function returns a pseudorandom integer in the range 0 (inclusive) to RAND_MAX (32767). 
			// We need r in [0, i]
			int r = rand() / (RAND_MAX / (i + 1));
			Swap(i, i - r);
		}
	}

	template<class T> const T Permutation<T>::operator[](unsigned int index) const
	{
		return _output[index];
	}

	template<class T> const void Permutation<T>::Print(void) const
	{
		for (int i = _length - 1; i >= 0; i --) {
			cout << "\t" << _output[i];
		}

		cout << endl;
	}
}