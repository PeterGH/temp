#pragma once

#include <iostream>
#include <ppl.h>

using namespace std;
using namespace Concurrency;

template<class T> class QuickSort {
private:
	static int Partition(T *, int, int);
	static void Sort(T *, int, int);
	static void PSort(T *, int, int);
public:
	static void Sort(T *, int);
	static void ParallelSort(T *, int);
	static void Print(T *, int, int);
};

template<class T> int QuickSort<T>::Partition(T * A, int l, int h)
{
	if (l >= 0 && h >= 0 && l < h) {
		int i = l - 1;
		for (int j = l; j < h; j ++) {
			if (A[j] < A[h]) {
				i ++;
				swap(A[i], A[j]);
			}
		}
		i ++;
		swap(A[i], A[h]);
		return i;
	} else {
		return -1;
	}
}

template<class T> void QuickSort<T>::Sort(T * A, int l, int h)
{
	if (l >= 0 && h >= 0 && l < h) {
		int m = Partition(A, l, h);
		if (l <= m && m <= h) {
			Sort(A, l, m - 1);
			Sort(A, m + 1, h);
		}		
	}
}

template<class T> void QuickSort<T>::PSort(T * A, int l, int h)
{
	if (l >= 0 && h >= 0 && l < h) {
		int m = Partition(A, l, h);
		if (l <= m && m <= h) {
			parallel_invoke(
				[&A, l, m]{PSort(A, l, m - 1);},
				[&A, m, h]{PSort(A, m + 1, h);}
			);
		}		
	}
}

template<class T> void QuickSort<T>::Sort(T * A, int L)
{
	if (L > 1) {
		Sort(A, 0, L - 1);
	}
}

template<class T> void QuickSort<T>::ParallelSort(T * A, int L)
{
	if (L > 1) {
		PSort(A, 0, L - 1);
	}
}

template<class T> void QuickSort<T>::Print(T * A, int l, int h)
{	
	for (int i = l; i <= h; i ++) {
        cout << A[i] << " ";
	}
	cout << endl;
}


template __declspec(dllexport) class QuickSort<int>;
template __declspec(dllexport) class QuickSort<double>;