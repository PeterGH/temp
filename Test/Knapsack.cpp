#include "Knapsack.h"

namespace Test {

	// Assuming items<value, weight> are sorted by weight not decreasing
	// value:    v_0 v_1 v_2 v_3 ...... v_(n-1)
	// weight:   w_0 w_1 w_2 w_3 ...... w_(n-1), such that w_i <= w_j for i < j
	// capacity: W
	// matrix:   Define m[i][j] to be the maximum value that can be attained 
	//           with weight less than or equal to j using items up to i
	//           m[i][j] = m[i-1][j]                              if j < w_i
	//           m[i][j] = max(m[i-1][j], m[i-1][j-w_i] + v_i)    if j >= w_i
	//
	// i=0  0 1 2 3 ...... w_0-1 w_0 w_0+1 ...... W
	// v_0  0 0 0 0 ...... 0     v_0 v_0   ...... v_0
	//
	// i=1  0 1 2 3 ...... w_0-1 w_0 w_0+1 ...... w_1-1 w_1 w_1+1 ...... w_0+w_1-1 w_0+w_1 w_0+w_1+1 ...... W
	// v_1  0 0 0 0 ...... 0     v_0 v_0   ...... v_0 ......
	void Knapsack::ComputeValues(vector<pair<int,int>> & items, Matrix<int> & values)
	{
		int capacity = values.Cols() - 1;
		if (capacity <= 0) throw invalid_argument(String::Format("Invalid capacit %d", capacity));
		int countItems = items.size();
		int rows = values.Rows();
		if (countItems > rows) throw invalid_argument(String::Format("There are %d items but value matrix has only %d rows", countItems, rows));

		// Compute the first row of values[0][]
		// using item 0, i.e., value[0], weight[0]
		for (int j = 0; j <= capacity; j++) {
			if (j < items[0].second) {
				values(0, j) = 0;
			} else {
				values(0, j) = items[0].first;
			}
		}

		for (int i = 1; i < countItems; i++) {
			// Consider item i, i.e., value[i], weight[i]
			for (int j = 0; j <= capacity; j++) {
				if (j < items[i].second) {
					values(i, j) = values(i - 1, j);
				} else {
					values(i, j) = max(
						values(i - 1, j),
						values(i - 1, j - items[i].second) + items[i].first);
				}
			}
		}
	}

	void Knapsack::SelectItems(vector<pair<int,int>> & items, Matrix<int> & values, vector<pair<int,int>> & selected)
	{
		ComputeValues(items, values);

		int j = values.Cols() - 1;
		for (int i = items.size() - 1; i >= 0; i--) {
			if (i > 0 && values(i, j) > values(i - 1, j)) {
				selected.insert(selected.begin(), items[i]);
				j -= items[i].second;
			} else {
				if (j >= items[i].second && items[i].second > 0)
					selected.insert(selected.begin(), items[i]);
			}
		}
	}

	void Knapsack::PrintSolution(vector<pair<int,int>> & items, Matrix<int> & values)
	{
		vector<pair<int,int>> selected;
		SelectItems(items, values, selected);

		int capacity = values.Cols() - 1;
		int countItems = items.size();

		cout << "\t";
		for (int j = 0; j <= capacity; j++) {
			cout << "\t" << j;
		}

		cout << endl;

		for (int i = 0; i < countItems; i++) {
			cout << items[i].first << "\t" << items[i].second;
			for (int j = 0; j <= capacity; j++) {
				cout << "\t" << values(i, j);
			}

			cout << endl;
		}

		cout << "Selected items:" << endl;
		for_each(selected.begin(), selected.end(), [&](pair<int,int> & item){
			cout << "\t" << item.first << "\t" << item.second << endl;
		});
	}
}