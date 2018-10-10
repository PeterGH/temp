#pragma once
#include "Matrix.h"
namespace Test {
	template<class T> class Monge : public Matrix < T > {
	public:
		Monge(size_t r, size_t c) : Matrix<T>(r, c) {}
		static bool IsMonge(Matrix<T> & matrix);
		static void Random(Monge<T> & monge);
		void FindRowMins(vector<size_t> & mins);
		void FindRowMins2(vector<size_t> & mins);
	};

	template<class T> bool Monge<T>::IsMonge(Matrix<T> & matrix)
	{
		if (matrix.Rows() <= 1 || matrix.Cols() <= 1) return false;
		for (size_t i = 0; i < matrix.Rows() - 1; i++) {
			for (size_t j = 0; j < matrix.Cols() - 1; j++) {
				if (matrix(i, j) + matrix(i + 1, j + 1) > matrix(i, j + 1) + matrix(i + 1, j)) return false;
			}
		}
		return true;
	}

	template<class T> void Monge<T>::Random(Monge<T> & monge)
	{
		auto rnd = [&]()->int { return rand() >> 2; };
		for (size_t j = 0; j < monge.Cols(); j++) {
			monge(0, j) = rnd();
		}
		for (size_t i = 1; i < monge.Rows(); i++) {
			monge(i, 0) = rnd() + monge(i - 1, 0) - monge(i - 1, 1);
			for (size_t j = 1; j < monge.Cols(); j++) {
				monge(i, j) = min(rnd(), monge(i - 1, j) + monge(i, j - 1) - monge(i - 1, j - 1));
				if (j < monge.Cols() - 1) {
					int d = monge(i - 1, j) - monge(i - 1, j + 1) - monge(i, j);
					if (d > 0) {
						d += (rnd() >> 1);
						for (size_t k = 0; k <= j; k++) {
							monge(i, k) += d;
						}
					}
				}
			}
		}
	}

	template<class T> void Monge<T>::FindRowMins(vector<size_t> & mins)
	{
		if (mins.size() < this->Rows()) throw invalid_argument(String::Format("mins length %d is less than %d", mins.size(), this->Rows()));

		function<void(size_t, size_t, size_t, size_t)> find = [&](size_t i1, size_t j1, size_t i2, size_t j2) {
			if (j1 == j2) {
				for (size_t i = i1; i <= i2; i++) {
					mins[i] = j1;
				}
			} else {
				size_t i = i1 + ((i2 - i1) >> 1);
				T m = this->operator()(i, j1);
				mins[i] = j1;
				for (size_t j = j1 + 1; j <= j2; j++) {
					if (this->operator()(i, j) < m) {
						m = this->operator()(i, j);
						mins[i] = j;
					}
				}
				if (i1 < i) {
					find(i1, j1, i - 1, mins[i]);
				}
				if (i < i2) {
					find(i + 1, mins[i], i2, j2);
				}
			}
		};

		find(0, 0, this->Rows() - 1, this->Cols() - 1);
	}

	template<class T> void Monge<T>::FindRowMins2(vector<size_t> & mins)
	{
		if (mins.size() < this->Rows()) throw invalid_argument(String::Format("mins length %d is less than %d", mins.size(), this->Rows()));

		size_t k = 0;
		for (size_t i = 0; i < this->Rows(); i++) {
			T m = this->operator()(i, k);
			for (size_t j = k + 1; j < this->Cols(); j++) {
				if (this->operator()(i, j) < m) {
					m = this->operator()(i, j);
					k = j;
				}
			}
			mins[i] = k;
		}
	}
}