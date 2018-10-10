#include "KMP.h"

namespace Test {

	KMP::KMP(char * pattern)
	{
		this->prefix = nullptr;
		this->pattern = nullptr;
		if (pattern == nullptr) throw invalid_argument("pattern is nullptr");
		this->length = (int)strlen(pattern);
		if (this->length <= 0) throw invalid_argument(String::Format("length %d <= 0", this->length));

		this->pattern = new char[this->length+1];
		strcpy_s(this->pattern, this->length + 1, pattern);
		this->prefix = new int[this->length];
		memset(this->prefix, 0, this->length * sizeof(int));

		// Maintain prefix[i] = k, update prefix[i+1] by checking pattern[i+1] vs pattern[k+1]
		
		int k = -1;
		this->prefix[0] = k;
		for (int i = 1; i < this->length; i++) {
			while (k > -1 && this->pattern[k+1] != this->pattern[i]) {
				// Keep searching backward for minimum k 
				// such that pattern[0..k)] is a suffix of pattern[0..(i-1)]
				k = this->prefix[k];
			}

			// The while loop terminates when
			// 1. there is a k such that pattern[0..(k+1)] is a suffix of pattern[0..i], or
			// 2. k = -1

			if (this->pattern[k+1] == this->pattern[i]) {
				// One more match
				k = k+1;
			}

			this->prefix[i] = k;
		}
	}


	KMP::~KMP(void)
	{
		if (this->prefix != nullptr) {
			delete[] this->prefix;
			this->prefix = nullptr;
		}

		if (this->pattern != nullptr) {
			delete[] this->pattern;
			this->pattern = nullptr;
		}
	}

	void KMP::Print(void)
	{
		for (int i = 0; i < this->length; i++) {
			printf_s("\t%d", i);
		}

		printf_s("\n");

		for (int i = 0; i < this->length; i++) {
			printf_s("\t%d", this->prefix[i]);
		}

		printf_s("\n");
	}

	vector<int> KMP::SearchString(char * input, int length)
	{
		vector<int> indices;
		if (input == nullptr || input[0] == '\0' || length <= 0) return indices;

		int k = -1;
		for (int i = 0; i < length; i++) {
			while (k > -1 && this->pattern[k+1] != input[i]) {
				k = this->prefix[k];
			}

			if (this->pattern[k+1] == input[i]) {
				k = k+1;
			}

			if (k == this->length - 1) {
				indices.push_back(i - k);
				k = this->prefix[k];
			}
		}

		return indices;
	}
}