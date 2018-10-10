#include "Test.h"

void AlgorithmTest::Init(void)
{
	Add("LongestConsecutiveSequence", [&]() {
		auto check = [&](vector<int> & input, int expectBegin, int expectLength) {
			Logger().WriteInformation("Input: ");
			Logger().Print(input);
			int begin1;
			size_t length1;
			LongestConsecutiveSequence1(input, begin1, length1);
			Logger().WriteInformation("  Begin:  %d %s %d\n", begin1, begin1 == expectBegin ? "==" : "!=", expectBegin);
			Logger().WriteInformation("  Length: %d %s %d\n", length1, length1 == expectLength ? "==" : "!=", expectLength);
			int begin2;
			size_t length2;
			LongestConsecutiveSequence2(input, begin2, length2);
			Logger().WriteInformation("  Begin2:  %d %s %d\n", begin2, begin2 == expectBegin ? "==" : "!=", expectBegin);
			Logger().WriteInformation("  Length2: %d %s %d\n", length2, length2 == expectLength ? "==" : "!=", expectLength);
			ASSERT1(begin1 == expectBegin);
			ASSERT1(length1 == expectLength);
			ASSERT1(begin2 == expectBegin);
			ASSERT1(length2 == expectLength);
		};
		{
			vector<int> input = { 0 };
			check(input, 0, 1);
		}
		{
			vector<int> input = { 0, 0 };
			check(input, 0, 1);
		}
		{
			vector<int> input = { 0, 1 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 0, 2 };
			check(input, 0, 1);
		}
		{
			vector<int> input = { 0, 1, 2 };
			check(input, 0, 3);
		}
		{
			vector<int> input = { 0, 1, 3 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { -1, 1, 2 };
			check(input, 1, 2);
		}
		{
			vector<int> input = { 0, -1, 2 };
			check(input, -1, 2);
		}
		{
			vector<int> input = { 3, 1, 2 };
			check(input, 1, 3);
		}
		{
			vector<int> input = { 0, 1, 1 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0, 1, 1 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0, 1, 0 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0, -1 };
			check(input, -1, 3);
		}
		{
			vector<int> input = { 0, 1, 2, 1 };
			check(input, 0, 3);
		}
		{
			vector<int> input = { -7, -1, 3, -9, -4, 7, -3, 2, 4, 9, 4, -9, 8, -7 ,5, -1, -7 };
			check(input, 2, 4);
		}
		{
			vector<int> input = { -6, 8, -5, 7, -9, -1, -7, -6, -9, -7, 5, 7, -1, -8, -8, -2, 0 };
			check(input, -9, 5);
		}
		{
			for (int i = 0; i < 100; i++) {
				vector<int> input;
				Random(input);
				Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
				if (input.size() == 0) continue;
				int begin1;
				size_t length1;
				LongestConsecutiveSequence1(input, begin1, length1);
				int begin2;
				size_t length2;
				LongestConsecutiveSequence1(input, begin2, length2);
				Logger().WriteInformation("  Begin:  %d %s %d\n", begin1, begin1 == begin2 ? "==" : "!=", begin2);
				Logger().WriteInformation("  Length: %d %s %d\n", length1, length1 == length2 ? "==" : "!=", length2);
				ASSERT1(begin1 == begin2);
				ASSERT1(length1 == length2);
			}
		}
	});

	Add("Permutation", [&]() {
		{
			auto add = [&](vector<string> & freq, const string & s) {
				Logger().WriteInformation("%s\n", s.c_str());
				vector<string>::iterator it = find(freq.begin(), freq.end(), s);
				ASSERT2(it == freq.end(), String::Format("%s already exists", s.c_str()));
				freq.push_back(s);
			};

			PermutationGenerator perm(4);
			int count = (int)perm.TotalCount();
			ASSERT1(24 == count);

			vector<int> input1 = { 0, 1, 2, 3 };
			vector<int> output;
			vector<string> freq1;
			Logger().WriteInformation("PermutationGenerator.Next:\n");
			for (int i = 0; i < count; i++) {
				Duplicate(input1, output);
				perm.Next(output);
				add(freq1, String::Join(output, ":"));
			}

			vector<int> input2 = { 0, 1, 2, 3 };
			vector<vector<int>> all;
			AllPermutations(input2, all);
			vector<string> freq2;
			Logger().WriteInformation("AllPermutations:\n");
			for_each(all.begin(), all.end(), [&](vector<int> & v) {
				add(freq2, String::Join(v, ":"));
			});

			vector<int> input3 = { 0, 1, 2, 3 };
			vector<vector<int>> unique;
			UniquePermutations(input3, unique);
			vector<string> freq3;
			Logger().WriteInformation("UniquePermutations:\n");
			for_each(unique.begin(), unique.end(), [&](vector<int> & v) {
				add(freq3, String::Join(v, ":"));
			});

			vector<int> input4 = { 0, 1, 2, 3 };
			vector<string> freq4;
			Logger().WriteInformation("NextPermutation:\n");
			for (int i = 0; i < count; i++) {
				NextPermutation(input4);
				add(freq4, String::Join(input4, ":"));
			}

			ASSERT1(freq1.size() == freq2.size());
			ASSERT1(freq1.size() == freq3.size());
			ASSERT1(freq1.size() == freq4.size());
			for_each(freq1.begin(), freq1.end(), [&](string & s) {
				vector<string>::iterator it = find(freq2.begin(), freq2.end(), s);
				ASSERT2(it != freq2.end(), String::Format("%s is not found in freq2", s.c_str()));
				it = find(freq3.begin(), freq3.end(), s);
				ASSERT2(it != freq3.end(), String::Format("%s is not found in freq3", s.c_str()));
				it = find(freq4.begin(), freq4.end(), s);
				ASSERT2(it != freq4.end(), String::Format("%s is not found in freq4", s.c_str()));
			});
			for_each(freq2.begin(), freq2.end(), [&](string & s) {
				vector<string>::iterator it = find(freq1.begin(), freq1.end(), s);
				ASSERT2(it != freq1.end(), String::Format("%s is not found in freq1", s.c_str()));
			});
			for_each(freq3.begin(), freq3.end(), [&](string & s) {
				vector<string>::iterator it = find(freq1.begin(), freq1.end(), s);
				ASSERT2(it != freq1.end(), String::Format("%s is not found in freq1", s.c_str()));
			});
			for_each(freq4.begin(), freq4.end(), [&](string & s) {
				vector<string>::iterator it = find(freq1.begin(), freq1.end(), s);
				ASSERT2(it != freq1.end(), String::Format("%s is not found in freq1", s.c_str()));
			});
		}
		{
			auto check = [&](vector<int> & n) {
				Logger().WriteInformation("Permute: ");
				Logger().Print(n);
				vector<vector<int>> all;
				AllPermutations(n, all);
				set<string> allset;
				for_each(all.begin(), all.end(), [&](vector<int> & v) {
					allset.insert(String::Join(v, ","));
				});
				vector<vector<int>> unique;
				UniquePermutations(n, unique);
				vector<string> uniqueset;
				for_each(unique.begin(), unique.end(), [&](vector<int> & v) {
					uniqueset.push_back(String::Join(v, ","));
				});

				for_each(uniqueset.begin(), uniqueset.end(), [&](string & s) {
					Logger().WriteInformation("%s\n", s.c_str());
					ASSERT2(allset.find(s) != allset.end(), String::Format("%s is not found in allset", s.c_str()));
				});

				ASSERT1(allset.size() == uniqueset.size());
			};
			check(vector<int> { 1, 1 });
			check(vector<int> { 1, 1, 1 });
			check(vector<int> { 1, 1, 2 });
			check(vector<int> { 1, 1, 2, 2 });
			check(vector<int> { 1, 2, 3, 1, 2, 3 });
		}
		{
			auto check = [&](vector<int> & n) {
				Logger().WriteInformation("Permute: ");
				Logger().Print(n);
				vector<vector<int>> p;
				UniquePermutations(n, p);
				for_each(p.begin(), p.end(), [&](vector<int> & i) {
					Logger().WriteInformation("Unique:\t");
					Logger().Print(i);
					Logger().WriteInformation("Next:\t");
					Logger().Print(n);
					bool e = Equal(i, n);
					ASSERT1(e == true);
					NextPermutation(n);
				});
			};
			check(vector<int> { 1, 1 });
			check(vector<int> { 1, 1, 1 });
			check(vector<int> { 1, 1, 2 });
			check(vector<int> { 1, 1, 2, 2 });
			check(vector<int> { 1, 1, 2, 2, 3, 3 });
		} 
		{
			auto seq = [&](int n, vector<int> & output) {
				for (int i = 1; i <= n; i++) {
					output.push_back(i);
				}
			};
			auto check = [&](int n) {
				vector<int> v;
				seq(n, v);
				Logger().WriteInformation("Permute: ");
				Logger().Print(v);
				int m = (int)Factorial(n);
				for (int i = 1; i <= m; i++) {
					string p = KthPermutation(n, i);
					Logger().WriteInformation("  %d\t%s\n", i, p.c_str());
					string q = String::Join(v, "");
					ASSERT2(p == q, String::Format("%s != %s", p.c_str(), q.c_str()));
					NextPermutation(v);
				}
			};
			check(1);
			check(2);
			check(3);
			check(4);
			check(5);
		}
		{
			vector<int> input = { 0, 1, 2, 3 };
			vector<int> output;
			map<string, int> freq;
			int total = 100000;
			for (int i = 0; i < total; i++) {
				Duplicate(input, output);
				RandomPermutation(output);
				string s = String::Join(output, ":");
				map<string, int>::iterator it = freq.find(s);
				if (it == freq.end()) freq[s] = 1;
				else freq[s] ++;
			}

			int count = 24;
			int ave = total / count;
			int delta = ave >> 1;

			for_each(freq.begin(), freq.end(), [&](pair<string, int> p) {
				Logger().WriteInformation("%s\t%d\n", p.first.c_str(), p.second);
			});

			ASSERT1(freq.size() == count);
			
			for_each(freq.begin(), freq.end(), [&](pair<string, int> p) {
				ASSERT2(delta >= abs(p.second - ave), String::Format("%s occurs %d times, average %d, delta %d", p.first.c_str(), p.second, ave, delta));
			});
		}
	});

	Add("Queue", [&]() {
		{
			Queue<int> q1;
			queue<int> q2;

			ASSERT1(q1.Empty() == true);
			ASSERT1(q2.empty() == true);
			ASSERT1(q1.Size() == q2.size());

			for (int i = 0; i < 100; i++) {
				q1.Push(i);
				q2.push(i);
				ASSERT1(q1.Empty() == false);
				ASSERT1(q2.empty() == false);
				ASSERT1(q1.Size() == q2.size());
			}

			int t1, t2;
			for (int i = 0; i < 99; i++) {
				t1 = q1.Front();
				q1.Pop();
				t2 = q2.front();
				q2.pop();
				ASSERT1(t1 == t2);
				ASSERT1(q1.Empty() == false);
				ASSERT1(q2.empty() == false);
				ASSERT1(q1.Size() == q2.size());
			}

			t1 = q1.Front();
			q1.Pop();
			t2 = q2.front();
			q2.pop();
			ASSERT1(t1 == t2);
			ASSERT1(q1.Empty() == true);
			ASSERT1(q2.empty() == true);
			ASSERT1(q1.Size() == q2.size());
		}
		{
			Queue<int> q1;
			queue<int> q2;

			ASSERTERROR(q1.Front(), runtime_error);
			ASSERT1(q1.Size() == q2.size());

			int v1, v2;
			for (int i = 0; i < 100; i++) {
				q1.Push(i);
				q2.push(i);
				v1 = q1.Front();
				v2 = q2.front();
				ASSERT1(v1 == 0);
				ASSERT1(v2 == 0);
				ASSERT1(q1.Size() == q2.size());
			}

			for (int i = 0; i < 99; i++) {
				q1.Pop();
				q2.pop();
				v1 = q1.Front();
				v2 = q2.front();
				ASSERT1(v1 == i + 1);
				ASSERT1(v2 == i + 1);
				ASSERT1(q1.Size() == q2.size());
			}

			v1 = q1.Front();
			v2 = q2.front();
			ASSERT1(v1 == 99);
			ASSERT1(v2 == 99);
			ASSERT1(q1.Size() == q2.size());

			q1.Pop();
			q2.pop();

			ASSERTERROR(q1.Front(), runtime_error);
			ASSERT1(q1.Empty() == true);
			ASSERT1(q2.empty() == true);
			ASSERT1(q1.Size() == q2.size());
		}
		{
			Queue<int> q1;
			queue<int> q2;

			ASSERTERROR(q1.Back(), runtime_error);
			ASSERT1(q1.Size() == q2.size());

			int v1, v2;
			for (int i = 0; i < 100; i++) {
				q1.Push(i);
				q2.push(i);
				v1 = q1.Back();
				v2 = q2.back();
				ASSERT1(v1 == i);
				ASSERT1(v2 == i);
				ASSERT1(q1.Size() == q2.size());
			}

			for (int i = 0; i < 99; i++) {
				q1.Pop();
				q2.pop();
				v1 = q1.Back();
				v2 = q2.back();
				ASSERT1(v1 == 99);
				ASSERT1(v2 == 99);
				ASSERT1(q1.Size() == q2.size());
			}

			q1.Pop();
			q2.pop();

			ASSERTERROR(q1.Back(), runtime_error);
			ASSERT1(q1.Empty() == true);
			ASSERT1(q2.empty() == true);
			ASSERT1(q1.Size() == q2.size());
		}
	});

	Add("Stack", [&]() {
		{
			Stack<int> s1;
			stack<int> s2;

			ASSERTERROR(s1.Top(), runtime_error);
			ASSERTERROR(s1.Pop(), runtime_error);
			ASSERT1(s1.Empty() == true);
			ASSERT1(s2.empty() == true);
			ASSERT1(s1.Size() == s2.size());

			for (int i = 0; i < 100; i++) {
				s1.Push(i);
				s2.push(i);
				ASSERT1(s1.Top() == i);
				ASSERT1(s2.top() == i);
				ASSERT1(s1.Empty() == false);
				ASSERT1(s2.empty() == false);
				ASSERT1(s1.Size() == s2.size());
			}

			int v1, v2;
			for (int i = 0; i < 99; i++) {
				v1 = s1.Top();
				s1.Pop();
				v2 = s2.top();
				s2.pop();
				ASSERT1(v1 == 99 - i);
				ASSERT1(v2 == 99 - i);
				ASSERT1(s1.Top() == 99 - i - 1);
				ASSERT1(s2.top() == 99 - i - 1);
				ASSERT1(s1.Empty() == false);
				ASSERT1(s2.empty() == false);
				ASSERT1(s1.Size() == s2.size());
			}

			v1 = s1.Top();
			s1.Pop();
			v2 = s2.top();
			s2.pop();
			ASSERT1(v1 == 0);
			ASSERT1(v2 == 0);
			ASSERTERROR(s1.Top(), runtime_error);
			ASSERTERROR(s1.Pop(), runtime_error);
			ASSERT1(s1.Empty() == true);
			ASSERT1(s2.empty() == true);
			ASSERT1(s1.Size() == s2.size());
		}
	});

	Add("Partition", [&]() {
		{
			vector<int> I = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
			int L = (int)I.size();

			int i = PartitionByValue(I, 0, 0, 3);
			ASSERT1(i == 0);

			i = PartitionByValue(I, L - 1, L - 1, 64);
			ASSERT1(i == L - 1);

			i = PartitionByValue(I, 0, 1, 43);
			ASSERT1(i == 1);
			ASSERT1(I[0] == 3);
			ASSERT1(I[1] == 43);

			i = PartitionByValue(I, 2, 3, 1);
			ASSERT1(i == 2);
			ASSERT1(I[2] == 1);
			ASSERT1(I[3] == 42);

			i = PartitionByValue(I, 0, L - 1, 64);
			ASSERT1(i >= 0);
			ASSERT1(i <= L - 1);
			for (int j = 0; j < L - 1; j++) {
				if (j < i) ASSERT1(I[j] <= I[i]);
				else if (j > i) ASSERT1(I[j] >= I[i]);
			}

			for (int k = 0; k < 10; k++) {
				Random(I, 100);
				L = (int)I.size();
				Logger().Print(I);
				i = PartitionRandomly(I, 0, L - 1);
				Logger().WriteInformation("Partition by %d at index %d:\n", I[i], i);
				Logger().Print(I);
				ASSERT1(i >= 0);
				ASSERT1(i <= L - 1);
				for (int j = 0; j < L - 1; j++)
					if (j < i) ASSERT1(I[j] <= I[i]);
					else if (j > i) ASSERT1(I[j] > I[i]);
					Logger().WriteInformation("\n");
			}
		}
		{
			vector<int> I = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
			int L = (int)I.size();

			int i = PartitionByOrder(I, 0, 0, 0);
			ASSERT1(i == 3);

			i = PartitionByOrder(I, L - 1, L - 1, 0);
			ASSERT1(i == 64);

			i = PartitionByOrder(I, 0, 1, 0);
			ASSERT1(i == 3);
			ASSERT1(I[0] == 3);
			ASSERT1(I[1] == 43);

			i = PartitionByOrder(I, 0, 1, 1);
			ASSERT1(i == 43);
			ASSERT1(I[0] == 3);
			ASSERT1(I[1] == 43);

			i = PartitionByOrder(I, 2, 3, 0);
			ASSERT1(i == 1);
			ASSERT1(I[2] == 1);
			ASSERT1(I[3] == 42);

			i = PartitionByOrder(I, 2, 3, 1);
			ASSERT1(i == 42);
			ASSERT1(I[2] == 1);
			ASSERT1(I[3] == 42);

			for (int p = 0; p < 100; p++) {
				Random(I, 100);
				L = (int)I.size();
				Logger().Print(I);
				int j = rand() % L;
				i = PartitionByOrder(I, 0, L - 1, j);
				Logger().WriteInformation("Partition by %d at index %d:\n", I[j], j);
				Logger().Print(I);
				ASSERT1(i == I[j]);
				for (int k = 0; k < L - 1; k++)
					if (k < j) ASSERT1(I[k] <= I[j]);
					else if (k > j) ASSERT1(I[k] >= I[j]);
					Logger().WriteInformation("\n");
			}
		}
	});

	Add("QuickSort", [&]() {
		{
			vector<int> I = { 1 };
			QuickSort(I);
			ASSERT1(I[0] == 1);
		}
		{
			vector<int> I = { 2, 1 };

			QuickSort(I);
			ASSERT1(I[0] == 1);
			ASSERT1(I[1] == 2);

			QuickSort(I);
			ASSERT1(I[0] == 1);
			ASSERT1(I[1] == 2);

			I[1] = I[0];
			QuickSort(I);
			ASSERT1(I[0] == 1);
			ASSERT1(I[1] == 1);
		}
		{
			vector<int> I = { 3, 2, 1 };

			QuickSort(I);
			ASSERT1(I[0] == 1);
			ASSERT1(I[1] == 2);
			ASSERT1(I[2] == 3);

			QuickSort(I);
			ASSERT1(I[0] == 1);
			ASSERT1(I[1] == 2);
			ASSERT1(I[2] == 3);

			I[1] = I[0];
			I[2] = I[0];
			QuickSort(I);
			ASSERT1(I[0] == 1);
			ASSERT1(I[1] == 1);
			ASSERT1(I[2] == 1);
		}
		{
			vector<int> V = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
			vector<int> I1, I2, I3;
			Duplicate(V, I1);
			Duplicate(V, I2);
			Duplicate(V, I3);
			
			QuickSort(I1);
			QuickSortInParallel(I2);
			QuickSortRandomly(I3);

			std::sort(V.begin(), V.end());

			for (int i = 0; i < V.size(); i++) {
				ASSERT1(V[i] == I1[i]);
				ASSERT1(V[i] == I2[i]);
				ASSERT1(V[i] == I3[i]);
			}
		}
		{
			vector<int> V = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
			vector<int> I;
			Duplicate(V, I);

			QuickSort(I);
			std::sort(V.begin(), V.end());

			for (int i = 0; i < V.size(); i++) {
				ASSERT1(V[i] == I[i]);
			}
		}
		{
			vector<int> V = { 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2 };
			vector<int> I;
			Duplicate(V, I);

			QuickSort(I);
			std::sort(V.begin(), V.end());

			for (int i = 0; i < V.size(); i++) {
				ASSERT1(V[i] == I[i]);
			}
		}
		{
			for (int i = 0; i < 100; i++) {
				vector<int> v;
				Random(v);
				Logger().WriteInformation("Run %d: %d elements\n", i, v.size());

				vector<int> i1, i2, i3;
				Duplicate(v, i1);
				Duplicate(v, i2);
				Duplicate(v, i3);

				QuickSort(i1);
				QuickSortInParallel(i2);
				QuickSortRandomly(i3);

				std::sort(v.begin(), v.end());

				for (int i = 0; i < v.size(); i++) {
					ASSERT1(v[i] == i1[i]);
					ASSERT1(v[i] == i2[i]);
					ASSERT1(v[i] == i3[i]);
				}
			}
		}
	});

	Add("RadixSort", [&]() {
		{
			auto check = [&](vector<vector<int>> v) -> bool {
				for (int i = 1; i < (int)v.size(); i++) {
					for (int j = (int)v[0].size() - 1; j >= 0; j--) {
						if (v[i - 1][j] < v[i][j]) return true;
						if (v[i - 1][j] > v[i][j]) return false;
					}
				}
				return true;
			};

			for (int i = 0; i < 100; i++) {
				Logger().WriteInformation("Run %d:\n", i);
				vector<vector<int>> v;
				Random(v, 50, 50, 20);
				Logger().WriteInformation("Input:\n");
				Logger().Print(v, "%2d");
				RadixSort(v);
				Logger().WriteInformation("Sorted:\n");
				Logger().Print(v, "%2d");
				ASSERT1(true == check(v));
			}
		}
	});

	Add("PositionToInsert", [&]() {
		{
			int e = 2;
			int n = 100;
			vector<int> input(n, e);
			int i = PositionToInsert(e, input);
			ASSERT1(-1 == i);
			i = PositionToInsert(e, input, false);
			ASSERT1(n - 1 == i);
		}
		{
			for (int i = 0; i < 100; i++) {
				vector<int> input;
				Random(input, 200, 200);
				Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
				sort(input.begin(), input.end());
				Logger().Print(input);
				for (int j = 0; j < 10; j++) {
					int e1 = rand() % 50;
					int e2 = input[rand() % input.size()];
					Logger().WriteInformation("Found %d", e1);
					int i1 = PositionToInsert(e1, input);
					Logger().WriteInformation(" at %d\n", i1);
					Logger().WriteInformation("Found %d", e2);
					int i2 = PositionToInsert(e2, input);
					Logger().WriteInformation(" at %d\n", i2);
					if (i1 >= 0)
						ASSERT1(input[i1] < e1);
					if (i1 < (int)input.size() - 1)
						ASSERT1(e1 <= input[i1 + 1]);
					if (i2 >= 0)
						ASSERT1(input[i2] < e2);
					if (i2 < (int)input.size() - 1)
						ASSERT1(e2 <= input[i2 + 1]);
				}
			}
		}
		{
			for (int i = 0; i < 100; i++) {
				vector<int> input;
				Random(input, 200, 200);
				Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
				sort(input.begin(), input.end());
				Logger().Print(input);
				for (int j = 0; j < 10; j++) {
					int e1 = rand() % 50;
					int e2 = input[rand() % input.size()];
					Logger().WriteInformation("Found %d", e1);
					int i1 = PositionToInsert(e1, input, false);
					Logger().WriteInformation(" at %d\n", i1);
					Logger().WriteInformation("Found %d", e2);
					int i2 = PositionToInsert(e2, input, false);
					Logger().WriteInformation(" at %d\n", i2);
					if (i1 >= 0)
						ASSERT1(input[i1] <= e1);
					if (i1 < (int)input.size() - 1)
						ASSERT1(e1 < input[i1 + 1]);
					if (i2 >= 0)
						ASSERT1(input[i2] <= e2);
					if (i2 < (int)input.size() - 1)
						ASSERT1(e2 < input[i2 + 1]);
				}
			}
		}
	});

	Add("MaxSum", [&]() {
		auto check = [&](const vector<int> & a, int el, int er, int es) -> void {
			Logger().Print(a);
			int l1, r1, sum1;
			MaxSum1(a, l1, r1, sum1);
			Logger().WriteInformation("a[%d..%d] = %d\n", l1, r1, sum1);
			int l2, r2, sum2;
			MaxSum2(a, l2, r2, sum2);
			Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
			ASSERT1(el == l1);
			ASSERT1(er == r1);
			ASSERT1(es == sum1);
			ASSERT1(el == l2);
			ASSERT1(er == r2);
			ASSERT1(es == sum2);
		};
		{
			vector<int> A = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
			check(A, 7, 10, 43);
		}
		{
			vector<int> A = { 13 };
			check(A, 0, 0, 13);
		}
		{
			vector<int> A = { 13, -3 };
			check(A, 0, 0, 13);
		}
		{
			vector<int> A = { 13, -3, -25 };
			check(A, 0, 0, 13);
		}
		{
			vector<int> A = { 13, -3, -25, 20 };
			check(A, 3, 3, 20);
		}
		{
			vector<int> A = { 13, -3, -25, 20, -3 };
			check(A, 3, 3, 20);
		}
		{
			vector<int> A = { 13, -3, -25, 20, -3, -16, -23, 18 };
			check(A, 3, 3, 20);
		}
		{
			vector<int> A = { 13, 3, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 4, 7 };
			check(A, 0, (int)A.size() - 1, 213);
		}
		{
			vector<int> A = { 13, 3 };
			check(A, 0, 1, 16);
		}
		{
			vector<int> A = { 13, 3, 25 };
			check(A, 0, 2, 41);
		}
		{
			vector<int> A = { -13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
			check(A, 1, 1, -3);
		}
		{
			vector<int> A = { -13 };
			check(A, 0, 0, -13);
		}
		{
			vector<int> A = { -13, -3 };
			check(A, 1, 1, -3);
		}
		{
			vector<int> A = { 0, 0, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
			check(A, 0, 0, 0);
		}
		{
			vector<int> A = { 0 };
			check(A, 0, 0, 0);
		}
		{
			vector<int> A = { 0, 0, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 0, 0 };
			check(A, 2, 13, 186);
		}
		{
			vector<int> A = { -25, -20, -3, 0, 0, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
			check(A, 3, 3, 0);
		}
		{
			vector<int> A = { -25, -20, -3, 0, 0 };
			check(A, 3, 3, 0);
		}
		{
			vector<int> A = { 1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
			check(A, 0, 2, 3);
		}
		{
			vector<int> A = { 1, 1, 1, -1, -1, -1 };
			check(A, 0, 2, 3);
		}
		{
			vector<int> A = { 1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, 7 };
			check(A, (int)A.size() - 1, (int)A.size() - 1, 7);
		}
		{
			int d = RAND_MAX >> 1;
			for (int i = 0; i < 1000; i++) {
				vector<int> input;
				int length = 1 + (rand() % 100);
				for (int j = 0; j < length; j++) {
					input.push_back(rand() - d);
				}
				Logger().Print(input);
				int l1, r1, sum1;
				MaxSum1(input, l1, r1, sum1);
				Logger().WriteInformation("a[%d..%d] = %d\n", l1, r1, sum1);
				int l2, r2, sum2;
				MaxSum2(input, l2, r2, sum2);
				Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
				ASSERT1(l1 == l2);
				ASSERT1(r1 == r2);
				ASSERT1(sum1 == sum2);
			}
		}
		{
			for (int i = 0; i < 1000; i++) {
				vector<int> input;
				int length = 1 + (rand() % 100);
				for (int j = 0; j < length; j++) {
					input.push_back(rand() % 20 - 10);
				}
				Logger().Print(input);
				int l1, r1, sum1;
				MaxSum1(input, l1, r1, sum1);
				Logger().WriteInformation("a[%d..%d] = %d\n", l1, r1, sum1);
				int l2, r2, sum2;
				MaxSum2(input, l2, r2, sum2);
				Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
				ASSERT1(l1 == l2);
				ASSERT1(r1 == r2);
				ASSERT1(sum1 == sum2);
			}
		}
	});

	Add("Sort", [&]() {
		auto check = [&](vector<int> & input) {
			Logger().WriteInformation("Input:  ");
			Logger().Print(input);
			size_t count = 11;
			vector<vector<int>> inputs(count, vector<int> {});
			for_each(inputs.begin(), inputs.end(), [&](vector<int> & v) {
				Duplicate(input, v);
			});

			sort(input.begin(), input.end());
			Logger().WriteInformation("Sorted: ");
			Logger().Print(input);
			
			QuickSort(inputs[0]);
			QuickSortInParallel(inputs[1]);
			QuickSortRandomly(inputs[2]);
			InsertSort(inputs[3]);
			InsertSortRecursively(inputs[4], inputs[4].size());
			SelectSort(inputs[5]);
			MergeSort(inputs[6]);
			HeapSort(inputs[7]);
			HeapSortInParallel(inputs[8]);
			HeapSort(inputs[9], 3);
			HeapSortInParallel(inputs[10], 3);
			for (size_t i = 0; i < input.size(); i++) {
				for (size_t j = 0; j < count; j++) {
					ASSERT2(
						inputs[j][i] == input[i],
						String::Format("inputs[%d][%d] = %d != %d\n", j, i, inputs[j][i], input[i]));
				}
			}
		};
		{
			vector<int> i = { 1 };
			check(i);
		}
		{
			vector<int> i = { 1, 2 };
			check(i);
		}
		{
			vector<int> i = { 2, 1 };
			check(i);
		}
		{
			vector<int> i = { 2, 2 };
			check(i);
		}
		{
			vector<int> i = { 1, 2, 3 };
			check(i);
		}
		{
			vector<int> i = { 2, 1, 3 };
			check(i);
		}
		{
			vector<int> i = { 3, 1, 2 };
			check(i);
		}
		{
			vector<int> i = { 2, 2, 3 };
			check(i);
		}
		{
			vector<int> i = { 2, 3, 2 };
			check(i);
		}
		{
			vector<int> i = { 3, 2, 2 };
			check(i);
		}
		{
			vector<int> i = { 3, 3, 3 };
			check(i);
		}
		{
			for (int i = 0; i < 1000; i++) {
				vector<int> input;
				Random(input, 200, 200);
				Logger().WriteInformation("Run %d: %d elements\n", i, input.size());
				check(input);
			}
		}
	});

	Add("Heap", [&]() {
		{
			Heap<int> heap;

			ASSERT1(heap.IsHeap());

			heap.Push(0);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 1);

			heap.Push(2);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 2);

			heap.Push(-1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 2);

			for (int i = 3; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == i);
			}

			ASSERT1(heap.IsHeap());
		}
		{
			Heap<int> heap;

			for (int i = 0; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == i);
			}

			ASSERT1(heap.IsHeap());

			for (int i = 0; i < 10; i++) {
				int v = heap.Pop();
				ASSERT1(heap.IsHeap());
				ASSERT1(v == (9 - i));
			}
		}
		{
			vector<int> input;

			for (int i = 0; i < 10; i++) {
				input.push_back(i);
			}

			Heap<int> heap(input);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 9);
		}
		{
			Heap<int> heap(1);

			ASSERT1(heap.IsHeap());

			heap.Push(0);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(2);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(-1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == -1);

			for (int i = 3; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == -1);
			}

			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == -1);
		}
		{
			// This example shows the heap keeps the smallest two numbers from the input

			Heap<int> heap(2);

			ASSERT1(heap.IsHeap());

			heap.Push(0);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 1);

			heap.Push(2);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 1);

			heap.Push(-1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			for (int i = 3; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == 0);
			}

			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);
		}
		{
			Heap<int, greater<int>> heap;

			ASSERT1(heap.IsHeap());

			heap.Push(0);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(2);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(-1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == -1);

			for (int i = 3; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == -1);
			}

			ASSERT1(heap.IsHeap());
		}
		{
			Heap<int, greater<int>> heap;

			for (int i = 0; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == 0);
			}

			ASSERT1(heap.IsHeap());

			for (int i = 0; i < 10; i++) {
				int v = heap.Pop();
				ASSERT1(heap.IsHeap());
				ASSERT1(v == i);
			}
		}
		{
			vector<int> input;

			for (int i = 0; i < 10; i++) {
				input.push_back(i);
			}

			Heap<int, greater<int>> heap(input);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);
		}
		{
			Heap<int, greater<int>> heap(1);

			ASSERT1(heap.IsHeap());

			heap.Push(0);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 1);

			heap.Push(2);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 2);

			heap.Push(-1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 2);

			for (int i = 3; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == i);
			}

			ASSERT1(heap.IsHeap());
		}
		{
			// This example shows the heap keeps the greatest two numbers from the input

			Heap<int, greater<int>> heap(2);

			ASSERT1(heap.IsHeap());

			heap.Push(0);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 0);

			heap.Push(2);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 1);

			heap.Push(-1);
			ASSERT1(heap.IsHeap());
			ASSERT1(heap.Top() == 1);

			for (int i = 3; i < 10; i++) {
				heap.Push(i);
				ASSERT1(heap.Top() == (i - 1));
			}

			ASSERT1(heap.IsHeap());
		}
		{
			less<int> lt;
			for (int i = 0; i < 100; i++) {
				int count = 1 + rand() % 1000;
				Logger().WriteInformation("Run %d: %d elements\n", i, count);
				Heap<int, less<int>> heap;
				vector<int> vheap;
				for (int j = 0; j < count; j++) {
					int v = rand() % 1000;
					heap.Push(v);
					vheap.push_back(v);
					push_heap(vheap.begin(), vheap.end(), lt);
					ASSERT1(heap.Top() == vheap.front());
				}
				for (int j = 0; j < count; j++) {
					int h = heap.Pop();
					pop_heap(vheap.begin(), vheap.end(), lt);
					int vh = vheap.back();
					vheap.pop_back();
					ASSERT1(h == vh);
					if (j < count - 1)
						ASSERT1(heap.Top() == vheap.front());
				}
			}
		}
		{
			greater<int> gt;
			for (int i = 0; i < 100; i++) {
				int count = 1 + rand() % 1000;
				Logger().WriteInformation("Run %d: %d elements\n", i, count);
				Heap<int, greater<int>> heap;
				vector<int> vheap;
				for (int j = 0; j < count; j++) {
					int v = rand() % 1000;
					heap.Push(v);
					vheap.push_back(v);
					push_heap(vheap.begin(), vheap.end(), gt);
					ASSERT1(heap.Top() == vheap.front());
				}
				for (int j = 0; j < count; j++) {
					int h = heap.Pop();
					pop_heap(vheap.begin(), vheap.end(), gt);
					int vh = vheap.back();
					vheap.pop_back();
					ASSERT1(h == vh);
					if (j < count - 1)
						ASSERT1(heap.Top() == vheap.front());
				}
			}
		}
	});

	Add("MergeSort", [&]() {
		{
			vector<vector<int>> inputs = {
				{ 0, 5, 9, 11 },
				{ 0, 1, 2, 3, 5, 6 },
				{ 6, 7, 8 }
			};

			Logger().Print(inputs);

			vector<int> output;

			MergeSort(inputs, output);

			ASSERT1(is_sorted(output.begin(), output.end()));
			ASSERT1(output.size() == 13);

			Logger().Print(output);
			Logger().WriteInformation("\n");
		}
		{
			for (int i = 0; i < 100; i++) {
				int count = 1 + rand() % 10;
				vector<vector<int>> inputs(count, vector<int> {});
				size_t size = 0;
				for (int j = 0; j < count; j++) {
					Random(inputs[j], 10, 100);
					size += inputs[j].size();
					sort(inputs[j].begin(), inputs[j].end());
				}
				Logger().WriteInformation("Run %d: %d elements\n", i, size);
				Logger().Print(inputs);
				vector<int> output;
				MergeSort(inputs, output);
				Logger().Print(output);
				ASSERT1(is_sorted(output.begin(), output.end()));
				ASSERT1(output.size() == size);
			}
		}
	});

	Add("HeapSort", [&]() {
		{
			for (int j = 0; j < 100; j++) {
				vector<int> i1;
				Random(i1);
				Logger().WriteInformation("Run %d, %d elements\n", j, i1.size());
				vector<int> i2;
				Duplicate(i1, i2);

				Heapify(i1);
				HeapifyInParallel(i2);

				for (size_t i = 0; i < i1.size(); i++) {
					ASSERT2(i1[i] == i2[i], String::Format("i1[%d] %d != i2[%d] %d", i, i1[i], i, i2[i]));
				}
			}
		}
		{
			for (int j = 0; j < 100; j++) {
				vector<int> a, v;
				Random(a);
				Duplicate(a, v);
				unsigned int dimension = 2 + (rand() % 100);
				Logger().WriteInformation("Run %d, %d elements, %d-heap\n", j, a.size(), dimension);

				HeapSort(a, dimension);
				std::make_heap(v.begin(), v.end());
				std::sort_heap(v.begin(), v.end());

				for (size_t i = 0; i < a.size(); i++) {
					ASSERT2(a[i] == v[i], String::Format("i[%d] %d != v[%d] %d", i, a[i], i, v[i]));
				}
			}
		}
		{
			for (int j = 0; j < 100; j++) {
				vector<int> i1, i2;
				Random(i1);
				Duplicate(i1, i2);
				unsigned int dimension = 2 + (rand() % 100);
				Logger().WriteInformation("Run %d, %d elements, %d-heap\n", j, i1.size(), dimension);

				Heapify(i1, dimension);
				HeapifyInParallel(i2, dimension);

				for (size_t i = 0; i < i1.size(); i++) {
					ASSERT2(i1[i] == i2[i], String::Format("i1[%d] %d != i2[%d] %d", i, i1[i], i, i2[i]));
				}
			}
		}
	});

	Add("RemoveDuplicateChar", [&]() {
		auto check = [&](char * c, int length, char * e, int el) {
			Logger().WriteInformation("%s\t", c);
			int l = RemoveDuplicateChars(c, length);
			Logger().WriteInformation("%s\n", c);
			ASSERT1(0 == strcmp(c, e));
			ASSERT1(l == el);
		};
		{
			char * c;
			c = nullptr;
			int l = RemoveDuplicateChars(c, 0);
			ASSERT1(l == -1);
		}
		{
			char c[] = "Test";
			char e[] = "Test";
			check(c, 4, e, 4);
		}
		{
			char c[] = "TTeesstt";
			char e[] = "Test";
			check(c, 8, e, 4);
		}
		{
			char c[] = "TestTest";
			char e[] = "Test";
			check(c, 8, e, 4);
		}
		{
			char c[] = "";
			char e[] = "";
			check(c, 0, e, 0);
		}
		{
			string alphabet = "abcdefghijklmnopqrstuvwxyz";
			for (int i = 0; i < 100; i++) {
				size_t length = 1 + (rand() % 100);
				string s1 = String::Random(alphabet, length);
				Logger().WriteInformation("Run %d: %s\n", i, s1.c_str());
				unique_ptr<char[]> s2(new char[length + 1]);
				memcpy(s2.get(), s1.c_str(), length);
				s2[length] = '\0';
				set<char> ss1 = String::UniqueChars(s1);
				Logger().Print(ss1, "%c");
				int ls2 = RemoveDuplicateChars(s2.get(), (int)length);
				Logger().Print(s2.get(), (size_t)ls2, "%c");
				ASSERT1((int)ss1.size() == ls2);
				for (int j = 0; j < ls2; j++) {
					ASSERT2(ss1.find(s2[j]) != ss1.end(), String::Format("%c is not found in set\n", s2[j]));
				}
			}
		}
	});

	Add("IsMatch", [&]() {
		auto check = [&](char * s, char * p, bool e) {
			bool m1 = IsMatch1(s, p);
			bool m2 = IsMatch2(s, p);
			Logger().WriteInformation("IsMatch:\t%s %s %s\n", s, m1 ? "==" : "!=", p);
			Logger().WriteInformation("IsMatch2:\t%s %s %s\n", s, m2 ? "==" : "!=", p);
			ASSERT1(m1 == e);
			ASSERT1(m2 == e);
		};
		check("", "", true);
		check("a", "", false);
		check("", "a", false);
		check("", "*", true);
		check("", ".*", true);
		check("aa", "a", false);
		check("aa", ".", false);
		check("aa", "aa", true);
		check("aa", "..", true);
		check("aa", "*aa", true);
		check("aaa", "aa", false);
		check("aaa", "*aa", false);
		check("aaa", "aa*", true);
		check("aaa", "aa**", true);
		check("aaa", "a*a", true);
		check("aaa", "...", true);
		check("aaa", ".*.", true);
		check("aa", "a*", true);
		check("aa", ".*", true);
		check("ab", ".*", true);
		check("ab", "..", true);
		check("aab", "c*a*b", true);
		check("aab", "c***a**b", true);
		check("abbbc", "ab*c", true);
		check("ac", "ab*c", true);
		check("abbc", "ab*bbc", true);
		check("abcbcd", "a.*c.*d", true);
		const string ab1 = "ab";
		const string ab2 = "ab.*";
		for (int i = 0; i < 100; i++) {
			size_t len1 = 1 + rand() % 5;
			string input = String::Random(ab1, len1);
			size_t len2 = 1 + rand() % 5;
			string pattern = String::Random(ab2, len2);
			bool m1 = IsMatch1(input.c_str(), pattern.c_str());
			bool m2 = IsMatch2(input.c_str(), pattern.c_str());
			Logger().WriteInformation("IsMatch1:\t%s %s %s\n", input.c_str(), m1 ? "==" : "!=", pattern.c_str());
			Logger().WriteInformation("IsMatch2:\t%s %s %s\n", input.c_str(), m2 ? "==" : "!=", pattern.c_str());
			ASSERT1(m1 == m2);
		}
	});

	Add("LongestSubStringWithUniqueChars", [&]() {
		auto check = [&](char * s, int i, int l) {
			string ss(s);
			size_t ai1, al1;
			LongestSubStringWithUniqueChars1(ss, ai1, al1);
			size_t ai2, al2;
			LongestSubStringWithUniqueChars1(ss, ai2, al2);
			Logger().WriteInformation(
				"%s, (%d%s%d, %d%s%d), %s\n",
				ss.c_str(),
				ai1,
				ai1 == i ? "==" : "!=",
				i,
				al1,
				al1 == l ? "==" : "!=",
				l,
				ss.substr(ai1, al1).c_str());
			Logger().WriteInformation(
				"%s, (%d%s%d, %d%s%d), %s\n",
				ss.c_str(),
				ai2,
				ai2 == i ? "==" : "!=",
				i,
				al2,
				al2 == l ? "==" : "!=",
				l,
				ss.substr(ai2, al2).c_str());
			ASSERT1(ai1 == i);
			ASSERT1(al1 == l);
			ASSERT1(ai2 == i);
			ASSERT1(al2 == l);
		};
		check("a", 0, 1);
		check("aa", 0, 1);
		check("ab", 0, 2);
		check("aaa", 0, 1);
		check("aba", 0, 2);
		check("aab", 1, 2);
		check("abc", 0, 3);
		check("abab", 0, 2);
		check("abba", 0, 2);
		check("abca", 0, 3);
		check("aabc", 1, 3);
		check("abac", 1, 3);
		check("abcd", 0, 4);
		check("abcabc", 0, 3);
		check("abcad", 1, 4);
		check("aaabcd", 2, 4);
		check("abcabcbb", 0, 3);
		for (int i = 0; i < 100; i++) {
			size_t len = 1 + (rand() % 100);
			string ss = String::Random<char>(len);
			size_t ai1, al1;
			LongestSubStringWithUniqueChars1(ss, ai1, al1);
			size_t ai2, al2;
			LongestSubStringWithUniqueChars1(ss, ai2, al2);
			Logger().WriteInformation(
				"%s, (%d, %d), %s\n",
				ss.c_str(),
				ai1,
				al1,
				ss.substr(ai1, al1).c_str());
			Logger().WriteInformation(
				"%s, (%d, %d), %s\n",
				ss.c_str(),
				ai2,
				al2,
				ss.substr(ai2, al2).c_str());
			ASSERT1(ai1 == ai2);
			ASSERT1(al1 == al2);
		}
	});

	Add("ShortestSubStringContainingGivenChars", [&]() {
		{
			auto check = [&](const string & input, const string & chars, const string & expect) {
				int index1;
				int length1;
				ShortestSubStringContainingGivenChars::Solve1(chars, input, index1, length1);
				string match1 = index1 == -1 ? "" : input.substr(index1, length1);
				int index2;
				int length2;
				ShortestSubStringContainingGivenChars::Solve2(chars, input, index2, length2);
				string match2 = index2 == -1 ? "" : input.substr(index2, length2);
				int index3;
				int length3;
				ShortestSubStringContainingGivenChars::SolveGivenUniqueChars1(chars, input, index3, length3);
				string match3 = index3 == -1 ? "" : input.substr(index3, length3);
				int index4;
				int length4;
				ShortestSubStringContainingGivenChars::SolveGivenUniqueChars2(chars, input, index4, length4);
				string match4 = index4 == -1 ? "" : input.substr(index4, length4);
				Logger().WriteInformation("Input: %s\n", input.c_str());
				Logger().WriteInformation("Chars: %s\n", chars.c_str());
				Logger().WriteInformation("Match1: %s %s %s\n", match1.c_str(), match1 == expect ? "==" : "!=", expect.c_str());
				Logger().WriteInformation("Match2: %s %s %s\n", match2.c_str(), match2 == expect ? "==" : "!=", expect.c_str());
				Logger().WriteInformation("Match3: %s %s %s\n", match3.c_str(), match3 == expect ? "==" : "!=", expect.c_str());
				Logger().WriteInformation("Match4: %s %s %s\n", match4.c_str(), match4 == expect ? "==" : "!=", expect.c_str());
				ASSERT1(match1 == expect);
				ASSERT1(match2 == expect);
				ASSERT1(match3 == expect);
				ASSERT1(match4 == expect);
			};

			check("aaaaa", "a", "a");
			check("aaaaa", "b", "");
			check("aaaaa", "ab", "");
			check("abaa", "ab", "ab");
			check("abaa", "ba", "ab");
			check("ccab", "ab", "ab");
			check("ccab", "ba", "ab");
			check("aabaa", "ab", "ab");
			check("aabaa", "ba", "ab");
			check("ccaba", "ab", "ab");
			check("ccaba", "ba", "ab");
			check("aacbddaa", "ba", "acb");
			check("aacdbddbeaa", "ab", "bea");
			check("ADOBECODEBANC", "ABC", "BANC");
			check("aabbbccaa", "abc", "bcca");
			check("aabbbccbaa", "abc", "cba");
			check("bcdfdefdcfeecgfacecdeagadcb", "dcgab", "gadcb");
			check("cfegdgbddacafeaccceccedgagfcbagcfbcdfdefdcfeecgfacecdeagadcbeddcacadebafcdcga", "dcgab", "gadcb");
		}
		{
			auto check = [&](const string & input, const string & chars, const string & expect) {
				int index1;
				int length1;
				ShortestSubStringContainingGivenChars::Solve1(chars, input, index1, length1);
				string match1 = index1 == -1 ? "" : input.substr(index1, length1);
				int index2;
				int length2;
				ShortestSubStringContainingGivenChars::Solve2(chars, input, index2, length2);
				string match2 = index2 == -1 ? "" : input.substr(index2, length2);
				Logger().WriteInformation("Input: %s\n", input.c_str());
				Logger().WriteInformation("Chars: %s\n", chars.c_str());
				Logger().WriteInformation("Match1: %s %s %s\n", match1.c_str(), match1 == expect ? "==" : "!=", expect.c_str());
				Logger().WriteInformation("Match2: %s %s %s\n", match2.c_str(), match2 == expect ? "==" : "!=", expect.c_str());
				ASSERT1(match1 == expect);
				ASSERT1(match2 == expect);
			};

			check("aaaaa", "aa", "aa");
			check("aaaaa", "bb", "");
			check("aaaaa", "aba", "");
			check("abaa", "aab", "aba");
			check("abaa", "aba", "aba");
			check("ccab", "ccab", "ccab");
			check("ccab", "cba", "cab");
			check("aabaa", "aaab", "aaba");
			check("aabaa", "baa", "aab");
			check("ccaba", "aab", "aba");
			check("ccaba", "aba", "aba");
			check("aacbddaa", "aba", "aacb");
			check("aacdbddbeaa", "aabb", "bddbeaa");
			check("ADOBECODEBANC", "ABCC", "CODEBANC");
			check("aabbbccaa", "abbc", "abbbc");
			check("aabbbccbaa", "aabcc", "ccbaa");
		}
		{
			auto length = [&](int max)->int {
				return 1 + rand() % max;
			};
			string alphabet = "abcdefg";
			auto random = [&](int len)->string {
				string output = String::Random(alphabet, len);
				return output;
			};
			for (int i = 0; i < 1000; i++) {
				string chars = random(length(10));
				string input = random(length(100));
				int index1;
				int length1;
				ShortestSubStringContainingGivenChars::Solve1(chars, input, index1, length1);
				string match1 = index1 == -1 ? "" : input.substr(index1, length1);
				int index2;
				int length2;
				ShortestSubStringContainingGivenChars::Solve2(chars, input, index2, length2);
				string match2 = index2 == -1 ? "" : input.substr(index2, length2);
				Logger().WriteInformation("Input: %s\n", input.c_str());
				Logger().WriteInformation("Chars: %s\n", chars.c_str());
				Logger().WriteInformation("%s %s %s\n", match1.c_str(), match1 == match2 ? "==" : "!=", match2.c_str());
				ASSERT1(match1 == match2);
				if (ContainsUniqueChars(chars)) {
					int index3;
					int length3;
					ShortestSubStringContainingGivenChars::SolveGivenUniqueChars1(chars, input, index3, length3);
					string match3 = index3 == -1 ? "" : input.substr(index3, length3);
					Logger().WriteInformation("%s %s %s\n", match1.c_str(), match1 == match3 ? "==" : "!=", match3.c_str());
					int index4;
					int length4;
					ShortestSubStringContainingGivenChars::SolveGivenUniqueChars2(chars, input, index4, length4);
					string match4 = index4 == -1 ? "" : input.substr(index4, length4);
					Logger().WriteInformation("%s %s %s\n", match1.c_str(), match1 == match4 ? "==" : "!=", match4.c_str());
					ASSERT1(match1 == match4);
				}
			}
		}
	});

	Add("ReplaceWithShorterString", [&]() {
		auto check = [&](char * input, char * pattern, char * shorter, char * expect) {
			Logger().WriteInformation("\nInput:   %s\n", input);
			Logger().WriteInformation("Pattern: %s\n", pattern);
			Logger().WriteInformation("Shorter: %s\n", shorter);
			ReplaceWithShorterString(input, pattern, shorter);
			Logger().WriteInformation("Output:  %s\n", input);
			while (*input != '\0') {
				ASSERT1(*input++ == *expect++);
			}
		};
		char A[][4][256] = {
			{ "a", "a", "X", "X" },
			{ "aa", "aa", "X", "X" },
			{ "aa", "a", "X", "X" },
			{ "aa", "aaa", "X", "aa" },
			{ "abc", "abc", "X", "X" },
			{ "abcabc", "abc", "X", "X" },
			{ "abcabcabc", "abc", "X", "X" },
			{ "abcaabcaabc", "abc", "X", "XaXaX" },
			{ "abcaaabcaaabca", "abc", "X", "XaaXaaXa" },
			{ "abcabcabababcabc", "abc", "X", "XababX" },
			{ "abcabcabababcabcab", "abc", "X", "XababXab" },
			{ "aabbaabbaaabbbaabb", "aabb", "X", "XaXbX" },
			{ "aabbaabbaaabbbaabb", "aaabb", "X", "aabbaabbXbaabb" },
			{ "aabbaabbaaabbbaaabb", "aaabb", "X", "aabbaabbXbX" },
			{ "aabbaabbaaabbbaaabc", "aaabb", "X", "aabbaabbXbaaabc" },
			{ "abcdeffdfegabcabc", "abc", "X", "XdeffdfegX" },
			{ "abcdeffdfegabcabc", "ab", "X", "XcdeffdfegXcXc" },
			{ "abcdeffdfegabcabc", "a", "X", "XbcdeffdfegXbcXbc" },
			{ "abcdeffdfegabcab", "abc", "X", "XdeffdfegXab" },
			{ "abcdeffdfegabcabcab", "abc", "X", "XdeffdfegXab" },
			{ "abcdeffdfegabcaabcab", "abc", "X", "XdeffdfegXaXab" },
			{ "abcdeffdfegabcaaaabcab", "abc", "X", "XdeffdfegXaaaXab" },
			{ "aaaaaa", "a", "X", "X" },
			{ "aaaaaa", "aa", "X", "X" },
			{ "aaaaaa", "aaaaaa", "X", "X" },
			{ "aaaaaa", "aaaaaaa", "X", "aaaaaa" },
			{ "aabaababaaab", "a", "X", "XbXbXbXb" },
			{ "aabaababaaa", "a", "X", "XbXbXbX" },
			{ "aaaab", "a", "X", "Xb" },
			{ "baaa", "a", "X", "bX" },
			{ "aabaaabaab", "aaa", "X", "aabXbaab" },
			{ "aabaaabaab", "aa", "X", "XbXabXb" },
			{ "aabaaabaa", "aa", "X", "XbXabX" },
			{ "aa", "aa", "XY", "XY" },
			{ "aa", "aaa", "XY", "aa" },
			{ "abc", "abc", "XY", "XY" },
			{ "abcabc", "abc", "XY", "XY" },
			{ "abcabcabc", "abc", "XY", "XY" },
			{ "abcaabcaabc", "abc", "XY", "XYaXYaXY" },
			{ "abcaaabcaaabca", "abc", "XY", "XYaaXYaaXYa" },
			{ "abcabcabababcabc", "abc", "XY", "XYababXY" },
			{ "abcabcabababcabcab", "abc", "XY", "XYababXYab" },
			{ "aabbaabbaaabbbaabb", "aabb", "XY", "XYaXYbXY" },
			{ "aabbaabbaaabbbaabb", "aaabb", "XY", "aabbaabbXYbaabb" },
			{ "aabbaabbaaabbbaaabb", "aaabb", "XY", "aabbaabbXYbXY" },
			{ "aabbaabbaaabbbaaabc", "aaabb", "XY", "aabbaabbXYbaaabc" },
			{ "abcdeffdfegabcabc", "abc", "XY", "XYdeffdfegXY" },
			{ "abcdeffdfegabcabc", "ab", "XY", "XYcdeffdfegXYcXYc" },
			{ "abcdeffdfegabcab", "abc", "XY", "XYdeffdfegXYab" },
			{ "abcdeffdfegabcabcab", "abc", "XY", "XYdeffdfegXYab" },
			{ "abcdeffdfegabcaabcab", "abc", "XY", "XYdeffdfegXYaXYab" },
			{ "abcdeffdfegabcaaaabcab", "abc", "XY", "XYdeffdfegXYaaaXYab" },
			{ "aaaaaa", "aa", "XY", "XY" },
			{ "aaaaaa", "aaaaaa", "XY", "XY" },
			{ "aaaaaa", "aaaaaaa", "XY", "aaaaaa" },
			{ "aabaaabaab", "aaa", "XY", "aabXYbaab" },
			{ "aabaaabaab", "aa", "XY", "XYbXYabXYb" },
			{ "aabaaabaa", "aa", "XY", "XYbXYabXY" }
		};
		int len = sizeof(A) / sizeof(A[0]);
		for (int i = 0; i < len; i++) {
			check(A[i][0], A[i][1], A[i][2], A[i][3]);
		}
	});

	Add("RemoveExtraSpaces", [&]() {
		auto check = [&](char * input, char * expect) {
			Logger().WriteInformation("\"%s\"", input);
			RemoveExtraSpaces(input);
			Logger().WriteInformation("\t=>\t\"%s\"\n", input);
			ASSERT1(0 == strcmp(input, expect));
		};
		{
			char a[] = "";
			char b[] = "";
			check(a, b);
		}
		{
			char a[] = "   ";
			char b[] = "";
			check(a, b);
		}
		{
			char a[] = "ABCDEFG";
			char b[] = "ABCDEFG";
			check(a, b);
		}
		{
			char a[] = "A B C D E F G";
			char b[] = "A B C D E F G";
			check(a, b);
		}
		{
			char a[] = "AB CD EFG";
			char b[] = "AB CD EFG";
			check(a, b);
		}
		{
			char a[] = "AB   CD  EFG";
			char b[] = "AB CD EFG";
			check(a, b);
		}
		{
			char a[] = "ABCD     EFG";
			char b[] = "ABCD EFG";
			check(a, b);
		}
		{
			char a[] = " ABCDEFG ";
			char b[] = "ABCDEFG";
			check(a, b);
		}
		{
			char a[] = "    ABCDEFG    ";
			char b[] = "ABCDEFG";
			check(a, b);
		}
		{
			char a[] = "    A B C D E F G    ";
			char b[] = "A B C D E F G";
			check(a, b);
		}
		{
			char a[] = "    A B  C   D    E   F  G    ";
			char b[] = "A B C D E F G";
			check(a, b);
		}
		{
			char a[] = "    AB CD EF G    ";
			char b[] = "AB CD EF G";
			check(a, b);
		}
		{
			char a[] = "    AB CD  EF   GHI  JK L    ";
			char b[] = "AB CD EF GHI JK L";
			check(a, b);
		}
	});

	Add("ReverseWords", [&]() {
		auto check = [&](const char * input, const string & expect) {
			Logger().WriteInformation("\nInput:  %s\n", input);
			string input1(input);
			size_t len = strlen(input);
			unique_ptr<char[]> input2(new char[len + 1]);
			strcpy_s(input2.get(), len + 1, input);
			ReverseWords(input1);
			ReverseWords(input2.get());
			Logger().WriteInformation("Output: %s\n", input1.c_str());
			Logger().WriteInformation("Output: %s\n", input2.get());
			string input3(input2.get());
			ASSERT1(input1 == expect);
			ASSERT1(input3 == expect);
		};
		check("a", "a");
		check("", "");
		check(" ", "");
		check("  ", "");
		check("ab", "ab");
		check("a b", "b a");
		check("a  b", "b a");
		check(" a b ", "b a");
		check("  a  b  ", "b a");
		check("  ab  cd  ", "cd ab");
		check("   This is a test!   ", "test! a is This");
	});

	Add("StrStr", [&]() {
		auto check = [&](char * input1, char * input2, int index) {
			Logger().WriteInformation("\nInput1:\t%s\n", input1);
			Logger().WriteInformation("Input2:\t%s\n", input2);
			const char * p1 = StrStr1(input1, input2);
			int i1 = (int)(p1 == nullptr ? -1 : p1 - input1);
			const char * p2 = StrStr2(input1, input2);
			int i2 = (int)(p2 == nullptr ? -1 : p2 - input1);
			const char * p3 = strstr(input1, input2);
			int i3 = (int)(p3 == nullptr ? -1 : p3 - input1);
			Logger().WriteInformation("Index:\t%d\t%d\t%d\n", i1, i2, i3);
			ASSERT1(i1 == index);
			ASSERT1(i2 == index);
			ASSERT1(i3 == index);
		};
		check("", "", 0);
		check("", "a", -1);
		check("a", "", 0);
		check("a", "a", 0);
		check("a", "b", -1);
		check("a", "aa", -1);
		check("aa", "a", 0);
		check("aa", "b", -1);
		check("aa", "aa", 0);
		check("aa", "aaa", -1);
		check("ab", "a", 0);
		check("ab", "b", 1);
		check("ab", "c", -1);
		check("ab", "ab", 0);
		check("abc", "a", 0);
		check("abc", "b", 1);
		check("abc", "c", 2);
		check("abc", "d", -1);
		check("abc", "ab", 0);
		check("abc", "bc", 1);
		check("abc", "abc", 0);
		check("ababa", "ab", 0);
		check("ababa", "ba", 1);
		check("ababa", "aba", 0);
		check("ababa", "bab", 1);
		check("ababa", "ababa", 0);
		check("abcabcab", "abc", 0);
		check("abcabcab", "bca", 1);
		check("abcabcab", "cab", 2);
		check("abdabcab", "abc", 3);
		check("abdabcab", "bca", 4);
		check("abdabcab", "cab", 5);
	});

	Add("BreakWord", [&]() {
		function<void(Log &, const string &)>
		print = [&](Log & l, const string & s) {
			l.WriteInformation("%s", s.c_str());
		};

		auto check = [&](string s, unordered_set<string> & dict) {
			Logger().WriteInformation("Input: %s\n", s.c_str());
			Logger().WriteInformation("Dictionary: ");
			Logger().Print(dict, print, " ");
			bool breakable = BreakWords::Solvable(s, dict);
			if (breakable) Logger().WriteInformation("breakable\n");
			else Logger().WriteInformation("unbreakable\n");
			vector<string> sentences1 = BreakWords::Solve1(s, dict);
			vector<string> sentences2 = BreakWords::Solve2(s, dict);
			Logger().WriteInformation("Output1:\n");
			Logger().Print(sentences1, print, "\n");
			Logger().WriteInformation("Output2:\n");
			Logger().Print(sentences2, print, "\n");
			ASSERT1(sentences1.size() == sentences2.size());
			sort(sentences1.begin(), sentences1.end());
			sort(sentences2.begin(), sentences2.end());
			for (size_t i = 0; i < sentences1.size(); i++) {
				ASSERT1(sentences1[i] == sentences2[i]);
			}
		};
		{
			string s = "catsanddog";
			unordered_set<string> dict = { "cat", "cats", "and", "sand", "dog" };
			check(s, dict);
		}
		{
			string s;
			unordered_set<string> dict = { "cat", "cats", "and", "sand", "dog" };
			check(s, dict);
		}
		{
			string s = "aaaaaaa";
			unordered_set<string> dict = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa" };
			check(s, dict);
		}
		{
			string s = "dogs";
			unordered_set<string> dict = { "dog", "s", "gs" };
			check(s, dict);
		}
	});

}