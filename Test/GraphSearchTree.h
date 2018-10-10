#pragma once
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include "Graph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
using namespace std;
namespace Test {
	class GraphSearchTree {
	private:
		class Node {
		public:
			Node * parent;
			vector<Node *> children;
			unsigned int id;
			unsigned int distance;

			Node(unsigned int id, unsigned int d, Node * p) : id(id), distance(d), parent(p) {}
			Node(unsigned int id, unsigned int d) : id(id), distance(d), parent(nullptr) {}
			Node(unsigned int id) : id(id), distance(0), parent(nullptr) {}
			~Node(void);
			static void PostOrderWalk(Node * node, function<void(Node *)> f);
			static Node * Search(Node * node, unsigned int id);
			static stringstream & ToString(stringstream & ss, Node * node, int x, vector<int> & y);
		} * root;

		unsigned int rootId;

	public:
		__declspec(dllexport) GraphSearchTree(unsigned int id);
		__declspec(dllexport) ~GraphSearchTree(void);

		__declspec(dllexport) void Visit(unsigned int parentId, unsigned int childId);

		template<class VertexValueType, class EdgeValueType> void BreadthFirstSearch(Graph<VertexValueType, EdgeValueType> & g)
		{
			function<void(unsigned int, unsigned int)> v = [&](unsigned int p, unsigned int c){
				Visit(p, c);
			};

			g.BreadthFirstSearch(this->rootId, v);
		}

		template<class VertexValueType, class EdgeValueType> void DepthFirstSearch(Graph<VertexValueType, EdgeValueType> & g)
		{
			function<void(unsigned int, unsigned int)> v = [&](unsigned int p, unsigned int c){
				Visit(p, c);
			};

			g.DepthFirstSearch(this->rootId, v);
		}

		__declspec(dllexport) void Print(void);
	};
}