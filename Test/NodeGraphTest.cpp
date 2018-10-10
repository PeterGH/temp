#include "NodeGraphTest.h"

class ANode : public Test::NodeGraph::Node {
public:
	ANode(int i) : id(i) {}
	~ANode(void);
	int id;

	ANode * Clone(void);
	void Print(void);
};

ANode::~ANode(void)
{
	cout << "Deleting " << this->id << endl;
}

ANode * ANode::Clone(void)
{
	ANode * n = new ANode(this->id);
	return n;
}

void ANode::Print(void)
{
	set<ANode *> visited;
	queue<ANode *> q;
	visited.insert(this);
	q.push(this);

	while (!q.empty()) {
		ANode * n = q.front();
		q.pop();
		cout << n->id << endl;
		for_each (n->neighbors.begin(), n->neighbors.end(), [&](Node * c){
			cout << " ----> " << ((ANode *)c)->id << endl;
			if (visited.find((ANode *)c) == visited.end()) {
				visited.insert((ANode *)c);
				q.push((ANode *)c);
			}
		});
	}
}

void NodeGraphTest::Init(void)
{
	Add("DirectedClone", [&](){
		vector<unique_ptr<ANode>> nodes;
		for (int i = 0; i < 6; i++) {
			nodes.push_back(make_unique<ANode>(i));
		}

		function<void(int, int)> link = [&](int i, int j) {
			nodes[i]->neighbors.push_back(nodes[j].get());
		};

		// 0 -> 1    2
		// |   ^|   ^|
		// |  / |  / |
		// v /  v /  v
		// 3 <- 4    5
		link(0, 1);
		link(0, 3);
		link(1, 4);
		link(3, 1);
		link(4, 3);
		link(4, 2);
		link(2, 5);

		map<Test::NodeGraph::Node *, Test::NodeGraph::Node *> map;
		ANode * copy = (ANode *)Test::NodeGraph::Node::CloneGraph(nodes[0].get(), map);

		copy->Print();

		cout << "Deleting clone ... " << endl;
		for_each (map.begin(), map.end(), [&](pair<Test::NodeGraph::Node *, Test::NodeGraph::Node *> p){
			ANode * n = (ANode *)p.second;
			delete n;
		});

		cout << "Deleting original ... " << endl;
	});

	Add("UnDirectedClone", [&](){
		vector<unique_ptr<ANode>> nodes;
		for (int i = 0; i < 6; i++) {
			nodes.push_back(make_unique<ANode>(i));
		}

		function<void(int, int)> link = [&](int i, int j) {
			nodes[i]->neighbors.push_back(nodes[j].get());
		};

		// 0 -> 1    2
		// ^   ^^   ^^
		// |  / |  / |
		// v v  v /  v
		// 3 <- 4    5
		link(0, 1);
		link(0, 3);
		link(1, 3);
		link(1, 4);
		link(2, 5);
		link(3, 0);
		link(3, 1);
		link(4, 1);
		link(4, 2);
		link(4, 3);

		map<Test::NodeGraph::Node *, Test::NodeGraph::Node *> map;
		ANode * copy = (ANode *)Test::NodeGraph::Node::CloneGraph(nodes[0].get(), map);

		copy->Print();

		cout << "Deleting clone ... " << endl;
		for_each (map.begin(), map.end(), [&](pair<Test::NodeGraph::Node *, Test::NodeGraph::Node *> p){
			ANode * n = (ANode *)p.second;
			delete n;
		});

		cout << "Deleting original ... " << endl;
	});
}