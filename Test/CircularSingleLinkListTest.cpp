#include "CircularSingleLinkListTest.h"

void CircularSingleLinkListTest::Init()
{
	Add("Delete", [&]() {
		Test::CircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");
		for (int i = 0; i < 10; i++) {
			list.Insert(i);
		}

		(Logger() << list).WriteInformation("\n");

		ASSERT1(list.Contain(0));
		list.Delete(0);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(!list.Contain(0));

		ASSERT1(list.Contain(9));
		list.Delete(9);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(!list.Contain(9));

		ASSERT1(list.Contain(5));
		list.Delete(5);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(!list.Contain(5));

		for (int i = 0; i < 10; i++) {
			list.Delete(i);
			(Logger() << list).WriteInformation("\n");
			ASSERT1(!list.Contain(i));
		}
	});

	Add("Insert", [&]() {
		Test::CircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");
		for (int i = 0; i < 10; i++) {
			list.Insert(i);
			(Logger() << list).WriteInformation("\n");
		}

		for (int i = 0; i < 10; i++) {
			int v = list[i + 1];
			ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
		}

		ASSERT2(list[10] == list[0], Test::String::Format("list[10] = %d", list[10]));
	});
}
