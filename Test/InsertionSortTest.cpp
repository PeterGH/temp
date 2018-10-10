#include "InsertionSortTest.h"

void InsertionSortTest::Init(void)
{
	Add("SortList", [&](){
		auto check = [&](Test::SingleNode<int> * list){
			cout << "List: " << list << endl;
			size_t len1 = list->Length();
			Test::InsertionSort::Sort(list);
			cout << "Sort: " << list << endl;
			size_t len2 = list->Length();
			ASSERT1(len1 == len2);

			Test::SingleNode<int> * p = list;
			Test::SingleNode<int> * n = p->Next();
			while (n != nullptr && n != list) {
				ASSERT1(p->Value() <= n->Value());
				p = n;
				n = n->Next();
			}

			list->DeleteList();
			delete list;
		};
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			Test::SingleNode<int> * p = new Test::SingleNode<int>(2);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(2);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(2);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			for (int i = 0; i < 100; i++) {
				Logger().WriteInformation("Run %d\n", i);
				Test::SingleNode<int> * list = new Test::SingleNode<int>(Test::Random::Next());
				int len = Test::Random::Next(100);
				for (int j = 0; j < len; j++) {
					list->InsertAtEnd(new Test::SingleNode<int>(Test::Random::Next()));
				}
				check(list);
			}
		}
		{
			for (int i = 0; i < 100; i++) {
				Logger().WriteInformation("Run %d\n", i);
				Test::SingleNode<int> * list = new Test::SingleNode<int>(Test::Random::Next());
				int len = Test::Random::Next(100);
				for (int j = 0; j < len; j++) {
					list->InsertAtEnd(new Test::SingleNode<int>(Test::Random::Next()));
				}
				Test::SingleNode<int> * p = new Test::SingleNode<int>(Test::Random::Next());
				list->InsertAtEnd(p);
				p->Next() = list;
				check(list);
			}
		}
	});
}