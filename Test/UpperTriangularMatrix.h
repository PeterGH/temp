#pragma once
#include "Matrix.h"
namespace Test {
	template<class T> class UpperTriangularMatrix : public Matrix<T> {
	public:
		UpperTriangularMatrix(size_t rows, size_t cols);
		~UpperTriangularMatrix(void) {}
		T & operator()(size_t r, size_t c);
		T operator()(size_t r, size_t c) const;
	};

	template<class T> UpperTriangularMatrix<T>::UpperTriangularMatrix(size_t rows, size_t cols)
	{
		if (rows <= 0) throw invalid_argument(String::Format("Invalid rows %d", rows));
		if (cols <= 0) throw invalid_argument(String::Format("Invalid cols %d", cols));
		this->rows = rows;
		this->cols = cols;

		// if rows <= cols
		//   cols + (cols - 1) + ... + (cols - (rows - 1))) = cols * rows - (rows - 1) * rows / 2
		// if rows > cols
		//   cols + (cols - 1) + ... + 2 + 1 = (cols + 1) * cols / 2
		size_t c;
		if (rows > cols) c = ((cols + 1) * cols) >> 1;
		else c = cols * rows - (((rows - 1) * rows) >> 1);
		this->buffer = new T[c];
		memset(this->buffer, 0, c * sizeof(T));
	}

	template<class T> T & UpperTriangularMatrix<T>::operator()(size_t r, size_t c)
	{
		if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
		if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
		if (r > c) throw invalid_argument(String::Format("r %d is larger than c %d", r, c));
		// cols + (cols - 1) + ... + (cols - (i - 1)) + j - i
		// = cols * i - (i - 1) * i / 2 + j - i
		int index = this->cols * r - (((r - 1) * r) >> 1) + c - r;
		T & value = *(this->buffer + index);
		return value;
	}

	template<class T> T UpperTriangularMatrix<T>::operator()(size_t r, size_t c) const
	{
		if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
		if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
		if (r > c) {
			T d;
			memset(&d, 0, sizeof(T));
			return d;
		}
		return this->operator()(r, c);
	}
}