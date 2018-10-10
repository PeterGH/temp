#include "Misc.h"
#include "Mask.h"
#include <bitset>

// Returns a pointer to the first occurrence of str2 in str1, 
// or a null pointer if str2 is not part of str1.
// The matching process does not include the terminating null-characters.
// Return NULL if either str1 or str2 is invalid or an empty string.
const char * MyStrStr ( const char * str1, const char * str2 )
{
	if (NULL == str1 || NULL == str2 || '\0' == *str2) return NULL;

	while ( '\0' != *str1) {
		int i = 0;
		int j = 0;
		while ( '\0' != str1[i] && '\0' != str2[j] && str1[i] == str2[j]) {
			// Match at current position.
			i ++;
			j ++;
		}

		if ('\0' == str2[j]) {
			// All previous chars match.
			return str1;
		}

		if ('\0' == str1[i]) {
			// Now it is the end of str1.
			// No need to check again.
			return NULL;
		}
		
		// Check from next position.
		str1 ++;
	}
	// No matching substring.
	return NULL;
}

size_t RemoveDupChar(char * A, size_t L)
{
	if (A == NULL) return -1;
	
	// Using a 256 bits mask
	//Mask mask(256);
	bitset<256> mask;

	// Using i to point to the last position of a non-dup char that has been checked.
	// Next non-dup char should be copied to the position i+1.
	// 0 | 1 | ... | i | ... | j | ... | n-1
	// ~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~
	// Non-dup chars         chars to check
	
	int i = -1;	

	for (unsigned int j = 0; j < L; j ++) {
		if ('\0' == A[j]) break;
		// Should look at bit charArray[j] of mark
		//if (!mask.IsSet(A[j])) {
		if (!mask.test(A[j])) {
			// The bit is zero, and it means charArray[j] is not a dup.
			// Set the mark.
			//mask.Set(A[j]);
			mask.set(A[j]);
			if (1 < (j-i)) {
				// Have skipped some dups
				// Move current non-dup char to the front.
				A[++i] = A[j];
			} else {
				// Have not skipped any dups.
				// Hop i with j.
				i ++;
			}
		}
	}
	A[++i] = '\0';
	// Now i equals to the new length.
	return i;
}

// Insertion sort is in-place.
template<class T> void InsertionSort(T * A, int L)
{
	if (A == nullptr || L <= 0) return;
	for (int i = 1; i < L; i ++) {
		// Record the current value to insert into A[0..(i-1)]
		T key = A[i];
		// Shift any values in A[0..(i-1)] greater than the current value,
		// so that the right position for the current value is vacant.
		int j = i - 1;
		while (j >= 0 && A[j] > key) {
			A[j + 1] = A[j];
			j --;
		}
		// Insert the current value
		A[j+1] = key;
	}
}

// Recursively sort A[0..(L-1)] by insertion
// Use binary search to find the position to insert an element
template<class T> void InsertionSortRecursively(T * A, int L)
{
	// Invalid input
	if (A == nullptr || L <= 0) return;
	// Only one element. no need to recurse
	if (L == 1) return;
	// Recursively sort A[0..(L-2)]
	InsertionSortRecursively(A, L - 1);
	// Record the current value to insert into A[0..(L-2)]
	T key = A[L - 1];
	// Find the position after which the current value should be inserted
	// -1 <= i <= (L-2)
	int i = FindPositionToInsert(key, A, L - 1);
	// Shift A[(i+1)..(L-2)] so that the position (i+1) for the current value is vacant.
	for (int j = L - 2; j > i; j --) {
		A[j + 1] = A[j];
	}
	// Insert the current value
	A[i+1] = key;
}

// Assume array A[0..(L-1)] is already sorted and it can contain duplicate elements.
// Return -1 if e < A[0]
// Return (L-1) if A[L-1] <= e
// Return i if A[i] <= e < A[i+1].
template<class T> int FindPositionToInsert(T e, const T * A, int L)
{
	if (A == nullptr || L <= 0) return -2;
	int low = 0;
	int high = L - 1;
	// The loop ensures A[0..(low-1)] < e < A[(high+1)..(L-1)]
	while (low <= high) {
		// low <= middle <= high.
		// The case middle == high could happen when low == high.
		int middle = (low + high) >> 1;
		if (e < A[middle]) {
			if (middle == low) return low - 1;
			else high = middle - 1;
		} else if (e > A[middle]) {
			if (middle == high) return high;
			else low = middle + 1;
		} else {
			// The input array may contain duplicate elements. 
			// The index found so far may not be the last occurrence of the value to search.
			// So search backward to find the last occurrence.
			while (middle < L - 1 && e == A[middle + 1]) {
				middle ++;
			}
			return middle;
		}
	}
	// We should not hit this line.
	return -2;
}

template<class T> void SelectionSort(T * A, int L)
{
	if (A == nullptr || L <= 0) return;
	for (int i = 0; i < L - 1; i ++) {
		// Select the minimal value from A[i..(L-1)]
		int minIndex = Min<T>(&A[i], L - i);
		// Swap A[i] with the minimal value
		Swap<T>(A, i, i + minIndex);
	}
}

// Return the index of the minimum element in array A
template<class T> int Min(const T * A, int L)
{
	if (A == nullptr || L <= 0) return -1;
	T min = A[0];
	int index = 0;
	for (int i = 1; i < L; i ++) {
		if (A[i] < min) {
			min = A[i];
			index = i;
		}
	}
	return index;
}

template<class T> void Swap(T * A, int i, int j)
{
	if (A == nullptr || i < 0 || j < 0 || i == j) return;
	T temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

// Assume A[p..(q-1)] and a[q..r] are already sorted.
// Rearrange A so that a[p..r] is sorted.
// Merge is in-place.
template<class T> void Merge(T * A, int p, int q, int r)
{
	if (A == nullptr || p < 0 || r <= 0 || r < q || q <= p) return;
	while (p < q && q <= r) {
		if (A[p] <= A[q]) {
			p ++;
		} else {
			T t = A[q];
			for (int i = q; i > p; i --) {
				A[i] = A[i - 1];
			}
			A[p] = t;
			p ++;
			q ++;
		}
	}
}

// This is an in-place implementation of merge sort.
template<class T> void MergeSort(T * A, int p, int r)
{
	if (A == nullptr || p < 0 || r < 0 || r < p) return;
	if (p < r) {
		int q = p + (r - p) / 2 + 1;
		MergeSort<T>(A, p, q - 1);
		MergeSort<T>(A, q, r);
		Merge<T>(A, p, q, r);
	}
}

template<class T> void PrintArray(const T * A, int L)
{
	if (A == nullptr || L <= 0) return;
	for (int i = 0; i < L - 1; i ++) {
		cout << A[i] << ", ";
	}
	cout << A[L - 1] << endl;
}

template<class T> bool CompareArray(const T * A, const T * B, int L)
{
	if (A == nullptr || B == nullptr || L <= 0) return false;
	for (int i = 0; i < L; i ++) {
		if (A[i] != B[i]) return false;
	}
	return true;
}

// 1. Assume the input array is not sorted.
// 2. The input array may contain duplicate elements. 
// 3. The return value is the index of the first occurrence of the value to search in the input array if found, otherwise -1.
template<class T> int LinearSearch(T e, const T * A, int L)
{
	if (A == nullptr || L <= 0) return -1;
	for (int i = 0; i < L; i ++) {
		if (e == A[i]) {
			return i;
		}
	}
	return -1;
}

// 1. Assume the input array is already sorted.
//    We do not want to apply sorting in the implementation of binary search to enforce the assumption.
//    Instead, sorting should be the responsibility of the caller of binary search.
// 2. The input array may contain duplicate elements. 
// 3. The return value is the index of the first occurrence of the value to search in the sorted input array if found, otherwise -1.
template<class T> int BinarySearch(T e, const T * A, int L)
{
	if (A == nullptr || L <= 0) return -1;
	int low = 0;
	int high = L - 1;
	while (low <= high) {
		int middle = (low + high) >> 1;
		if (e < A[middle]) high = middle - 1;
		else if (e > A[middle]) low = middle + 1;
		else {
			// The input array may contain duplicate elements. 
			// The index found so far may not be the first occurrence of the value to search.
			// So search forward to find the first occurrence.
			while (middle > 0 && e == A[middle - 1]) {
				middle --;
			}
			return middle;
		}
	}
	return -1;
}

// 1. Assume the input array is already sorted.
//    We do not want to apply sorting in the implementation of binary search to enforce the assumption.
//    Instead, sorting should be the responsibility of the caller of binary search.
// 2. The input array may contain duplicate elements. 
// 3. The return value is the index of the first occurrence of the value to search in the sorted input array if found, otherwise -1.
template<class T> int BinarySearchRecursively(T e, const T * A, int l, int h)
{
	if (A == nullptr || l < 0 || h < 0 || h < l) return -1;
	int middle = (l + h) >> 1;
	if (e < A[middle]) return BinarySearchRecursively(e, A, l, middle - 1);
	else if (e > A[middle]) return BinarySearchRecursively(e, A, middle + 1, h);
	else {
		// The input array may contain duplicate elements. 
		// The index found so far may not be the first occurrence of the value to search.
		// So search forward to find the first occurrence.
		while (middle > 0 && e == A[middle - 1]) {
			middle --;
		}
		return middle;
	}
}


/*
//
// pwchars: 0 | 1 | ... | i | ... | j | ... | n-1
//          ~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~
//          Non-dup wchars        wchars to check
//
int RemoveDupWChar(wchar_t * pwchars, int len)
{
	// Using mark[0] 256 bits for the lower byte of a wchar
	// Using mark[1] 256 bits for the higher byte of a wchar
	int mark0[8], mark1[8];
	int x, y;

	if (NULL == pwchars) return -1;

	// Set all bits to zero.
	memset(mark0, 0, 8*sizeof(int));
	memset(mark1, 0, 8*sizeof(int));

	// Using i to point to the last position of a non-dup wchar that has been checked.
	// Next non-dup char should be copied to the position i+1.
	int i = -1;	

	for (int j = 0; j < len; j ++) {

		if ('\0' == charArray[j]) break;

		x = charArray[j] / 32;
		y = charArray[j] % 32;

		if (0 == y) {
			if (x) {
				// Look at mark[x-1];
				x --;
				y = 32;
			}
		} 	
		// Should look at bit y of mark[x]
		if ( 0 == ( (mark[x] >> (y-1)) & 0x1) ) {
			// Zero means not a dup
			// Set the mark.
			mark[x] ^= 0x1 << (y-1);
			if (1 < (j-i)) {
				// Have skipped some dups
				// Move current non-dup char to the front.
				charArray[++i] = charArray[j];
			} else {
				// Have not skipped any dups.
				// Hop i with j.
				i ++;
			}
		}
	}
	charArray[++i] = '\0';
	// Now i equals to the new length.
	return i;

}
*/


