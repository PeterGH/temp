#include "SortedCircularSingleLinkListTest.h"

void SortedCircularSingleLinkListTest::Init(void)
{
	Add("Insert 1", [&](){
		Test::SortedCircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");

		list.Insert(0);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == 0);
		
		list.Insert(0);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == 0);
		ASSERT1(list[1] == 0);
		
		list.Insert(2);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == 0);
		ASSERT1(list[1] == 0);
		ASSERT1(list[2] == 2);
		
		list.Insert(2);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == 0);
		ASSERT1(list[1] == 0);
		ASSERT1(list[2] == 2);
		ASSERT1(list[3] == 2);

		list.Insert(-1);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == -1);
		ASSERT1(list[1] == 0);
		ASSERT1(list[2] == 0);
		ASSERT1(list[3] == 2);
		ASSERT1(list[4] == 2);

		list.Insert(-1);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == -1);
		ASSERT1(list[1] == -1);
		ASSERT1(list[2] == 0);
		ASSERT1(list[3] == 0);
		ASSERT1(list[4] == 2);
		ASSERT1(list[5] == 2);

		list.Insert(1);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == -1);
		ASSERT1(list[1] == -1);
		ASSERT1(list[2] == 0);
		ASSERT1(list[3] == 0);
		ASSERT1(list[4] == 1);
		ASSERT1(list[5] == 2);
		ASSERT1(list[6] == 2);

		list.Insert(1);
		(Logger() << list).WriteInformation("\n");
		ASSERT1(list[0] == -1);
		ASSERT1(list[1] == -1);
		ASSERT1(list[2] == 0);
		ASSERT1(list[3] == 0);
		ASSERT1(list[4] == 1);
		ASSERT1(list[5] == 1);
		ASSERT1(list[6] == 2);
		ASSERT1(list[7] == 2);
	});

	Add("Insert 2", [&](){
		Test::SortedCircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");

		for (int i = 0; i < 100; i++) {
			list.Insert(i);
		}

		(Logger() << list).WriteInformation("\n");

		for (int i = 0; i < 100; i++) {
			ASSERT2(list[i] == i, Test::String::Format("list[%d] = %d", i, list[i]));
		}
	});

	Add("Insert 3", [&](){
		Test::SortedCircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");

		for (int i = 0; i < 100; i++) {
			list.Insert(99 - i);
		}

		(Logger() << list).WriteInformation("\n");

		for (int i = 0; i < 100; i++) {
			ASSERT2(list[i] == i, Test::String::Format("list[%d] = %d", i, list[i]));
		}
	});

	Add("Insert 4", [&](){
		Test::SortedCircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");

		for (int i = 0; i < 100; i++) {
			list.Insert(9);
		}

		(Logger() << list).WriteInformation("\n");

		list.Insert(9);
		(Logger() << list).WriteInformation("\n");
		for (int i = 0; i < 101; i++) {
			ASSERT2(list[i] == 9, Test::String::Format("list[%d] = %d", i, list[i]));
		}

		list.Insert(5);
		(Logger() << list).WriteInformation("\n");
		ASSERT2(list[0] == 5, Test::String::Format("list[0] = %d", list[0]));

		for (int i = 1; i < 102; i++) {
			ASSERT2(list[i] == 9, Test::String::Format("list[%d] = %d", i, list[i]));
		}
	});

	Add("Insert 5", [&](){
		Test::SortedCircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");

		for (int i = 0; i < 100; i++) {
			list.Insert(9);
		}

		(Logger() << list).WriteInformation("\n");

		list.Insert(15);
		(Logger() << list).WriteInformation("\n");
		for (int i = 0; i < 100; i++) {
			ASSERT2(list[i] == 9, Test::String::Format("list[%d] = %d", i, list[i]));
		}

		ASSERT2(list[100] == 15, Test::String::Format("list[100] = %d", list[100]));
	});

	Add("Insert 6", [&](){
		Test::SortedCircularSingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");

		int count = 1 + rand();
		for (int i = 0; i < count; i++) {
			list.Insert(rand());
		}

		(Logger() << list).WriteInformation("\n");

		int t = list[0];
		for (int i = 1; i < count; i++) {
			int v = list[i];
			ASSERT2(v >= t, Test::String::Format("list[%d] = %d > list[%d] = %d", i - 1, t, i, v));
			t = v;
		}
	});
}