#pragma once
#include "Graph.h"
namespace Test {
	template<class VertexValueType, class EdgeValueType> class MatrixGraph : public Graph<VertexValueType, EdgeValueType> {
	private:
		struct Less : binary_function <pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>, bool> {
			bool operator() (const pair<unsigned int, unsigned int> & first, const pair<unsigned int, unsigned int> & second)
			{
				if (first.first < second.first) return true;
				if (first.first == second.first && first.second < second.second) return true;
				return false;
			}
		};

		map<pair<unsigned int, unsigned int>, unsigned int, Less> matrix;
	public:
		// Default the graph is directed
		MatrixGraph(void) : Graph() {}
		MatrixGraph(bool directed) : Graph(directed) {}
		~MatrixGraph(void) {}

		void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
		{
			Graph::InsertEdge(id, from, to, value);
			pair<unsigned int, unsigned int> key = make_pair(from, to);
			this->matrix[key] = id;
			if (!this->directed && from != to) {
				key = make_pair(to, from);
				this->matrix[key] = id;
			}
		}

		int OutDegree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Vertex *>::iterator to;
			pair<unsigned int, unsigned int> key;
			int i = 0;
			for (to = this->vertices.begin(); to != this->vertices.end(); to++) {
				key = make_pair(id, to->first);
				if (this->matrix.find(key) != this->matrix.end()) {
					int edgeId = this->matrix[key];
					if (this->edges[edgeId]->from == id) i++;
				}
			}

			return i;
		}

		int InDegree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Vertex *>::iterator from;
			pair<unsigned int, unsigned int> key;
			int i = 0;
			for (from = this->vertices.begin(); from != this->vertices.end(); from++) {
				key = make_pair(from->first, id);
				if (this->matrix.find(key) != this->matrix.end()) {
					int edgeId = this->matrix[key];
					if (this->edges[edgeId]->to == id) i++;
				}
			}

			return i;
		}

		int Degree(unsigned int id)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			int i = 0;
			if (!this->directed) {
				map<unsigned int, Vertex *>::iterator it;
				pair<unsigned int, unsigned int> key;
				for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
					key = make_pair(id, it->first);
					if (this->matrix.find(key) != this->matrix.end()) {
						int edgeId = this->matrix[key];
						if (this->edges[edgeId]->from == id) i++;
						if (this->edges[edgeId]->to == id) i++;
					}
				}
			} else {
				i += OutDegree(id);
				i += InDegree(id);
			}

			return i;
		}

		void OutNeighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Vertex *>::iterator to;
			pair<unsigned int, unsigned int> key;
			for (to = this->vertices.begin(); to != this->vertices.end(); to++) {
				if (to->first == id) continue;
				key = make_pair(id, to->first);
				if (this->matrix.find(key) != this->matrix.end()) {
					int edgeId = this->matrix[key];
					if (this->edges[edgeId]->from == id) neighbors.push_back(this->edges[edgeId]->to);
				}
			}
		}

		void InNeighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			map<unsigned int, Vertex *>::iterator from;
			pair<unsigned int, unsigned int> key;
			for (from = this->vertices.begin(); from != this->vertices.end(); from++) {
				if (from->first == id) continue;
				key = make_pair(from->first, id);
				if (this->matrix.find(key) != this->matrix.end()) {
					int edgeId = this->matrix[key];
					if (this->edges[edgeId]->to == id) neighbors.push_back(this->edges[edgeId]->from);
				}
			}
		}

		void Neighbors(unsigned int id, vector<unsigned int> & neighbors)
		{
			if (this->vertices.find(id) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", id));

			if (!this->directed) {
				map<unsigned int, Vertex *>::iterator it;
				pair<unsigned int, unsigned int> key;
				for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
					if (it->first == id) continue;
					key = make_pair(id, it->first);
					if (this->matrix.find(key) != this->matrix.end()) {
						int edgeId = this->matrix[key];
						if (this->edges[edgeId]->from == id) neighbors.push_back(this->edges[edgeId]->to);
						if (this->edges[edgeId]->to == id) neighbors.push_back(this->edges[edgeId]->from);
					}
				}
			} else {
				OutNeighbors(id, neighbors);
				InNeighbors(id, neighbors);
			}
		}

		void Print(void)
		{
			map<unsigned int, Vertex *>::iterator to;
			for (to = this->vertices.begin(); to != this->vertices.end(); to++) {
				cout << "\t" << to->first;
			}

			cout << endl;

			map<unsigned int, Vertex *>::iterator from;
			pair<unsigned int, unsigned int> key;
			for (from = this->vertices.begin(); from != this->vertices.end(); from++) {
				cout << from->first;
				for (to = this->vertices.begin(); to != this->vertices.end(); to++) {
					key = make_pair(from->first, to->first);
					cout << "\t";
					if (this->matrix.find(key) != this->matrix.end()) {
						cout << this->edges[this->matrix[key]]->value;
					}
				}

				cout << endl;
			}
		}
	};
}