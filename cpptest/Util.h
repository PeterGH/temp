#pragma once

#include <vector>

using namespace std;

namespace Test {

    class Util
    {
    public:
        static int RandomInt(int max = RAND_MAX, int min = 0)
        {
            return min + (rand() % (max - min + 1));
        }

        static vector<int> RandomVector(size_t n, int max = RAND_MAX, int min = 0)
        {
            vector<int> result(n);
            std::generate(result.begin(), result.end(), [&]() { return RandomInt(max, min); });
            return result;
        }

        static vector<vector<int>> RandomMatrix(size_t m, size_t n, int max = RAND_MAX, int min = 0)
        {
            vector<vector<int>> result(m, vector<int>(n));
            for (size_t i = 0; i < m; i++)
            {
                std::generate(result[i].begin(), result[i].end(), [&]() { return RandomInt(max, min); });
            }
            return result;
        }

        static vector<int> Duplicate(const vector<int> & input)
        {
            vector<int> output(input.size());
            std::copy(input.begin(), input.end(), output.begin());
            return output;
        }

        static int Compare(const vector<int> & lhs, const vector<int> & rhs)
        {
            if (lhs.empty() && rhs.empty()) return 0;
            if (lhs.empty()) return -1;
            if (rhs.empty()) return 1;
            size_t n = min(lhs.size(), rhs.size());
            for (size_t i = 0; i < n; i++)
            {
                if (lhs[i] < rhs[i]) return -1;
                else if (lhs[i] > rhs[i]) return 1;
            }
            if (lhs.size() < rhs.size()) return -1;
            else if (lhs.size() > rhs.size()) return 1;
            else return 0;
        }

        static vector<int> SortedArrayWithShift(size_t n, size_t shift, int first = 0)
        {
            vector<int> result(n);
            shift %= n;
            size_t i = 0;
            std::generate(result.begin(), result.end(), [&]()
            {
                return (first + n - shift + (i++)) % n;
            });
            return result;
        }

        static void Sort(vector<vector<int>> & grid)
        {
            sort(grid.begin(), grid.end(), [&](vector<int>& lhs, vector<int>& rhs)->bool {
                if (lhs.empty() && rhs.empty()) return false;
                if (lhs.empty()) return true;
                size_t n = min(lhs.size(), rhs.size());
                for (size_t i = 0; i < n; i++)
                {
                    if (lhs[i] < rhs[i]) return true;
                    else if (lhs[i] > rhs[i]) return false;
                }
                return lhs.size() < rhs.size();
            });
        }
        
        static void SortGrid(vector<vector<int>> & grid)
        {
            for_each(grid.begin(), grid.end(), [&](vector<int>& v) {
                sort(v.begin(), v.end());
            });
            sort(grid.begin(), grid.end(), [&](vector<int>& lhs, vector<int>& rhs)->bool {
                if (lhs.empty() && rhs.empty()) return false;
                if (lhs.empty()) return true;
                size_t n = min(lhs.size(), rhs.size());
                for (size_t i = 0; i < n; i++)
                {
                    if (lhs[i] < rhs[i]) return true;
                    else if (lhs[i] > rhs[i]) return false;
                }
                return lhs.size() < rhs.size();
            });
        }

        static vector<int> IncreasingVector(size_t n, int init = 0)
        {
            vector<int> result(n);
            std::generate(result.begin(), result.end(), [&]() { return init++; });
            return result;
        }

        static void Shuffle(vector<int>& input)
        {
            for (size_t i = 0; i < input.size(); i++)
            {
                size_t j = rand() % input.size();
                swap(input[i], input[j]);
            }
        }

        static unsigned long long Factorial(unsigned int n)
        {
            unsigned long long f = 1;
            for (unsigned int i = 2; i <= n; i++) f *= i;
            return f;
        }
    };
}