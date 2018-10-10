#pragma once

#include <stdlib.h>
#include <string>
#include <assert.h>
#include <iostream>
#include <stdarg.h>
#include "MyString.h"

using namespace std;

namespace My {
	
	template<class T> class Array1D {
	private:
		T * _array;
		size_t _length;
		void Check(unsigned int index);
	public:
		Array1D(size_t length);
		~Array1D(void);
		const size_t Length(void) const { return _length; }
		T & operator[](unsigned int index);
		const T & GetValue(unsigned int index);
		void SetValue(unsigned int index, T value);
		void Print(void) const;
	};
	
	template<class T> void Array1D<T>::Check(unsigned int index)
	{
		if (! (0 <= index && index < _length)) {
			throw invalid_argument(String::Format("Invalid indices [%d]", index));
		}
		if ( _array == NULL) {
			throw logic_error(String::Format("Array uninitialized"));
		}
	}

	template<class T> Array1D<T>::Array1D(size_t length)
	{
		if (0 < length) {
			_length = length;
			//size_t cb = _length * sizeof(T);
			//_array = (T *)malloc(cb);
			//memset(_array, 0, cb);

			// If T is a primitive type, e.g. int, the memory may not be initialized.
			// If T is an object, then the constructor handles initialization.
			_array = new T[_length];	
		} else {
			_length = 0;
			_array = NULL;
		}
	}
	
	template<class T> Array1D<T>::~Array1D(void)
	{
		if (_array != NULL) {
			//free(_array);
			delete[] _array;
			_array = NULL;
			_length = 0;
		}
	}
	
	template<class T> T & Array1D<T>::operator[](unsigned int index)
	{
		Check(index);
		T & value = _array[index];
		return value;
	}
	
	template<class T> const T & Array1D<T>::GetValue(unsigned int index)
	{
		Check(index);
		T & value = _array[index];
		return value;
	}
	
	template<class T> void Array1D<T>::SetValue(unsigned int index, T value)
	{
		Check(index);
		_array[index] = value;
	}
	
	template<class T> void Array1D<T>::Print(void) const
	{
		for (size_t i = 0; i < _length; i ++) {
			cout << "\t" << i;
		}
		cout << endl;
		for (size_t i = 0; i < _length; i ++) {
			cout << "\t" << _array[i];
		}
		cout << endl;
	}
	
	template<class T> class Array2D {
	private:
		T * _array;
		size_t _rows;
		size_t _cols;
		void Check(unsigned int row, unsigned int col);
	public:
		Array2D(size_t rows, size_t cols);
		~Array2D(void);
		const size_t CountRows(void) const { return _rows; }
		const size_t CountCols(void) const { return _cols; }
		const T & GetValue(unsigned int row, unsigned int col);
		void SetValue(unsigned int row, unsigned int col, T value);
		T & Element(unsigned int row, unsigned int col);
		void Print(void) const;
	};
	
	template<class T> void Array2D<T>::Check(unsigned int row, unsigned int col)
	{
		if (! (0 <= row && row < _rows && 0 <= col && col < _cols)) {
			throw invalid_argument(String::Format("Invalid indices [%d][%d]", row, col));
		}
		if ( _array == NULL) {
			throw logic_error(String::Format("Array uninitialized"));
		}
	}

	template<class T> Array2D<T>::Array2D(size_t rows, size_t cols)
	{
		if ((0 < rows) && (0 < cols)) {
			_rows = rows;
			_cols = cols;
			//size_t cb = _rows * _cols * sizeof(T);
			//_array = (T *)malloc(cb);
			//memset(_array, 0, cb);
			
			// If T is a primitive type, e.g. int, the memory may not be initialized.
			// If T is an object, then the constructor handles initialization.
			_array = new T[_rows * _cols];
		} else {
			_rows = 0;
			_cols = 0;
			_array = NULL;
		}
	}
	
	template<class T> Array2D<T>::~Array2D(void)
	{
		if (_array != NULL) {
			//free(_array);
			delete[] _array;
			_array = NULL;
			_rows = 0;
			_cols = 0;
		}
	}
	
	template<class T> const T & Array2D<T>::GetValue(unsigned int row, unsigned int col)
	{
		Check(row, col);
		T & value = *(_array + row * _cols + col);
		return value;
	}
	
	template<class T> void Array2D<T>::SetValue(unsigned int row, unsigned int col, T value)
	{
		Check(row, col);
		*(_array + row * _cols + col) = value;
	}

	template<class T> T & Array2D<T>::Element(unsigned int row, unsigned int col)
	{
		Check(row, col);
		T & value = *(_array + row * _cols + col);
		return value;
	}

	template<class T> void Array2D<T>::Print(void) const
	{
		for (size_t i = 0; i < _cols; i ++) {
			cout << "\t" << i;
		}
		cout << endl;
		for (size_t i = 0; i < _rows; i ++) {
			cout << i;
			for (size_t j = 0; j < _cols; j ++) {
				cout << "\t" << *(_array + i * _cols + j);
			}
			cout << endl;
		}
		cout << endl;
	}

#if NULL

	template<class T> class ArrayMD {
	private:		
		T * _array;          // _array[D_0][D_1][D_2]...[D_(n-1)]
		size_t _dimensions;  // = n
		size_t * _sizes;     // = {D_0,       D_1,       D_2,       ..., D_(n-2),     D_(n-1)}
		size_t * _volumes;   // = {M(1, n-1), M(2, n-1), M(3, n-1), ..., M(n-1, n-1), 1}, where M(i, j) = D_i * D_(i+1) *...*D_j
		size_t _size;        // = M(0, n-1) = D_0 *...* D_(n-1)
		void Check(size_t dimension);
	public:
		ArrayMD(size_t _dimensions, ...);
		~ArrayMD(void);
		const size_t Size(size_t dimension) const { Check(dimension); return _sizes[dimension]; }
		T * Element(size_t _dimensions, ...);
		void Print(void) const;
	};

	template<class T> void ArrayMD<T>::Check(size_t dimension)
	{
		if (dimension > _dimensions) {
			throw invalid_argument(String::Format("Invalid dimension %d", dimension));
		}
		if ( _array == NULL) {
			throw logic_error(String::Format("Array uninitialized"));
		}
	}

	template<class T> ArrayMD<T>::ArrayMD(size_t dimensions, ...)
	{
		_dimensions = dimensions;
		_sizes = new size_t[_dimensions];
		_size = 1;
		va_list args;
		va_start(args, _dimensions);
		for (size_t i = 0; i < _dimensions; i++) {
			int t = va_arg(args, int); // This fails to get the value. Don't know why
			cout << t << " ";
			_sizes[i] = t;
			_size *= _sizes[i];
		}
		va_end(args);
		if (_size > 0) {
			_array = new T[_size];
			_volumes = new size_t[_dimensions];
			_volumes[_dimensions - 1] = 1;
			for (int i = _dimensions - 2; i >= 0; i-- ) {
				_volumes[i] = _sizes[i+1] * _volumes[i+1];
			}
		} else {
			_array = NULL;
			delete[] _sizes;
			_sizes = NULL;
		}
	}

	template<class T> ArrayMD<T>::~ArrayMD(void)
	{
		if (_array != NULL) {
			delete[] _array;
			_array = NULL;
		}
		if (_sizes != NULL) {
			delete[] _sizes;
			_sizes = NULL;
		}
		if (_volumes != NULL) {
			delete[] _volumes;
			_volumes = NULL;
		}
	}

	template<class T> T * ArrayMD<T>::Element(size_t dimensions, ...)
	{
		Check(dimensions);
		T * p = _array;
		va_list args;
		va_start(args, dimensions);
		for (size_t i = 0; i < _dimensions; i++) {
			p += (i * _volumes[i]);
		}
		va_end(args);
		return p;
	}

	template<class T> void ArrayMD<T>::Print(void) const
	{
		for (size_t i = 0; i < _dimensions; i ++) {
			cout << "\t" << i;
		}
		cout << endl;
		for (size_t i = 0; i < _dimensions; i ++) {
			cout << "\t" << _sizes[i];
		}
		cout << endl;
		for (size_t i = 0; i < _dimensions; i ++) {
			cout << "\t" << _volumes[i];
		}
		cout << endl;
	}
#endif
}