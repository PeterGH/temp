#pragma once
#include <iostream>
using namespace std;

template<class T> class BitonicSort {
private:
	static void Compare(T *, int, int, bool);
	static void Merge(T *, int, int, bool);
	static void Sort(T *, int, int, bool);
	
public:
	static void Sort(T *, int);
	static void Print(T *, int, int);
};
	
// Comparator function for the bitonic sort algorithm.
template <class T> void BitonicSort<T>::Compare(T * items, int i, int j, bool dir)
{
	cout << "Compare(" << i << "," << j << ")=>";
	cout << "(" << items[i] << "," << items[j] << ")";
	if (dir == (items[i] > items[j])) {
		swap(items[i], items[j]);
		cout << "=>(" << items[i] << "," << items[j] << ")";
	}	
}

// Sorts a bitonic sequence in the specified order.
template <class T> void BitonicSort<T>::Merge(T * items, int index, int count, bool dir)
{
	cout << "Merge(" << index << "," << count << ")=>";
	if (count > 1) {
		int m = count >> 1;
		for (int i = index; i < index + m; ++i) {
			Compare(items, i, i + m, dir);
		}
		Merge(items, index, m, dir);
		Merge(items, index + m, count - m, dir);
	}	
	Print(items, index, count);
}

// Sorts the given sequence in the specified order.
template <class T> void BitonicSort<T>::Sort(T * items, int index, int count, bool dir)
{
	cout << "Sort(" << index << "," << count << ")=>";
	if (count > 1) {
		// Divide the array into two partitions and then sort 
		// the partitions in different directions.
		int m = count >> 1;
		
		Sort(items, index, m, true);
		Sort(items, index + m, count - m, false);
		
		// Merge the results.
		Merge(items, index, count, dir);
	}
	Print(items, index, count);
}

// Sorts the given sequence in increasing order.
template <class T> void BitonicSort<T>::Sort(T * items, int size)
{
	Print(items, 0, size);
    Sort(items, 0, size, true);
	Print(items, 0, size);
}

template<class T> void BitonicSort<T>::Print(T * items, int index, int count)
{	
	for (int i = index; i < (index + count); i ++) {
        cout << items[i] << " ";
	}
	cout << endl;
}

template __declspec(dllexport) class BitonicSort<int>;
template __declspec(dllexport) class BitonicSort<double>;
