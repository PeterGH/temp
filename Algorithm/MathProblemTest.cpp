#include "Header.h"

void MathProblemTest::Init(void)
{
	Add("AddBits", [&]() {
		auto toArray = [&](int n, size_t l, int * a) {
			for (size_t i = 0; i < l; i++) {
				a[i] = n & 0x1;
				n = n >> 1;
			}
		};
		auto toNum = [&](int * a, size_t l)->int {
			int n = 0;
			for (size_t i = 0; i < l; i++) {
				if (a[i] == 1) n = n + (0x1 << i);
			}
			return n;
		};
		auto check = [&](int n0, int n1, int e) {
			size_t l0 = Math::CountBits(n0);
			unique_ptr<int[]> b0(new int[l0]);
			toArray(n0, l0, b0.get());
			size_t l1 = Math::CountBits(n1);
			unique_ptr<int[]> b1(new int[l1]);
			toArray(n1, l1, b1.get());
			size_t l2 = 1 + max(l0, l1);
			unique_ptr<int[]> b2(new int[l2]);
			MathProblem::Add::Bits(b0.get(), l0, b1.get(), l1, b2.get());
			int a = toNum(b2.get(), l2);
			Logger().WriteInformation("%d + %d = %d\n", n0, n1, a);
			ASSERT1(a == e);
		};
		check(2, 1, 3);
		check(3, 1, 4);
		check(3, 2, 5);
		for (int i = 0; i < 10; i++) {
			int n0 = 1 + rand();
			int n1 = 1 + rand();
			check(n0, n1, n0 + n1);
		}
	});

	Add("Excel", [&]() {
		auto check = [&](const string & input, unsigned long long expect) {
			Logger().WriteInformation("%s = ", input.c_str());
			unsigned long long r = MathProblem::Excel::Decode(input);
			string e = MathProblem::Excel::Encode(r);
			Logger().WriteInformation("%llu = %s\n", r, e.c_str());
			ASSERT1(r == expect);
			ASSERT1(e == input);
		};
		check("A", 0);
		check("B", 1);
		check("C", 2);
		check("X", 23);
		check("Y", 24);
		check("Z", 25);
		check("AA", 26);
		check("AB", 27);
		check("AY", 50);
		check("AZ", 51);
		check("BA", 52);
		check("BB", 53);
		check("BZ", 77);
		check("CA", 78);
		check("ZA", 676);
		check("ZY", 700);
		check("ZZ", 701);
		check("AAA", 702);
		check("AAB", 703);
		check("AAZ", 727);
		for (unsigned long long i = 0; i < 1000; i++) {
			string code = MathProblem::Excel::Encode(i);
			unsigned long long decode = MathProblem::Excel::Decode(code);
			Logger().WriteInformation("%llu, %s, %llu\n", i, code.c_str(), decode);
			ASSERT1(decode == i);
		}
		for (unsigned int i = 0; i < 1000; i++) {
			unsigned long long n = rand();
			string code = MathProblem::Excel::Encode(n);
			unsigned long long decode = MathProblem::Excel::Decode(code);
			Logger().WriteInformation("%llu, %s, %llu\n", n, code.c_str(), decode);
			ASSERT1(decode == n);
		}
	});

	Add("ExclusiveMultiplication", [&]() {
		auto check = [&](int * input, int length, long long * output, long long * expect) {
			MathProblem::ExclusiveMultiplication(input, length, output);
			Logger().WriteInformation("Input:  ");
			Logger().Print<int>(input, length, "%4d", " ");
			Logger().WriteInformation("Output: ");
			Logger().Print<long long>(output, length, "%4ld", " ");
			for (int i = 0; i < length; i++) {
				ASSERT1(output[i] == expect[i]);
			}
		};
		{
			int A[] = { 4, 3, 2, 1, 2 };
			long long B[5];
			long long C[] = { 12, 16, 24, 48, 24 };
			check(A, 5, B, C);
		}
		{
			int A[] = { 4, 3, 2, 1, 2, 3 };
			long long B[6];
			long long C[] = { 36, 48, 72, 144, 72, 48 };
			check(A, 6, B, C);
		}
	});

	Add("ReversePolishNotation", [&]() {
		auto check = [&](vector<string> & tokens, int expect) {
			Logger().WriteInformation("Expression:");
			for_each(tokens.begin(), tokens.end(), [&](string & t) {
				Logger().WriteInformation(" %s", t.c_str());
			});
			Logger().WriteInformation("\n");
			int r = MathProblem::EvalReversePolishNotation(tokens);
			Logger().WriteInformation("Result:     %d\n", r);
			ASSERT1(r == expect);
		};
		vector<string> t = { "2", "1", "+", "3", "*" };
		check(t, 9);
		t = { "4", "13", "5", "/", "+" };
		check(t, 6);
		t = { "-1", "-22", "+" };
		check(t, -23);
		t = { "1", "-22", "-" };
		check(t, 23);
		t = { "-2", "-3", "*" };
		check(t, 6);
		t = { "-22", "-2", "/" };
		check(t, 11);
	});

	Add("SingleNumber", [&]() {
		auto check = [&](int input[], int length, int expect) {
			int r1 = MathProblem::SingleNumber::FindOutOfThree(input, length);
			int r2 = MathProblem::SingleNumber::FindOutOfThree(input, length);
			int r3 = MathProblem::SingleNumber::FindOutOfThree(input, length);
			int r4 = MathProblem::SingleNumber::FindLOutOfK(input, length, 3, 1);
			int r5 = MathProblem::SingleNumber::FindLOutOfK2(input, length, 3, 1);
			Logger().WriteInformation("Single number: %d, %d, %d, %d, %d\n", r1, r2, r3, r4, r5);
			ASSERT1(r1 == expect);
			ASSERT1(r2 == expect);
			ASSERT1(r3 == expect);
			ASSERT1(r4 == expect);
			ASSERT1(r5 == expect);
		};
		{
			int A[] = { 0, 1, 0, 0 };
			check(A, 4, 1);
		}
		{
			int a = 0xFFFFFFFF;
			int A[] = { a, 3, a, a };
			check(A, 4, 3);
		}
		{
			int A[] = { 1, 2, 3, 1, 2, 3, 4, 1, 2, 3 };
			check(A, 10, 4);
		}
		{
			int A[] = { 0, 1, 0, 1, 0, 1, 99 };
			check(A, 7, 99);
		}
		{
			for (int j = 0; j < 100; j++) {
				int k = 2 + rand() % 10;
				int l = 1 + rand() % (k - 1);
				vector<int> n;
				int c;
				for (int i = 0; i < 10; i++) {
					c = 1 + rand() % INT_MAX;
					n.insert(n.end(), k, c);
				}
				c = 1 + rand() % INT_MAX;
				n.insert(n.end(), l, c);
				random_shuffle(n.begin(), n.end());
				Logger().Print(n);
				unique_ptr<int[]> input(new int[n.size()]);
				Array::ToArray(n, input.get());
				int r = MathProblem::SingleNumber::FindLOutOfK(input.get(), n.size(), k, l);
				int r2 = MathProblem::SingleNumber::FindLOutOfK2(input.get(), n.size(), k, l);
				Logger().WriteInformation("Run %d: Single (%d, %d out of %d): %d, %d\n", j, c, l, k, r, r2);
				ASSERT1(r == c);
				ASSERT1(r2 == c);
			}
		}
	});

	Add("CountInversions", [&]() {
		auto check = [&](int * A, int L, int expected) -> void {
			int count = MathProblem::CountInversions<int>(A, L);
			ASSERT1(expected == count);
		};

		int I1[] = { 0 };
		check(I1, 1, 0);

		int I2[] = { 0, 1 };
		check(I2, 2, 0);

		int I3[] = { 1, 0 };
		check(I3, 2, 1);

		int I4[] = { 0, 1, 2 };
		check(I4, 3, 0);

		int I5[] = { 1, 0, 2 };
		check(I5, 3, 1);

		int I6[] = { 2, 0, 1 };
		check(I6, 3, 2);

		int I7[] = { 2, 1, 0 };
		check(I7, 3, 3);

		int I8[] = { 0, 2, 1 };
		check(I8, 3, 1);

		int I9[] = { 1, 2, 0 };
		check(I9, 3, 2);

		int I10[] = { 3, 2, 1, 0 };
		check(I10, 4, 6);

		int I11[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		int L = sizeof(I11) / sizeof(I11[0]);
		check(I11, L, 45);
	});

	Add("Range", [&]() {
		auto check = [&](double b1, double e1, double b2, double e2, bool o) {
			MathProblem::OverLap::Range r1 = make_pair(b1, e1);
			MathProblem::OverLap::Range r2 = make_pair(b2, e2);
			bool r = MathProblem::OverLap::IsOverlap(r1, r2);
			Logger().WriteInformation("(%.2f, %.2f) and (%.2f, %.2f) %s overlap\n", b1, e1, b2, e2, r ? "" : "not");
			ASSERT1(r == o);
		};

		check(0.0, 1.0, 2.0, 3.0, false);
		check(0.0, 2.0, 1.5, 3.0, true);
		check(0.0, 4.0, 2.0, 3.0, true);
	});

	Add("Rectangle", [&]() {
		auto check = [&](
			double b1, double e1, double b2, double e2,
			double b3, double e3, double b4, double e4,
			bool o) {
			MathProblem::OverLap::Rectangle r1 = make_pair(make_pair(b1, e1), make_pair(b2, e2));
			MathProblem::OverLap::Rectangle r2 = make_pair(make_pair(b3, e3), make_pair(b4, e4));
			bool r = MathProblem::OverLap::IsOverlap(r1, r2);
			Logger().WriteInformation(
				"((%.2f, %.2f), (%.2f, %.2f)) and ((%.2f, %.2f), (%.2f, %.2f)) %s overlap\n",
				b1, e1, b2, e2, b3, e3, b4, e4, r ? "" : "not");
			ASSERT1(r == o);
		};

		check(0, 6, 2, 5, 3, 4, 5, 3, false);
		check(1, 6, 3, 5, 3, 4, 5, 3, false);
		check(2, 6, 4, 5, 3, 4, 5, 3, false);
		check(3, 6, 5, 5, 3, 4, 5, 3, false);
		check(4, 6, 6, 5, 3, 4, 5, 3, false);
		check(5, 6, 7, 5, 3, 4, 5, 3, false);
		check(6, 6, 8, 5, 3, 4, 5, 3, false);

		check(0, 4.5, 2, 3.5, 3, 4, 5, 3, false);
		check(1, 4.5, 3, 3.5, 3, 4, 5, 3, false);
		check(2, 4.5, 4, 3.5, 3, 4, 5, 3, true);
		check(3, 4.5, 5, 3.5, 3, 4, 5, 3, true);
		check(4, 4.5, 6, 3.5, 3, 4, 5, 3, true);
		check(5, 4.5, 7, 3.5, 3, 4, 5, 3, false);
		check(6, 4.5, 8, 3.5, 3, 4, 5, 3, false);

		check(0, 4, 2, 3, 3, 4, 5, 3, false);
		check(1, 4, 3, 3, 3, 4, 5, 3, false);
		check(2, 4, 4, 3, 3, 4, 5, 3, true);
		check(3, 4, 5, 3, 3, 4, 5, 3, true);
		check(4, 4, 6, 3, 3, 4, 5, 3, true);
		check(5, 4, 7, 3, 3, 4, 5, 3, false);
		check(6, 4, 8, 3, 3, 4, 5, 3, false);

		check(0, 3.5, 2, 2.5, 3, 4, 5, 3, false);
		check(1, 3.5, 3, 2.5, 3, 4, 5, 3, false);
		check(2, 3.5, 4, 2.5, 3, 4, 5, 3, true);
		check(3, 3.5, 5, 2.5, 3, 4, 5, 3, true);
		check(4, 3.5, 6, 2.5, 3, 4, 5, 3, true);
		check(5, 3.5, 7, 2.5, 3, 4, 5, 3, false);
		check(6, 3.5, 8, 2.5, 3, 4, 5, 3, false);

		check(0, 2, 2, 1, 3, 4, 5, 3, false);
		check(1, 2, 3, 1, 3, 4, 5, 3, false);
		check(2, 2, 4, 1, 3, 4, 5, 3, false);
		check(3, 2, 5, 1, 3, 4, 5, 3, false);
		check(4, 2, 6, 1, 3, 4, 5, 3, false);
		check(5, 2, 7, 1, 3, 4, 5, 3, false);
		check(6, 2, 8, 1, 3, 4, 5, 3, false);
	});

	Add("IntPoint", [&]() {
		vector<MathProblem::PointsOnALine::IntPoint> points = {
			MathProblem::PointsOnALine::IntPoint{ 3, 1 },
			MathProblem::PointsOnALine::IntPoint{ 3, 1 },
			MathProblem::PointsOnALine::IntPoint{ 0, 2 },
			MathProblem::PointsOnALine::IntPoint{ 0, 1 },
			MathProblem::PointsOnALine::IntPoint{ -1, 0 },
			MathProblem::PointsOnALine::IntPoint{ 0, 0 }
		};
		sort(points.begin(), points.end());
		for_each(points.begin(), points.end(), [&](MathProblem::PointsOnALine::IntPoint & p) {
			Logger().WriteInformation("  (%d, %d)", p.x, p.y);
		});
		Logger().WriteInformation("\n");
		MathProblem::PointsOnALine::IntPoint p0(-1, 0);
		ASSERT1(points[0] == p0);
		MathProblem::PointsOnALine::IntPoint p1(0, 0);
		ASSERT1(points[1] == p1);
		MathProblem::PointsOnALine::IntPoint p2(0, 1);
		ASSERT1(points[2] == p2);
		MathProblem::PointsOnALine::IntPoint p3(0, 2);
		ASSERT1(points[3] == p3);
		MathProblem::PointsOnALine::IntPoint p4(3, 1);
		ASSERT1(points[4] == p4);
		MathProblem::PointsOnALine::IntPoint p5(3, 1);
		ASSERT1(points[5] == p5);
	});

	Add("MaxPointsOnLine", [&]() {
		auto check = [&](vector<MathProblem::PointsOnALine::IntPoint> & points, int expect) {
			Logger().WriteInformation("Input %d points:\n", points.size());
			for_each(points.begin(), points.end(), [&](const MathProblem::PointsOnALine::IntPoint & p) {
				Logger().WriteInformation("  (%d, %d)", p.x, p.y);
			});
			Logger().WriteInformation("\n");
			set<MathProblem::PointsOnALine::IntPoint> output;
			int count = MathProblem::PointsOnALine::MaxPointsOnALine(points, output);
			Logger().WriteInformation("Max points on a line: %d\n", count);
			for_each(output.begin(), output.end(), [&](const MathProblem::PointsOnALine::IntPoint & p) {
				Logger().WriteInformation("  (%d, %d)", p.x, p.y);
			});
			Logger().WriteInformation("\n");
			ASSERT1(count == expect);
		};
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 1, 1 }
			};
			check(points, 1);
		}
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 1, 1 },
				MathProblem::PointsOnALine::IntPoint{ 1, 2 }
			};
			check(points, 2);
		}
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 1, 1 },
				MathProblem::PointsOnALine::IntPoint{ 2, 1 }
			};
			check(points, 2);
		}
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 2, 3 },
				MathProblem::PointsOnALine::IntPoint{ 4, 5 }
			};
			check(points, 2);
		}
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 1, 2 },
				MathProblem::PointsOnALine::IntPoint{ 2, 2 },
				MathProblem::PointsOnALine::IntPoint{ 1, 1 },
				MathProblem::PointsOnALine::IntPoint{ 2, 1 }
			};
			check(points, 2);
		}
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 1, 2 },
				MathProblem::PointsOnALine::IntPoint{ 2, 2 },
				MathProblem::PointsOnALine::IntPoint{ 1, 1 },
				MathProblem::PointsOnALine::IntPoint{ 2, 1 },
				MathProblem::PointsOnALine::IntPoint{ 3, 1 }
			};
			check(points, 3);
		}
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 2, 3 },
				MathProblem::PointsOnALine::IntPoint{ 1, 2 },
				MathProblem::PointsOnALine::IntPoint{ 2, 2 },
				MathProblem::PointsOnALine::IntPoint{ 1, 1 },
				MathProblem::PointsOnALine::IntPoint{ 2, 1 }
			};
			check(points, 3);
		}
		{
			vector<MathProblem::PointsOnALine::IntPoint> points = {
				MathProblem::PointsOnALine::IntPoint{ 1, 4 },
				MathProblem::PointsOnALine::IntPoint{ 1, 3 },
				MathProblem::PointsOnALine::IntPoint{ 2, 3 },
				MathProblem::PointsOnALine::IntPoint{ 1, 2 },
				MathProblem::PointsOnALine::IntPoint{ 2, 2 },
				MathProblem::PointsOnALine::IntPoint{ 3, 2 },
				MathProblem::PointsOnALine::IntPoint{ 2, 1 },
				MathProblem::PointsOnALine::IntPoint{ 3, 1 },
				MathProblem::PointsOnALine::IntPoint{ 4, 1 }
			};
			check(points, 4);
		}
	});
}