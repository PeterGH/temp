#include "AVLTreeTest.h"

void AVLTreeTest::Init(void)
{
	Add("Insert 1", [&](){
		Test::AVLTree<int> tree;
		bool valid;
		for (int i = 0; i < 20; i ++) {
			tree.Insert(i);
			valid = tree.Verify();
			if (!valid)	tree.Print();
			ASSERT1(valid == true);
		}
	});

	Add("Insert 2", [&](){
		for (int i = 0; i < 100; i++) {
			int count = 1 + Test::Random::Next(1000);
			cout << "Run " << i << ", " << count << " elements" << endl;
			Test::AVLTree<int> tree;
			bool valid;
			int v;
			for (int j = 0; j < count; j ++) {
				v = Test::Random::Next();
				tree.Insert(v);
				valid = tree.Verify();
				if (!valid) {
					cout << "Insert " << v << endl;
					tree.Print();
				}
				ASSERT1(valid == true);
			}
		}
	});

	Add("Delete 1", [&](){
		Test::AVLTree<int> tree;
		int count = 10;
		for (int i = 0; i < count; i++) {
			tree.Insert(i);
		}

		tree.Print();
		bool valid = tree.Verify();
		ASSERT1(valid == true);

		for (int i = 0; i < count; i++) {
			cout << "Deleting " << i << endl;
			tree.Delete(i);
			tree.Print();
			valid = tree.Verify();
			ASSERT1(valid == true);
		}
	});

	Add("Delete 2", [&](){
		for (int j = 0; j < 1000; j++) {
			Test::AVLTree<int> tree;
			int count = Test::Random::Next(1000);
			cout << "Run " << j << ", " << count << " elements" << endl;

			int v;
			vector<int> vals;
			for (int i = 0; i < count; i++) {
				v = Test::Random::Next();
				vals.push_back(v);
				tree.Insert(v);
			}

			bool valid = tree.Verify();
			ASSERT1(valid == true);

			for (int i = 0; i < count; i++) {
				v = vals[i];
				tree.Delete(v);
				valid = tree.Verify();
				if (!valid) {
					cout << "Delete " << v << endl;
					tree.Print();
				}

				ASSERT1(valid == true);
			}
		}
	});

	Add("Update", [&](){
		for (int j = 0; j < 100; j++) {
			unsigned int count = 1 + Test::Random::Next(1000);
			cout << "Run " << j << ", " << count << " elements" << endl;

			Test::AVLTree<int> tree;
			vector<int> values;
			int v;
			bool valid;
			string action;
			while (values.size() < count) {
				if (Test::Random::Next(100) < 70) {
					v = Test::Random::Next();
					action = Test::String::Format("Insert %d", v);
					tree.Insert(v);
					values.push_back(v);
				} else if (values.size() > 0) {
					int i = Test::Random::Next(values.size() - 1);
					v = values[i];
					action = Test::String::Format("Delete %d", v);
					tree.Delete(v);
					values.erase(values.begin() + i);
				}

				valid = tree.Verify();
				if (!valid) {
					cout << action << endl;
					tree.Print();
				}

				ASSERT1(valid == true);
			}
		}
	});
}