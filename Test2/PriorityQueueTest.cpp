#include "PriorityQueueTest.h"
#include <queue>
#include <algorithm>
using namespace std;

void PriorityQueueTest::Init(void)
{
	Add("PriorityQueue", [&](){
		vector<int> v(20);
		generate(v.begin(), v.end(), rand);

		cout << "Vector v is ( " ;
		for_each (v.begin(), v.end(), [&](int x) {
			cout << x << " ";
		});
		cout << ")." << endl;

		priority_queue<int> maxQueue (v.begin(), v.end());
		cout << "Max Priority Queue:" << endl;
		while (!maxQueue.empty()) {
			int i = maxQueue.top();
			cout << i << " ";
			maxQueue.pop();
		}
		cout << endl;

		priority_queue<int, vector<int>, greater<int>> minQueue (v.begin(), v.end());
		cout << "Min Priority Queue:" << endl;
		while (!minQueue.empty()) {
			int i = minQueue.top();
			cout << i << " ";
			minQueue.pop();
		}
		cout << endl;
	});
}