#include "MatrixChain.h"

namespace My {
	// Matrices:    A_0,       A_1,       A_2,       ..., A_i,           ..., A_j,           ..., A_(n-2)
	// Dimensions:  d_0 x d_1, d_1 x d_2, d_2 x d_3, ..., d_i x d_(i+1), ..., d_j x d_(j+1), ..., d_(n-2) x d_(n-1)
	// count = n
	// Costs:
	//   cost[i][i] = 0, for i = 0, 1, 2, ..., (n-2)
	//   cost[i][j] = min { (cost[i][i] + cost[i+1][j] + d_i x d_(i+1) x d_(j+1)),
	//                      (cost[i][i+1] + cost[i+2][j] + d_i x d_(i+2) x d_(j+1)),
	//                      (cost[i][i+2] + cost[i+3][j] + d_i x d_(i+3) x d_(j+1)),
	//                      ...
	//                      (cost[i][j-1] + cost[j][j] + d_i x d_j x d_(j+1))
	//                    }, 
	//                 for i < j, 
	//                     i = 0, 1, 2, ..., n-3
	//                     j =    1, 2, ..., n-3, n-2
	void MatrixChain::ComputeCostTable(int * dimension, int count, int * cost, int * split)
	{
		for (int i = 0; i < count - 1; i ++) {
			// The following statement will throw an access denied error
			//cost[i][i] = 0;
			*(cost + i*(count-1) + i) = 0;
		}

		// l = 1,   cost[0][1],   cost[1][2],   cost[2][3], ..., cost[i][i+1], ..., cost[n-4][n-3], cost[n-3][n-2]
		// l = 2,   cost[0][2],   cost[1][3],   cost[2][4], ..., cost[i][i+2], ..., cost[n-4][n-2]
		// ...
		// l = n-3, cost[0][n-3], cost[1][n-2]
		// l = n-2, cost[0][n-2]
		for (int l = 1; l < count - 1; l++) {
			for (int i = 0; i < count - 1 - l; i++) {
				int j = i + l;
				*(cost + i*(count-1)+ j) = 0x7FFFFFFF;
				for (int k = i; k < j; k++) {
					// split A_i..A_k, A_(k+1)..A_j
					int min = 
						*(cost + i*(count-1)+ k)
						+ *(cost + (k+1)*(count-1)+ j)
						+ dimension[i] * dimension[k+1] * dimension[j+1];
					if (min < *(cost + i*(count-1)+ j)) {
						*(cost + i*(count-1)+ j) = min;
						*(split + i*(count-1)+ j) = k;
					}
				}
			}
		}
	}
}