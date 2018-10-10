#include "Header.h"

void DPProblemTest::Init(void)
{
	Add("CointSelect", [&]() {
		auto check = [&](int * input, int length) {
			Logger().WriteInformation("Input:");
			Logger().Print(input, length);

			auto print = [&](int value, vector<int> & indices) {
				Logger().WriteInformation("\tMax value:\t  %d\n", value);
				Logger().WriteInformation("\tIndices:\t");
				Logger().Print(indices);
				Logger().WriteInformation("\tItems:\t");
				Logger().Print<int>(indices, [&](Log & l, int i) {
					l.WriteInformation("%d", input[i]);
				});
			};

			vector<int> indices;
			vector<int> indices2;
			int v = DPProblem::CoinSelect::MaxSelection(input, length, indices);
			Logger().WriteInformation("Solution 1\n");
			print(v, indices);
			int v2 = DPProblem::CoinSelect::MaxSelection2(input, length, indices2);
			Logger().WriteInformation("Solution 2\n");
			print(v2, indices2);

			ASSERT1(v == v2);
			ASSERT1(indices.size() == indices2.size());
			for (unsigned int i = 0; i < indices.size(); i++) {
				ASSERT1(indices[i] == indices2[i]);
			}
		};

		int c[] = { 3, 2, 2, 3, 1, 2 };
		int l = sizeof(c) / sizeof(c[0]);
		check(c, l);

		int c2[] = { 3, 2, 2, 3, 1, 2, 1 };
		int l2 = sizeof(c2) / sizeof(c2[0]);
		check(c2, l2);

		for (int i = 0; i < 100; i++) {
			int length = 1 + rand() % 100;
			unique_ptr<int[]> input(new int[length]);
			Array::Random(input.get(), length);
			Logger().WriteInformation("Run %d: %d elements\n", i, length);
			check(input.get(), length);
		}
	});

	Add("LongestStringWithKeystrokes", [&]() {
		unsigned long long expect[100] = {
			1,	2,	3,	4,	5,	6,	7,	9,	12,	16,
			20,	25,	30,	36,	48,	64,	80,	100,	125,	150,
			192,	256,	320,	400,	500,	625,	768,	1024,	1280,	1600,
			2000,	2500,	3125,	4096,	5120,	6400,	8000,	10000,	12500,	16384,
			20480,	25600,	32000,	40000,	50000,	65536,	81920,	102400,	128000,	160000,
			200000,	262144,	327680,	409600,	512000,	640000,	800000,	1048576,	1310720,	1638400,
			2048000,	2560000,	3200000,	4194304,	5242880,	6553600,	8192000,	10240000,	12800000,	16777216,
			20971520,	26214400,	32768000,	40960000,	51200000,	67108864,	83886080,	104857600,	131072000,	163840000,
			204800000,	268435456,	335544320,	419430400,	524288000,	655360000,	819200000,	1073741824,	1342177280,	1677721600,
			2097152000,	2621440000,	3276800000,	4294967296,	5368709120,	6710886400,	8388608000,	10485760000,	13107200000,	17179869184 };
		unsigned long long actual[100];
		DPProblem::LongestStringWithKeystrokes(100, actual);
		for (int i = 0; i < 100; i++) {
			Logger().WriteInformation("%d: %llu %s %llu\n", i + 1, actual[i], actual[i] == expect[i] ? "==" : "!=", expect[i]);
			ASSERT1(actual[i] == expect[i]);
		}
	});

	Add("Knapsack", [&]() {
		{
			vector<pair<int, int>> items;
			items.push_back(make_pair(60, 2));
			items.push_back(make_pair(100, 4));
			items.push_back(make_pair(120, 6));
			Matrix<int> values(3, 11);
			DPProblem::Knapsack::PrintSolution(items, values);
		}
		{
			vector<pair<int, int>> items;
			items.push_back(make_pair(60, 2));
			items.push_back(make_pair(100, 2));
			items.push_back(make_pair(120, 6));
			Matrix<int> values(3, 11);
			DPProblem::Knapsack::ComputeValues(items, values);
			DPProblem::Knapsack::PrintSolution(items, values);
		}
	});

	Add("LongestCommonSubsequence", [&]() {
		string x = "ABCBDAB";
		string y = "BDCABA";
		DPProblem::LongestCommonSubsequence::PrintLCS(x, y);

		x = "ABCBDABJOHBFUOBLNJIPIOHUGOYO";
		y = "BDCABATIOFTYFIBLOILUIIGGOBLOBIP";
		DPProblem::LongestCommonSubsequence::PrintLCS(x, y);
	});

	Add("LongestIncreasingSubsequence", [&]() {
		{
			int I[] = { 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I, 1);
		}
		{
			int I1[] = { 1, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I1, 2);

			int I2[] = { 2, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I2, 2);
		}
		{
			int I1[] = { 1, 2, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I1, 3);

			int I2[] = { 1, 3, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I2, 3);

			int I3[] = { 2, 1, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I3, 3);

			int I4[] = { 2, 3, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I4, 3);

			int I5[] = { 3, 1, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I5, 3);

			int I6[] = { 3, 2, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I6, 3);
		}
		{
			int I1[] = { 1, 2, 3, 4 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I1, 4);

			int I2[] = { 1, 2, 4, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I2, 4);

			int I3[] = { 1, 3, 2, 4 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I3, 4);

			int I4[] = { 1, 3, 4, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I4, 4);

			int I5[] = { 1, 4, 2, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I5, 4);

			int I6[] = { 1, 4, 3, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I6, 4);

			int I7[] = { 2, 1, 3, 4 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I7, 4);

			int I8[] = { 2, 1, 4, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I8, 4);

			int I9[] = { 2, 3, 1, 4 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I9, 4);

			int I10[] = { 2, 3, 4, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I10, 4);

			int I11[] = { 2, 4, 1, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I11, 4);

			int I12[] = { 2, 4, 3, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I12, 4);

			int I13[] = { 3, 1, 2, 4 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I13, 4);

			int I14[] = { 3, 1, 4, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I14, 4);

			int I15[] = { 3, 2, 1, 4 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I15, 4);

			int I16[] = { 3, 2, 4, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I16, 4);

			int I17[] = { 3, 4, 1, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I17, 4);

			int I18[] = { 3, 4, 2, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I18, 4);

			int I19[] = { 4, 1, 2, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I19, 4);

			int I20[] = { 4, 1, 3, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I20, 4);

			int I21[] = { 4, 2, 1, 3 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I21, 4);

			int I22[] = { 4, 2, 3, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I22, 4);

			int I23[] = { 4, 3, 1, 2 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I23, 4);

			int I24[] = { 4, 3, 2, 1 };
			DPProblem::LongestIncreasingSubsequence::PrintSolution(I24, 4);
		}
	});

	Add("MatrixChain", [&]() {
		int dimension[7] = { 30, 35, 15, 5, 10, 20, 25 };
		int count = 7;
		int cost[6][6];
		int split[6][6];

		memset(cost, 0, 36 * sizeof(int));
		memset(split, 0, 36 * sizeof(int));

		DPProblem::MatrixChain::ComputeCostTable(dimension, count, &cost[0][0], &split[0][0]);

		for (int i = 0; i < 6; i++) {
			cout << "\t" << dimension[i] << "x" << dimension[i + 1];
		}

		cout << endl;

		for (int i = 0; i < 6; i++) {
			cout << "\t" << i;
		}

		cout << endl;

		for (int i = 0; i < 6; i++) {
			cout << i;
			for (int j = 0; j < 6; j++) {
				cout << "\t";
				if (j >= i) cout << cost[i][j];
			}

			cout << endl;
		}

		cout << endl;

		for (int i = 0; i < 6; i++) {
			cout << i;
			for (int j = 0; j < 6; j++) {
				cout << "\t";
				if (j >= i) cout << split[i][j];
			}

			cout << endl;
		}

		DPProblem::MatrixChain::PrintSolution(dimension, count);
	});

	Add("MazeUniquePaths", [&]() {
		auto check = [&](int rows, int cols) {
			Logger().WriteInformation("Maze %d x %d:", rows, cols);
			Matrix<double> count(rows, cols);
			Matrix<double> count2(rows, cols);
			DPProblem::Maze::CountUniquePaths(rows, cols, count);
			DPProblem::Maze::CountUniquePaths2(rows, cols, count2);
			Logger().WriteInformation(" unique paths (%f, %f)\n", count(0, 0), count2(0, 0));
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					ASSERT1(count(i, j) == count2(i, j));
				}
			}
		};

		// overflow may happen if the maze is too large
		for (int i = 1; i <= 15; i++) {
			for (int j = 1; j <= 15; j++) {
				check(i, j);
			}
		}
	});

	Add("MinMaxPartitionSum", [&]() {
		auto check = [&](int * input, int length, int partitions, int expectedSum) {
			Logger().WriteInformation("\nInput:");
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation(" %d", input[i]);
			}
			Logger().WriteInformation("\n%d partitions\n", partitions);

			unique_ptr<int[]> indices(new int[partitions]);
			unique_ptr<int[]> indices2(new int[partitions]);
			int sum = DPProblem::MinMaxPartitionSum::Solve(input, length, indices.get(), partitions);
			int sum2 = DPProblem::MinMaxPartitionSum::Solve2(input, length, indices2.get(), partitions);

			auto print = [&](unique_ptr<int[]> & indicesArray) {
				for (int j = 0; j < partitions; j++) {
					int b = indicesArray[j];
					int e = j == partitions - 1 ? length - 1 : indicesArray[j + 1] - 1;
					int s = 0;
					for (int i = b; i <= e; i++) {
						s += input[i];
					}
					Logger().WriteInformation("  %d = sum{A[%d..%d]} = ", s, b, e);
					for (int i = b; i <= e; i++) {
						Logger().WriteInformation("%s%d", i == b ? "" : " + ", input[i]);
					}
					Logger().WriteInformation("\n");
				}
			};

			Logger().WriteInformation("\nSolution using dynamic programming: %d\n", sum);
			print(indices);
			Logger().WriteInformation("\nSolution using binary search: %d\n", sum2);
			print(indices2);
			ASSERT1(sum == expectedSum);
			ASSERT1(sum2 == expectedSum);
			for (int i = 0; i < partitions; i++) {
				ASSERT1(indices[i] == indices2[i]);
			}
		};

		int A1[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };
		check(A1, 9, 3, 1700);

		int A2[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };
		check(A2, 9, 9, 900);

		int A3[] = { 900, 800, 700, 600, 500, 400, 300, 200, 100 };
		check(A3, 9, 3, 1700);

		int A4[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A4, 9, 3, 300);

		int A5[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A5, 9, 2, 500);

		int A6[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A6, 9, 9, 100);

		int A7[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A7, 9, 4, 300);

		int A8[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A8, 12, 5, 300);
	});
}