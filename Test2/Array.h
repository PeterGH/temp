#pragma once
#include <assert.h>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Mask.h"
using namespace std;

namespace My {
	class __declspec(dllexport) Array {
	public:
		static void MaxSubArray(const int * A, const int L, int & start, int & end, long long & sum);
		static vector<int> PartialSum(const vector<int> & input);
		static vector<int> PartialSum(const vector<int> & input, unsigned int range);
		static vector<int> PartialSum2(const vector<int> & input, unsigned int range);
		static void PartialSum3(vector<int> & input, unsigned int range);
		static void Transpose(int * input, const int length, const int columns);
		static void Print(const int * input, const int length, const int columns);
	};

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
			_array = nullptr;
		}
	}

	template<class T> Array1D<T>::~Array1D(void)
	{
		if (_array != nullptr) {
			free(_array);
			_array = nullptr;
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
		T & Element(unsigned int row, unsigned int col);
		void Print(void);
	};

	template<class T> Array2D<T>::Array2D(size_t rows, size_t cols)
	{
		if ((0 < rows) && (0 < cols)) {
			_rows = rows;
			_cols = cols;
			size_t cb = _rows * _cols * sizeof(T);
			//_array = (T *)malloc(cb);
			_array = new T[cb];
			memset(_array, 0, cb);
		} else {
			_rows = 0;
			_cols = 0;
			_array = nullptr;
		}
	}

	template<class T> Array2D<T>::~Array2D(void)
	{
		if (_array != nullptr) {
			//free(_array);
			delete[] _array;
			_array = nullptr;
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
		assert(_array != nullptr);
		T value = *(_array + row * _cols + col);
		return value;
	}

	template<class T> void Array2D<T>::SetValue(unsigned int row, unsigned int col, T value)
	{
		assert(0 <= row);
		assert(row < _rows);
		assert(0 <= col);
		assert(col < _cols);
		assert(_array != nullptr);
		*(_array + row * _cols + col) = value;
	}

	template<class T> T & Array2D<T>::Element(unsigned int row, unsigned int col)
	{
		assert(0 <= row);
		assert(row < _rows);
		assert(0 <= col);
		assert(col < _cols);
		assert(_array != nullptr);
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
}