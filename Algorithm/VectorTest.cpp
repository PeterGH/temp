#include "Header.h"

void VectorTest::Init(void)
{
	Add("SortPairs", [&]() {
		vector<int> v;
		for (int i = 0; i < 20; i++) {
			v.push_back(rand());
		}
		auto print = [&](vector<pair<int, int>> i) {
			Logger().WriteInformation("[");
			for (size_t j = 0; j < i.size(); j++) {
				if (j > 0) Logger().WriteInformation(", ");
				Logger().WriteInformation("<%d,%d>", i[j].first, i[j].second);
			}
			Logger().WriteInformation("]\n");
		};
		vector<pair<int, int>> p;
		for (int i = 0; i < (int)v.size(); i++) {
			p.push_back(make_pair(i, v[i]));
		}
		print(p);
		random_shuffle(p.begin(), p.end());
		print(p);
		sort(p.begin(), p.end());
		print(p);
	});
}