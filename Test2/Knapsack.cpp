#include "Knapsack.h"
#include <iostream>
#include <algorithm>
using namespace std;
namespace My {
	// value:	0	60	100	120
	// weight:	0	10	20	30
	// maxValue:
	// 0	0	0	0	0	0
	// 60	1	0	10	

	// Assuming weight array is not decreasing
	// value:    v_0 v_1 v_2 v_3 ...... v_(n-1)
	// weight:   w_0 w_1 w_2 w_3 ...... w_(n-1), such that w_i <= w_j for i < j
	// capacity: W
	// matrix:   Define m[i][j] to be the maximum value that can be attained with weight less than or equal to j using items up to i
	//           m[i][j] = m[i-1][j]                              if j < w_i
	//           m[i][j] = max(m[i-1][j], m[i-1][j-w_i] + v_i)    if j >= w_i
	//
	// i=0  0 1 2 3 ...... w_0-1 w_0 w_0+1 ...... W
	// v_0  0 0 0 0 ...... 0     v_0 v_0   ...... v_0
	//
	// i=1  0 1 2 3 ...... w_1-1 w_1 w_1+1 ...... W
	// v_1  0 0 0 0 ...... 0     v_0 v_0   ...... v_0

	void Knapsack::ProgramValueMatrix(unsigned int * value, unsigned int * weight, unsigned int length, unsigned int * matrix, unsigned int capacity)
	{
		// Compute the first row of matrix[0][]
		// using item 0, i.e., value[0], weight[0]
		for (unsigned int j = 0; j <= capacity; j++) {
			if (j < *weight) {
				*(matrix + j) = 0;
			} else {
				*(matrix + j) = *value;
			}
		}

		for (unsigned int i = 1; i < length; i++) {
			// Consider item i, i.e., value[i], weight[i]
			for (unsigned int j = 0; j <= capacity; j++) {
				if (j < *(weight+i)) {
					// matrix[i][j] = matrix[i-1][j]
					*(matrix + i* (1+capacity) + j) = *(matrix + (i-1)*(1+capacity) + j);
				} else {
					// m[i][j] = max(m[i-1][j], m[i-1][j-w_i] + v_i)
					*(matrix + i* (1+capacity) + j) = max(
						*(matrix + (i-1)*(1+capacity) + j),
						*(matrix + (i-1)*(1+capacity) + (j - *(weight+i))) + *(value+i));
				}
			}
		}
	}

	void Knapsack::Print(unsigned int * value, unsigned int * weight, unsigned int length, unsigned int * matrix, unsigned int capacity)
	{
		cout << "\t";
		for (unsigned int j = 0; j <= capacity; j++) {
			cout << "\t" << j;
		}
		cout << endl;

		for (unsigned int i = 0; i < length; i++) {
			cout << *(value+i) << "\t" << *(weight+i);
			for (unsigned int j = 0; j <= capacity; j++) {
				cout << "\t" << *(matrix + i* (1+capacity) + j);
			}
			cout << endl;
		}
	}
}