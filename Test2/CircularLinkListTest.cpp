#include "CircularLinkListTest.h"


void CircularLinkListTest::Init(void)
{
	Add("Insert", [&](){
		My::CircularLinkList<int> list;

		cout << "Empty:" << endl;
		list.Print();

		cout << "One node:" << endl;
		int v = rand();
		list.Insert(v);
		list.Print();

		cout << "Two nodes" << endl;
		v = rand();
		list.Insert(v);
		list.Print();

		cout << "More nodes" << endl;
		for (int i = 0; i < 20; i++) {
			v = rand();
			list.Insert(v);
		}

		list.Print();

		cout << "One more node" << endl;
		v = rand();
		list.Insert(v);
		list.Print();
	});

	Add("Duplicate nodes", [&](){
		My::CircularLinkList<int> list;

		cout << "Two nodes" << endl;
		int v = rand();
		list.Insert(v);
		list.Insert(v);
		list.Print();

		cout << "Add the same node" << endl;
		list.Insert(v);
		list.Print();

		cout << "Add a smaller node" << endl;
		list.Insert(v-1);
		list.Print();

		cout << "Add the same node" << endl;
		list.Insert(v-1);
		list.Print();

		cout << "Add a larger node" << endl;
		list.Insert(v+1);
		list.Print();

		cout << "Add the same node" << endl;
		list.Insert(v+1);
		list.Print();

		cout << "Add a different node" << endl;
		v = rand();
		list.Insert(v);
		list.Print();
	});
}
