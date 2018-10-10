#pragma once
#include "..\Algorithm\Graph.h"
#include "..\Algorithm\GraphSearchTree.h"
#include "..\Algorithm\ListGraph.h"
#include "..\Algorithm\MatrixGraph.h"
#include "..\Algorithm\TestClass.h"
class GraphTest : public Test::TestClass {
private:
	void CreateGraph(Test::Graph<int, int> & g);

public:
	GraphTest(Test::Log & log) : Test::TestClass(log) {}
	~GraphTest(void) {}
	void Init(void);
};

