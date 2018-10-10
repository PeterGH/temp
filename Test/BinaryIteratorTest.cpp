#include "BinaryIteratorTest.h"

void BinaryIteratorTest::Init(void)
{
	Add("Constructor", [&](){
		Test::BinaryNode<int> node(3);
		Test::BinaryIterator<int, Test::BinaryNode> it(&node);
		Logger().WriteInformation("it.Current() = %d\n", it.Current());
		Logger().WriteInformation("it->Value() = %d\n", it->Value());
		Logger().WriteInformation("*it = %d\n", *it);

		Test::BinaryIterator<int, Test::BinaryNode> it2(it);
		Logger().WriteInformation("it2.Current() = %d\n", it2.Current());
		Logger().WriteInformation("it2->Value() = %d\n", it2->Value());
		Logger().WriteInformation("*it2 = %d\n", *it2);

		ASSERT1(it.Current() == it2.Current());
		ASSERT1(it->Value() == it2->Value());
		ASSERT1(*it == it2.Current());
		ASSERT1(*it == it2->Value());
		ASSERT1(*it == *it2);

		ASSERT1(it);
		ASSERT1(it2);
	});
}