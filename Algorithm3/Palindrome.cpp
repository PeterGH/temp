#include "Palindrome.h"
#include <algorithm>
#include <functional>

Palindrome::Palindrome(void)
{
}


Palindrome::~Palindrome(void)
{
}

// input: c_0, c_1, c_2, ..., c_i, ..., c_j, ..., c_(n-1)
// Let L_(i, j) be the length of the longest palindrome subsequence of input
// L_(i, j) = 1,                             if i == j
//            2,                             if i+1 == j, c_i == c_j
//            1,                             if i+1 == j, c_i != c_j
//            2 + L_(i+1, j-1),              if c_i == c_j, i+1 < j
//            max(L_(i, j-1), L_(i+1, j),    if c_i != c_j, i+1 < j
//
//	       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
// 0(c)    1       1       1       1       3       5       5       5       5
// 1(h)    0       1       1       1       3       3       3       3       3
// 2(a)    0       0       1       1       3       3       3       3       3
// 3(r)    0       0       0       1       1       1       1       1       3
// 4(a)    0       0       0       0       1       1       1       1       1
// 5(c)    0       0       0       0       0       1       1       1       1
// 6(t)    0       0       0       0       0       0       1       1       1
// 7(e)    0       0       0       0       0       0       0       1       1
// 8(r)    0       0       0       0       0       0       0       0       1
//	
void Palindrome::LengthTable(string & input, Array2D<size_t> & length)
{
	for (size_t i = 0; i < input.length(); i ++) {
		length.SetValue(i, i, 1);
		if (i + 1 < input.length()) {
			if (input[i] == input[i+1]) {
				length.SetValue(i, i+1, 2);
			} else {
				length.SetValue(i, i+1, 1);
			}
		}
	}

	for (size_t j = 2; j < input.length(); j ++) {
		for (size_t i = 0; i + j < input.length(); i ++) {
			if (input[i] == input[i+j]) {
				length.SetValue(i, i+j, 2 + length.GetValue(i+1, i+j-1));					
			} else {
				length.SetValue(i, i+j, max(length.GetValue(i, i+j-1), length.GetValue(i+1, i+j)));
			}			
		}
	}
}

void Palindrome::LongestSubsequenceByTable(string & input, string & output)
{
	Array2D<size_t> length(input.length(), input.length());
	LengthTable(input, length);

	size_t i = 0;
	size_t j = input.length() - 1;

	if (length.GetValue(i, j) == 1) {
		// no Parlindrome found, return the last char
		output.append(&input[j], 1);
		return;
	}

	size_t k = 0;

	while ((j-i) > 1) {
		while (length.GetValue(i, j-1) == length.GetValue(i, j)) {
			j --;
		}
		char c = input[j];
		j --;
		output.insert(k++, 1, c);
		output.insert(k, 1, c);
		while (input[i] != c) {
			i ++;
		}
		i ++;
	}

	output.insert(k, 1, input[j]);
	if (i+1 == j) {
		// The palindrome is of form xxxccxxxx
		output.insert(k, 1, input[j]);		
	}
}

// k       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
// 0       1       1       1       1       1       1       1       1       1
// 1       1       1       1       1       1       1       1       1       1
// 2       1       1       1       1       3       1       1       1       1
// 3       1       1       1       1       3       3       1       1       1
// 4       1       1       1       1       3       3       3       1       1
// 5       1       1       1       1       3       5       3       3       1
// 6       1       1       1       1       3       5       5       3       3
// 7       1       1       1       1       3       5       5       5       3
// 8       1       1       1       1       3       5       5       5       5
void Palindrome::LengthArray(string & input, size_t length[])
{
	/*
	function<void (size_t *, size_t)> print = [](size_t a[], size_t l) {
		for (size_t i = 0; i < l; i ++) {
		cout << "\t" << a[i];
		}
		cout << endl;
	};
	*/
	// Use int instead of size_t
	// size_t is unsigned int. When i = 0, i-- will be larger than 0 and thus the loop never ends.
	for (int i = input.length() - 1; i >= 0; i --) {
		length[i] = 1;
	}
	
	//print(length, input.length());

	for (int i = input.length() - 1; i >= 1; i --) {
		if (input[i-1] == input [i]) {
			length[i] = 2;
		}
	}	
	
	//print(length, input.length());
		
	for (int k = 2; k < (int)input.length(); k ++) {
		for (int i = input.length() - 1; i >= k; i --) {
			if (input[i-k] == input[i]) {
				length[i] = 2 + length[i-1];
			} else {
				length[i] = max(length[i-1], length[i]);
			}
		}

		//print(length, input.length());
	}
}

void Palindrome::LongestSubsequenceByArray(string & input, string & output)
{
	size_t * length = new size_t[input.length()];
	LengthArray(input, length);

	size_t i = 0;
	size_t j = input.length() - 1;

	if (length[j] == 1) {
		// no Parlindrome found, return the last char
		output.append(&input[j], 1);
		return;
	}

	size_t k = 0;

	while ((j-i) > 1) {
		while (length[j-1] == length[j]) {
			j --;
		}
		char c = input[j];
		j --;
		output.insert(k++, 1, c);
		output.insert(k, 1, c);
		while (input[i] != c) {
			i ++;
		}
		i ++;
	}

	output.insert(k, 1, input[j]);
	if (i+1 == j) {
		// The palindrome is of form xxxccxxxx
		output.insert(k, 1, input[j]);		
	}

	delete[] length;
}
