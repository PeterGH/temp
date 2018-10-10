#pragma once
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
using namespace std;

namespace Test {
	namespace NodeGraph {
		class Node {
		public:
			__declspec(dllexport) Node(void) {}
			__declspec(dllexport) virtual ~Node(void) {}

			// Contain pointers to neighboring nodes
			vector<Node *> neighbors;

			// Get a cloned copy, not including neighbors
			__declspec(dllexport) virtual Node * Clone(void);

			// Clone the graph at node. 
			// Return the pointer to the copy of input node.
			// Use map to return the mapping of graph nodes and their clones.
			__declspec(dllexport) static Node * CloneGraph(Node * node, map<Node *, Node *> & map);
		};
	}
}