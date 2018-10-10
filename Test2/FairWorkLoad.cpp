#include "FairWorkLoad.h"

namespace My {

	// The problem comes from http://www.topcoder.com/, and 
	// also appears as the Painter's Partition problem on http://leetcode.com/.
	// The exact state is:
	//   Given an array of non-negative integers, devide them into k non-overlapping partitions, so that
	//   the maximum sumation over all the partitions is minimized.
	// This can be solved using dynamic programming.
	// Suppose input array A[0..(n-1)], k partitions, and 
	// define M[n][k] to be the object value, then it can be computed as
	//   M[n][k] = min{ max{M[1][k-1], A[1]+...+A[n-1]}, 
    //                  max{M[2][k-1], A[2]+...+A[n-1]},
	//                  max{M[3][k-1], A[3]+...+A[n-1]},
	//                  ......
	//                  max{M[n-2][k-1], A[n-2] + A[n-1]},
	//                  max{M[n-1][k-1], A[n-1]} }
	//   M[1][1]
	//   M[2][1]   M[2][2]
	//   M[3][1]   M[3][2]  M[3][3]
	//   ......
	//   M[n-1][1] M[n-1][2] ...... M[n-1][n-1]
	//   M[n][1]   M[n][2]   ...... M[n][n-1]   M[n][n]
	void FairWorkLoad::ComputeSumTable(int * input, int length, int partitions, int * sum)
	{

	}
}