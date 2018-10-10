#pragma once
#include <vector>
#include "Matrix.h"
using namespace std;
namespace Test {
	// Give a matrix, a seam is a path from one side to the other such that
	// successiv elements are adjacent vertically or diagnoally. The sum of
	// elements of a seam is of interesting, and people usually wants to find
	// a seam with minimum sum. This is useful in many image processing applications.
	template<class T> class SeamCarving {
	public:
		SeamCarving(void) {};
		~SeamCarving(void) {};
		static void ComputeSeams(Matrix<T> & input, Matrix<T> & seams);
		static void MinSeam(Matrix<T> & input, vector<pair<size_t, size_t>> & seam);
	};

	template<class T> void SeamCarving<T>::ComputeSeams(Matrix<T> & input, Matrix<T> & seams)
	{
		int rows = input.Rows();
		int cols = input.Cols();
		for (int i = 0; i < cols; i++) {
			seams(0, i) = input(0, i);
		}

		T min;
		for (int i = 1; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (j - 1 >= 0) {
					min = seams(i - 1, j - 1);
					if (seams(i - 1, j) < min)
						min = seams(i - 1, j);
				} else {
					min = seams(i - 1, j);
				}

				if (j + 1 < cols && input(i - 1, j + 1) < min)
					min = seams(i - 1, j + 1);

				seams(i, j) = input(i, j) + min;
			}
		}
	}

	template<class T> void SeamCarving<T>::MinSeam(Matrix<T> & input, vector<pair<size_t, size_t>> & seam)
	{
		int rows = input.Rows();
		int cols = input.Cols();
		Matrix<T> seams(rows, cols);
		ComputeSeams(input, seams);
		int j = 0;
		T min = seams(rows - 1, 0);
		for (int i = 1; i < cols; i++) {
			if (seams(rows - 1, i) < min) {
				min = seams(rows - 1, i);
				j = i;
			}
		}

		seam.insert(seam.begin(), make_pair(rows - 1, j));

		int k = j;
		for (int i = rows - 2; i >= 0; i--) {
			if (j - 1 >= 0) {
				min = seams(i, j - 1);
				k = j - 1;
				if (seams(i, j) < min) {
					min = seams(i, j);
					k = j;
				}
			} else {
				min = seams(i, j);
				k = j;
			}
			
			if (j + 1 < cols && seams(i, j + 1) < min) {
				k = j + 1;
			}

			seam.insert(seam.begin(), make_pair(i, k));
			j = k;
		}
	}
}