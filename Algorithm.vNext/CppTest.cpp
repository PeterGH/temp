#include "Test.h"

void CppTest::Init(void)
{
	Add("string", [&]() {
		{
			string s = "Test";
			s[1] = 'E';
			bool eq = (s == "TEst");
			Logger().WriteInformation("%s\n", s.c_str());
			ASSERT2(eq, String::Format("%s %s TEst\n", s.c_str(), eq ? "==" : "!="));
		}
		{
			string s = "Test";
			s[2] = '\0';
			bool eq1 = (s == "Te");
			int eq2 = strcmp(s.c_str(), "Te");
			cout << s << endl;
			Logger().WriteInformation("%s\n", s.c_str());
			ASSERT2(eq1 == false, String::Format("%s %s Te\n", s.c_str(), eq1 ? "==" : "!="));
			ASSERT2(eq2 == 0, String::Format("%s %s Te\n", s.c_str(), eq2 ? "==" : "!="));
		}
	});
}