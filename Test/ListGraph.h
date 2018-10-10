#pragma once
#include "Graph.h"
namespace Test {
	template<class VertexValueType, class EdgeValueType> class ListGraph : public Graph<VertexValueType, EdgeValueType> {
	private:
		class AdjacencyNode {
		public:
			AdjacencyNode * next;
			unsigned int edgeId;
			AdjacencyNode(unsigned int id) : edgeId(id), next(nullptr) {}
		};

		class AdjacencyHead {
		public:
			AdjacencyNode * head;
			unsigned int vertexId;
			AdjacencyHead(unsigned int id) : vertexId(id), head(nullptr) {}
		};

		// [TODO] Get rid of AdjacencyHead. Use AdjacencyNode only.
		map<unsigned int, AdjacencyHead *> list;
	public:
		// Default the graph is directed
		ListGraph(void) : Graph() {}
		ListGraph(bool directed) : Graph(directed) {}
		~ListGraph(void)
		{
			map<unsigned int, AdjacencyHead *>::iterator it;
			for (it = this->list.begin(); it != this->list.end(); it++) {
				AdjacencyNode * h = it->second->head;
				if (h != nullptr) {
					AdjacencyNode * n;
					while (h->next != nullptr) {
						n = h;
						h = n->next;
						delete n;
					}

					delete h;
				}

				delete it->second;
			}
		}

		void InsertVertex(unsigned int id, VertexValueType value = 1)
		{
			Graph::InsertVertex(id, value);
			this->list[id] = new AdjacencyHead(id);
		}

		void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
		{
			Graph::InsertEdge(id, from, to, value);
			function<void(unsigned int)> link = [&](unsigned int f){
				AdjacencyNode * n = this->list[f]->head;
				if (n == nullptr) {
					this->list[f]->head = new AdjacencyNode(id);
				} else {
					while (n->next != nullptr) {
						n = n->next;
					}
					
					n->next = new AdjacencyNode(id);
				}
			};
			
			link(from);
			if (!this->directed && from != to) {
				// This will not be executed if
				// 1. It is a directed graph, or
				// 2. The edge is a circle
				
				// Note the neighboring vertex is edge->from
				link(to);
			}
		}

		int OutDegree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			AdjacencyNode * n = this->list[id]->head;
			int i = 0;
			while (n != nullptr) {
				// If the graph is undirected, then check if the edge is out or in.
				if (this->edges[n->edgeId]->from == id) i++;
				n = n->next;
			}

			return i;
		}

		int InDegree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			int i = 0;
			if (!this->directed) {
				AdjacencyNode * n = this->list[id]->head;
				while (n != nullptr) {
					if (this->edges[n->edgeId]->to == id) i++;
					n = n->next;
				}
			} else {
				// Directed graph. Have to enumerate all the edges.
				i = Graph::InDegree(id);
			}

			return i;
		}

		int Degree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			int i = 0;
			if (!this->directed) {
				AdjacencyNode * n = this->list[id]->head;
				while (n != nullptr) {
					if (this->edges[n->edgeId]->from == id) i++;
					if (this->edges[n->edgeId]->to == id) i++;
					n = n->next;
				}
			} else {
				i = Graph::Degree(id);
			}

			return i;
		}

		void OutNeighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			AdjacencyNode * n = this->list[id]->head;
			while (n != nullptr) {
				Edge * e = this->edges[n->edgeId];
				// If the graph is undirected, then check if the edge is out or in.
				if (e->from == id && e->to != id) neighbors.push_back(e->to);
				n = n->next;
			}
		}

		void InNeighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			if (!this->directed) {
				AdjacencyNode * n = this->list[id]->head;
				while (n != nullptr) {
					Edge * e = this->edges[n->edgeId];
					// If the graph is undirected, then check if the edge is out or in.
					if (e->from != id && e->to == id) neighbors.push_back(e->from);
					n = n->next;
				}
			} else {
				Graph::InNeighbors(id, neighbors);
			}
		}

		void Neighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			if (!this->directed) {
				AdjacencyNode * n = this->list[id]->head;
				while (n != nullptr) {
					Edge * e = this->edges[n->edgeId];
					// If the graph is undirected, then check if the edge is out or in.
					if (e->from == id && e->to != id) neighbors.push_back(e->to);
					if (e->from != id && e->to == id) neighbors.push_back(e->from);
					n = n->next;
				}
			} else {
				Graph::Neighbors(id, neighbors);
			}
		}

		void Print(void)
		{
			map<unsigned int, AdjacencyHead *>::iterator it;
			for (it = this->list.begin(); it != this->list.end(); it++) {
				unsigned int vid = it->second->vertexId;
				cout << vid;
				AdjacencyNode * n = it->second->head;
				while (n != nullptr) {
					unsigned int eid = n->edgeId;
					// Depending on if the graph is directed or not,
					// the neighboring vertex id can be edge->from or edge->to
					unsigned int tid = vid == this->edges[eid]->from ? this->edges[eid]->to :this->edges[eid]->from;
					cout << "->" << tid;
					n = n->next;
				}

				cout << endl;
			}
		}
	};
}