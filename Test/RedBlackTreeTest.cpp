#include "RedBlackTreeTest.h"

void RedBlackTreeTest::Init(void)
{
	Add("Insert", [&](){
		Test::RedBlackTree<int> tree;

		for (int i = 0; i < 200; i++) {
			tree.Insert(i);
		}

		tree.Print();
	});

	Add("BlackHeight", [&](){
		for (int i = 0; i < 100; i++) {
			Test::RedBlackTree<int> tree;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			bool valid = tree.Verify();
			int h = tree.BlackHeight();
			int h2 = tree.BlackHeight2();
			cout << "Run " << i << ", " << count << " elements, height " << h << " " << h2 << ", " << (valid ? "valid" : "invalid") << endl;
			ASSERT1(h == h2);
		}
	});

	Add("Delete 1", [&](){
		Test::RedBlackTree<int> tree;
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
		for (int j = 0; j < 100; j++) {
			Test::RedBlackTree<int> tree;
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
}