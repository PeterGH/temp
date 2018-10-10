#pragma once
#include <cstring>
#include <array>

__declspec(dllexport) const char* MyStrStr(const char *, const char *);

__declspec(dllexport) size_t RemoveDupChar(char *, size_t);

template<class T> void InsertionSort(T *, int);
template __declspec(dllexport) void InsertionSort(int *, int);
template __declspec(dllexport) void InsertionSort(double *, int);

template<class T> void InsertionSortRecursively(T *, int);
template __declspec(dllexport) void InsertionSortRecursively(int *, int);
template __declspec(dllexport) void InsertionSortRecursively(double *, int);

template<class T> int FindPositionToInsert(T, const T *, int);
template __declspec(dllexport) int FindPositionToInsert(int, const int *, int);
template __declspec(dllexport) int FindPositionToInsert(double, const double *, int);

template<class T> void SelectionSort(T *, int);
template __declspec(dllexport) void SelectionSort(int *, int);
template __declspec(dllexport) void SelectionSort(double *, int);

template<class T> void Merge(T *, int, int, int);
template __declspec(dllexport) void Merge(int *, int, int, int);
template __declspec(dllexport) void Merge(double *, int, int, int);

template<class T> void MergeSort(T *, int, int);
template __declspec(dllexport) void MergeSort(int *, int, int);
template __declspec(dllexport) void MergeSort(double *, int, int);

template<class T> __declspec(dllexport) int Min(const T *, int);
template __declspec(dllexport) int Min(const int *, int);
template __declspec(dllexport) int Min(const double *, int);

template<class T> void Swap(T *, int, int);
template __declspec(dllexport) void Swap(int *, int, int);
template __declspec(dllexport) void Swap(double *, int, int);

template<class T> void PrintArray(const T *, int);
template __declspec(dllexport) void PrintArray(const int *, int);
template __declspec(dllexport) void PrintArray(const double *, int);

template<class T> bool CompareArray(const T *, const T *, int);
template __declspec(dllexport) bool CompareArray(const int *, const int *, int);
template __declspec(dllexport) bool CompareArray(const double *, const double *, int);

template<class T> int LinearSearch(T, const T *, int);
template __declspec(dllexport) int LinearSearch(int, const int *, int);
template __declspec(dllexport) int LinearSearch(double, const double *, int);

template<class T> int BinarySearch(T, const T *, int);
template __declspec(dllexport) int BinarySearch(int, const int *, int);
template __declspec(dllexport) int BinarySearch(double, const double *, int);

template<class T> int BinarySearchRecursively(T, const T *, int, int);
template __declspec(dllexport) int BinarySearchRecursively(int, const int *, int, int);
template __declspec(dllexport) int BinarySearchRecursively(double, const double *, int, int);



