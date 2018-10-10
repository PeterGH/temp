#pragma once

#include <memory>
#include "MRInteger.h"

namespace Test {
	class Permutation {

	private:
		// Keep the permutation state
		MRInteger * _counter;
		template<class T> static void Swap(T * buffer, unsigned int position1, unsigned int position2);
	public:
		__declspec(dllexport) Permutation(unsigned int length);
		__declspec(dllexport) ~Permutation(void);

		// Permutation the buffer.
		template<class T> void Next(T * buffer, int length);
		template<class T> void Next(T * input, T * output, int length);
		template<class T> static void Random(T * buffer, int length);
		template<class T> static void Random(T * input, T * output, int length);
		// Current counter value at position index
		__declspec(dllexport) const unsigned int operator[](unsigned int index) const { return (*_counter)[index]; }
		// maximum number of permutations
		__declspec(dllexport) const unsigned long Max(void) const { return _counter->Max(); }

		// Given a collection of numbers, return all possible permutations. For example,
		// [1,2,3] have the following permutations:
		// [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
		template<class T> static vector<vector<T>> All(vector<T> & input);

		// Given a collection of numbers that might contain duplicates, return all possible unique permutations.
		// For example,
		// [1,1,2] have the following unique permutations:
		// [1,1,2], [1,2,1], and [2,1,1].
		template<class T> static vector<vector<T>> Unique(vector<T> & input);

		// The set {1, 2, 3, ..., n} contains a total of n! unique permutations.
		// By listing and labeling all of the permutations in order,
		// We get the following sequence (ie, for n = 3):
		// 1. "123"
		// 2. "132"
		// 3. "213"
		// 4. "231"
		// 5. "312"
		// 6. "321"
		// Given n and k, return the k-th permutation sequence.
		// Note: Given n will be between 1 and 9 inclusive.
		__declspec(dllexport) static string GetPermutation(int n, int k);

		// Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
		// If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
		// The replacement must be in-place, do not allocate extra memory.
		// Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
		// 1,2,3 -> 1,3,2
		// 3,2,1 -> 1,2,3
		// 1,1,5 -> 1,5,1
		template<class T> static void NextPermutation(vector<T> & input);
	};

	template<class T> void Permutation::Swap(T * buffer, unsigned int position1, unsigned int position2)
	{
		if (position1 != position2) {
			T t = buffer[position1];
			buffer[position1] = buffer[position2];
			buffer[position2] = t;
		}
	}
	
	template<class T> void Permutation::Next(T * buffer, int length)
	{
		int len = min(length, (int)_counter->Length());
		for (int i = len - 1; i >= 0; i--) {
			Swap(buffer, i, i - (*_counter)[i]);
		}

		// Prepare for the next permutation
		(*_counter)++;
	}

	template<class T> void Permutation::Next(T * input, T * output, int length)
	{
		memcpy(output, input, length * sizeof(T));
		Next(output, length);
	}

	template<class T> void Permutation::Random(T * buffer, int length)
	{
		for (int i = length - 1; i >= 0; i--) {
			// The rand function returns a pseudorandom integer in the range 0 (inclusive) to RAND_MAX (32767). 
			// We need r in [0, i]
			int r = Random::Next(i);
			Swap(buffer, i, i - r);
		}
	}

	template<class T> void Permutation::Random(T * input, T * output, int length)
	{
		memcpy(output, input, length * sizeof(T));
		Random(output, length);
	}

	template<class T> vector<vector<T>> Permutation::All(vector<T> & input)
	{
		if (input.size() == 0) return vector<vector<T>> { };

		// Compute all permutations starting at index i
		function<void(vector<T> &, size_t, vector<vector<T>> &)>
		permute = [&](vector<T> & n, size_t i, vector<vector<T>> & o) {
			if (i == n.size() - 1) {
				o.push_back(n);
				return;
			}
			for (size_t j = i; j < n.size(); j++) {
				vector<T> m(n);
				if (j != i) {
					// Should just swap m[i] and m[j]
					// But we erase and insert, which effectively push m[i] one more positin to the right.
					// This way keeps the lexicographical order
					T t = m[j];
					m.erase(m.begin() + j);
					m.insert(m.begin() + i, t);
				}
				permute(m, i + 1, o);
			}
		};

		vector<vector<T>> output;
		permute(input, 0, output);
		return output;
	}

	template<class T> vector<vector<T>> Permutation::Unique(vector<T> & input)
	{
		if (input.size() == 0) return vector<vector<T>> { };

		function<void(vector<T> &, size_t, vector<vector<T>> &)>
		permute = [&](vector<T> & n, size_t i, vector<vector<T>> & o) {
			if (i == n.size() - 1) {
				o.push_back(n);
				return;
			}
			unordered_set<T> swapped;
			swapped.insert(n[i]);
			for (size_t j = i; j < n.size(); j++) {
				if (j != i && swapped.find(n[j]) != swapped.end()) {
					continue;
				}
				swapped.insert(n[j]);
				vector<T> m(n);
				if (j != i) {
					T t = m[j];
					m.erase(m.begin() + j);
					m.insert(m.begin() + i, t);
				}
				permute(m, i + 1, o);
			}
		};

		vector<vector<T>> output;
		permute(input, 0, output);
		return output;
	}

	template<class T> void Permutation::NextPermutation(vector<T> & input)
	{
		if (input.size() <= 1) return;

		// Find highest i such that input[i..] decreases and input[i-1] < input[i]
		int i = input.size() - 1;
		while (i - 1 >= 0 && input[i - 1] >= input[i]) i--;

		// Reverse input[i..] such that it increases
		int j = i;
		int k = input.size() - 1;
		T t;
		while (j < k) {
			t = input[j];
			input[j] = input[k];
			input[k] = t;
			j++;
			k--;
		}

		// Find first element from input[i..] that is greater than input[i-1],
		// and then swap these two elements.
		if (i != 0) {
			j = i - 1;
			while (input[j] >= input[i]) i++;
			t = input[j];
			input[j] = input[i];
			input[i] = t;
		}
	}
}

