#pragma once
#include <deque>
#include <functional>
#include <queue>
#include <stack>
#include <vector>
#include "BinarySearch.h"
#include "BitSet.h"
#include "Search.h"
#include "String.h"

using namespace std;

namespace Test {
	class __declspec(dllexport) Array {
	public:

		// Permute a two dimensional matrix in place. 
		// The permute function takes three parameters: index of the element to permute, number of rows and number of columns,
		// and output the index of the new position of the element.
		template<class T> static void Permute(T * input, const int length, const int columns, function<int(int, int, int)> & permute);

		// Rotate an input array to the left by a distance. The elements rotated out are shifted into the right.
		template<class T> static void RotateLeft(T * input, const int length, int distance);

		// Rotate an input array to the right by a distance. The elements rotated out are shifted into the left.
		template<class T> static void RotateRight(T * input, const int length, int distance);

		// Swap contiguous elements between the first and the second positions.
		template<class T> static void Swap(T * first, T * second, const int count);

		// Swap elements at two positions
		template<class T> static void Swap(T * buffer, unsigned int position1, unsigned int position2);

		// Transpose a two dimensional matrix in place
		template<class T> static void Transpose(T * input, const int length, const int columns);

		// Transpose rows to columns for a two dimensional matrix in place. Not change the dimensions.
		template<class T> static void TransposeRowsToColumns(T * input, const int length, const int columns);
		
		// Transpose columns to rows for a two dimensional matrix in place. Not change the dimensions.
		template<class T> static void TransposeColumnsToRows(T * input, const int length, const int columns);
	};

	template<class T> void Array::Swap(T * buffer, unsigned int position1, unsigned int position2)
	{
		if (position1 != position2) {
			T t = buffer[position1];
			buffer[position1] = buffer[position2];
			buffer[position2] = t;
		}
	}
}

