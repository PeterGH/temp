#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include "..\Algorithm\BinarySearch.h"
#include "..\Algorithm\InsertionSort.h"
#include "..\Algorithm\MergeSort.h"
#include "..\Algorithm\Array.h"
#include "..\Algorithm\MRInteger.h"
#include "..\Algorithm\String.h"
#include "..\Algorithm\HeapSort.h"
#include "..\Algorithm\QuickSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(ArrayTest_MaxSubArray)
		{
			int A1[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
			int L = sizeof(A1)/sizeof(A1[0]);
			int l, r;
			long long sum;

			auto check = [&](int el, int er, int es) -> void {
				Assert::AreEqual<int>(el, l);
				Assert::AreEqual<int>(er, r);
				Assert::AreEqual<int>(es, (int)sum);
			};

			My::Array::MaxSubArray(A1, L, l, r, sum);
			check(7, 10, 43);

			My::Array::MaxSubArray(A1, 1, l, r, sum);
			check(0, 0, 13);

			My::Array::MaxSubArray(A1, 2, l, r, sum);
			check(0, 0, 13);

			My::Array::MaxSubArray(A1, 3, l, r, sum);
			check(0, 0, 13);

			My::Array::MaxSubArray(A1, 4, l, r, sum);
			check(3, 3, 20);

			My::Array::MaxSubArray(A1, 5, l, r, sum);
			check(3, 3, 20);

			My::Array::MaxSubArray(A1, 8, l, r, sum);
			check(3, 3, 20);

			int A2[] = {13, 3, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 4, 7};
			My::Array::MaxSubArray(A2, L, l, r, sum);
			check(0, L-1, 213);

			My::Array::MaxSubArray(A2, 1, l, r, sum);
			check(0, 0, 13);

			My::Array::MaxSubArray(A2, 2, l, r, sum);
			check(0, 1, 16);

			My::Array::MaxSubArray(A2, 3, l, r, sum);
			check(0, 2, 41);

			int A3[] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
			My::Array::MaxSubArray(A3, L, l, r, sum);
			check(1, 1, -3);

			My::Array::MaxSubArray(A3, 1, l, r, sum);
			check(0, 0, -13);

			My::Array::MaxSubArray(A3, 2, l, r, sum);
			check(1, 1, -3);

			int A4[] = {0, 0, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
			My::Array::MaxSubArray(A4, L, l, r, sum);
			check(0, 0, 0);

			My::Array::MaxSubArray(A4, 1, l, r, sum);
			check(0, 0, 0);

			int A5[] = {0, 0, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 0, 0};
			My::Array::MaxSubArray(A5, L, l, r, sum);
			check(2, 13, 186);

			My::Array::MaxSubArray(A5, 1, l, r, sum);
			check(0, 0, 0);

			int A6[] = {-25, -20, -3, 0, 0, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
			My::Array::MaxSubArray(A6, L, l, r, sum);
			check(3, 3, 0);

			My::Array::MaxSubArray(A6, 1, l, r, sum);
			check(0, 0, -25);

			My::Array::MaxSubArray(A6, 2, l, r, sum);
			check(1, 1, -20);

			My::Array::MaxSubArray(A6, 5, l, r, sum);
			check(3, 3, 0);

			int A7[] = {1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, -7};
			My::Array::MaxSubArray(A7, L, l, r, sum);
			check(0, 2, 3);

			My::Array::MaxSubArray(A7, 6, l, r, sum);
			check(0, 2, 3);

			int A8[] = {1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, 7};
			My::Array::MaxSubArray(A8, L, l, r, sum);
			check(L-1, L-1, 7);
		}

		TEST_METHOD(BinarySearchTest)
		{
			int I2[] = {1, 1, 3, 3, 7, 8, 34, 35, 42, 43, 64, 445, 3556, 8769, 96656532};
			int L = sizeof(I2)/sizeof(I2[0]);
			Assert::AreEqual<int>(0, My::BinarySearch<int>::Search(1, I2, 1));
			Assert::AreEqual<int>(0, My::BinarySearch<int>::SearchRecursively(1, I2, 0, 1));
			Assert::AreEqual<int>(0, My::BinarySearch<int>::Search(1, I2, L));
			Assert::AreEqual<int>(0, My::BinarySearch<int>::SearchRecursively(1, I2, 0, L - 1));
			Assert::AreNotEqual<int>(1, My::BinarySearch<int>::Search(1, I2, L));
			Assert::AreNotEqual<int>(1, My::BinarySearch<int>::SearchRecursively(1, I2, 0, L - 1));
			Assert::AreEqual<int>(2, My::BinarySearch<int>::Search(3, I2, L));
			Assert::AreEqual<int>(2, My::BinarySearch<int>::SearchRecursively(3, I2, 0, L - 1));
			Assert::AreNotEqual<int>(3, My::BinarySearch<int>::Search(3, I2, L));
			Assert::AreNotEqual<int>(3, My::BinarySearch<int>::SearchRecursively(3, I2, 0, L - 1));
			Assert::AreEqual<int>(9, My::BinarySearch<int>::Search(43, I2, L));
			Assert::AreEqual<int>(9, My::BinarySearch<int>::SearchRecursively(43, I2, 0, L - 1));
			Assert::AreEqual<int>(L - 1, My::BinarySearch<int>::Search(96656532, I2, L));
			Assert::AreEqual<int>(L - 1, My::BinarySearch<int>::SearchRecursively(96656532, I2, 0, L - 1));
			Assert::AreEqual<int>(-1, My::BinarySearch<int>::Search(222, I2, L));
			Assert::AreEqual<int>(-1, My::BinarySearch<int>::SearchRecursively(222, I2, 0, L - 1));
		}

		TEST_METHOD(HeapSortTest)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);

			std::vector<int> V1;
			for (int i = 0; i < L; i++) {
				V1.push_back(I1[i]);
			}

			My::HeapSort<int>::Sort(I1, L);

			std::make_heap(V1.begin(), V1.end());
			std::sort_heap(V1.begin(), V1.end());

			for (int i = 0; i < L; i++) {
				Assert::AreEqual<int>(V1[i], I1[i]);
			}		
		}

		TEST_METHOD(HeapSortTest_Heapify)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int I2[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);

			My::HeapSort<int>::Heapify(I1, L);
			My::HeapSort<int>::ParallelHeapify(I2, L);

			for (int i = 0; i < L; i++) {
				Assert::AreEqual<int>(I1[i], I2[i]);
			}
		}

		TEST_METHOD(InsertionSortTest_RecursiveSort)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);

			std::vector<int> V1;
			for (int i = 0; i < L; i++) {
				V1.push_back(I1[i]);
			}

			My::InsertionSort<int>::RecursiveSort(I1, L);

			std::sort(V1.begin(), V1.end());

			for (int i = 0; i < L; i++) {
				Assert::AreEqual<int>(V1[i], I1[i]);
			}			
		}

		TEST_METHOD(InsertionSortTest_Sort)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);

			std::vector<int> V1;
			for (int i = 0; i < L; i++) {
				V1.push_back(I1[i]);
			}

			My::InsertionSort<int>::Sort(I1, L);

			std::sort(V1.begin(), V1.end());

			for (int i = 0; i < L; i++) {
				Assert::AreEqual<int>(V1[i], I1[i]);
			}			
		}

		TEST_METHOD(MergeSortTest_CountInversions)
		{
			auto check = [](int * A, int L, int expected) -> void {
				int count = My::MergeSort<int>::CountInversions(A, L);
				Assert::AreEqual<int>(expected, count);
			};

			int I1[] = {0};
			int L = sizeof(I1)/sizeof(I1[0]);
			check(I1, L, 0);

			int I2[] = {0, 1};
			L = sizeof(I2)/sizeof(I2[0]);
			check(I2, L, 0);

			int I3[] = {1, 0};
			L = sizeof(I3)/sizeof(I3[0]);
			check(I3, L, 1);

			int I4[] = {0, 1, 2};
			L = sizeof(I4)/sizeof(I4[0]);
			check(I4, L, 0);

			int I5[] = {1, 0, 2};
			L = sizeof(I5)/sizeof(I5[0]);
			check(I5, L, 1);

			int I6[] = {2, 0, 1};
			L = sizeof(I6)/sizeof(I6[0]);
			check(I6, L, 2);

			int I7[] = {2, 1, 0};
			L = sizeof(I7)/sizeof(I7[0]);
			check(I7, L, 3);

			int I8[] = {0, 2, 1};
			L = sizeof(I8)/sizeof(I8[0]);
			check(I8, L, 1);

			int I9[] = {1, 2, 0};
			L = sizeof(I9)/sizeof(I9[0]);
			check(I9, L, 2);

			int I10[] = {3, 2, 1, 0};
			L = sizeof(I10)/sizeof(I10[0]);
			check(I10, L, 6);

			int I11[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
			L = sizeof(I11)/sizeof(I11[0]);
			check(I11, L, 45);
		}

		TEST_METHOD(MergeSortTest_ParallelSort)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);

			std::vector<int> V1;
			for (int i = 0; i < L; i++) {
				V1.push_back(I1[i]);
			}

			My::MergeSort<int>::ParallelSort(I1, L);

			std::sort(V1.begin(), V1.end());

			for (int i = 0; i < L; i++) {
				Assert::AreEqual<int>(V1[i], I1[i]);
			}		
		}

		TEST_METHOD(MergeSortTest_Sort)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);

			std::vector<int> V1;
			for (int i = 0; i < L; i++) {
				V1.push_back(I1[i]);
			}

			My::MergeSort<int>::Sort(I1, L);

			std::sort(V1.begin(), V1.end());

			for (int i = 0; i < L; i++) {
				Assert::AreEqual<int>(V1[i], I1[i]);
			}		
		}

		TEST_METHOD(MRIntegerTest)
		{
			auto check = [](My::MRInteger & c, int e0, int e1, int e2) -> void {
				Assert::AreEqual<int>(e0, c[0]);
				Assert::AreEqual<int>(e1, c[1]);
				Assert::AreEqual<int>(e2, c[2]);			
			};

			unsigned int c[] = {1, 3, 2};

			My::MRInteger ctr(c, 3);
			Assert::AreEqual<int>(6, (int)ctr.Max());
			check(ctr, 0, 0, 0);

			ctr ++;
			check(ctr, 0, 1, 0);

			++ ctr;
			check(ctr, 0, 2, 0);

			My::MRInteger ctr2 = ctr;
			check(ctr2, 0, 2, 0);

			ctr2 ++;
			++ ctr2;
			check(ctr2, 0, 1, 1);

			ctr2 ++;
			++ ctr2;
			check(ctr2, 0, 0, 0);

			ctr2 ++;
			++ ctr2;
			check(ctr2, 0, 2, 0);

			My::MRInteger ctr3(ctr2);
			check(ctr3, 0, 2, 0);

			ctr = ctr3 ++;
			check(ctr, 0, 2, 0);
			check(ctr3, 0, 0, 1);

			ctr3.Reset();
			check(ctr3, 0, 0, 0);

			My::MRInteger ctr4(ctr3);
			check(ctr4, 0, 0, 0);

			ctr4 = My::MRInteger(ctr);
			check(ctr4, 0, 2, 0);
		}

		TEST_METHOD(MRIntegerTest_Equal)
		{
			unsigned int c[] = {1, 3, 2};
			My::MRInteger ctr(c, 3);

			unsigned int c1[] = {1, 3, 2, 1};
			My::MRInteger ctr1(c1, 4);

			Assert::IsFalse(ctr < ctr1);
			Assert::IsFalse(ctr1 < ctr);
			Assert::IsTrue(ctr == ctr1);
			Assert::IsTrue(ctr1 == ctr);
			Assert::IsFalse(ctr != ctr1);
			Assert::IsFalse(ctr1 != ctr);
		}

		TEST_METHOD(MRIntegerTest_GreaterThan)
		{
			unsigned int c[] = {3, 3, 3};
			My::MRInteger ctr(c, 3);

			unsigned int c1[] = {3, 3, 3, 3};
			My::MRInteger ctr1(c1, 4);

			ctr ++;
			Assert::IsTrue(ctr > ctr1);
			Assert::IsFalse(ctr1 > ctr);
			ctr1++;
			ctr1++;
			Assert::IsFalse(ctr > ctr1);
			Assert::IsTrue(ctr <= ctr1);
			Assert::IsTrue(ctr1 > ctr);
			Assert::IsFalse(ctr1 <= ctr);

			unsigned int d[] = {0, 1, 1};
			unsigned int d1[] = {0, 1, 1, 1};
			ctr.Set(d, 3);
			ctr1.Set(d1, 4);
			Assert::IsTrue(ctr1 > ctr);
			Assert::IsFalse(ctr1 <= ctr);
			Assert::IsFalse(ctr > ctr1);
			Assert::IsTrue(ctr <= ctr1);

			unsigned int d2[] = {0, 1, 2};
			unsigned int d3[] = {0, 1, 1, 1};
			ctr.Set(d2, 3);
			ctr1.Set(d3, 4);
			Assert::IsTrue(ctr1 > ctr);
			Assert::IsFalse(ctr1 <= ctr);
			Assert::IsFalse(ctr > ctr1);
			Assert::IsTrue(ctr <= ctr1);

			unsigned int d4[] = {0, 1, 1, 0};
			ctr1.Set(d4, 4);
			Assert::IsFalse(ctr1 > ctr);
			Assert::IsTrue(ctr1 <= ctr);
			Assert::IsTrue(ctr > ctr1);
			Assert::IsFalse(ctr <= ctr1);
		}

		TEST_METHOD(MRIntegerTest_LessThan)
		{
			unsigned int c[] = {1, 3, 3};
			My::MRInteger ctr(c, 3);

			unsigned int c1[] = {1, 3, 3, 2};
			My::MRInteger ctr1(c1, 4);

			ctr ++;
			Assert::IsFalse(ctr < ctr1);
			Assert::IsTrue(ctr1 < ctr);
			ctr1++;
			ctr1++;
			Assert::IsTrue(ctr < ctr1);
			Assert::IsFalse(ctr >= ctr1);
			Assert::IsFalse(ctr1 < ctr);
			Assert::IsTrue(ctr1 >= ctr);

			unsigned int d[] = {0, 1, 1};
			unsigned int d1[] = {0, 1, 1, 1};
			ctr.Set(d, 3);
			ctr1.Set(d1, 4);
			Assert::IsTrue(ctr < ctr1);
			Assert::IsFalse(ctr >= ctr1);
			Assert::IsFalse(ctr1 < ctr);
			Assert::IsTrue(ctr1 >= ctr);

			unsigned int d2[] = {0, 1, 2};
			unsigned int d3[] = {0, 1, 1, 1};
			ctr.Set(d2, 3);
			ctr1.Set(d3, 4);
			Assert::IsTrue(ctr < ctr1);
			Assert::IsFalse(ctr >= ctr1);
			Assert::IsFalse(ctr1 < ctr);
			Assert::IsTrue(ctr1 >= ctr);

			unsigned int d4[] = {0, 1, 1, 0};
			ctr1.Set(d4, 4);
			Assert::IsFalse(ctr < ctr1);
			Assert::IsTrue(ctr >= ctr1);
			Assert::IsTrue(ctr1 < ctr);
			Assert::IsFalse(ctr1 >= ctr);
		}

		TEST_METHOD(QuickSortTest)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int I2[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int I3[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);

			std::vector<int> V1;
			for (int i = 0; i < L; i++) {
				V1.push_back(I1[i]);
			}

			My::QuickSort<int>::Sort(I1, L);
			My::QuickSort<int>::ParallelSort(I2, L);
			My::QuickSort<int>::RandomSort(I3, L);

			std::sort(V1.begin(), V1.end());

			for (int i = 0; i < L; i++) {
				Assert::AreEqual<int>(V1[i], I1[i]);
				Assert::AreEqual<int>(V1[i], I2[i]);
				Assert::AreEqual<int>(V1[i], I3[i]);
			}		
		}

		TEST_METHOD(QuickSortTest_Select)
		{
			int I1[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};
			int L = sizeof(I1)/sizeof(I1[0]);
			int e = My::QuickSort<int>::RandomSelect(I1, L, 0);
			Assert::AreEqual<int>(1, e);

			int I2[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I2, L, 1);
			Assert::AreEqual<int>(1, e);

			int I3[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I3, L, 2);
			Assert::AreEqual<int>(3, e);

			int I4[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I4, L, 3);
			Assert::AreEqual<int>(3, e);

			int I5[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I5, L, 4);
			Assert::AreEqual<int>(7, e);

			int I6[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I6, L, 5);
			Assert::AreEqual<int>(8, e);

			int I7[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I7, L, 6);
			Assert::AreEqual<int>(34, e);

			int I8[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I8, L, 7);
			Assert::AreEqual<int>(35, e);

			int I9[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I9, L, 8);
			Assert::AreEqual<int>(42, e);

			int I10[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I10, L, 9);
			Assert::AreEqual<int>(43, e);

			int I11[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I11, L, 10);
			Assert::AreEqual<int>(64, e);

			int I12[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I12, L, 11);
			Assert::AreEqual<int>(445, e);

			int I13[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I13, L, 12);
			Assert::AreEqual<int>(3556, e);

			int I14[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I14, L, 13);
			Assert::AreEqual<int>(8769, e);

			int I15[] = {3,43,42,1,3,3556,7,34,8,8769,96656532,1,445,35,64};			
			e = My::QuickSort<int>::RandomSelect(I15, L, 14);
			Assert::AreEqual<int>(96656532, e);
		}

		TEST_METHOD(StringTest)
		{
			{
				string e = My::String::Empty<char>();
				Assert::AreEqual<int>(0, e.length());
				Assert::AreEqual<string>("", e);
				string s;
				Assert::AreEqual<string>(s, e);
			} 
			{
				wstring e = My::String::Empty<wchar_t>();
				Assert::AreEqual<int>(0, e.length());
				Assert::AreEqual<wstring>(L"", e);
				wstring s;
				Assert::AreEqual<wstring>(s, e);
			} 
			{
				string i = "AFf34z df  g3zds^(%98FSDSFE";
				char * pi = (char *)i.c_str();
				string o = My::String::ToLower(i);
				Assert::AreEqual<int>(strlen(pi), o.length());
				Assert::AreEqual<int>(0, o.compare("aff34z df  g3zds^(%98fsdsfe"));
			}
			{
				wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
				wchar_t * pi = (wchar_t *)i.c_str();
				wstring o = My::String::ToLower(i);
				Assert::AreEqual<int>(wcslen(pi), o.length());
				Assert::AreEqual<wstring>(L"aff34z df  g3zds^(%98fsdsfe", o);
			} 
			{
				string i = "AFf34z df  g3zds^(%98FSDSFE";
				char * pi = (char *)i.c_str();
				int li = strlen(pi);
				wstring o = My::String::ToWString(pi);
				Assert::AreEqual<int>(li, o.size());
				Assert::AreEqual<int>(0, o.compare(L"AFf34z df  g3zds^(%98FSDSFE"));
			} 
			{
				wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
				wchar_t * pi = (wchar_t *)i.c_str();
				int li = wcslen(pi);
				string o = My::String::ToString(pi);
				char * p = (char *)o.c_str();
				Assert::AreEqual<int>(li, strlen(p));
				Assert::AreEqual<string>("AFf34z df  g3zds^(%98FSDSFE", o);
			} 
			{
				wstring i = L"AFf34z df  g3zds^(%98FSDSFE";
				string o = My::String::ToString(i);
				Assert::AreEqual<string>("AFf34z df  g3zds^(%98FSDSFE", o);
			}
			{
				string i = "AFf34z df  g3zds^(%98FSDSFE";
				wstring o = My::String::ToWString(i);
				Assert::AreEqual<wstring>(L"AFf34z df  g3zds^(%98FSDSFE", o);
			}
			{
				string s = My::String::Format("Hello World!");
				Assert::AreEqual<string>("Hello World!", s);
				s = My::String::Format("Hello %s!", "Peter");
				Assert::AreEqual<string>("Hello Peter!", s);
				s = My::String::Format("Hello %s! You are %d years old.", "Peter", 18);
				Assert::AreEqual<string>("Hello Peter! You are 18 years old.", s);
			}
			{
				wstring s = My::String::Format(L"Hello World!");
				Assert::AreEqual<wstring>(L"Hello World!", s);
				s = My::String::Format(L"Hello %s!", L"Peter");
				Assert::AreEqual<wstring>(L"Hello Peter!", s);
				s = My::String::Format(L"Hello %s! You are %d years old.", L"Peter", 18);
				Assert::AreEqual<wstring>(L"Hello Peter! You are 18 years old.", s);
			}
			{
				string s1 = "Hello World!";
				string s2 = "Hello";
				Assert::IsTrue(My::String::StartsWith(s1, s2));
				s2 = "hello w";
				Assert::IsTrue(My::String::StartsWith(s1, s2));
				s2 = "World";
				Assert::IsFalse(My::String::StartsWith(s1, s2));
				s2 = "Hellow World! Great!";
				Assert::IsFalse(My::String::StartsWith(s1, s2));
				s2 = "";
				Assert::IsTrue(My::String::StartsWith(s1, s2));
				s1 = "";
				s2 = "Hello";
				Assert::IsFalse(My::String::StartsWith(s1, s2));
			}
			{
				wstring s1 = L"Hello World!";
				wstring s2 = L"Hello";
				Assert::IsTrue(My::String::StartsWith(s1, s2));
				s2 = L"hello w";
				Assert::IsTrue(My::String::StartsWith(s1, s2));
				s2 = L"World";
				Assert::IsFalse(My::String::StartsWith(s1, s2));
				s2 = L"Hellow World! Great!";
				Assert::IsFalse(My::String::StartsWith(s1, s2));
				s2 = L"";
				Assert::IsTrue(My::String::StartsWith(s1, s2));
				s1 = L"";
				s2 = L"Hello";
				Assert::IsFalse(My::String::StartsWith(s1, s2));
			}
			{
				string s1 = "Hello World!";
				string s2 = "Hello";
				Assert::IsFalse(My::String::EndsWith(s1, s2));
				s2 = "!";
				Assert::IsTrue(My::String::EndsWith(s1, s2));
				s2 = "world!";
				Assert::IsTrue(My::String::EndsWith(s1, s2));
				s2 = "Hellow World! Great!";
				Assert::IsFalse(My::String::EndsWith(s1, s2));
				s2 = "";
				Assert::IsTrue(My::String::EndsWith(s1, s2));
				s1 = "";
				s2 = "Hello";
				Assert::IsFalse(My::String::EndsWith(s1, s2));
			}
			{
				wstring s1 = L"Hello World!";
				wstring s2 = L"Hello";
				Assert::IsFalse(My::String::EndsWith(s1, s2));
				s2 = L"!";
				Assert::IsTrue(My::String::EndsWith(s1, s2));
				s2 = L"world!";
				Assert::IsTrue(My::String::EndsWith(s1, s2));
				s2 = L"Hellow World! Great!";
				Assert::IsFalse(My::String::EndsWith(s1, s2));
				s2 = L"";
				Assert::IsTrue(My::String::EndsWith(s1, s2));
				s1 = L"";
				s2 = L"Hello";
				Assert::IsFalse(My::String::EndsWith(s1, s2));
			}
			{
				string s1 = "Hello World!";
				Assert::IsTrue(My::String::Contains(s1, s1));
				string s2 = "Hello";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = "ello w";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = "World";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = "Hellow World! Great!";
				Assert::IsFalse(My::String::Contains(s1, s2));
				s2 = " ";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = "";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = "  ";
				Assert::IsFalse(My::String::Contains(s1, s2));
			}
			{
				wstring s1 = L"Hello World!";
				Assert::IsTrue(My::String::Contains(s1, s1));
				wstring s2 = L"Hello";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = L"ello w";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = L"World";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = L"Hellow World! Great!";
				Assert::IsFalse(My::String::Contains(s1, s2));
				s2 = L" ";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = L"";
				Assert::IsTrue(My::String::Contains(s1, s2));
				s2 = L"  ";
				Assert::IsFalse(My::String::Contains(s1, s2));
			}
			{
				wstring s1 = L"  Hello World!*X&&**";
				wstring s2 = My::String::TrimStart(s1, L" ");
				Assert::AreEqual<wstring>(L"Hello World!*X&&**", s2);
				wstring s3 = My::String::TrimStart(s2, L" ");
				Assert::AreEqual<wstring>(s2, s3);
				wstring s4 = My::String::TrimStart(s3, L"Hello ");
				Assert::AreEqual<wstring>(L"World!*X&&**", s4);
				wstring s5 = My::String::TrimStart<wchar_t>(L"", L"H");
				Assert::AreEqual<wstring>(L"", s5);
			}
			{
				string s1 = "  Hello World!*X&&**";
				string s2 = My::String::TrimStart(s1, " ");
				Assert::AreEqual<string>("Hello World!*X&&**", s2);
				string s3 = My::String::TrimStart(s2, " ");
				Assert::AreEqual<string>(s2, s3);
				string s4 = My::String::TrimStart(s3, "Hello ");
				Assert::AreEqual<string>("World!*X&&**", s4);
				string s5 = My::String::TrimStart<char>("", "H");
				Assert::AreEqual<string>("", s5);
			}
			{
				wstring s1 = L"  Hello World!*X&&**";
				wstring s2 = My::String::TrimEnd(s1, L" ");
				Assert::AreEqual<wstring>(s1, s2);
				wstring s3 = My::String::TrimEnd(s2, L"*&");
				Assert::AreEqual<wstring>(L"  Hello World!*X", s3);
				wstring s4 = My::String::TrimEnd(s3, L" World!*X");
				Assert::AreEqual<wstring>(L"  He", s4);
				wstring s5 = My::String::TrimEnd<wchar_t>(L"", L"*");
				Assert::AreEqual<wstring>(L"", s5);
			}
			{
				string s1 = "  Hello World!*X&&**";
				string s2 = My::String::TrimEnd(s1, " ");
				Assert::AreEqual<string>(s1, s2);
				string s3 = My::String::TrimEnd(s2, "*&");
				Assert::AreEqual<string>("  Hello World!*X", s3);
				string s4 = My::String::TrimEnd(s3, " World!*X");
				Assert::AreEqual<string>("  He", s4);
				string s5 = My::String::TrimEnd<char>("", "*");
				Assert::AreEqual<string>("", s5);
			}
			{
				wstring s1 = L"  Hello World!*X&&**";
				wstring s2 = My::String::Trim(s1, L" ");
				Assert::AreEqual<wstring>(L"Hello World!*X&&**", s2);
				wstring s3 = My::String::Trim(s2, L" ");
				Assert::AreEqual<wstring>(s3, s2);
				wstring s4 = My::String::Trim(s3, L"*&H");
				Assert::AreEqual<wstring>(L"ello World!*X", s4);
				wstring s5 = My::String::Trim<wchar_t>(L"", L" *");
				Assert::AreEqual<wstring>(L"", s5);
			}
			{
				string s1 = "  Hello World!*X&&**";
				string s2 = My::String::Trim(s1, " ");
				Assert::AreEqual<string>("Hello World!*X&&**", s2);
				string s3 = My::String::Trim(s2, " ");
				Assert::AreEqual<string>(s3, s2);
				string s4 = My::String::Trim(s3, "*&H");
				Assert::AreEqual<string>("ello World!*X", s4);
				string s5 = My::String::Trim<char>("", " *");
				Assert::AreEqual<string>("", s5);
			}
		}
	};
}