#include "StringTest.h"

void StringTest::Init(void)
{
	Add("RemoveDuplicateChar", [&](){
		char * c;
		c = nullptr;
		int l = My::String::RemoveDuplicateChars(c, 0);
		ASSERT1(l == -1);

		char c1[] = "Test";
		printf_s("%s\t", c1);
		l = My::String::RemoveDuplicateChars(c1, 4);
		printf_s("%s\n", c1);
		ASSERT1(0 == strcmp("Test", c1));
		ASSERT1(4 == l);

		char c2[] = "TTeesstt";
		printf_s("%s\t", c2);
		l = My::String::RemoveDuplicateChars(c2, 8);
		printf_s("%s\n", c2);
		ASSERT1(0 == strcmp("Test", c2));
		ASSERT1(4 == l);

		char c3[] = "TestTest";
		printf_s("%s\t", c3);
		l = My::String::RemoveDuplicateChars(c3, 8);
		printf_s("%s\n", c3);
		ASSERT1(0 == strcmp("Test", c3));
		ASSERT1(4 == l);

		char c4[] = "";
		printf_s("%s\t", c4);
		l = My::String::RemoveDuplicateChars(c4, 0);
		printf_s("%s\n", c4);
		ASSERT1(0 == strcmp("", c4));
		ASSERT1(0 == l);
	});
}