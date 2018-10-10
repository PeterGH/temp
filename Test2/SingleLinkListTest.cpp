#include "SingleLinkListTest.h"

void SingleLinkListTest::Init(void)
{
	Add("Insert", [&]() {
		My::SingleLinkList<int> list;
		list.Print();
		for (int i = 0; i < 10; i ++) {
			list.Insert(i);
			list.Print();
		}
		for (int i = 0; i < 10; i ++) {
			int v = list[i];
			cout << i << "\t" << v << endl;
			ASSERT2(v == i, My::String::Format("list[%d] = %d", i, v));
		}

		ASSERTERROR(list[10], std::invalid_argument);
	});

	Add("Reverse", [&]() {
		My::SingleLinkList<int> list;
		list.Print();
		list.Reverse();
		list.Print();
		for (int i = 0; i < 10; i ++) {
			list.Insert(i);
			list.Print();
			list.Reverse();
			list.Print();
			for (int j = 0; j <= i; j ++) {
				int v = list[j];				
				ASSERT2(v == (i-j), My::String::Format("list[%d] = %d", i, v));
			}
			list.Reverse();
		}

		ASSERTERROR(list[10], std::invalid_argument);
	});

	Add("Middle", [&]() {
		My::SingleLinkList<int> list;
		list.Print();
		ASSERTERROR(list.Middle(), std::invalid_argument);

		for (int i = 0; i < 10; i ++) {
			list.Insert(i);
			list.Print();
			int v = list.Middle();
			cout << "Middle = " << v << endl;
			ASSERT2(v == (i >> 1), My::String::Format("list[%d] = %d", i, v));			
		}

		ASSERTERROR(list[10], std::invalid_argument);
	});

	Add("Iterator", [&]() {
		My::SingleLinkList<int> list;
		list.Print();
		for (int i = 0; i < 10; i ++) {
			list.Insert(i);
			list.Print();
		}

		cout << "++ it, it->" << endl;
		for (My::SingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++ it) {
			unsigned int i = it.index();
			int v = it->data;
			cout << i << "\t" << v << endl;
			ASSERT2(v == i, My::String::Format("list[%d] = %d", i, v));
		}

		cout << "it ++, it.current()" << endl;
		for (My::SingleLinkList<int>::iterator it = list.begin(); it != list.end(); it ++) {
			unsigned int i = it.index();
			int v = it.current();
			cout << i << "\t" << v << endl;
			ASSERT2(v == i, My::String::Format("list[%d] = %d", i, v));
		}

		cout << "++ it, *it" << endl;
		for (My::SingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++ it) {
			unsigned int i = it.index();
			int v = *it;
			cout << i << "\t" << v << endl;
			ASSERT2(v == i, My::String::Format("list[%d] = %d", i, v));
		}

		cout << "bool(it) == true" << endl;
		My::SingleLinkList<int>::iterator it = list.begin();
		ASSERT1(it);

		cout << "bool(it) == false" << endl;
		it = list.end();
		ASSERTERROR(it, std::invalid_argument);
	});
}
