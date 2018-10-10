#include "GraphSearchTree.h"
namespace Test {
	GraphSearchTree::Node::~Node(void)
	{
		this->parent = nullptr;
		this->children.clear();
	}

	void GraphSearchTree::Node::PostOrderWalk(Node * node, function<void(Node *)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<Node *> path;
		map<Node *, vector<Node *>::iterator> next;
		path.push(node);
		next[node] = node->children.begin();
		while (!path.empty()) {
			Node * top = path.top();
			vector<Node *>::iterator it = next[top];
			if (it == top->children.end()) {
				// Either top has no children, or
				// all the children have been visited.
				if (top->parent != nullptr) next[top->parent]++;
				f(top);
				path.pop();
			} else {
				path.push(*it);
				next[*it] = (*it)->children.begin();
			}
		}
	}

	GraphSearchTree::Node * GraphSearchTree::Node::Search(Node * node, unsigned int id)
	{
		if (node == nullptr) return nullptr;
		if (node->id == id) return node;
		queue<Node *> q;
		q.push(node);
		while (!q.empty()) {
			Node * n = q.front();
			q.pop();
			for (unsigned int i = 0; i < n->children.size(); i++) {
				Node * c = n->children[i];
				if (c->id == id) return c;
				q.push(c);
			}
		}

		return nullptr;
	}

	stringstream & GraphSearchTree::Node::ToString(stringstream & ss, Node * node, int x, vector<int> & y)
	{
		static string link = "____";
		string c = String::Format(" %d:%d ", node->id, node->distance);
		ss << c;

		if (node->children.size() == 0) return ss;

		x += c.length();
		if (node->children.size() > 1) {
			// Record current x coordinate,
			// so it can be used to draw '|'
			y.push_back(x);
		}

		vector<Node *>::iterator it = node->children.begin();
		ss << link;
		ToString(ss, *it, x + link.length(), y);
		it++;
		while (it != node->children.end()) {
			ss << endl;
			for (size_t i = 0; i < y.size(); i++) {
				int len = i == 0 ? y[i] : y[i] - y[i - 1];
				string blank(len - 1, ' ');
				ss << blank << '|';
			}

			if (it + 1 == node->children.end())	{
				// The last child is ready to print
				// Remove its coordinate because it is not needed any more
				y.pop_back();
			}

			ss << link;
			ToString(ss, *it, x + link.length(), y);
			it++;
		}

		return ss;
	}

	GraphSearchTree::GraphSearchTree(unsigned int id)
	{
		this->rootId = id;
		this->root = new Node(rootId);
	}

	GraphSearchTree::~GraphSearchTree()
	{
		Node::PostOrderWalk(this->root, [&](Node * n){ delete n; });
	}

	void GraphSearchTree::Visit(unsigned int parentId, unsigned int childId)
	{
		if (childId == this->rootId) return;
		Node * p = Node::Search(this->root, parentId);
		if (p == nullptr) return;
		Node * c = new Node(childId, p->distance + 1, p);
		p->children.push_back(c);
	}

	void GraphSearchTree::Print(void)
	{
		stringstream ss;
		vector<int> y;
		Node::ToString(ss, this->root, 0, y);
		ss << endl;
		cout << ss.str();
	}
}