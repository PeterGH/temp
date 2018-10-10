#include "PalindromeTest.h"

void PalindromeTest::Init(void)
{
	string s = "character";
	string t;
	string a;
	cout << "Input: " << s << endl;
	My::Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	My::Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;

	s = "racecar";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	My::Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	My::Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;

	s = "raceecar";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	My::Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	My::Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;

	s = "ra";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	My::Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	My::Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;

	s = "rac";
	t = "";
	a = "";
	cout << "Input: " << s << endl;
	My::Palindrome::LongestSubsequenceByTable(s, t);
	cout << "Table: " << t << endl;
	My::Palindrome::LongestSubsequenceByArray(s, a);
	cout << "Array: " << a << endl;
	cout << endl;
}
