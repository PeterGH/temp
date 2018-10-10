#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <stack>
#include <string.h>
#include <vector>
#include "Math.h"

using namespace std;

namespace Test {

	class MathProblem {
	public:
		class Add {
		public:
			// Add two bit arrays, n2 = n0 + n1. Assume bit-0 is the LSB.
			__declspec(dllexport) static void Bits(const int * n0, size_t l0, const int * n1, size_t l1, int * n2)
			{
				if (n0 == nullptr || n1 == nullptr) return;
				if (l0 == 0 || l1 == 0) return;
				if (n2 == nullptr) return;
				if (l0 > l1) { // adjust so that n0 is shorter than n1
					swap(n0, n1);
					swap(l0, l1);
				}
				memset(n2, 0, (l1 + 1) * sizeof(int));
				memcpy(n2, n0, l0 * sizeof(int));
				int c = 0;
				size_t i = 0;
				for (i = 0; i < l1; i++) {
					int s = n2[i] + n1[i] + c;
					switch (s) {
					case 0:
					case 1:
						n2[i] = s;
						c = 0;
						break;
					case 2:
					case 3:
						n2[i] = s & 0x1;
						c = 1;
						break;
					default:
						break;
					}
				}
				if (c == 1) n2[i] = 1;
			}
		};

		class Excel {
		public:
			// Convert Excel column number to integer:
			//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
			//     0, 1, ..., 25, 26, 27, ..., 51, 52, 53, ..., 701, 702, 703, ...
			// If we encode [A-Z] to [1 - 26], then
			//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
			//     1, 2, ..., 26, 27, 28, ..., 52, 53, 54, ..., 702, 703, 704, ...
			// The output is merely one less.
			// input  I[0..n-1]
			// output I[0] * 26^(n-1) + I[1] * 26^(n-2) + ... + I[i] * 26^(n-1-i) + ... + I[n-2] * 26^1 + I[n-1]
			__declspec(dllexport) static unsigned long long Decode(const string & input)
			{
				unsigned long long s = 0;
				for (unsigned int i = 0; i < input.length(); i++) {
					s = s * 26 + (input[i] - 'A' + 1);
				}
				return s - 1;
			}

			// Convert integer tp Excel column number:
			//     0, 1, ..., 25, 26, 27, ..., 51, 52, 53, ..., 701, 702, 703, ...
			//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
			// If we encode [A-Z] to [1 - 26], then
			//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
			//     1, 2, ..., 26, 27, 28, ..., 52, 53, 54, ..., 702, 703, 704, ...
			__declspec(dllexport) static string Encode(unsigned long long input)
			{
				string code;
				unsigned int r;
				input++;
				while (input > 0) {
					r = input % 26;
					input /= 26;
					if (r == 0) {
						// make sure r is in [1, 26]
						// so if r = 0, then borrow one from next higher position
						input--;
						r = 26;
					}
					code.insert(0, 1, r - 1 + 'A');
				}
				return code;
			}
		};

		// http://leetcode.com/2010/04/multiplication-of-numbers.html
		// There is an array A[N] of N numbers. You have to compose an array Output[N] such that Output[i]
		// will be equal to multiplication of all the elements of A[N] except A[i]. Solve it without division operator and in O(n).
		// For example Output[0] will be multiplication of A[1] to A[N-1]
		// and Output[1] will be multiplication of A[0] and from A[2] to A[N-1].
		// Example:
		// A: {4, 3, 2, 1, 2}
		// OUTPUT: {12, 16, 24, 48, 24}
		// Let M[i..j] = I[i] * I[i+1] * ... * I[j]
		// I[i]  I[0]      I[1]      I[2]      ...... I[i]        ...... I[n-1]
		// L[i]  1         M[0..0]   M[0..1]   ...... M[0..i-1]   ...... M[0..n-2]
		// R[i]  M[1..n-1] M[2..n-1] M[3..n-1] ...... M[i+1..n-1] ...... 1
		// O[i] = L[i] * R[i]
		__declspec(dllexport) static void ExclusiveMultiplication(const int * input, int length, long long * output)
		{
			for (int i = 0; i < length; i++) output[i] = 1;
			long long left = 1;
			long long right = 1;
			for (int i = 0; i < length; i++) {
				// At loop i, output[i] = left = multiplication of input[0..i-1]
				// At loop length - 1 - i, output[i] *= right = multiplication of input[i+1..length-1]
				output[i] *= left;
				output[length - 1 - i] *= right;
				left *= input[i];
				right *= input[length - 1 - i];
			}
		}

		// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
		__declspec(dllexport) static int EvalReversePolishNotation(vector<string> & tokens)
		{
			if (tokens.size() == 0) throw invalid_argument("No token is provided");
			stack<int> args;
			int first;
			int second;
			int s;
			for_each(tokens.begin(), tokens.end(), [&](string & t) {
				if (t != "+" && t != "-" && t != "*" && t != "/") {
					if (t.length() == 0) throw invalid_argument("Token is empty");
					s = (int)Math::ToInteger(t);
					args.push(s);
				} else {
					if (args.empty()) throw invalid_argument("Not enough tokens");
					second = args.top();
					args.pop();
					if (args.empty()) throw invalid_argument("Not enough tokens");
					first = args.top();
					args.pop();
					if (t == "+") s = first + second;
					else if (t == "-") s = first - second;
					else if (t == "*") s = first * second;
					else if (t == "/") {
						if (second == 0) throw runtime_error("Divided by zero");
						s = first / second;
					}
					args.push(s);
				}
			});
			return args.top();
		}

		class SingleNumber {
		public:
			// An array contain numbers duplicated by three times, except one single number.
			// Find the single number.
			// Count number of bit 1 per position and modulo 3.
			__declspec(dllexport) static int FindOutOfThree(int input[], int length)
			{
				if (length % 3 != 1) throw invalid_argument("The count of numbers is not 3n+1");
				int n = 0;
				int bits = 8 * sizeof(int);
				for (int i = 0; i < bits; i++) {
					int count = 0;
					for (int j = 0; j < length; j++) count += ((input[j] >> i) & 0x1);
					n |= ((count % 3) << i);
				}
				return n;
			}

			__declspec(dllexport) static int FindOutOfThree2(int input[], int length)
			{
				if (length % 3 != 1) throw invalid_argument("The count of numbers is not 3n+1");
				int o0 = ~0; // positions that bit 1 occurred 0 or 3 times
				int o1 = 0;  // positions that bit 1 occurred 1 time
				int o2 = 0;  // positions that bit 1 occurred 2 times
				int t = 0;
				for (int i = 0; i < length; i++) {
					t = o2; // keep o2 temporarily to calculate o0 later
					o2 = (o1 & input[i]) | (o2 & ~input[i]); // Update the positions that bit 1 occurred the second time due to input[i], and
															 // keep the positions that bit 1 already occurred two times and not affected by input[i]
					o1 = (o0 & input[i]) | (o1 & ~input[i]); // Update the positions that bit 1 occurred the first time due to input[i], and
															 // keep the positions that bit 1 already occurred one time and not affected by input[i]
					o0 = (t & input[i]) | (o0 & ~input[i]);  // Update the positions that bit 1 occurred the third time due to input[i], and
															 // keep the positions that bit 1 already occurred zero or three times and not affected by input[i]
				}
				return o1;
			}

			__declspec(dllexport) static int FindOutOfThree3(int input[], int length)
			{
				if (length % 3 != 1) throw invalid_argument("The count of numbers is not 3n+1");
				int o1 = 0; // positions that bit 1 occurred 0 or 3 times
				int o2 = 0; // positions that bit 1 occurred 1 time
				int o3 = 0; // positions that bit 1 occurred 2 times
				for (int i = 0; i < length; i++) {
					o2 |= o1 & input[i];
					o1 ^= input[i];
					o3 = o1 & o2;
					o1 &= ~o3;
					o2 &= ~o3;
				}
				return o1;
			}

			// An array contain numbers duplicated by k times, except
			// one single number occurring l times.
			// Find the single number.
			_declspec(dllexport) static int FindLOutOfK(int input[], int length, int k, int l)
			{
				if (length % k != l) throw invalid_argument("The count of numbers is not kn+l");
				int bits = 8 * sizeof(int);
				int r = 0;
				for (int i = 0; i < bits; i++) {
					int c = 0;
					for (int j = 0; j < length; j++) c += ((input[j] >> i) & 0x1);
					c %= k;
					if (c > 0) r |= (0x1 << i);
				}
				return r;
			}

			_declspec(dllexport) static int FindLOutOfK2(int input[], int length, int k, int l)
			{
				if (length % k != l) throw invalid_argument("The count of numbers is not kn+l");
				unique_ptr<int[]> o(new int[k]);
				memset(o.get(), 0, k * sizeof(int));
				o[0] = ~0;
				for (int i = 0; i < length; i++) {
					int t = o[k - 1];
					for (int j = k - 1; j > 0; j--)
						o[j] = (o[j - 1] & input[i]) | (o[j] & ~input[i]);
					o[0] = (t & input[i]) | (o[0] & ~input[i]);
				}
				return o[l];
			}
		};

		template<class T> static int CountInversions(T * input, size_t length)
		{
			if (input == nullptr || length <= 1) return 0;

			// Count inversions between a[h..(m-1)] and a[m..t], assuming both subarrays are sorted
			function<int(T *, int, int, int)>
			merge = [&](T * a, int h, int m, int t)->int {
				int c = 0;
				// head and middle point to the heads of two sub sorted arrays.
				while (h < m && m <= t) {
					if (a[h] <= a[m]) {
						h++;
					} else {
						T x = a[m];
						for (int i = m; i > (int)h; i--) {
							a[i] = a[i - 1];
						}
						a[h] = x;
						// There (m - h) elements moved.
						// Each of them paired with a[m] is an inversion.
						c += (m - h);
						// Move to the next pair of elements
						h++;
						m++;
					}
				}
				return c;
			};

			function<int(T *, int, int)> count = [&](T * a, int h, int t)->int {
				if (a == nullptr || h >= t) return 0;
				int c = 0;
				if (h < t) {
					int m = h + ((t - h) >> 1) + 1;
					c += count(a, h, m - 1);
					c += count(a, m, t);
					c += merge(a, h, m, t);
				}
				return c;
			};

			return count(input, 0, length - 1);
		}

		class OverLap {
		public:
			// [pair.first, pair.second]
			typedef pair<double, double> Range;

			__declspec(dllexport) static bool IsOverlap(const Range & r1, const Range & r2)
			{
				// Non-overlap r1.second <= r2.first || r2.second <= r1.first;
				return r1.first < r2.second && r2.first < r1.second;
			}

			// (Point.x, Point.y) = (pair.first, pair.second)
			typedef pair<double, double> Point;

			// The sides of Rectangle are in parallel with x-axis or y-axis
			// Top-Left Point = pair.first
			// Bottom-Right Point = pair.second
			typedef pair<Point, Point> Rectangle;

			__declspec(dllexport) static bool IsOverlap(const Rectangle & r1, const Rectangle & r2)
			{
				// r1 and r2 overlaps if their projections onto x-axis and y-axis overlap
				// [r1.first.first, r1.second.first] and [r2.first.first, r2.second.first] overlaps.
				// [r1.second.second, r1.first.second] and [r2.second.second, r2.first.second] overlaps.
				return r1.first.first < r2.second.first && r2.first.first < r1.second.first
					&& r1.second.second < r2.first.second && r2.second.second < r1.first.second;
			}
		};

		class PointsOnALine {
		public:
			struct IntPoint {
				int x;
				int y;
				IntPoint() : x(0), y(0) {}
				IntPoint(int a, int b) : x(a), y(b) {}
				bool operator== (const IntPoint & other) const
				{
					return x == other.x && y == other.y;
				}
				bool operator< (const IntPoint & other) const
				{
					if (x == other.x) return y < other.y;
					return x < other.x;
				}
			};

			// slope = (p1.y - p0.y) / (p1.x - p0.x)
			// Reduce the slope so that the numerator and denominator are co-prime
			// Return a pair <deltaX, deltaY> after reduction
			__declspec(dllexport) static pair<int, int> NomalizeSlope(const IntPoint & p0, const IntPoint & p1)
			{
				int dX = p1.x - p0.x;
				int dY = p1.y - p0.y;
				int gcd = Math::GreatestCommonDivisor(dX, dY);
				dX = dX / gcd;
				dY = dY / gcd;
				return make_pair(dX, dY);
			}

			// Find a line containing maximum number of points
			__declspec(dllexport) static int MaxPointsOnALine(vector<IntPoint> & points, set<IntPoint> & output)
			{
				if (points.size() <= 1) {
					output.clear();
					output.insert(points.begin(), points.end());
					return points.size();
				}

				// Group pairs of points by slopes. The points with the same slope
				// are potentially on the same lines.

				// Use comparer of IntPoint
				sort(points.begin(), points.end());
				map<pair<int, int>, vector<pair<IntPoint, IntPoint>>> slopes;
				for (size_t i = 0; i < points.size() - 1; i++) {
					for (size_t j = i + 1; j < points.size(); j++) {
						if (points[i] == points[j]) {
							// Ignore duplication
							continue;
						}

						pair<int, int> slope = NomalizeSlope(points[i], points[j]);

						// Treat vertical line specially
						if (slope.first == 0) slope.second = 1;
						// Treat horizontal line specially
						if (slope.second == 0) slope.first = 1;

						if (slopes.find(slope) == slopes.end()) {
							slopes[slope] = vector<pair<IntPoint, IntPoint>>{};
						}

						slopes[slope].push_back(make_pair(points[i], points[j]));
					}
				}

				size_t max = 0;

				for (map<pair<int, int>, vector<pair<IntPoint, IntPoint>>>::iterator slope = slopes.begin(); slope != slopes.end(); slope++) {
					// lines of the same slope
					vector<set<IntPoint>> lines;
					for_each(slope->second.begin(), slope->second.end(), [&](pair<IntPoint, IntPoint> & s) {
						// s is a line segament ending with two points.
						// Check and assign the points into the set of points on the same line.

						// first is the line containing the first point of segament s
						vector<set<IntPoint>>::iterator & first = lines.end();
						// second is the line containing the second point of segament s
						vector<set<IntPoint>>::iterator & second = lines.end();

						for (vector<set<IntPoint>>::iterator it = lines.begin(); it != lines.end(); it++) {
							// it refers to the set of points on the same line
							if (it->find(s.first) != it->end()) {
								first = it;
							}
							if (it->find(s.second) != it->end()) {
								second = it;
							}
						}

						if (first == lines.end() && second == lines.end()) {
							// Segament s is a new line
							set<IntPoint> line;
							line.insert(s.first);
							line.insert(s.second);
							lines.push_back(line);
						} else if (first == lines.end()) {
							second->insert(s.first);
						} else if (second == lines.end()) {
							first->insert(s.second);
						}
						else if (first == second) {
							;
						} else {
							set<IntPoint> line;
							line.insert(first->begin(), first->end());
							line.insert(second->begin(), second->end());
							lines.erase(first);
							lines.erase(second);
							lines.push_back(line);
						}
					});

					for_each(lines.begin(), lines.end(), [&](set<IntPoint> & l) {
						if (l.size() > max) {
							max = l.size();
							output.clear();
							output.insert(l.begin(), l.end());
						}
					});
				}

				return max;
			}
		};
	};
}