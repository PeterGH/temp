#include "String.h"

namespace My {

	string String::Format(const char * format, ...)
	{
		char buffer[MaxLength];
		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);
		return string(buffer);
	}

	wstring String::Format(const wchar_t * format, ...)
	{
		wchar_t buffer[MaxLength];
		va_list args;
		va_start(args, format);
		vswprintf_s(buffer, format, args);
		va_end(args);
		return wstring(buffer);
	}

	int String::RemoveDuplicateChars(char * input, int length)
	{
		if (input == nullptr) return -1;
		if (length <= 0) return length;
		bitset<256> mask;

		// Using i to point to the last position of a non-dup char that has been checked.
		// Next non-dup char should be copied to the position i+1.
		// 0 | 1 | ... | i | ... | j | ... | n-1
		// ~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~
		// Non-dup chars         chars to check

		int i = -1;
		for (int j = 0; j < length; j ++) {
			if ('\0' == input[j]) break;
			// Should look at bit input[j] of mark			
			if (!mask.test(input[j])) {
				// The bit is zero, and it means input[j] is not a dup.
				// Set the bit.
				mask.set(input[j]);
				if (1 < (j-i)) {
					// Have skipped some dups
					// Move current non-dup char to the front.
					input[++i] = input[j];
				} else {
					// Have not skipped any dups.
					// Hop i with j.
					i ++;
				}
			}
		}

		input[++i] = '\0';
		// Now i equals to the new length.
		return i;
	}
}
