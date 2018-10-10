#include "DynamicProgramming.h"
namespace Test {
	// http://leetcode.com/2011/01/ctrla-ctrlc-ctrlv.html
	// Produce the longest string with N keystrokes using four keys: A, Ctrl+A (Select), Ctrl+C (Copy), Ctrl+V (Paste)
	// If we encode the keys with letters 'A', 'S', 'C', 'P' then the keystrokes form a sequence of these four letters.
	// 1. One occurrence of (S, C, P) actually does nothing but copying existing string into the clipboard.
	//    (S, C) copies existing string into the clipboard, and following P just replace existing string with
	//    the same string from the clipboard.
	// 2. One occurrence of P pastes what is in the clipboard to the output. So in order to double the length of existing string,
	//    we need four keystrokes (S, C, P, P).
	// 3. When the number of keystrokes is large, then the single key A is useless and we need only consider the other three keys.
	// 4. Given N keystrokes, the max length M(N) is:
	//    M(N) = max {  N,                  // when N is small, we may just type A repeatly
	//                  2 * M(N-4),         // the last four keystrokes are SCPP
	//                  3 * M(N-5),         // the last five keystrokes are SCPPP
	//                  ......
	//                  (k-2) * M(N-k),     // the last k keystrokes are SC and (k-2) Ps
	//                  ......
	//                  (N-3) * M(1)        // the sequence starts with ASC following by (N-3) Ps
	//                }
	void DynamicProgramming::LongestStringWithKeystrokes(int n, unsigned long long length[])
	{
		length[0] = 1;
		length[1] = 2;
		length[2] = 3;
		length[3] = 4;
		for (int i = 4; i < n; i++) {
			unsigned long long m = i + 1; // when all i+1 keystrokes are As
			for (int j = 4; j <= i; j++) {
				unsigned long long n = (j - 2) * length[i - j];
				if (n > m) m = n;
			}
			length[i] = m;
		}
	}
}