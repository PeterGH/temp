#include "VectorTest.h"

void VectorTest::Init(void)
{
	Add("Jagged Array", [&](){
		vector<vector<int>> jagged;

		for (int i = 1; i < 10; i++) {
			vector<int> v;
			for (int j = 0; j < i; j++) {
				v.push_back(j);
			}

			jagged.push_back(v);
		}

		for_each (jagged.begin(), jagged.end(), [&](const vector<int> & v) -> void {
			for_each (v.begin(), v.end(), [&](int i) -> void {
				cout << "\t" << i;
			});

			cout << endl;
		});
	});

	Add("Array[i]", [&](){
		vector<vector<int>> jagged;

		for (int i = 1; i < 10; i++) {
			vector<int> v;
			for (int j = 0; j < i; j++) {
				v.push_back(j);
			}

			jagged.push_back(v);
		}

		for (size_t j = 0; j < jagged.size(); j++) {
			for (size_t i = 0; i < jagged[j].size(); i++) {
				cout << "\t" << jagged[j][i];
			}

			cout << endl;
		}
	});
}