#include "MatrixGraphTest.h"

void MatrixGraphTest::Init(void)
{
	Add("InsertDirected", [&](){
		Test::MatrixGraph<int, int> graph;
		for (int i = 1; i < 7; i++) {
			graph.InsertVertex(i);
		}

		graph.InsertEdge(1, 1, 2, 1);
		graph.InsertEdge(2, 1, 4, 1);
		graph.InsertEdge(3, 2, 5, 1);
		graph.InsertEdge(4, 3, 5, 1);
		graph.InsertEdge(5, 3, 6, 1);
		graph.InsertEdge(6, 4, 2);
		graph.InsertEdge(7, 5, 4);
		graph.InsertEdge(8, 6, 6);
		graph.Print();
	});

	Add("InsertUnDirected", [&](){
		Test::MatrixGraph<int, int> graph(false);
		for (int i = 1; i < 7; i++) {
			graph.InsertVertex(i);
		}

		graph.InsertEdge(1, 1, 2, 1);
		graph.InsertEdge(2, 1, 4, 1);
		graph.InsertEdge(3, 2, 5, 1);
		graph.InsertEdge(4, 3, 5, 1);
		graph.InsertEdge(5, 3, 6, 1);
		graph.InsertEdge(6, 4, 2);
		graph.InsertEdge(7, 5, 4);
		graph.InsertEdge(8, 6, 6);
		graph.Print();
	});
}