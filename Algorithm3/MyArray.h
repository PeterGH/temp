#pragma once

#include <stdlib.h>
#include <string>
#include <assert.h>
#include <iostream>

using namespace std;

template<class T> class Array1D {
private:
	T * _array;
	size_t _length;

public:
	Array1D(size_t length);
	~Array1D(void);

	T & operator[](unsigned int index);
	T GetValue(unsigned int index);
	void SetValue(unsigned int index, T value);
	void Print(void);
};

template<class T> Array1D<T>::Array1D(size_t length)
{
	if (0 < length) {
		_length = length;
		size_t cb = _length * sizeof(T);
		_array = (T *)malloc(cb);
		memset(_array, 0, cb);
	} else {
		_length = 0;
		_array = NULL;
	}
}

template<class T> Array1D<T>::~Array1D(void)
{
	if (_array != NULL) {
		free(_array);
		_array = NULL;
		_length = 0;
	}
}

template<class T> T & Array1D<T>::operator[](unsigned int index)
{
	assert(0 <= index);
	assert(index < _length);
	T & value = _array[index];
	return value;
}

template<class T> T Array1D<T>::GetValue(unsigned int index)
{
	assert(0 <= index);
	assert(index < _length);
	T value = _array[index];
	return value;
}

template<class T> void Array1D<T>::SetValue(unsigned int index, T value)
{
	assert(0 <= index);
	assert(index < _length);
	_array[index] = value;
}

template<class T> void Array1D<T>::Print(void)
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

template __declspec(dllexport) class Array1D<int>;




template<class T> class Array2D {
private:
	T * _array;
	size_t _rows;
	size_t _cols;

public:
	Array2D(size_t rows, size_t cols);
	~Array2D(void);

	T GetValue(unsigned int row, unsigned int col);
	void SetValue(unsigned int row, unsigned int col, T value);
	//T * Element(unsigned int row, unsigned int col);
	T & Element(unsigned int row, unsigned int col);
	void Print(void);
};

template<class T> Array2D<T>::Array2D(size_t rows, size_t cols)
{
	if ((0 < rows) && (0 < cols)) {
		_rows = rows;
		_cols = cols;
		size_t cb = _rows * _cols * sizeof(T);
		_array = (T *)malloc(cb);
		memset(_array, 0, cb);
	} else {
		_rows = 0;
		_cols = 0;
		_array = NULL;
	}
}

template<class T> Array2D<T>::~Array2D(void)
{
	if (_array != NULL) {
		free(_array);
		_array = NULL;
		_rows = 0;
		_cols = 0;
	}
}

template<class T> T Array2D<T>::GetValue(unsigned int row, unsigned int col)
{
	assert(0 <= row);
	assert(row < _rows);
	assert(0 <= col);
	assert(col < _cols);
	assert(_array != NULL);
	T value = *(_array + row * _cols + col);
	return value;
}

template<class T> void Array2D<T>::SetValue(unsigned int row, unsigned int col, T value)
{
	assert(0 <= row);
	assert(row < _rows);
	assert(0 <= col);
	assert(col < _cols);
	assert(_array != NULL);
	*(_array + row * _cols + col) = value;
}

/*
template<class T> T * Array2D<T>::Element(unsigned int row, unsigned int col)
{
	assert(0 <= row);
	assert(row < _rows);
	assert(0 <= col);
	assert(col < _cols);
	assert(_array != NULL);
	return (_array + row * _cols + col);
}
*/

template<class T> T & Array2D<T>::Element(unsigned int row, unsigned int col)
{
	assert(0 <= row);
	assert(row < _rows);
	assert(0 <= col);
	assert(col < _cols);
	assert(_array != NULL);
	T & value = *(_array + row * _cols + col);
	return value;
}

template<class T> void Array2D<T>::Print(void)
{
	for (size_t i = 0; i < _cols; i ++) {
		cout << "\t" << i;
	}
	cout << endl;
	for (size_t i = 0; i < _rows; i ++) {
		cout << i;
		for (size_t j = 0; j < _cols; j ++) {
			cout << "\t" << GetValue(i, j);
		}
		cout << endl;
	}
	cout << endl;
}

template __declspec(dllexport) class Array2D<int>;