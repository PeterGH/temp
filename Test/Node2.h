#pragma once
#include <map>
#include <queue>
#include "Node1.h"
using namespace std;
namespace Test {
	template<class T> class Node2 : public Node1<T> {
	protected:
		Node * second;
	public:
		Node2(const T & v) : Node1(v), second(nullptr) {}

		virtual ~Node2(void)
		{
			if (this->second != nullptr) {
				this->second = nullptr;
			}
		}

		static Node2 * Clone(Node2 * node);
	};

	template<class T> Node2<T> * Node2<T>::Clone(Node2 * node)
	{
		if (node == nullptr) return nullptr;
		queue<Node2<T> *> q;
		map<Node2<T> *, Node2<T> *> cloned;
		Node2<T> * nodeCopy = new Node2<T>(node->value);
		q.push(node);
		cloned[node] = nodeCopy;
		while (!q.empty()) {
			node = q.front();
			q.pop();
			if (node->first != nullptr) {
				if (cloned.find((Node2<T> *)node->first) == cloned.end()) {
					Node2<T> * firstCopy = new Node2<T>(((Node2<T> *)node->first)->value);
					cloned[(Node2<T> *)node->first] = firstCopy;
					q.push((Node2<T> *)node->first);
				}
				cloned[node]->first = cloned[(Node2<T> *)node->first];
			}
			if (node->second != nullptr) {
				if (cloned.find((Node2<T> *)node->second) == cloned.end()) {
					Node2<T> * secondCopy = new Node2<T>(((Node2<T> *)node->second)->value);
					cloned[(Node2<T> *)node->second] = secondCopy;
					q.push((Node2<T> *)node->second);
				}
				cloned[node]->second = cloned[(Node2<T> *)node->second];
			}
		}
		return nodeCopy;
	}
}