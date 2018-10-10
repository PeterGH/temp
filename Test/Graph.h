#pragma once
#include <functional>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include "String.h"
using namespace std;
namespace Test {
	template<class VertexValueType, class EdgeValueType> class Graph {
	protected:
		class Vertex {
		public:
			unsigned int id;
			VertexValueType value;
			Vertex(unsigned int id, VertexValueType value) : id(id), value(value) {}
		};

		class Edge {
		public:
			unsigned int id;
			EdgeValueType value;
			unsigned int from;
			unsigned int to;
			Edge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value)
				: id(id), from(from), to(to), value(value)
			{
			}
		};

		map<unsigned int, Vertex *> vertices;
		map<unsigned int, Edge *> edges;
		bool directed;

	public:
		// Default the graph is directed
		Graph(void) : directed(true) {}
		Graph(bool directed) : directed(directed) {}
		virtual ~Graph(void)
		{
			map<unsigned int, Edge *>::iterator eit;
			for (eit = this->edges.begin(); eit != this->edges.end(); eit++) {
				delete eit->second;
			}

			map<unsigned int, Vertex *>::iterator vit;
			for (vit = this->vertices.begin(); vit != this->vertices.end(); vit++) {
				delete vit->second;
			}
		}

		virtual void InsertVertex(unsigned int id, VertexValueType value = 1)
		{
			if (this->vertices.find(id) != this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d already exists", id));

			this->vertices[id] = new Vertex(id, value);
		}

		virtual void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
		{
			if (this->edges.find(id) != this->edges.end())
				throw invalid_argument(String::Format("Edge id %d already exists", id));

			if (this->vertices.find(from) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", from));

			if (this->vertices.find(to) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", to));

			this->edges[id] = new Edge(id, from, to, value);
		}

		// Enumerate all the edges to compute the out-degree
		virtual int OutDegree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Edge *>::iterator it;
			int i = 0;
			for (it = this->edges.begin(); it != this->edges.end(); it++) {
				if (it->second->from == id) i++;
			}

			return i;
		}

		// Enumerate all the edges to compute the in-degree
		virtual int InDegree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Edge *>::iterator it;
			int i = 0;
			for (it = this->edges.begin(); it != this->edges.end(); it++) {
				if (it->second->to == id) i++;
			}

			return i;
		}

		// Enumerate all the edges to compute the degree
		// degree == out-degree + in-degree.
		virtual int Degree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Edge *>::iterator it;
			int i = 0;
			for (it = this->edges.begin(); it != this->edges.end(); it++) {
				if (it->second->from == id) i++;
				if (it->second->to == id) i++;
			}

			return i;
		}

		void Transpose(Graph & transpose)
		{
			map<unsigned int, Vertex *>::iterator vit;
			Vertex * v;
			for (vit = this->vertices.begin(); vit != this->vertices.end(); vit++) {
				v = vit->second;
				transpose.InsertVertex(v->id, v->value);
			}

			map<unsigned int, Edge *>::iterator eit;
			Edge * e;
			for (eit = this->edges.begin(); eit != this->edges.end(); eit++) {
				e = eit->second;
				transpose.InsertEdge(e->id, e->to, e->from, e->value);
			}
		}

		// Enumerate all the edges and get the neighbors pointing from a vertex.
		virtual void OutNeighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Edge *>::iterator it;
			for (it = this->edges.begin(); it != this->edges.end(); it++) {
				Edge * e = it->second;
				if (e->from == id && e->to != id) neighbors.push_back(e->to);
			}
		}

		// Enumerate all the edges and get the neighbors being pointed to a vertex.
		virtual void InNeighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Edge *>::iterator it;
			for (it = this->edges.begin(); it != this->edges.end(); it++) {
				Edge * e = it->second;
				if (e->from != id && e->to == id) neighbors.push_back(e->from);
			}
		}

		// Enumerate all the edges to compute neighbors
		// neighbors == out-neighbors + in-neighbors.
		virtual void Neighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Edge *>::iterator it;
			for (it = this->edges.begin(); it != this->edges.end(); it++) {
				Edge * e = it->second;
				if (e->from == id && e->to != id) neighbors.push_back(e->to);
				if (e->from != id && e->to == id) neighbors.push_back(e->from);
			}
		}

		// BreadthFirstSearch can find the shortest path

		// Starting at a vertex id, breadth-first search through the graph.
		// For each vertex call the provided function.
		void BreadthFirstSearch(unsigned int id, function<void(unsigned int)> & visit)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			set<unsigned int> visited;
			vector<unsigned int> frontier;
			frontier.push_back(id);
			while (!frontier.empty()) {
				unsigned int u = frontier.front();
				frontier.erase(frontier.begin());

				visit(u);
				visited.insert(u);

				vector<unsigned int> neighbors;
				if (this->directed) OutNeighbors(u, neighbors);
				else Neighbors(u, neighbors);
				for_each (neighbors.begin(), neighbors.end(), [&](unsigned int n)->void{
					if (visited.find(n) == visited.end()
						&& find(frontier.begin(), frontier.end(), n) == frontier.end()) {
						frontier.push_back(n);
					}
				});
			}
		}

		// Starting at a vertex id, breadth-first search through the graph.
		// For each vertex and its unvisited child, call the provided function.
		virtual void BreadthFirstSearch(unsigned int id, function<void(unsigned int, unsigned int)> & visit)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			set<unsigned int> visited;
			vector<unsigned int> frontier;

			visit(id, id);
			visited.insert(id);

			frontier.push_back(id);
			while (!frontier.empty()) {
				unsigned int u = frontier.front();
				frontier.erase(frontier.begin());
				vector<unsigned int> neighbors;
				if (this->directed) OutNeighbors(u, neighbors);
				else Neighbors(u, neighbors);
				for_each (neighbors.begin(), neighbors.end(), [&](unsigned int n)->void{
					if (visited.find(n) == visited.end()) {

						visit(u, n);
						visited.insert(n);

						frontier.push_back(n);
					}
				});
			}
		}

		// DepthFirstSearch cannot guarantee to find the shortest path

		// Starting at a vertex id, depth-first search through the graph.
		// For each vertex and its unvisited child, call the provided function.
		virtual void DepthFirstSearchInternal(unsigned int id, function<void(unsigned int)> & visit, set<unsigned int> & visited)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			visit(id);
			visited.insert(id);

			vector<unsigned int> neighbors;
			if (this->directed) OutNeighbors(id, neighbors);
			else Neighbors(id, neighbors);

			for_each (neighbors.begin(), neighbors.end(), [&](unsigned int n)->void{
				if (visited.find(n) == visited.end()) {
					DepthFirstSearchInternal(n, visit, visited);
				}
			});
		}

		virtual void DepthFirstSearch(unsigned int id, function<void(unsigned int)> & visit)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			set<unsigned int> visited;
			DepthFirstSearchInternal(id, visit, visited);
		}

		// Starting at a vertex id, depth-first search through the graph.
		// For each vertex and its unvisited child, call the provided function.
		virtual void DepthFirstSearch(unsigned int id, function<void(unsigned int, unsigned int)> & visit)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			set<unsigned int> visited;
			stack<unsigned int> path;
			map<unsigned int, vector<unsigned int>> children;
			map<unsigned int, vector<unsigned int>::iterator> next;
			function<void(unsigned int)> initChildren = [&](unsigned int n){
				vector<unsigned int> neighbors;
				if (this->directed) OutNeighbors(n, neighbors);
				else Neighbors(n, neighbors);
				children[n] = neighbors;
				next[n] = children[n].begin();
			};

			visit(id, id);
			visited.insert(id);
			path.push(id);
			initChildren(id);

			while (!path.empty()) {
				unsigned int top = path.top();
				vector<unsigned int>::iterator it = next[top];
				if (next[top] != children[top].end()) next[top]++;
				if (it == children[top].end()) {
					path.pop();
				} else if (visited.find(*it) == visited.end()) {
					visit(top, *it);
					visited.insert(*it);
					path.push(*it);
					initChildren(*it);
				}
			}
		}

		virtual void Print(void) {}
	};
}