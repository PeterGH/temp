#include "Header.h"

void ArrayProblemTest::Init(void)
{
	Add("BuySellStock.OneTransaction", [&]() {
		auto check = [&](int * input, int length) {
			Logger().Print(input, length);
			int buy;
			int sell;
			int profit;
			ArrayProblem::BuySellStock::OneTransaction(input, length, buy, sell, profit);
			int buy2;
			int sell2;
			int profit2;
			ArrayProblem::BuySellStock::OneTransaction2(input, length, buy2, sell2, profit2);
			Logger().WriteInformation("\t%d\t%d\t%ld\n", buy, sell, profit);
			Logger().WriteInformation("\t%d\t%d\t%ld\n", buy2, sell2, profit2);
			ASSERT1(buy == buy2);
			ASSERT1(sell == sell2);
			ASSERT1(profit == profit2);
		};
		auto check2 = [&](vector<int> input) {
			auto inputs = Permutation::All(input);
			int len = (int)input.size();
			for_each(inputs.begin(), inputs.end(), [&](vector<int> & it) {
				unique_ptr<int[]> A(new int[len]);
				Array::ToArray(it, A.get());
				check(A.get(), len);
			});
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			vector<int> A = { 1, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			vector<int> A = { 1, 2, 3 };
			check2(A);
		}
		{
			vector<int> A = { 1, 1, 2 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			vector<int> A = { 1, 2, 3, 4 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 6, 7 };
			check2(A);
		}
		{
			for (int i = 0; i < 100; i++) {
				int len = 1 + rand() % 100;
				unique_ptr<int[]> A(new int[len]);
				for (int j = 0; j < len; j++) {
					A[j] = rand();
				}
				Logger().WriteInformation("\nRun %d with %d elements\n", i, len);
				check(A.get(), len);
			}
		}
	});

	Add("BuySellStock.MultipleTransactions", [&]() {
		auto check = [&](int * input, int length) {
			Logger().Print(input, length);
			vector<int> buy;
			vector<int> sell;
			vector<int> profit;
			ArrayProblem::BuySellStock::MultipleTransactions(input, length, buy, sell, profit);
			int total = 0;
			for (size_t i = 0; i < buy.size(); i++) {
				total += profit[i];
				Logger().WriteInformation("\t%d\t%d\t%ld\n", buy[i], sell[i], profit[i]);
			}
			Logger().WriteInformation("\tTotal: %d\n", total);
			vector<int> buy2;
			vector<int> sell2;
			vector<int> profit2;
			ArrayProblem::BuySellStock::MinimumTransactions(input, length, buy2, sell2, profit2);
			int total2 = 0;
			for (size_t i = 0; i < buy2.size(); i++) {
				total2 += profit2[i];
				Logger().WriteInformation("\t%d\t%d\t%ld\n", buy2[i], sell2[i], profit2[i]);
			}
			Logger().WriteInformation("\tTotal: %d\n", total2);
			ASSERT1(total == total2);
		};
		auto check2 = [&](vector<int> input) {
			auto inputs = Permutation::All(input);
			int len = (int)input.size();
			for_each(inputs.begin(), inputs.end(), [&](vector<int> & it) {
				unique_ptr<int[]> A(new int[len]);
				Array::ToArray(it, A.get());
				check(A.get(), len);
			});
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			vector<int> A = { 1, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			vector<int> A = { 1, 2, 3 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			vector<int> A = { 1, 2, 3, 4 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 6, 7 };
			check2(A);
		}
		{
			vector<int> A = { 1, 3, 6, 7 };
			check2(A);
		}
		{
			int A[] = { 9, 7, 10, 9, 5, 8, 3, 7, 2, 1, 5, 3 };
			check(A, 12);
		}
		{
			vector<int> A = { 6, 1, 3, 2, 4, 7 };
			check2(A);
		}
	});

	Add("BuySellStock.TwoTransactions", [&]() {
		auto check = [&](int * input, int length) {
			Logger().Print(input, length);
			vector<int> buy;
			vector<int> sell;
			vector<int> profit;
			ArrayProblem::BuySellStock::TwoTransactions(input, length, buy, sell, profit);
			int total = 0;
			for (size_t i = 0; i < buy.size(); i++) {
				total += profit[i];
				Logger().WriteInformation("\t%d\t%d\t%ld\n", buy[i], sell[i], profit[i]);
			}
			Logger().WriteInformation("\tTotal: %d\n", total);
			vector<int> buy2;
			vector<int> sell2;
			vector<int> profit2;
			ArrayProblem::BuySellStock::TwoTransactions2(input, length, buy2, sell2, profit2);
			int total2 = 0;
			for (size_t i = 0; i < buy2.size(); i++) {
				total2 += profit2[i];
				Logger().WriteInformation("\t%d\t%d\t%ld\n", buy2[i], sell2[i], profit2[i]);
			}
			Logger().WriteInformation("\tTotal: %d\n", total2);
			vector<int> buy3;
			vector<int> sell3;
			vector<int> profit3;
			ArrayProblem::BuySellStock::TwoTransactions3(input, length, buy3, sell3, profit3);
			int total3 = 0;
			for (size_t i = 0; i < buy3.size(); i++) {
				total3 += profit3[i];
				Logger().WriteInformation("\t%d\t%d\t%ld\n", buy3[i], sell3[i], profit3[i]);
			}
			Logger().WriteInformation("\tTotal: %d\n", total3);
			ASSERT1(total == total2);
			ASSERT1(total == total3);
		};
		auto check2 = [&](vector<int> input) {
			auto inputs = Permutation::All(input);
			int len = (int)input.size();
			for_each(inputs.begin(), inputs.end(), [&](vector<int> & it) {
				unique_ptr<int[]> A(new int[len]);
				Array::ToArray(it, A.get());
				check(A.get(), len);
			});
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			vector<int> A = { 1, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			vector<int> A = { 1, 2, 3 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			vector<int> A = { 1, 2, 3, 4 };
			check2(A);
		}
		{
			vector<int> A = { 2, 7, 1, 6 };
			check2(A);
		}
		{
			vector<int> A = { 3, 7, 1, 6 };
			check2(A);
		}
		{
			int A[] = { 9, 7, 10, 9, 5, 8, 3, 7, 2, 1, 5, 3 };
			check(A, 12);
		}
		{
			vector<int> A = { 6, 1, 3, 2, 4, 7 };
			check2(A);
		}
		{
			for (int i = 0; i < 100; i++) {
				int len = 1 + rand() % 100;
				unique_ptr<int[]> A(new int[len]);
				for (int j = 0; j < len; j++) {
					A[j] = rand();
				}
				Logger().WriteInformation("\nRun %d with %d elements\n", i, len);
				check(A.get(), len);
			}
		}
	});

	Add("MaxInversionDistance", [&]() {
		auto check = [&](int A[], int l, int f, int d) {
			Logger().Print(A, l);
			int first, first2;
			int distance, distance2;
			ArrayProblem::MaxInversionDistance::Solve(A, l, first, distance);
			ArrayProblem::MaxInversionDistance::Solve2(A, l, first2, distance2);
			Logger().WriteInformation("\t%d(%d)\t%d(%d)\n\n", first, f, distance, d);
			Logger().WriteInformation("\t%d(%d)\t%d(%d)\n\n", first2, f, distance2, d);
			ASSERT1(first == f);
			ASSERT1(distance == d);
			ASSERT1(first2 == f);
			ASSERT1(distance2 == d);
		};
		{
			int A[] = { 1 };
			check(A, 1, 0, 0);
		}
		{
			int A[] = { 2, 3 };
			check(A, 2, 0, 0);
		}
		{
			int A[] = { 4, 4 };
			check(A, 2, 0, 0);
		}
		{
			int A[] = { 5, 6, 7 };
			check(A, 3, 0, 0);
		}
		{
			int A[] = { 5, 7, 6 };
			check(A, 3, 1, 1);
		}
		{
			int A[] = { 6, 5, 7 };
			check(A, 3, 0, 1);
		}
		{
			int A[] = { 6, 7, 5 };
			check(A, 3, 0, 2);
		}
		{
			int A[] = { 7, 5, 6 };
			check(A, 3, 0, 2);
		}
		{
			int A[] = { 7, 6, 5 };
			check(A, 3, 0, 2);
		}
		{
			int A[] = { 5, 7, 7 };
			check(A, 3, 0, 0);
		}
		{
			int A[] = { 7, 5, 7 };
			check(A, 3, 0, 1);
		}
		{
			int A[] = { 7, 7, 5 };
			check(A, 3, 0, 2);
		}
		{
			int A[] = { 7, 7, 7 };
			check(A, 3, 0, 0);
		}
		{
			int A[] = { 1, 2, 3, 4 };
			check(A, 4, 0, 0);
		}
		{
			int A[] = { 1, 3, 2, 4 };
			check(A, 4, 1, 1);
		}
		{
			int A[] = { 4, 3, 2, 1 };
			check(A, 4, 0, 3);
		}
		{
			int A[] = { 3, 4, 1, 2 };
			check(A, 4, 0, 3);
		}
		{
			int A[] = { 2, 4, 1, 3 };
			check(A, 4, 1, 2);
		}
		{
			int A[] = { 2, 1, 4, 3 };
			check(A, 4, 2, 1);
		}
		{
			int A[] = { 4, 2, 3, 1 };
			check(A, 4, 0, 3);
		}
		{
			int A[] = { 1, 2, 4, 3 };
			check(A, 4, 2, 1);
		}
		{
			int A[] = { 1, 3, 4, 2 };
			check(A, 4, 1, 2);
		}
		{
			int A[] = { 1, 4, 3, 2 };
			check(A, 4, 1, 2);
		}
		{
			int A[] = { 1, 4, 2, 3 };
			check(A, 4, 1, 2);
		}
	});

	Add("MaxInSlidingWindow", [&]() {
		auto checkWindow = [&](int A[], int l, int w) {
			vector<int> output;
			vector<int> output2;
			ArrayProblem::MaxInSlidingWindow::Solve(A, l, w, output);
			ArrayProblem::MaxInSlidingWindow::Solve2(A, l, w, output2);
			ASSERT1(true == Equal(output, output2));
		};
		auto check = [&](int A[], int l) {
			Logger().Print(A, l);
			for (int w = 1; w <= l; w++) {
				Logger().WriteInformation("Window:     %d\n", w);
				checkWindow(A, l, w);
			}
		};
		auto check2 = [&](vector<int> input) {
			auto inputs = Permutation::All(input);
			int len = (int)input.size();
			for_each(inputs.begin(), inputs.end(), [&](vector<int> & it) {
				unique_ptr<int[]> A(new int[len]);
				Array::ToArray(it, A.get());
				check(A.get(), len);
			});
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			vector<int> A = { 1, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			vector<int> A = { 1, 2, 3 };
			check2(A);
		}
		{
			vector<int> A = { 1, 2, 2 };
			check2(A);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			vector<int> A = { 1, 2, 3, 4 };
			check2(A);
		}
		{
			for (int i = 0; i < 100; i++) {
				int length = 1 + rand() % 100;
				unique_ptr<int[]> input(new int[length]);
				for (int j = 0; j < length; j++) {
					input[j] = rand();
				}
				int w = 1;
				do {
					Logger().WriteInformation("Run %d: %d window over %d elements\n", i, w, length);
					checkWindow(input.get(), length, w);
					if (w >= length - 10 && w < length) {
						w = length;
					} else {
						w += (1 + rand() % 10);
					}
				} while (w <= length);
			}
		}
	});

	Add("AllocateCandy", [&]() {
		auto check = [&](int ratings[], int length, int amount[], int expect) {
			Logger().WriteInformation("Input:");
			Logger().Print(ratings, length);
			int total = ArrayProblem::AllocateCandy::Solve(ratings, length, amount);
			Logger().WriteInformation("Candy:");
			Logger().Print(amount, length);
			Logger().WriteInformation("Total:  %d\n", total);
			int total2 = ArrayProblem::AllocateCandy::Solve2(ratings, length, amount);
			Logger().WriteInformation("Candy:");
			Logger().Print(amount, length);
			Logger().WriteInformation("Total:  %d\n", total2);
			ASSERT1(total == expect);
			ASSERT1(total2 == expect);
		};
		{
			int r[] = { 0 };
			int a[1];
			check(r, 1, a, 1);
		}
		{
			int r[] = { 0, 0 };
			int a[2];
			check(r, 2, a, 2);
		}
		{
			int r[] = { 0, 1 };
			int a[2];
			check(r, 2, a, 3);
		}
		{
			int r[] = { 1, 0 };
			int a[2];
			check(r, 2, a, 3);
		}
		{
			int r[] = { 0, 0, 0 };
			int a[3];
			check(r, 3, a, 3);
		}
		{
			int r[] = { 0, 0, 1 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 0, 1, 0 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 1, 0, 0 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 0, 1, 1 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 1, 0, 1 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 1, 1, 0 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 0, 1, 2 };
			int a[3];
			check(r, 3, a, 6);
		}
		{
			int r[] = { 0, 2, 1 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 1, 0, 2 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 1, 2, 0 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 2, 0, 1 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 2, 1, 0 };
			int a[3];
			check(r, 3, a, 6);
		}
		{
			int r[] = { 0, 0, 0, 0 };
			int a[4];
			check(r, 4, a, 4);
		}
		{
			int r[] = { 0, 0, 0, 1 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 0, 1, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 1, 0, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 1, 0, 0, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 0, 1, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 0, 1, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 1, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 1, 0, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 0, 1, 1, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 0, 1, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 1, 0, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 1, 1, 0 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 0, 1, 2 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 1, 0, 2 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 0, 2 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 2, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 2, 0, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 0, 2, 1 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 2, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 2, 0, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 2, 0, 1, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 2, 1, 0, 0 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 1, 1, 2 };
			int a[4];
			check(r, 4, a, 8);
		}
		{
			int r[] = { 1, 0, 1, 2 };
			int a[4];
			check(r, 4, a, 8);
		}
		{
			int r[] = { 1, 1, 0, 2 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 1, 2, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 1, 2, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 2, 1, 1 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 2, 0, 1, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 0, 0, 0, 0 };
			int a[5];
			check(r, 5, a, 5);
		}
	});

	Add("CoinChange", [&]() {
		{
			vector<unsigned int> denoms{ 1, 3, 4 };
			map<unsigned int, unsigned int> changes;
			unsigned int amount = 6;
			ArrayProblem::CoinChange::ComputeSolution(amount, denoms, changes);
			map<unsigned int, unsigned int>::iterator it;
			Logger().WriteInformation("For amount %d, changes are :\n", amount);
			for (it = changes.begin(); it != changes.end(); it++) {
				Logger().WriteInformation("\tcoint %d, count %d\n", it->first, it->second);
			}

			ASSERT1(changes.size() == 1);
			ASSERT1(changes[3] == 2);
		}
		{
			vector<unsigned int> denoms{ 1, 5, 10, 25 };
			for (int i = 0; i < 100; i++) {
				unsigned int amount = 1 + rand() % 1000;
				map<unsigned int, unsigned int> changes1;
				map<unsigned int, unsigned int> changes2;
				ArrayProblem::CoinChange::ComputeSolution(amount, denoms, changes1);
				ArrayProblem::CoinChange::GreedySolution(amount, denoms, changes2);

				ASSERT1(changes1.size() == changes2.size());

				map<unsigned int, unsigned int>::iterator it;
				Logger().WriteInformation("Run %d, amount %d, changes are :\n", i, amount);
				for (it = changes1.begin(); it != changes1.end(); it++) {
					Logger().WriteInformation("\tcoint %d, count %d\n", it->first, it->second);
					ASSERT1(it->second == changes2[it->first]);
				}
			}
		}
		{
			auto check = [&](unsigned int sum, vector<unsigned int> & denoms, unsigned int count) {
				vector<map<unsigned int, unsigned int>> solutions;
				ArrayProblem::CoinChange::ComputeAllSolutions(sum, denoms, solutions);
				Logger().WriteInformation("Sum %d numbers: ", sum);
				Logger().Print(denoms);
				for_each(solutions.begin(), solutions.end(), [&](map<unsigned int, unsigned int> & m) {
					Logger().WriteInformation("  %d = ", sum);
					int i = 0;
					for_each(m.begin(), m.end(), [&](pair<unsigned int, unsigned int> p) {
						if (i != 0) {
							Logger().WriteInformation(" + ");
						}
						Logger().WriteInformation("%d x %d", p.second, p.first);
						i++;
					});
					Logger().WriteInformation("\n");
				});
				ASSERT1(solutions.size() == count);
			};

			vector<unsigned int> denoms{ 2, 3, 6, 7 };
			check(7, denoms, 2);
		}
		{
			auto check = [&](unsigned int sum, vector<unsigned int> & denoms, unsigned int count) {
				vector<map<unsigned int, unsigned int>> solutions;
				ArrayProblem::CoinChange::ComputeSubSetSolutions(sum, denoms, solutions);
				Logger().WriteInformation("Sum %d numbers: ", sum);
				Logger().Print(denoms);
				for_each(solutions.begin(), solutions.end(), [&](map<unsigned int, unsigned int> & m) {
					Logger().WriteInformation("  %d = ", sum);
					int i = 0;
					for_each(m.begin(), m.end(), [&](pair<unsigned int, unsigned int> p) {
						if (i != 0) {
							Logger().WriteInformation(" + ");
						}
						Logger().WriteInformation("%d x %d", p.second, p.first);
						i++;
					});
					Logger().WriteInformation("\n");
				});
				ASSERT1(solutions.size() == count);
			};

			vector<unsigned int> denoms{ 2, 3, 6, 7 };
			check(7, denoms, 1);
		}
	});

}