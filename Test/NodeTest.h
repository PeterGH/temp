#pragma once
#include "..\Algorithm\Node.h"
#include "..\Algorithm\Node1.h"
#include "..\Algorithm\Node2.h"
#include "..\Algorithm\DoubleNode.h"
#include "..\Algorithm\SingleNode.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class NodeTest : public TestClass {
public:
	NodeTest(Log & log) : TestClass(log) {}
	~NodeTest(void) {}
	void Init(void);
};

