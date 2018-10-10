#pragma once

#include <iostream>
using namespace std;

template<class T> class HeapSort {
	
private:
	T * _array;
	unsigned int _length;
	unsigned int _height;

	//         0
	//    1          2
	//  3   4     5     6
	// 7 8 9 10 11 12 13 14
	unsigned int Parent(unsigned int i) { return (i - 1) >> 1; }
	unsigned int Left(unsigned int i) { return (i << 1) + 1; }
	unsigned int Right(unsigned int i) { return (i << 1) + 2; }
	unsigned int Height(void);
	void Swap(unsigned int, unsigned int);
	void Heapify(unsigned int, unsigned int);
	void Heapify(void);	

public:
	HeapSort(T *, unsigned int);
	~HeapSort(void) { _array = NULL; };
	void Sort(void);
	void Print(ostream &);
};

template<class T> HeapSort<T>::HeapSort(T * A, unsigned int L)
{
	_array = A;
	_length = L;
	_height = Height();
}

// 2^(Height - 1) - 1 < _length <= 2^Height - 1
template<class T> unsigned int HeapSort<T>::Height(void)
{
	unsigned int x = _length;
	unsigned int h = 0;
	while (x > 0) {
		x = x >> 1;
		h ++;
	}
	return h;
}

template<class T> void HeapSort<T>::Swap(unsigned int i, unsigned int j)
{
	if (i >= _length || j >= _length || i == j) return;
	T temp = _array[i];
	_array[i] = _array[j];
	_array[j] = temp;
}

// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
// The assumption is the subtrees rooted at i are already heapified.
template<class T> void HeapSort<T>::Heapify(unsigned int i, unsigned length)
{
	if (i >= length) return;
	unsigned int max = i;
	unsigned int l = Left(i);
	if (l < length && _array[l] > _array[i]) {
		max = l;
	}
	unsigned int r = Right(i);
	if (r < length && _array[r] > _array[max]) {
		max = r;
	}
	if (max != i) {
		Swap(i, max);
		Heapify(max, length);
	}
}

template<class T> void HeapSort<T>::Heapify()
{
	// Do not define i as unsigned int, otherwise the for loop will continue forever 
	// because i is unsigned and thus i is always non-negative. When i = 0, (i --) becomes 4294967295
	//for (unsigned int i = ((1 << (_height - 1)) - 2) ; i >= 0; i --) {
	for (long long i = ((1 << (_height - 1)) - 2) ; i >= 0; i --) {
		Heapify((unsigned int)i, _length);
	}
}

template<class T> void HeapSort<T>::Sort()
{
	// Construct the array into a heap
	Heapify();

	// Sort
	for (long long i = _length - 1; i >= 0; i --) {
		// Swap the current maximum value, which is at position 0, to position i.
		// The range [i, length - 1] is sorted.
		Swap(0, (unsigned int)i);
		// Rearrange [0, i - 1] so that it is a heap
		Heapify(0, (unsigned int)i);
	}
}

template<class T> void HeapSort<T>::Print(ostream & os)
{
	for (unsigned int i = 1; i <= _height; i ++) {
		for (unsigned int j = ((1 << (i - 1)) - 1); j <= (unsigned int)((1 << i) - 2); j ++) {
			os << _array[j] << " ";
		}
		os << endl;
	}
}

template __declspec(dllexport) class HeapSort<int>;
template __declspec(dllexport) class HeapSort<double>;

