#include "LongestCommonSubsequence.h"

namespace Test {
	//         0 y_0 y_1 y_2 ... y_(n-1)
	// 0       0 0   0   0       0
	// x_0     0
	// x_1     0
	// x_2     0
	// ...     
	// x_(m-1) 0
	//
	// select = 
	//          1    Up
	//          0    Diag
	//         -1    Left
	void LongestCommonSubsequence::LengthTable(string & x, string & y, int * length, int * select)
	{
		if (length == nullptr) throw invalid_argument("length is nullptr");
		if (select == nullptr) throw invalid_argument("select is nullptr");

		size_t m = x.length();
		size_t n = y.length();
		
		function<int &(int, int)> len = [&](int i, int j)->int &{
			return *(length + i*(1 + n) + j);
		};

		function<int &(int, int)> sel = [&](int i, int j)->int &{
			return *(select + i*(1 + n) + j);
		};

		for (unsigned int i = 0; i <= m; i ++) {
			len(i, 0) = 0;
		}

		for (unsigned int i = 1; i <= n; i ++) {
			len(0, i) = 0;
		}
		
		for (unsigned int i = 1; i <= m; i ++) {
			for (unsigned int j = 1; j <= n; j ++) {
				if (x[i-1] == y[j-1]) {
					len(i, j) = len(i - 1, j - 1) + 1;
					sel(i, j) = 0;
				} else if (len(i - 1, j) >= len(i, j - 1)) {
					len(i, j) = len(i - 1, j);
					sel(i, j) = 1;
				} else {
					len(i, j) = len(i, j - 1);
					sel(i, j) = -1;
				}
			}
		}
	}

	void LongestCommonSubsequence::PrintTable(int * T, size_t m, size_t n)
	{
		for (size_t i = 0; i < n; i ++) {
			cout << "\t" << i;
		}

		cout << endl;

		for (size_t i = 0; i < m; i ++) {
			cout << i;
			for (size_t j = 0; j < n; j ++) {
				cout << "\t" << *(T + i*n + j);
			}

			cout << endl;
		}
	}

	void LongestCommonSubsequence::PrintLCS(string & x, string & y)
	{
		size_t m = x.length();
		size_t n = y.length();
		size_t s = (1 + m) * (1 + n);
		unique_ptr<int[]> length(new int[s]);
		memset(length.get(), 0, s * sizeof(int));
		unique_ptr<int[]> select(new int[s]);
		memset(select.get(), 0, s * sizeof(int));

		LengthTable(x, y, length.get(), select.get());

		PrintTable(length.get(), 1 + m, 1 + n);
		PrintTable(select.get(), 1 + m, 1 + n);
		
		string lcs = "";
		int i = m;
		int j = n;
		while (i > 0 && j > 0) {
			int s = *(select.get() + i * (1 + n) + j);
			switch (s) {
			case 0:
				lcs.insert(0, &x[i-1], 1);
				i --;
				j --;
				break;
			case 1:
				i --;
				break;
			case -1:
				j --;
				break;
			}
		}

		cout << "X: " << x << endl;
		cout << "Y: " << y << endl;
		cout << "LCS: " << lcs << endl;
	}
}