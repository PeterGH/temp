#pragma once

#include <memory>
#include <stack>
#include "Array.h"
#include "BinarySearch.h"

using namespace std;

namespace Test {
	class ArrayProblem {
	public:
		class BuySellStock {
		public:
			// Given an array of stock prices. Buy on one day and sell later. Maximize the profit.
			// Return the indices of buy day and sell day and the profit.
			template<class T> static void OneTransaction(const T * input, int length, int & buy, int & sell, T & profit)
			{
				int min = 0;
				buy = 0;
				sell = 0;
				profit = 0;
				for (int i = 1; i < length; i++) {
					if (input[i] < input[min]) {
						min = i;
					} else {
						T diff = input[i] - input[min];
						if (diff > profit) {
							buy = min;
							sell = i;
							profit = diff;
						}
					}
				}
			}

			template<class T> static void OneTransaction2(const T * input, int length, int & buy, int & sell, T & profit)
			{
				buy = 0;
				sell = 0;
				profit = 0;
				stack<int> sellCandidates; // track the increasing values from end to beginning
				sellCandidates.push(length - 1);
				for (int i = length - 2; i > 0; i--) {
					if (input[i] >= input[sellCandidates.top()]) {
						// i is the possible sell date, because
						// other dates later than i have less stock values
						sellCandidates.push(i);
					}
				}
				int min = 0;
				for (int i = 0; i < length - 1; i++) {
					if (i == 0 || input[i] < input[min]) {
						min = i;
						while (min >= sellCandidates.top()) {
							// i may be way later than top candidates
							sellCandidates.pop();
						}
						T diff = input[sellCandidates.top()] - input[min];
						if (diff > profit) {
							buy = min;
							sell = sellCandidates.top();
							profit = diff;
						}
					}
				}
			}

			// Multiple transactions. But two transactions cannot overlap, i.e., must sell before buy again.
			// However, sell and buy can happen on the same day.
			template<class T> static void MultipleTransactions(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
			{
				if (input == nullptr || length < 2) return;
				for (int i = 1; i < length; i++) {
					if (input[i] > input[i - 1]) {
						buy.push_back(i - 1);
						sell.push_back(i);
						profit.push_back(input[i] - input[i - 1]);
					}
				}
			}

			// Multiple transactions. But two transactions cannot overlap, i.e., must sell before buy again.
			// However, sell and buy can happen on the same day.
			// Use as less transactions as possible.
			template<class T> static void MinimumTransactions(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
			{
				if (input == nullptr || length < 2) return;
				int i = 0;
				int j = 0;
				while (j < length) {
					while (j + 1 < length && input[j + 1] >= input[j]) j++;
					if (i < j) {
						// input[i..j] is increasing
						buy.push_back(i);
						sell.push_back(j);
						profit.push_back(input[j] - input[i]);
					}
					i = j + 1;
					j++;
				}
			}

			// At most two transactions. But two transactions cannot overlap, i.e., must sell before buy again.
			// However, sell and buy can happen on the same day.
			template<class T> static void TwoTransactions(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
			{
				if (input == nullptr || length < 2) return;

				// Find one transaction during input[begin..end]
				auto maxProfit = [&](int begin, int end, int & buy, int & sell, int & profit) {
					int min = begin;
					buy = begin;
					sell = begin;
					profit = 0;
					if (end == begin) return;
					for (int i = begin + 1; i <= end; i++) {
						if (input[i] < input[min]) {
							min = i;
						} else {
							if (input[i] - input[min] > profit) {
								buy = min;
								sell = i;
								profit = input[i] - input[min];
							}
						}
					}
				};

				int buy1 = 0;
				int sell1 = 0;
				int profit1 = 0;
				int buy2 = 0;
				int sell2 = 0;
				int profit2 = 0;

				int b1 = 0;
				int s1 = 0;
				int p1 = 0;
				int b2 = 0;
				int s2 = 0;
				int p2 = 0;
				int i = 0;
				while (i < length - 1) {
					// Increase i so that [0..i] contains one more increasing subarray
					while (i < length - 1 && input[i + 1] <= input[i]) i++;
					if (i == length - 1) break;
					while (i < length - 1 && input[i + 1] > input[i]) i++;

					// Find the max transaction before i
					maxProfit(b1, i, b1, s1, p1);

					// Find the max transaction after i
					if (i > b2) {
						// If i <= b2, then no need to reevaluate because b2/s2 is already maximum after i
						maxProfit(i, length - 1, b2, s2, p2);
					}

					if (p1 + p2 > profit1 + profit2) {
						buy1 = b1;
						sell1 = s1;
						profit1 = p1;
						buy2 = b2;
						sell2 = s2;
						profit2 = p2;
					}

					i++;
				}

				int b3;
				int s3;
				int p3;
				maxProfit(0, length - 1, b3, s3, p3);
				if (p3 > profit1 + profit2) {
					buy.push_back(b3);
					sell.push_back(s3);
					profit.push_back(p3);
				} else {
					buy.push_back(buy1);
					sell.push_back(sell1);
					profit.push_back(profit1);
					buy.push_back(buy2);
					sell.push_back(sell2);
					profit.push_back(profit2);
				}
			}

			// Linear
			template<class T> static void TwoTransactions2(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
			{
				if (input == nullptr || length < 2) return;

				// Record the maximum two transactions
				int buy1 = 0;
				int sell1 = 0;
				int buy2 = 0;
				int sell2 = 0;
				// Record the maximum transactions
				int buym = 0;
				int sellm = 0;
				// Record the latest potential sell-buy candidate
				int i = 0;
				int j = 0;
				while (j < length) {
					while (j + 1 < length && input[j] >= input[j + 1]) {
						// Find the next local minimum
						j++;
					}
					if (i < sell2 || input[i] >= input[j]) {
						// i is the minimal in the range [sell2, j]
						// [sell2, j] may contain multiple increasing ranges
						i = j;
					}
					while (j + 1 < length && input[j] < input[j + 1]) {
						// Find the next local maximum
						j++;
					}
					if (i == j) {
						j++;
						continue;
					}
					// now input[i..j] is next potential sell-buy candidate.
					// input[i..j] may contain more than one increasing ranges.
					if (buy1 == sell1) {
						// Get the first two increasing ranges
						buy1 = buy2;
						sell1 = sell2;
						buy2 = i;
						sell2 = j;
					} else {
						// Given [buy1, sell1], [buy2, sell2] and [i, j]
						// Compute new [buy1, sell1] and [buy2, sell2]
						// Need to compare following cases:
						// 1. [buy1, sell1], [buy2, sell2]
						// 2. [buy1, sell1], [buy2, j]
						// 3. [buy1, sell1], [i, j]
						// 4. [buy2, sell2], [i, j]
						// 5. [buy1, sell2], [i, j]
						// Start with case 1
						int b1 = buy1;
						int s1 = sell1;
						int b2 = buy2;
						int s2 = sell2;
						if (input[j] > input[s2]) {
							// Covered case 2
							s2 = j;
						}
						if (input[j] - input[i] + input[sellm] - input[buym] >
							input[s2] - input[b2] + input[s1] - input[b1]) {
							// Covered case 3, 4 and 5
							b1 = buym;
							s1 = sellm;
							b2 = i;
							s2 = j;
						}
						buy1 = b1;
						sell1 = s1;
						buy2 = b2;
						sell2 = s2;
					}
					if (input[sell1] - input[buy1] > input[sellm] - input[buym]) {
						buym = buy1;
						sellm = sell1;
					}
					if (input[sell2] - input[buy2] > input[sellm] - input[buym]) {
						buym = buy2;
						sellm = sell2;
					}
					if (input[sell2] - input[buy1] > input[sellm] - input[buym]) {
						buym = buy1;
						sellm = sell2;
					}
					j++;
				}
				if (input[sellm] - input[buym] >= input[sell2] - input[buy2] + input[sell1] - input[buy1]) {
					buy.push_back(buym);
					sell.push_back(sellm);
					profit.push_back(input[sellm] - input[buym]);
				} else {
					buy.push_back(buy1);
					sell.push_back(sell1);
					profit.push_back(input[sell1] - input[buy1]);
					buy.push_back(buy2);
					sell.push_back(sell2);
					profit.push_back(input[sell2] - input[buy2]);
				}
			}

			// Linear
			template<class T> static void TwoTransactions3(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
			{
				if (input == nullptr || length < 2) return;

				// Record the maximum two transactions
				int buy1 = 0;
				int sell1 = 0;
				int buy2 = 0;
				int sell2 = 0;
				// Record the maximum transactions
				int buym = 0;
				int sellm = 0;
				// Record the latest potential buy-sell dates
				int i = 0; // track the min in [sell2, j]
				int j = 0;
				// Record the latest increasing range
				int i1 = -1;
				int j1 = -1;
				while (true) {
					Array::NextIncreasingRange(input, length, j1 + 1, i1, j1);
					if (j1 == -1) break; // No increasing range found
					if (i < sell2 || input[i1] <= input[i]) i = i1;
					j = j1;

					// now input[i..j] is next potential sell-buy candidate
					if (buy1 == sell1) {
						// Get the first two increasing ranges
						buy1 = buy2;
						sell1 = sell2;
						buy2 = i;
						sell2 = j;
					} else {
						// Given [buy1, sell1], [buy2, sell2] and [i, j]
						// Compute new [buy1, sell1] and [buy2, sell2]
						// Need to compare following cases:
						// 1. [buy1, sell1], [buy2, sell2]
						// 2. [buy1, sell1], [buy2, j]
						// 3. [buy1, sell1], [i, j]
						// 4. [buy2, sell2], [i, j]
						// 5. [buy1, sell2], [i, j]
						// Start with case 1
						int b1 = buy1;
						int s1 = sell1;
						int b2 = buy2;
						int s2 = sell2;
						if (input[j] > input[s2]) {
							// Covered case 2
							s2 = j;
						}
						if (input[j] - input[i] + input[sellm] - input[buym] >
							input[s2] - input[b2] + input[s1] - input[b1]) {
							// Covered case 3, 4 and 5
							b1 = buym;
							s1 = sellm;
							b2 = i;
							s2 = j;
						}
						buy1 = b1;
						sell1 = s1;
						buy2 = b2;
						sell2 = s2;
					}
					if (input[sell1] - input[buy1] > input[sellm] - input[buym]) {
						buym = buy1;
						sellm = sell1;
					}
					if (input[sell2] - input[buy2] > input[sellm] - input[buym]) {
						buym = buy2;
						sellm = sell2;
					}
					if (input[sell2] - input[buy1] > input[sellm] - input[buym]) {
						buym = buy1;
						sellm = sell2;
					}
				}
				if (input[sellm] - input[buym] >= input[sell2] - input[buy2] + input[sell1] - input[buy1]) {
					buy.push_back(buym);
					sell.push_back(sellm);
					profit.push_back(input[sellm] - input[buym]);
				} else {
					buy.push_back(buy1);
					sell.push_back(sell1);
					profit.push_back(input[sell1] - input[buy1]);
					buy.push_back(buy2);
					sell.push_back(sell2);
					profit.push_back(input[sell2] - input[buy2]);
				}
			}
		};

		class MaxInversionDistance {
		public:
			// An inversion is a pair (i, j) such that i < j and I[i] > I[j].
			// Find an inversion such that j - i is maximized.
			// Use parameter first to return value i and distance to return value j - i
			template<class T> static void Solve(const T * input, int length, int & first, int & distance)
			{
				first = 0;
				distance = 0;
				if (input == nullptr || length <= 1) return;

				// Array firstIndices to contain the indices of a increasing subsequence of input
				// Each element of firstIndices is a candidate for the first index of maximum inversion
				//       firstIndices[0]  <       firstIndices[1]  <       firstIndices[2]  < ...
				// input[firstIndices[0]] < input[firstIndices[1]] < input[firstIndices[2]] < ...
				unique_ptr<int[]> firstIndices(new int[length]);
				int index = 0;
				firstIndices[index] = 0;
				// Ignore input[length - 1]
				for (int i = 1; i < length - 1; i++) {
					if (input[i] > input[firstIndices[index]]) {
						index++;
						firstIndices[index] = i;
					}
				}

				int prev;
				// Ignore input[0]
				for (int i = length - 1; i > 0; i--) {
					if (i < length - 1 && input[i] >= prev) {
						// if there is an inversion ending at i, then
						// prev would extend it by one more position.
						// So input[i] should be ignored.
						continue;
					}

					prev = input[i];

					while (i <= firstIndices[index]) index--;

					int f = BinarySearch::PositionToInsert<int, int>(
						i,
						firstIndices.get(),
						index + 1,
						false,
						[&](int i) -> int { return input[i]; });

					if (f == index) {
						// input[i] is equal or greater than all elements referenced by firstIndices
						continue;
					}

					// firstIndices[f] < firstIndices[f + 1] < i
					// input[firstIndices[f]] <= input[i] < input[firstIndices[f+1]]
					int d = i - firstIndices[f + 1];
					if (d > distance) {
						distance = d;
						first = firstIndices[f + 1];
					}
				}
			}

			template<class T> static void Solve2(const T * input, int length, int & first, int & distance)
			{
				first = 0;
				distance = 0;
				if (input == nullptr || length <= 1) return;

				// Array firstIndices to contain the indices of a increasing subsequence of input
				// Each element of firstIndices is a candidate for the first index of maximum inversion
				//       firstIndices[0]  <       firstIndices[1]  <       firstIndices[2]  < ...
				// input[firstIndices[0]] < input[firstIndices[1]] < input[firstIndices[2]] < ...
				unique_ptr<int[]> firstIndices(new int[length]);
				int index = 0;
				firstIndices[index] = 0;
				// Ignore input[length - 1]
				for (int i = 1; i < length - 1; i++) {
					if (input[i] > input[firstIndices[index]]) {
						index++;
						firstIndices[index] = i;
					}
				}

				int prev;
				// Ignore input[0]
				for (int i = length - 1; i > 0; i--) {
					if (i < length - 1 && input[i] >= prev) {
						// if there is an inversion ending at i, then
						// prev would extend it by one more position.
						// So input[i] should be ignored.
						continue;
					}

					prev = input[i];

					while (i <= firstIndices[index]) index--;

					if (prev >= input[firstIndices[index]]) {
						// prev is greater than all possible first indices
						continue;
					}

					while (index > 0 && input[firstIndices[index - 1]] > prev) {
						index--;
					}

					// Now firstIndices[index] is the first element greater than input[i]
					int d = i - firstIndices[index];
					if (d > distance) {
						first = firstIndices[index];
						distance = i - first;
					}

					if (index == 0) {
						// All elements of firstIndices are examined
						break;
					}
				}
			}
		};

		// http://leetcode.com/2011/01/sliding-window-maximum.html
		class MaxInSlidingWindow {
		public:
			// Slide a window across an input, output the maximum on every move.
			template<class T> static void Solve(const T * input, int length, int window, vector<T> & output)
			{
				if (input == nullptr) throw invalid_argument("input is a nullptr");
				if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
				if (window <= 0 || window > length) throw invalid_argument(String::Format("window %d is out of range (0, %d]", window, length));

				priority_queue<pair<T, int>> heap; // Default it is a max-heap

				for (int i = 0; i < window; i++) {
					heap.push(make_pair(input[i], i));
				}

				output.push_back(heap.top().first);

				for (int i = window; i < length; i++) {
					// The size of heap may be more than the window size.
					// Consider one case where the input contains increasing numbers.
					// But the top of heap is always the max within the current window.

					while (!heap.empty() && heap.top().second <= i - window) {
						heap.pop();
					}

					heap.push(make_pair(input[i], i));
					output.push_back(heap.top().first);
				}
			}

			template<class T> static void Solve2(const T * input, int length, int window, vector<T> & output)
			{
				if (input == nullptr) throw invalid_argument("input is a nullptr");
				if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
				if (window <= 0 || window > length) throw invalid_argument(String::Format("window %d is out of range (0, %d]", window, length));

				deque<int> queue;

				// Establish the baseline:
				// 1. queue contains the latest k elements where k <= window
				// 2. queue is sorted and the maximum is queue.front()
				// 3. queue.back() is the latest element
				// 4. queue.front() is the oldest element
				// so effectively the queue contains a decreasing sequence between [max, i]
				for (int i = 0; i < window; i++) {
					while (!queue.empty() && input[i] >= input[queue.back()]) {
						queue.pop_back();
					}
					queue.push_back(i);
				}

				output.push_back(input[queue.front()]);

				for (int i = window; i < length; i++) {
					while (!queue.empty() && input[i] >= input[queue.back()]) {
						queue.pop_back();
					}
					while (!queue.empty() && queue.front() <= i - window) {
						queue.pop_front();
					}
					queue.push_back(i);
					output.push_back(input[queue.front()]);
				}
			}
		};

		class AllocateCandy {
		public:
			// Allocate candies to children with ratings.
			// Each child gets at least one candy.
			// The children with higher rating get more candies than their neighbors.
			__declspec(dllexport) static int Solve(int ratings[], int length, int amount[])
			{
				amount[0] = 1;
				for (int i = 1; i < length; i++) {
					if (ratings[i] > ratings[i - 1])
						amount[i] = amount[i - 1] <= 1 ? 2 : amount[i - 1] + 1;
					else if (ratings[i] == ratings[i - 1])
						amount[i] = amount[i - 1];
					else
						amount[i] = amount[i - 1] > 1 ? 1 : amount[i - 1] - 1;
				}
				int delta = 0;
				for (int i = length - 1; i >= 0; i--) {
					if (amount[i] > 1) {
						if (i < length - 1)
							if (ratings[i] == ratings[i + 1]) amount[i] = amount[i + 1];
						if (amount[i] <= 1 + delta) amount[i] = 2 + delta;
						delta = 0;
					} else {
						if (delta == 0) delta = 1 - amount[i];
						amount[i] += delta;
					}
				}
				int s = 0;
				for (int i = 0; i < length; i++) s += amount[i];
				return s;
			}

			__declspec(dllexport) static int Solve2(int ratings[], int length, int amount[])
			{
				amount[0] = 1;
				for (int i = 1; i < length; i++) {
					if (ratings[i] > ratings[i - 1])
						amount[i] = amount[i - 1] == 0 ? 2 : amount[i - 1] + 1;
					else if (ratings[i] == ratings[i - 1])
						amount[i] = amount[i - 1];
					else
						amount[i] = 0;
				}
				if (amount[length - 1] == 0) amount[length - 1] = 1;
				for (int i = length - 2; i >= 0; i--) {
					if (amount[i] == 0) {
						if (ratings[i] < ratings[i + 1])
							amount[i] = 1;
						else if (ratings[i] == ratings[i + 1])
							amount[i] = amount[i + 1];
						else
							amount[i] = amount[i + 1] + 1;
					} else {
						if (ratings[i] > ratings[i + 1] && amount[i] <= amount[i + 1])
							amount[i] = amount[i + 1] + 1;
						else if (ratings[i] == ratings[i + 1])
							amount[i] = amount[i + 1];
					}
				}
				int s = 0;
				for (int i = 0; i < length; i++) s += amount[i];
				return s;
			}
		};

		class __declspec(dllexport) CoinChange {
		public:
			CoinChange() {}
			~CoinChange() {}

			// Given an amount n and a set of coin denominations:
			// d_0, d_1, d_2, ......, d_(k-1)
			// The minimum count of coins to make up n:
			// N(n) = 1 + min{N(n - d_0), N(n - d_1), ..., N(n - d_(k-1))}
			static void ComputeMinCounts(unsigned int amount, vector<unsigned int> & denominations, vector<pair<unsigned int, unsigned int>> & counts)
			{
				// Sort coins increasingly
				sort(denominations.begin(), denominations.end());

				// counts[i] tracks the min count to make up amount i, and
				// the last change coin picked.
				counts.push_back(make_pair(0, 0));
				counts.push_back(make_pair(1, 1));
				for (unsigned int i = 2; i <= amount; i++) {
					unsigned int minCount = amount;
					unsigned int change;
					unsigned int j = 0;
					while (j < denominations.size() && denominations[j] <= i) {
						if (counts[i - denominations[j]].first < minCount) {
							minCount = counts[i - denominations[j]].first;
							change = denominations[j];
						}

						j++;
					}

					counts.push_back(make_pair(1 + minCount, change));
				}
			}

			static void ComputeSolution(unsigned int amount, vector<unsigned int> & denominations, map<unsigned int, unsigned int> & changes)
			{
				vector<pair<unsigned int, unsigned int>> counts;
				ComputeMinCounts(amount, denominations, counts);
				int i = amount;
				while (i > 0) {
					unsigned int c = counts[i].second;
					if (changes.find(c) == changes.end()) {
						changes[c] = 1;
					} else {
						changes[c]++;
					}

					i -= (int)c;
				}
			}

			static unsigned int GreedySolution(unsigned int amount, vector<unsigned int> & denominations, map<unsigned int, unsigned int> & changes)
			{
				function<bool(unsigned int, unsigned int)> greater = [&](unsigned int first, unsigned int second)->bool {
					return first > second;
				};

				// Sort in decreasing order
				sort(denominations.begin(), denominations.end(), greater);

				for_each(denominations.begin(), denominations.end(), [&](unsigned int d) {
					if (amount == 0) return;

					if (amount >= d) {
						unsigned int count = amount / d;
						changes[d] = count;
						amount = amount % d;
					}
				});

				// Return what ever cannot be changed, e.g. the minimum denomination is not 1.
				return amount;
			}

			// http://leetcode.com/2010/09/print-all-combinations-of-number-as-sum.html
			// Compute all sets of changes sum up to a given ammount
			static void ComputeAllSolutions(unsigned int amount, vector<unsigned int> & denominations, vector<map<unsigned int, unsigned int>> & changes)
			{
				// [TODO] no need to sort if use minIndex instead of minD in compute()
				sort(denominations.begin(), denominations.end());

				function<void(int, unsigned int, map<unsigned int, unsigned int>)>
				compute = [&](int sum, unsigned int minD, map<unsigned int, unsigned int> & s) {
					for_each(denominations.begin(), denominations.end(), [&](unsigned int d) {
						if (d >= minD && sum >= (int)d) {
							// Since denominations is already sorted, we can use
							// minD as a gate to avoid to recompute solutions with smaller denoms.
							map<unsigned int, unsigned int> copy(s);
							if (copy.find(d) == copy.end()) {
								copy[d] = 1;
							} else {
								copy[d]++;
							}

							if (sum == d) {
								changes.push_back(copy);
							} else {
								compute(sum - d, d, copy);
							}
						}
					});
				};

				map<unsigned int, unsigned int> s;
				compute(amount, denominations.front(), s);
			}

			// http://leetcode.com/2010/09/print-all-combinations-of-number-as-sum.html
			// Compute all sub sets of changes sum up to a given ammount. Duplication of a change is disallowed.
			static void ComputeSubSetSolutions(unsigned int amount, vector<unsigned int> & denominations, vector<map<unsigned int, unsigned int>> & changes)
			{
				// [TODO] no need to sort if use minIndex instead of minD in compute()
				sort(denominations.begin(), denominations.end());

				function<void(int, unsigned int, map<unsigned int, unsigned int>)>
				compute = [&](int sum, unsigned int minD, map<unsigned int, unsigned int> & s) {
					for_each(denominations.begin(), denominations.end(), [&](unsigned int d) {
						if (d >= minD && sum >= (int)d) {
							// Since denominations is already sorted, we can use
							// minD as a gate to avoid to recompute solutions with smaller denoms.
							map<unsigned int, unsigned int> copy(s);
							if (copy.find(d) == copy.end()) {
								copy[d] = 1;
							} else {
								copy[d]++;
							}

							if (sum == d) {
								changes.push_back(copy);
							} else {
								compute(sum - d, d + 1, copy);
							}
						}
					});
				};

				map<unsigned int, unsigned int> s;
				compute(amount, denominations.front(), s);
			}
		};
	};
}