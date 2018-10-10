#include "LongestCommonSubsequenceTest.h"

void LongestCommonSubsequenceTest::Init(void)
{
	Add("LongestCommonSubsequence", [&](){
		string x = "ABCBDAB";
		string y = "BDCABA";
		My::LongestCommonSubsequence::PrintLCS(x, y);

		x = "ABCBDABJOHBFUOBLNJIPIOHUGOYO";
		y = "BDCABATIOFTYFIBLOILUIIGGOBLOBIP";
		My::LongestCommonSubsequence::PrintLCS(x, y);
	});
}
