#include "GraphTest.h"

void GraphTest::CreateGraph(Test::Graph<int, int> & g){
	for (int i = 1; i < 7; i++) {
		g.InsertVertex(i);
	}

	g.InsertEdge(1, 1, 2, 1);
	g.InsertEdge(2, 1, 4, 1);
	g.InsertEdge(3, 2, 5, 1);
	g.InsertEdge(4, 3, 5, 1);
	g.InsertEdge(5, 3, 6, 1);
	g.InsertEdge(6, 4, 2);
	g.InsertEdge(7, 5, 4);
	g.InsertEdge(8, 6, 6);
}

void GraphTest::Init(void)
{	
	Add("Degree", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;
		Test::Graph<int, int> ug(false);
		Test::ListGraph<int, int> ulg(false);
		Test::MatrixGraph<int, int> umg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			function<void(int, int)> check = [&](int id, int degree){
				int d = g.Degree(id);
				Logger().WriteInformation("Vertex %d degree %d\n", id, d);
				ASSERT1(degree == d);
			};

			check(1, 2);
			check(2, 3);
			check(3, 2);
			check(4, 3);
			check(5, 3);
			check(6, 3);
		};

		Logger().WriteInformation("Graph\n");
		test(g);
		Logger().WriteInformation("ListGraph\n");
		test(lg);
		Logger().WriteInformation("MatrixGraph\n");
		test(mg);
		Logger().WriteInformation("Undirected Graph\n");
		test(ug);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(ulg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(umg);
	});

	Add("OutDegree", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;
		Test::Graph<int, int> ug(false);
		Test::ListGraph<int, int> ulg(false);
		Test::MatrixGraph<int, int> umg(false);
		
		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			function<void(int, int)> check = [&](int id, int degree){
				int d = g.OutDegree(id);
				Logger().WriteInformation("Vertex %d degree %d\n", id, d);
				ASSERT1(degree == d);
			};

			check(1, 2);
			check(2, 1);
			check(3, 2);
			check(4, 1);
			check(5, 1);
			check(6, 1);
		};

		Logger().WriteInformation("Graph\n");
		test(g);
		Logger().WriteInformation("ListGraph\n");
		test(lg);
		Logger().WriteInformation("MatrixGraph\n");
		test(mg);
		Logger().WriteInformation("Undirected Graph\n");
		test(ug);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(ulg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(umg);
	});

	Add("InDegree", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;
		Test::Graph<int, int> ug(false);
		Test::ListGraph<int, int> ulg(false);
		Test::MatrixGraph<int, int> umg(false);
		
		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			function<void(int, int)> check = [&](int id, int degree){
				int d = g.InDegree(id);
				Logger().WriteInformation("Vertex %d degree %d\n", id, d);
				ASSERT1(degree == d);
			};

			check(1, 0);
			check(2, 2);
			check(3, 0);
			check(4, 2);
			check(5, 2);
			check(6, 2);
		};

		Logger().WriteInformation("Graph\n");
		test(g);
		Logger().WriteInformation("ListGraph\n");
		test(lg);
		Logger().WriteInformation("MatrixGraph\n");
		test(mg);
		Logger().WriteInformation("Undirected Graph\n");
		test(ug);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(ulg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(umg);
	});

	Add("Neighbors", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;
		Test::Graph<int, int> ug(false);
		Test::ListGraph<int, int> ulg(false);
		Test::MatrixGraph<int, int> umg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			map<unsigned int, vector<unsigned int>> neighbors;
			neighbors[1] = vector<unsigned int> { 2, 4 };
			neighbors[2] = vector<unsigned int> { 1, 4, 5 };
			neighbors[3] = vector<unsigned int> { 5, 6 };
			neighbors[4] = vector<unsigned int> { 1, 2, 5 };
			neighbors[5] = vector<unsigned int> { 2, 3, 4 };
			neighbors[6] = vector<unsigned int> { 3 };

			function<void(unsigned int)> check = [&](unsigned int id){
				vector<unsigned int> n;
				g.Neighbors(id, n);
				sort(n.begin(), n.end());
				Logger().WriteInformation("Vertex %d neighbors:", id);
				for_each(n.begin(), n.end(), [&](unsigned int i){
					Logger().WriteInformation("\t%d", i);
				});

				Logger().WriteInformation("\n");

				ASSERT1(neighbors[id].size() == n.size());
				for (unsigned int i = 0; i < n.size(); i++) {
					ASSERT1(neighbors[id][i] == n[i]);
				}
			};

			check(1);
			check(2);
			check(3);
			check(4);
			check(5);
			check(6);
		};

		Logger().WriteInformation("Graph\n");
		test(g);
		Logger().WriteInformation("ListGraph\n");
		test(lg);
		Logger().WriteInformation("MatrixGraph\n");
		test(mg);
		Logger().WriteInformation("Undirected Graph\n");
		test(ug);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(ulg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(umg);
	});

	Add("OutNeighbors", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;
		Test::Graph<int, int> ug(false);
		Test::ListGraph<int, int> ulg(false);
		Test::MatrixGraph<int, int> umg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			map<unsigned int, vector<unsigned int>> neighbors;
			neighbors[1] = vector<unsigned int> { 2, 4 };
			neighbors[2] = vector<unsigned int> { 5 };
			neighbors[3] = vector<unsigned int> { 5, 6 };
			neighbors[4] = vector<unsigned int> { 2 };
			neighbors[5] = vector<unsigned int> { 4 };
			neighbors[6] = vector<unsigned int> { };

			function<void(unsigned int)> check = [&](unsigned int id){
				vector<unsigned int> n;
				g.OutNeighbors(id, n);
				sort(n.begin(), n.end());
				Logger().WriteInformation("Vertex %d neighbors:", id);
				for_each(n.begin(), n.end(), [&](unsigned int i){
					Logger().WriteInformation("\t%d", i);
				});

				Logger().WriteInformation("\n");

				ASSERT1(neighbors[id].size() == n.size());
				for (unsigned int i = 0; i < n.size(); i++) {
					ASSERT1(neighbors[id][i] == n[i]);
				}
			};

			check(1);
			check(2);
			check(3);
			check(4);
			check(5);
			check(6);
		};

		Logger().WriteInformation("Graph\n");
		test(g);
		Logger().WriteInformation("ListGraph\n");
		test(lg);
		Logger().WriteInformation("MatrixGraph\n");
		test(mg);
		Logger().WriteInformation("Undirected Graph\n");
		test(ug);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(ulg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(umg);
	});

	Add("InNeighbors", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;
		Test::Graph<int, int> ug(false);
		Test::ListGraph<int, int> ulg(false);
		Test::MatrixGraph<int, int> umg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			map<unsigned int, vector<unsigned int>> neighbors;
			neighbors[1] = vector<unsigned int> { };
			neighbors[2] = vector<unsigned int> { 1, 4 };
			neighbors[3] = vector<unsigned int> { };
			neighbors[4] = vector<unsigned int> { 1, 5 };
			neighbors[5] = vector<unsigned int> { 2, 3 };
			neighbors[6] = vector<unsigned int> { 3 };

			function<void(unsigned int)> check = [&](unsigned int id){
				vector<unsigned int> n;
				g.InNeighbors(id, n);
				sort(n.begin(), n.end());
				Logger().WriteInformation("Vertex %d neighbors:", id);
				for_each(n.begin(), n.end(), [&](unsigned int i){
					Logger().WriteInformation("\t%d", i);
				});

				Logger().WriteInformation("\n");

				ASSERT1(neighbors[id].size() == n.size());
				for (unsigned int i = 0; i < n.size(); i++) {
					ASSERT1(neighbors[id][i] == n[i]);
				}
			};

			check(1);
			check(2);
			check(3);
			check(4);
			check(5);
			check(6);
		};

		Logger().WriteInformation("Graph\n");
		test(g);
		Logger().WriteInformation("ListGraph\n");
		test(lg);
		Logger().WriteInformation("MatrixGraph\n");
		test(mg);
		Logger().WriteInformation("Undirected Graph\n");
		test(ug);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(ulg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(umg);
	});

	Add("TransposeListGraph", [&](){
		Test::ListGraph<int, int> g;
		Test::ListGraph<int, int> gt;
		CreateGraph(g);
		g.Print();
		g.Transpose(gt);
		gt.Print();
	});

	Add("TransposeMatrixGraph", [&](){
		Test::MatrixGraph<int, int> g;
		Test::MatrixGraph<int, int> gt;
		CreateGraph(g);
		g.Print();
		g.Transpose(gt);
		gt.Print();
	});

	Add("BFSUnDirected", [&](){
		Test::Graph<int, int> g(false);
		Test::ListGraph<int, int> lg(false);
		Test::MatrixGraph<int, int> mg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			vector<unsigned int> visited;
			function<void(unsigned int)> visit = [&](unsigned int id){
				visited.push_back(id);
			};
			
			g.BreadthFirstSearch(1, visit);
			sort(visited.begin(), visited.end());

			vector<unsigned int> visited2;
			function<void(unsigned int, unsigned int)> visit2 = [&](unsigned int u, unsigned int id){
				visited2.push_back(id);
			};
			
			g.BreadthFirstSearch(1, visit2);
			sort(visited2.begin(), visited2.end());

			Logger().WriteInformation("Breadth-First Search:");
			for_each (visited.begin(), visited.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			Logger().WriteInformation("Breadth-First Search 2:");
			for_each (visited2.begin(), visited2.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			ASSERT1(visited.size() == 6);
			ASSERT1(visited2.size() == 6);
			for (int i = 1; i < 7; i++) {
				ASSERT1(visited[i - 1] == i);
				ASSERT1(visited2[i - 1] == i);
			}
		};

		Logger().WriteInformation("Undirected Graph\n");
		test(g);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(lg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(mg);
	});

	Add("BFSDirected", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;
				
		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			vector<unsigned int> visited;
			function<void(unsigned int)> visit = [&](unsigned int id){
				visited.push_back(id);
			};
			
			g.BreadthFirstSearch(1, visit);
			sort(visited.begin(), visited.end());

			vector<unsigned int> visited2;
			function<void(unsigned int, unsigned int)> visit2 = [&](unsigned int u, unsigned int id){
				visited2.push_back(id);
			};
			
			g.BreadthFirstSearch(1, visit2);
			sort(visited2.begin(), visited2.end());

			Logger().WriteInformation("Breadth-First Search:");
			for_each (visited.begin(), visited.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			Logger().WriteInformation("Breadth-First Search 2:");
			for_each (visited2.begin(), visited2.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			ASSERT1(visited.size() == 4);
			ASSERT1(visited2.size() == 4);
			ASSERT1(visited[0] == 1);
			ASSERT1(visited2[0] == 1);
			ASSERT1(visited[1] == 2);
			ASSERT1(visited2[1] == 2);
			ASSERT1(visited[2] == 4);
			ASSERT1(visited2[2] == 4);
			ASSERT1(visited[3] == 5);
			ASSERT1(visited2[3] == 5);
		};

		Logger().WriteInformation("Directed Graph\n");
		test(g);
		Logger().WriteInformation("Directed ListGraph\n");
		test(lg);
		Logger().WriteInformation("Directed MatrixGraph\n");
		test(mg);
	});

	Add("DFSUnDirected", [&](){
		Test::Graph<int, int> g(false);
		Test::ListGraph<int, int> lg(false);
		Test::MatrixGraph<int, int> mg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			vector<unsigned int> visited;
			function<void(unsigned int)> visit = [&](unsigned int id){
				visited.push_back(id);
			};

			g.DepthFirstSearch(1, visit);
			sort(visited.begin(), visited.end());

			vector<unsigned int> visited2;
			function<void(unsigned int, unsigned int)> visit2 = [&](unsigned int u, unsigned int id){
				visited2.push_back(id);
			};

			g.DepthFirstSearch(1, visit2);
			sort(visited2.begin(), visited2.end());

			Logger().WriteInformation("Depth-First Search:");
			for_each (visited.begin(), visited.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			Logger().WriteInformation("Depth-First Search 2:");
			for_each (visited2.begin(), visited2.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			ASSERT1(visited.size() == 6);
			ASSERT1(visited2.size() == 6);
			for (int i = 1; i < 7; i++) {
				ASSERT1(visited[i - 1] == i);
				ASSERT1(visited2[i - 1] == i);
			}
		};

		Logger().WriteInformation("Undirected Graph\n");
		test(g);
		Logger().WriteInformation("Undirected ListGraph\n");
		test(lg);
		Logger().WriteInformation("Undirected MatrixGraph\n");
		test(mg);
	});

	Add("DFSDirected", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);

			vector<unsigned int> visited;
			function<void(unsigned int)> visit = [&](unsigned int id){
				visited.push_back(id);
			};

			g.DepthFirstSearch(1, visit);
			sort(visited.begin(), visited.end());

			vector<unsigned int> visited2;
			function<void(unsigned int, unsigned int)> visit2 = [&](unsigned int u, unsigned int id){
				visited2.push_back(id);
			};

			g.DepthFirstSearch(1, visit2);
			sort(visited2.begin(), visited2.end());

			Logger().WriteInformation("Depth-First Search:");
			for_each (visited.begin(), visited.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			Logger().WriteInformation("Depth-First Search 2:");
			for_each (visited2.begin(), visited2.end(), [&](unsigned int i){
				Logger().WriteInformation("\t%d", i);
			});

			Logger().WriteInformation("\n");

			ASSERT1(visited.size() == 4);
			ASSERT1(visited2.size() == 4);
			ASSERT1(visited[0] == 1);
			ASSERT1(visited2[0] == 1);
			ASSERT1(visited[1] == 2);
			ASSERT1(visited2[1] == 2);
			ASSERT1(visited[2] == 4);
			ASSERT1(visited2[2] == 4);
			ASSERT1(visited[3] == 5);
			ASSERT1(visited2[3] == 5);
		};

		Logger().WriteInformation("Directed Graph\n");
		test(g);
		Logger().WriteInformation("Directed ListGraph\n");
		test(lg);
		Logger().WriteInformation("Directed MatrixGraph\n");
		test(mg);
	});

	Add("BFSTreeDirected", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);
			Test::GraphSearchTree tree(1);
			tree.BreadthFirstSearch<int, int>(g);
			tree.Print();
		};

		Logger().WriteInformation("Directed Graph\n");
		test(g);
		Logger().WriteInformation("Directed ListGraph\n");
		test(lg);
		Logger().WriteInformation("Directed MatrixGraph\n");
		test(mg);
	});

	Add("BFSTreeUnDirected", [&](){
		Test::Graph<int, int> g(false);
		Test::ListGraph<int, int> lg(false);
		Test::MatrixGraph<int, int> mg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);
			Test::GraphSearchTree tree(5);
			tree.BreadthFirstSearch<int, int>(g);
			tree.Print();
		};

		Logger().WriteInformation("UnDirected Graph\n");
		test(g);
		Logger().WriteInformation("UnDirected ListGraph\n");
		test(lg);
		Logger().WriteInformation("UnDirected MatrixGraph\n");
		test(mg);
	});

	Add("DFSTreeDirected", [&](){
		Test::Graph<int, int> g;
		Test::ListGraph<int, int> lg;
		Test::MatrixGraph<int, int> mg;

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);
			Test::GraphSearchTree tree(1);
			tree.DepthFirstSearch<int, int>(g);
			tree.Print();
		};

		Logger().WriteInformation("Directed Graph\n");
		test(g);
		Logger().WriteInformation("Directed ListGraph\n");
		test(lg);
		Logger().WriteInformation("Directed MatrixGraph\n");
		test(mg);
	});

	Add("DFSTreeUnDirected", [&](){
		Test::Graph<int, int> g(false);
		Test::ListGraph<int, int> lg(false);
		Test::MatrixGraph<int, int> mg(false);

		function<void(Test::Graph<int, int> &)> test = [&](Test::Graph<int, int> & g){
			CreateGraph(g);
			Test::GraphSearchTree tree(5);
			tree.DepthFirstSearch<int, int>(g);
			tree.Print();
		};

		Logger().WriteInformation("UnDirected Graph\n");
		test(g);
		Logger().WriteInformation("UnDirected ListGraph\n");
		test(lg);
		Logger().WriteInformation("UnDirected MatrixGraph\n");
		test(mg);
	});
}