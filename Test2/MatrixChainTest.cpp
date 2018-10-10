#include "MatrixChainTest.h"

void MatrixChainTest::Init(void) {
	Add("MatrixChain", [&](){
		int dimension[7] = {30, 35, 15, 5, 10, 20, 25};
		int count = 7;
		int cost[6][6];
		int split[6][6];

		memset(cost, 0, 36*sizeof(int));
		memset(split, 0, 36*sizeof(int));

		My::MatrixChain::ComputeCostTable(dimension, count, &cost[0][0], &split[0][0]);

		for (int i = 0; i < 6; i ++) {
			cout << "\t" << dimension[i] << "x" << dimension[i+1];
		}
		cout << endl;

		for (int i = 0; i < 6; i ++) {
			cout << "\t" << i;
		}
		cout << endl;

		for (int i = 0; i < 6; i ++) {
			cout << i;
			for (int j = 0; j < 6; j ++) {
				cout << "\t";
				if (j >= i) cout << cost[i][j];
			}
			cout << endl;
		}

		cout << endl;

		for (int i = 0; i < 6; i ++) {
			cout << i;
			for (int j = 0; j < 6; j ++) {
				cout << "\t";
				if (j >= i) cout << split[i][j];
			}
			cout << endl;
		}
	});
}