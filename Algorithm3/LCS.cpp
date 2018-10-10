#include "LCS.h"
#include <iostream>
#include <stdlib.h>

LCS::LCS(void)
{
}


LCS::~LCS(void)
{
}

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
void LCS::LengthTable(string & x, string & y, int * length, int * select)
{
	size_t m = x.length();
	size_t n = y.length();
	for (unsigned int i = 0; i <= m; i ++) {
		// length[i][0] = 0;
		*(length + i*(1+n)) = 0;
	}
	for (unsigned int i = 1; i <= n; i ++) {
		// length[0][i] = 0;
		*(length + i) = 0;
	}
	for (unsigned int i = 1; i <= m; i ++) {
		for (unsigned int j = 1; j <= n; j ++) {
			if (x[i-1] == y[j-1]) {
				*(length + i*(1+n) + j) = *(length + (i-1)*(1+n) + (j-1)) + 1;
				*(select + i*(1+n) + j) = 0;
			} else if (*(length + (i-1)*(1+n) + j) >= *(length + i*(1+n) + (j-1))) {
				*(length + i*(1+n) + j) = *(length + (i-1)*(1+n) + j);
				*(select + i*(1+n) + j) = 1;
			} else {
				*(length + i*(1+n) + j) = *(length + i*(1+n) + (j-1));
				*(select + i*(1+n) + j) = -1;
			}
		}
	}
}

void LCS::PrintTable(int * T, size_t m, size_t n)
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

void LCS::PrintLCS(string & x, string & y)
{
	size_t m = x.length();
	size_t n = y.length();
	size_t s = (1 + m) * (1 + n);
	int * length = (int *)malloc(s * sizeof(int));
	memset(length, 0, s*sizeof(int));
	int * select = (int *)malloc(s * sizeof(int));	
	memset(select, 0, s*sizeof(int));

	LengthTable(x, y, length, select);

	PrintTable(length, (1+m), (1+n));
	PrintTable(select, (1+m), (1+n));

	string lcs = "";
	int i = m;
	int j = n;
	while (i > 0 && j > 0) {
		int s = *(select + i*(1+n) + j);
		switch (s)
		{
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

	free(length);
	free(select);
	
	cout << "X: " << x << endl;
	cout << "Y: " << y << endl;
	cout << "LCS: " << lcs << endl;

	
}