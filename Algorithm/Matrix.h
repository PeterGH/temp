#pragma once

#include <functional>
#include <stdexcept>
#include "String.h"

using namespace std;

namespace Test {
	template<class T> class Matrix {
	protected:
		T * buffer;
		size_t rows;
		size_t cols;
		// Default constructor for inheritance
		Matrix(void) : rows(0), cols(0), buffer(nullptr) {}
	public:
		Matrix(size_t rows, size_t cols)
		{
			if (rows <= 0) throw invalid_argument(String::Format("Invalid rows %d", rows));
			if (cols <= 0) throw invalid_argument(String::Format("Invalid cols %d", cols));
			this->rows = rows;
			this->cols = cols;
			size_t c = rows * cols;
			this->buffer = new T[c];
			memset(this->buffer, 0, c * sizeof(T));
		}

		virtual ~Matrix(void)
		{
			if (this->buffer != nullptr) {
				delete[] this->buffer;
				this->buffer = nullptr;
				this->rows = 0;
				this->cols = 0;
			}
		}

		virtual T & operator()(size_t r, size_t c)
		{
			if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
			if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
			T & value = *(this->buffer + r * this->cols + c);
			return value;
		}

		virtual T operator()(size_t r, size_t c) const { return this->operator()(r, c); }

		const size_t Rows(void) const { return this->rows; }
		const size_t Cols(void) const { return this->cols; }
	};

	template<class T> class LowerTriangularMatrix : public Matrix<T> {
	public:
		LowerTriangularMatrix(size_t rows, size_t cols)
		{
			if (rows <= 0) throw invalid_argument(String::Format("Invalid rows %d", rows));
			if (cols <= 0) throw invalid_argument(String::Format("Invalid cols %d", cols));
			this->rows = rows;
			this->cols = cols;
			// if rows <= cols
			//   rows + ... + 2 + 1 = (rows + 1) * rows / 2
			// if rows > cols
			//   rows + (rows - 1) + ... + (rows - (cols - 1)) = rows * cols - (cols - 1) * cols / 2
			size_t c;
			if (rows <= cols) c = ((rows + 1) * rows) >> 1;
			else c = rows * cols - (((cols - 1) * cols) >> 1);
			this->buffer = new T[c];
			memset(this->buffer, 0, c * sizeof(T));
		}

		~LowerTriangularMatrix(void) {}

		T & operator()(size_t r, size_t c)
		{
			if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
			if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
			if (r < c) throw invalid_argument(String::Format("r %d is smaller than c %d", r, c));
			// if rows <= cols
			//   1 + 2 + ... + i + j = (i + 1) * i / 2 + j
			// if rows > cols
			//   if i <= cols - 1
			//     1 + 2 + ... + i + j = (i + 1) * i / 2 + j
			//   if cols <= i <= rows - 1
			//     1 + 2 + ... + cols + ((i - 1) - (cols - 1)) * cols  + j = (cols + 1) * cols / 2 + (i - cols) * cols + j
			int index;
			if (this->cols <= r && r < this->rows)
				index = (((this->cols + 1) * this->cols) >> 1) + (r - this->cols) * this->cols + c;
			else
				index = (((r + 1) * r) >> 1) + c;
			T & value = *(this->buffer + index);
			return value;
		}

		T operator()(size_t r, size_t c) const
		{
			if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
			if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
			if (r < c) {
				T d;
				memset(&d, 0, sizeof(T));
				return d;
			}
			return this->operator()(r, c);
		}
	};

	template<class T> class UpperTriangularMatrix : public Matrix<T> {
	public:
		UpperTriangularMatrix(size_t rows, size_t cols)
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

		~UpperTriangularMatrix(void) {}

		T & operator()(size_t r, size_t c)
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

		T operator()(size_t r, size_t c) const
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
	};
}