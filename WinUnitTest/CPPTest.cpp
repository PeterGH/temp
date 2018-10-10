#include "WinUnit.h"
#include "cpp.h"

BEGIN_TEST(VarArg_Int)
{
	int i = Test_VarArg<int>(4, 1, 2, 3, 4);
	WIN_ASSERT_EQUAL(0, i);
}
END_TEST

	BEGIN_TEST(VarArg_PChar)
{
	char * j = Test_VarArg<char *>(4, "arg1", "arg2", "arg3", "arg4");
	WIN_ASSERT_EQUAL((char *)NULL, j);
}
END_TEST