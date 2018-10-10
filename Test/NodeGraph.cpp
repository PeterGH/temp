#include "NodeGraph.h"

namespace Test {
	namespace NodeGraph {
		Node * Node::Clone()
		{
			Node * n = new Node();
			return n;
		}

		Node * Node::CloneGraph(Node * node, map<Node *, Node *> & map)
		{
			if (node == nullptr) return nullptr;

			Node * copy = node->Clone();
			map[node] = copy;
			queue<Node *> q;
			q.push(node);

			while (!q.empty()) {
				Node * n = q.front();
				q.pop();

				for_each (n->neighbors.begin(), n->neighbors.end(), [&](Node * c){
					if (map.find(c) == map.end()) {
						map[c] = c->Clone();
						q.push(c);
					}

					map[n]->neighbors.push_back(map[c]);
				});
			}

			return copy;
		}
	}
}