#include "DestructorTest.h"

class Node {
public:
	int data;
	Node * next;

	Node(int d)
	{
		data = d;
		next = nullptr;
	}

	// This will be called recursively.
	~Node(void)
	{
		if (next != nullptr)
		{
			delete next;
			next = nullptr;
		}

		cout << "Deleting " << data << endl;
	}
};

void DestructorTest::Init(void)
{
	Add("Link", [&](){
		Node n(0);
		n.next = new Node(1);
		n.next->next = new Node(2);
	});
}