// StringMatch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <strsafe.h>

void match(char* pattern, size_t sizePattern, char* input, size_t sizeInput)
{
	char* buffer = new char[sizeInput];
	size_t b = 0;
	for (size_t i = 0; i < sizeInput; i ++) {
		size_t j = 0;
		size_t k = 0;
		size_t b = 0;
		while (k < sizePattern) {
			printf_s("(i, j, k, b) = (%d, %d, %d, %d) = (%c, %c, %c, %c)\n", i, j, k, b,
				input[i], input[i+j], pattern[k], buffer[b]);
			if (input[i+j] == pattern[k]) {
				buffer[b++] = input[i+j];
				j ++;
				k ++;
			} else if (pattern[k] == '*') {
				// Wild char
				while (pattern[++k] == '*');
				if (k < sizePattern) {
					while (input[i+j] != pattern[k]) {
						buffer[b++] = input[i+j];
						j ++;
					}
				}
			} else {
				// Not match
				break;
			}
		}
		if (k == sizePattern) {
			buffer[b] = '\0';
			printf_s("%s\n", buffer);
		}
	}
	
	delete[] buffer;	
}

// for each input character
//     if current
void match(char* pattern, size_t sizePattern, char* input, size_t sizeInput, char* buffer, size_t sizeBuffer, bool keepPrefix)
{
	while ((*input) != (*pattern) && (*input) != '\0' && (*pattern) != '\0') {
		if ((*pattern) == '*') {
			pattern ++;
		} else if (keepPrefix) {
			*buffer = *input;
			buffer ++;
			input ++;
		}
	}

	// Now input and pattern align with each other at the beginning
		
	for (size_t i = 0; i < sizeInput; i ++) {
		size_t j = 0;
		size_t k = 0;
		size_t b = 0;
		while (k < sizePattern) {
			printf_s("(i, j, k, b) = (%d, %d, %d, %d) = (%c, %c, %c, %c)\n", i, j, k, b,
				input[i], input[i+j], pattern[k], buffer[b]);
			if (input[i+j] == pattern[k]) {
				buffer[b++] = input[i+j];
				j ++;
				k ++;
			} else if (pattern[k] == '*') {
				// Wild char
				while (pattern[++k] == '*');
				if (k < sizePattern) {
					while (input[i+j] != pattern[k]) {
						buffer[b++] = input[i+j];
						j ++;
					}
				}
			} else {
				// Not match
				break;
			}
		}
		if (k == sizePattern) {
			buffer[b] = '\0';
			printf_s("%s\n", buffer);
		}
	}
	
	delete[] buffer;	
}


int main(int argc, char* argv[])
{
	HRESULT error = S_OK;
	size_t sizePattern = 0;
	char* pattern = argv[1];
	if (FAILED(error = StringCchLengthA(pattern, _MAX_PATH, &sizePattern))) {
		printf_s("Failed to calculate the length of %s, %d\n", pattern, error);
		return error;
	}

	size_t sizeInput = 0;
	char* input = argv[2];
	if (FAILED(error = StringCchLengthA(input, _MAX_PATH, &sizeInput))) {
		printf_s("Failed to calculate the length of %s, %d\n", input, error);
		return error;
	}

	match(pattern, sizePattern, input, sizeInput);
	return 0;
}

