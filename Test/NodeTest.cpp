#include "NodeTest.h"

void NodeTest::Init(void)
{
	Add("Node", [&](){
		{
			Node<int> node(1);
			ASSERT1(0 == node.CountNeighbors());
			ASSERT1(nullptr == node.Neighbor(0));
			ASSERT1(1 == node.CountNeighbors());
			ASSERT1(nullptr == node.Neighbor(0));
			ASSERT1(1 == node.CountNeighbors());
		}
		{
			Node<int> * p = new Node<int>(2);
			ASSERT1(0 == p->CountNeighbors());
			ASSERT1(nullptr == p->Neighbor(0));
			ASSERT1(1 == p->CountNeighbors());
			ASSERT1(nullptr == p->Neighbor(0));
			ASSERT1(1 == p->CountNeighbors());
			ASSERT1(nullptr == p->Neighbor(1));
			ASSERT1(2 == p->CountNeighbors());
			delete p;
		}
	});

	Add("SingleNode1", [&](){
		{
			SingleNode<int> node(1);
			cout << &node;
			cout << "Count: " << node.CountNeighbors() << endl;
			ASSERT1(1 == node.CountNeighbors());
			cout << "Middle: " << node.Middle()->Value() << endl;
			ASSERT1(1 == node.Middle()->Value());
			SingleNode<int> * r = node.Reverse();
			cout << "Reverse:" << endl << r;
			ASSERT1(1 == r->Value());
			r = nullptr;
			r = new SingleNode<int>(2);
			cout << r;
			delete r;
		}
		{
			SingleNode<int> node(1);
			node.Next() = &node;
			cout << &node;
			cout << "Count: " << node.CountNeighbors() << endl;
			ASSERT1(1 == node.CountNeighbors());
			cout << "Middle: " << node.Middle()->Value() << endl;
			ASSERT1(1 == node.Middle()->Value());
			SingleNode<int> * r = node.Reverse();
			cout << "Reverse:" << endl << r;
			ASSERT1(1 == r->Value());
			r = nullptr;
			r = new SingleNode<int>(2);
			r->Next() = r;
			cout << r;
			delete r;
		}
	});

	Add("SingleNode2", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;

			cout << n1 << endl;

			cout << "Middle: " << n1->Middle()->Value() << endl;
			ASSERT1(2 == n1->Middle()->Value());

			SingleNode<int>::DeleteList(n1);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next(n2);
			n2->Next(n3);
			n3->Next(n4);

			cout << n1;

			SingleNode<int> * n = SingleNode<int>::Reverse(n1);
			cout << "Reverse:" << endl;
			cout << n;

			SingleNode<int>::DeleteList(n);
		}
	});

	Add("SingleNode3", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;
			n4->Next() = n1;

			cout << n1 << endl;

			cout << "Middle: " << n1->Middle()->Value() << endl;

			SingleNode<int> * n = SingleNode<int>::Reverse(n1);
			cout << "Reverse:" << endl;
			cout << n;

			SingleNode<int>::DeleteList(n);
		}
	});

	Add("SingleNode4", [&](){
		{
			SingleNode<int> n1(0);
			for (int i = 1; i < 10; i++) {
				n1.InsertAtEnd(new SingleNode<int>(i));
				cout << &n1;
				int m = n1.Middle()->Value();
				cout << "Middle: " << m << endl;
				ASSERT1(m == i >> 1);
			}
			n1.DeleteList();
		}
		{
			SingleNode<int> n1(0);
			for (int i = 9; i > 0; i--) {
				n1.InsertAfter(new SingleNode<int>(i));
				cout << &n1;
			}
			int m = n1.Middle()->Value();
			cout << "Middle: " << m << endl;
			ASSERT1(m == 4);
			n1.DeleteList();
		}
	});

	Add("SingleNode5", [&](){
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			for (int i = 1; i < 10; i++) {
				n->InsertAtEnd(new SingleNode<int>(i));
				cout << n;
				n = n->Reverse();
				cout << "Reverse: " << endl << n;
			}
			SingleNode<int>::DeleteList(n);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->Next() = n;
			for (int i = 1; i < 10; i++) {
				n->InsertAtEnd(new SingleNode<int>(i));
				cout << n;
				n = n->Reverse();
				cout << "Reverse: " << endl << n;
			}
			SingleNode<int>::DeleteList(n);
		}
	});

	Add("SingleNode6", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;
			n4->Next() = n1;

			cout << n1;

			SingleNode<int> * p = SingleNode<int>::Tail(n1);
			cout << "Tail: " << p->Value() << endl;
			ASSERT1(4 == p->Value());

			n1 = SingleNode<int>::Reverse(n1);
			cout << n1;

			p = SingleNode<int>::Tail(n1);
			cout << "Tail: " << p->Value() << endl;
			ASSERT1(1 == p->Value());

			SingleNode<int>::DeleteList(n1);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;
			n4->Next() = n2;

			cout << n1;

			SingleNode<int> * p = SingleNode<int>::Tail(n1);
			cout << "Tail: " << p->Value() << endl;
			ASSERT1(4 == p->Value());

			n1 = SingleNode<int>::Reverse(n1);
			cout << n1;

			p = SingleNode<int>::Tail(n1);
			cout << "Tail: " << p->Value() << endl;
			ASSERT1(1 == p->Value());

			SingleNode<int>::DeleteList(n1);
		}
	});

	Add("SingleNode7", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			n1->Next() = n1;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
	});

	Add("SingleNode8", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			n1->Next() = n2;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			n1->Next() = n2;
			n2->Next() = n1;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			n1->Next() = n2;
			n2->Next() = n2;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			n1->Next() = n2;
			n2->Next() = n2;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
	});

	Add("SingleNode9", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
	});

	Add("SingleNode10", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n1;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n1;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n1;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n2;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n2;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n3;
			cout << n1;
			cout << "Delete 0:" << endl;
			n1 = SingleNode<int>::Delete(n1, 0);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 2:" << endl;
			n1 = SingleNode<int>::Delete(n1, 2);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 3:" << endl;
			n1 = SingleNode<int>::Delete(n1, 3);
			cout << n1;
			ASSERT1(n1 != nullptr);
			cout << "Delete 1:" << endl;
			n1 = SingleNode<int>::Delete(n1, 1);
			cout << n1;
			ASSERT1(n1 == nullptr);
		}
	});

	Add("SingleNodeReorder", [&](){
		auto check = [&](SingleNode<int> * node) {
			size_t len = node->Length();
			cout << node << endl;
			SingleNode<int>::Reorder(node);
			size_t len2 = node->Length();
			cout << node << endl;
			ASSERT1(len == len2);
			size_t i = 0;
			SingleNode<int> * p = node;
			while (p != nullptr) {
				ASSERT1(p->Value() == i);
				p = p->Next();
				i++;
			}
			SingleNode<int>::DeleteList(node);
		};
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			check(n);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(2));
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(2));
			n->InsertAtEnd(new SingleNode<int>(3));
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n);
		}
		{
			for (int i = 5; i < 100; i++) {
				Logger().WriteInformation("Reorder a list of %d nodes\n", i);
				SingleNode<int> * n = new SingleNode<int>(0);
				int j = (i + 1) >> 1;
				for (int k = 1; k < j; k++) {
					n->InsertAtEnd(new SingleNode<int>(2 * k));
				}
				j = i >> 1;
				for (int k = j; k > 0; k--) {
					n->InsertAtEnd(new SingleNode<int>(2 * k - 1));
				}
				check(n);
			}
		}
	});

	Add("SingleNodeCycle", [&](){
		auto check = [&](SingleNode<int> * node, int beginning){
			cout << node;
			size_t l1 = node->Length();
			size_t l2 = SingleNode<int>::Length(node);
			bool hasCycle = SingleNode<int>::HasCycle(node);
			if (hasCycle) {
				SingleNode<int> * cycle = SingleNode<int>::FindCycle(node);
				Logger().WriteInformation("Has cycle at %d\n", cycle->Value());
				int v = cycle->Value();
				ASSERT1(beginning == v);
			} else {
				Logger().WriteInformation("No cycle\n");
				ASSERT1(beginning == -1);
			}
			node = SingleNode<int>::Reverse(node);
			Logger().WriteInformation("Reverse:\n");
			cout << node;
			hasCycle = SingleNode<int>::HasCycle(node);
			if (hasCycle) {
				SingleNode<int> * cycle = SingleNode<int>::FindCycle(node);
				Logger().WriteInformation("Has cycle at %d\n", cycle->Value());
			} else {
				Logger().WriteInformation("No cycle\n");
			}
			size_t l3 = SingleNode<int>::Length(node);
			SingleNode<int>::DeleteList(node);
			ASSERT1(l1 == l2);
			ASSERT1(l1 == l3);
		};
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			check(n, -1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->Next() = n;
			check(n, 0);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n, -1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->Next() = n;
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n, 0);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			SingleNode<int> * c = new SingleNode<int>(1);
			c->Next() = c;
			n->Next() = c;
			check(n, 1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			n->InsertAtEnd(new SingleNode<int>(2));
			check(n, -1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->Next() = n;
			n->InsertAtEnd(new SingleNode<int>(1));
			n->InsertAtEnd(new SingleNode<int>(2));
			check(n, 0);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			SingleNode<int> * c = new SingleNode<int>(1);
			c->Next() = c;
			c->InsertAtEnd(new SingleNode<int>(2));
			n->Next() = c;
			check(n, 1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			SingleNode<int> * c = new SingleNode<int>(2);
			c->Next() = c;
			n->Next() = c;
			check(n, 2);
		}
		{
			for (int i = 4; i < 100; i++) {
				Logger().WriteInformation("Test %d nodes\n", i);
				for (int j = 0; j < i; j++) {
					SingleNode<int> * n;
					SingleNode<int> * c = new SingleNode<int>(j);
					c->Next() = c;
					for (int k = j+1; k < i; k++) {
						c->InsertAtEnd(new SingleNode<int>(k));
					}
					if (j == 0) {
						n = c;
					} else {
						n = new SingleNode<int>(0);
						SingleNode<int> * p = n;
						for (int k = 1; k < j; k++) {
							p = new SingleNode<int>(k);
							n->InsertAtEnd(p);
						}
						p->Next() = c;
					}
					check(n, j);
				}
			}
		}
	});

	Add("DoubleNode1", [&](){
		{
			DoubleNode<int> node(1);
			cout << &node;
		}
		{
			DoubleNode<int> * p = new DoubleNode<int>(2);
			cout << p;
			delete p;
		}
		{
			DoubleNode<int> * n1 = new DoubleNode<int>(1);
			DoubleNode<int> * n2 = new DoubleNode<int>(2);
			DoubleNode<int> * n3 = new DoubleNode<int>(3);
			DoubleNode<int> * n4 = new DoubleNode<int>(4);
			n1->Next() = n2;
			n2->Prev() = n1;
			n2->Next() = n3;
			n3->Prev() = n2;
			n3->Next() = n4;
			n4->Prev() = n3;

			cout << n1;
			DoubleNode<int>::DeleteList(n1);
		}
		{
			DoubleNode<int> * n1 = new DoubleNode<int>(1);
			DoubleNode<int> * n2 = new DoubleNode<int>(2);
			DoubleNode<int> * n3 = new DoubleNode<int>(3);
			DoubleNode<int> * n4 = new DoubleNode<int>(4);
			n1->Next(n2);
			n2->Prev(n1);
			n2->Next(n3);
			n3->Prev(n2);
			n3->Next(n4);
			n4->Prev(n3);
			n4->Next(n1);
			n1->Prev(n4);

			cout << n1;
			DoubleNode<int>::DeleteList(n1);
		}
	});

	Add("DoubleNodeClone", [&](){
		{
			DoubleNode<int> node(1);
			cout << &node;
			DoubleNode<int> * copy = (DoubleNode<int> *)Node<int>::Clone(&node);
			cout << copy;
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Prev() == nullptr);
			ASSERT1(copy->Next() == nullptr);
			delete copy;
		}
		{
			DoubleNode<int> node(1);
			node.Prev() = &node;
			node.Next() = &node;
			cout << &node;
			DoubleNode<int> * copy = (DoubleNode<int> *)Node<int>::Clone(&node);
			cout << copy;
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Prev() == copy);
			ASSERT1(copy->Next() == copy);
			delete copy;
		}
		{
			DoubleNode<int> * n1 = new DoubleNode<int>(1);
			DoubleNode<int> * n2 = new DoubleNode<int>(2);
			DoubleNode<int> * n3 = new DoubleNode<int>(3);
			DoubleNode<int> * n4 = new DoubleNode<int>(4);
			n1->Next() = n2;
			n2->Prev() = n1;
			n2->Next() = n3;
			n3->Prev() = n2;
			n3->Next() = n4;
			n4->Prev() = n3;

			DoubleNode<int> * copy = (DoubleNode<int> *)Node<int>::Clone(n1);

			cout << n1;
			cout << copy;

			DoubleNode<int>::DeleteList(n1);
			DoubleNode<int>::DeleteList(copy);
		}
		{
			DoubleNode<int> * n1 = new DoubleNode<int>(1);
			DoubleNode<int> * n2 = new DoubleNode<int>(2);
			DoubleNode<int> * n3 = new DoubleNode<int>(3);
			DoubleNode<int> * n4 = new DoubleNode<int>(4);
			n1->Next() = n2;
			n2->Prev() = n1;
			n2->Next() = n3;
			n3->Prev() = n1;
			n3->Next() = n4;
			n4->Prev() = n1;

			DoubleNode<int> * copy = (DoubleNode<int> *)Node<int>::Clone(n1);

			cout << n1;
			cout << copy;

			ASSERT1(copy->Prev() == nullptr);
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Next()->Value() == 2);
			ASSERT1(copy->Next()->Prev() == copy);
			ASSERT1(copy->Next()->Next()->Value() == 3);
			ASSERT1(copy->Next()->Next()->Prev() == copy);
			ASSERT1(copy->Next()->Next()->Next()->Value() == 4);
			ASSERT1(copy->Next()->Next()->Next()->Prev() == copy);
			ASSERT1(copy->Next()->Next()->Next()->Next() == nullptr);

			DoubleNode<int>::DeleteList(n1);
			DoubleNode<int>::DeleteList(copy);
		}
		{
			DoubleNode<int> * n1 = new DoubleNode<int>(1);
			DoubleNode<int> * n2 = new DoubleNode<int>(2);
			DoubleNode<int> * n3 = new DoubleNode<int>(3);
			DoubleNode<int> * n4 = new DoubleNode<int>(4);
			n1->Prev() = n4;
			n1->Next() = n2;
			n2->Prev() = n4;
			n2->Next() = n3;
			n3->Prev() = n4;
			n3->Next() = n4;
			n4->Prev() = n4;
			n4->Next() = nullptr;

			DoubleNode<int> * copy = (DoubleNode<int> *)Node<int>::Clone(n1);

			cout << n1;
			cout << copy;

			ASSERT1(copy->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Next()->Value() == 2);
			ASSERT1(copy->Next()->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Next()->Next()->Value() == 3);
			ASSERT1(copy->Next()->Next()->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Next()->Next()->Next()->Value() == 4);
			ASSERT1(copy->Next()->Next()->Next()->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Next()->Next()->Next()->Next() == nullptr);

			DoubleNode<int>::DeleteList(n1);
			DoubleNode<int>::DeleteList(copy);
		}
	});
}