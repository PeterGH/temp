#pragma once
#include "..\Algorithm\BinaryNode.h"
#include "..\Algorithm\BinaryNodeWithParent.h"
#include "..\Algorithm\BinaryNodeWithRightSibling.h"
#include "..\Algorithm\PreOrderBinaryIterator.h"
#include "..\Algorithm\PreOrderBinaryIteratorWithOutStack.h"
#include "..\Algorithm\InOrderBinaryIterator.h"
#include "..\Algorithm\InOrderBinaryIteratorWithOutStack.h"
#include "..\Algorithm\PostOrderBinaryIterator.h"
#include "..\Algorithm\PostOrderBinaryIteratorWithOutStack.h"
#include "..\Algorithm\DoubleNode.h"
#include "..\Algorithm\TestClass.h"
using namespace std;
using namespace Test;
class BinaryNodeTest : public TestClass {
public:
	BinaryNodeTest(Log & log) : TestClass(log) {}
	~BinaryNodeTest(void) {}
	void Init(void);
};

