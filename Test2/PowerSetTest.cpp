#include "PowerSetTest.h"

void PowerSetTest::Init(void)
{
	Add("Recursive", [&](){
		vector<int> set;
		for (int i = 0; i < 5; i ++) {
			set.push_back(i);
		}

		vector<vector<int>> powerset = My::PowerSet<int>::Compute(set);
		for_each (powerset.begin(), powerset.end(), [](vector<int> & v){
			cout << "{ ";
			for_each (v.begin(), v.end(), [](int i){
				cout << i << " ";
			});

			cout << "}" << endl;
		});
	});
}