#include "Array.h"

namespace My {
	// Find a subarray of contiguous elements whose summation is maximized
	// If array A contains both positive and negative numbers, return the maximum subarray
	// If array A contains positive numbers, return entire array A
	// If array A contains non-positive numbers, return the maximum number
	// Parameter sum is the summation of the returned subarray
	// Parameters l and r are the begin and end indices of the returned subarray
	void Array::MaxSubArray(const int * A, const int L, int & start, int & end, long long & sum)
	{
		start = -1;
		end = -1;
		sum = 0;
		
		if (A == nullptr || L <= 0) return;
		
		// Track the last maximum sum so far
		start = 0;
		end = 0;
		sum = 0;

		int l = 0;
		// Cumulative sum up to current element
		long long c = 0;
		int max = 0;

		for (int i = 0; i < L; i ++) {
			// Add current element
			c += A[i];

			if (c > sum) {
				// Current element is positive,
				// and the current sum is larger than the last one.
				// Update the last seen maximum sum
				start = l;
				end = i;
				sum = c;
			} else if (c <= 0) {
				// Current element is negative
				// and everything cancel out
				// Reset
				l = i + 1;
				c = 0;
			}

			// Record the max element so far
			if (A[i] > A[max]) max = i;			
		}

		if (sum <= 0) {
			// All elements are zero or negative
			// Return the maximum element
			start = max;
			end = max;
			sum = A[max];
		}
	}

	// This is similar to standard c++ function partial_sum in <numeric>
	vector<int> Array::PartialSum(const vector<int> & input)
	{
		vector<int> output;
		int sum = 0;
		for (unsigned int i = 0; i < input.size(); i++) {
			sum += input[i];
			output.push_back(sum);
		}

		return output;
	}

	// For each input[i] compute the sum of range elements before input[i], inclusively.
	vector<int> Array::PartialSum(const vector<int> & input, unsigned int range)
	{
		range = range > input.size() ? input.size() : range;
		vector<int> output(input);
		for (int i = 1; i < (int)range; i++) {
			for (int j = (int)input.size() - 1; j >= i; j--) {
				output[j] += input[j-i];
			}
		}

		return output;
	}
	
	// For each input[i] compute the sum of range elements before input[i], inclusively.
	vector<int> Array::PartialSum2(const vector<int> & input, unsigned int range)
	{
		range = range > input.size() ? input.size() : range;
		vector<int> output;
		int sum = 0;
		for (unsigned int i = 0; i < input.size(); i++) {
			sum += input[i];
			if (i >= range) {
				sum -= input[i-range];
			}

			output.push_back(sum);
		}

		return output;
	}

	// For each input[i] compute the sum of range elements before input[i], inclusively.
	/*void Array::PartialSum3(vector<int> & input, unsigned int range)
	{
		range = range > input.size() ? input.size() : range;
		int sum = 0;
		for (unsigned int i = 0; i < input.size(); i++) {
			sum += input[i];
			if (i >= range) {
				sum -= input[i-range];
			}

			input[i] = sum; // This is wrong because input[i-range] is changed during the process and thus not the original one.
		}
	}*/

	// For each input[i] compute the sum of range elements before input[i], inclusively.
	void Array::PartialSum3(vector<int> & input, unsigned int range)
	{
		range = range > input.size() ? input.size() : range;

		// sum A[n-k .. n-1]
		int sum = 0;
		for (int i = input.size() - 1; i >= (int)(input.size() - range); i --) {
			sum += input[i];
		}

		int last = 0;
		for (int i = input.size() - range - 1; i >= 0; i--) {
			last = sum;
			sum -= input[i + range];
			input[i + range] = last;
			sum += input[i];
		}

		// Now sum = A[0 .. k-1]

		for (int i = range - 1; i >= 0; i--) {
			last = sum;
			sum -= input[i];
			input[i] = last;
		}
	}

	// 1. Given an MxN array
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2) (0,M-1)    (0,M)    (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2) (1,M-1)    (1,M)    (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2) (2,M-1)    (2,M)    (2,M+1)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
	// 2. Transpose
	//     (0,0)   (1,0)   (2,0)   ...... (M-2,0)   (M-1,0)
	//     (0,1)   (1,1)   (2,1)   ...... (M-2,1)   (M-1,1)
	//     (0,2)   (1,2)   (2,2)   ...... (M-2,2)   (M-1,2)
	//                             ......
	//                             ......
	//     (0,M-2) (1,M-2) (2,M-2) ...... (M-2,M-2) (M-1,M-2)
	//     (0,M-1) (1,M-1) (2,M-1) ...... (M-2,M-1) (M-1,M-1)
	//     (0,M)   (1,M)   (2,M)   ...... (M-2,M)   (M-1,M)
	//     (0,M+1) (1,M+1) (2,M+1) ...... (M-2,M+1) (M-1,M+1)
	//                             ......
	//                             ......
	//     (0,N-2) (1,N-2) (2,N-2) ...... (M-2,N-2) (M-1,N-2)
	//     (0,N-1) (1,N-1) (2,N-1) ...... (M-2,N-1) (M-1,N-1)

	// In-place matrix transposition (http://en.wikipedia.org/wiki/In-place_matrix_transposition)
	// Transpose element (m,n) to (n,m) means the index i=Nm+n is mapped to j=Mn+m. The mapping is
	// actually a permutation:
	// P(i) = MN-1            if i = MN-1, or
	//        Mi mod (MN-1)   if 0 <= i < MN-1
	// The reason is 
	// P(i) = P(Nm+n) = M(Nm+n) mod (MN-1) = MNm+Mn mod (MN-1) = (MN-1)m+m+Mn mod (MN-1) = Mn+m
	void Array::Transpose(int * input, const int length, const int columns)
	{
		if (length % columns > 0) throw invalid_argument("Array::Transpose(input, length, columns): length is not multiple of columns.");
		int rows = length / columns;
		
		function<int(int)> permute = [=](int i)->int {			
			if (i == (length - 1)) return i;
			int j = (rows * i) % (length - 1);
			return j;
		};

		Mask updated(length);

		// ------+------------+--------------
		//       j            k
		//       s            t
		for (int i = 0; i < length; i++) {
			if (updated.Test(i)) continue;
			int j = i;
			int s = input[j];
			int k = permute(j);
			while (k != i) {
				int t = input[k];
				input[k] = s;
				updated.Set(k);
				j = k;
				s = t;
				k = permute(j);
			}

			input[i] = s;
			updated.Set(i);
		}
	}

	void Array::Print(const int * input, const int length, const int columns)
	{
		int rows = length / columns;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int k = i * columns + j;
				cout << "\t" << input[k];
			}
			
			cout << endl;
		}

		int r = length % columns;
		for (int i = 0; i < r; i++) {
			cout << "\t" << input[length - r + i];
		}

		cout << endl;
	}
}