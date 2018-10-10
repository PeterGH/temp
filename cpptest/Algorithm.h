#pragma once

#include <functional>
#include <vector>

using namespace std;

namespace Test {
    namespace Algorithm {

        namespace Search {
            // comp is a binary function returning a boolean value.
            // If comp(first, second) returns true, then the first input should
            // go before the second input.
            // Default comp is std::less, which forms a non-decreasing sequence.
            // Return -1 if not found
            template<class Compare = std::less<>>
            static int BinarySearch(
                int value,
                size_t begin,
                size_t end,
                function<int(size_t)> get,
                bool first = true,
                Compare comp = std::less<>())
            {
                int b = begin;
                int e = end;
                while (b <= e)
                {
                    // (1) b < m < e
                    // (2) b == m < e == b + 1
                    // (3) b == m == e
                    int m = b + ((e - b) >> 1);
                    int v = get(m);
                    if (comp(value, v)) e = m - 1;
                    else if (comp(v, value)) b = m + 1;
                    else
                    {
                        if (first)
                        {
                            if (b == m) return m; // case (2) or (3)
                            else e = m; // case (1)
                        }
                        else
                        {
                            if (m == e) return m; // case (3)
                            else if (b < m) b = m; // case (1)
                            else if (comp(value, get(e))) return m; // case (2), m is the last
                            else return e; // case (2), e is the last
                        }
                    }
                }
                return -1;
            }

            template<class Compare = std::less<>>
            static int BinarySearch(
                vector<int> & input,
                int value,
                size_t begin,
                size_t end,
                bool first = true,
                Compare comp = std::less<>())
            {
                return BinarySearch(
                    value,
                    begin,
                    end,
                    [&](size_t i)->int { return input[i]; },
                    first,
                    comp);
            }

            template<class Compare = std::less<>>
            static int BinarySearchColumn(
                vector<vector<int>> & input,
                size_t col,
                int value,
                size_t begin,
                size_t end,
                bool first = true,
                Compare comp = std::less<>())
            {
                return BinarySearch(
                    value,
                    begin,
                    end,
                    [&](size_t i)->int { return input[i][col]; },
                    first,
                    comp);
            }

            // comp is a binary function returning a boolean value.
            // If comp(first, second) returns true, then the first input should
            // go before the second input.
            // Default comp is std::less, which forms a non-decreasing sequence.
            // Return i in [begin, end] if should insert value to position i.
            // Return end + 1 if should append value
            template<class Compare = std::less<>>
            static size_t FindInsertPoint(
                int value,
                size_t begin,
                size_t end,
                function<int(size_t)> get,
                bool first = true,
                Compare comp = std::less<>())
            {
                size_t b = begin;
                size_t e = end;
                while (b <= e)
                {
                    // (1) b < m < e
                    // (2) b == m < e == b + 1
                    // (3) b == m == e
                    size_t m = b + ((e - b) >> 1);
                    int v = get(m);
                    if (comp(value, v))
                    {
                        if (b == m) return m; // case (2) or (3)
                        else e = m - 1; // case (1)
                    }
                    else if (comp(v, value))
                    {
                        if (m == e) return e + 1; // case (3)
                        else b = m + 1; // case (1) or (2)
                    }
                    else
                    {
                        if (first)
                        {
                            if (b == m) return m; // case (2) or (3)
                            else e = m; // case (1)
                        }
                        else
                        {
                            if (m == e) return m; // case (3)
                            else if (b < m) b = m; // case (1)
                            else if (comp(value, get(e))) return m; // case (2), m is the last
                            else return e; // case (2), e is the last
                        }
                    }
                }
                throw runtime_error("Unreachable code");
            }

            template<class Compare = std::less<>>
            static size_t FindInsertPoint(
                vector<int> & input,
                int value,
                size_t begin,
                size_t end,
                bool first = true,
                Compare comp = std::less<>())
            {
                return FindInsertPoint(
                    value,
                    begin,
                    end,
                    [&](size_t i)->int { return input[i]; },
                    first,
                    comp);
            }

            template<class Compare = std::less<>>
            static size_t FindInsertPointColumn(
                vector<vector<int>> & input,
                size_t col,
                int value,
                size_t begin,
                size_t end,
                bool first = true,
                Compare comp = std::less<>())
            {
                return FindInsertPoint(
                    value,
                    begin,
                    end,
                    [&](size_t i)->int { return input[i][col]; },
                    first,
                    comp);
            }

            // A sorted array is rotated. Find the index of the minimal
            // element, i.e., the shift distance.
            // Assume no duplicates in the array.
            static size_t FindShiftPoint(const vector<int> & input)
            {
                // Check if no shift
                if (*input.begin() < *(input.end() - 1)) return 0;
                // Now the shift > 0
                int b = 0;
                int e = input.size() - 1;
                while (b <= e)
                {
                    int m = b + ((e - b) >> 1);
                    if (input[b] < input[m]) b = m;
                    else if (input[b] > input[m]) e = m;
                    else return b == e ? b : e;
                }
                throw runtime_error("Unreachable code");
            }
        }

        namespace Sort {
            // comp is a binary function returning a boolean value.
            // If comp(first, second) returns true, then the first input should
            // go before the second input.
            // Default comp is std::less, which forms a non-decreasing sequence.
            template<class Compare = std::less<>>
            static void MergeSortColumn(vector<vector<int>> & input, size_t col, Compare comp = std::less<>())
            {
                function<void(size_t, size_t, size_t)> merge =
                    [&](size_t head1, size_t head2, size_t tail2)
                {
                    // merge input[head1..(head2 - 1)] with input[head2..tail2]
                    while (head1 < head2 && head2 <= tail2)
                    {
                        if (comp(input[head2][col], input[head1][col]))
                        {
                            // input[head1][col] > input[head2][col]
                            int t = input[head2][col];
                            for (size_t i = head2; i > head1; i--)
                            {
                                input[i][col] = input[i - 1][col];
                            }
                            input[head1][col] = t;
                            head2++;
                        }
                        head1++;
                    }
                };

                function<void(size_t, size_t)> sort =
                    [&](size_t head, size_t tail)
                {
                    if (head >= tail) return;
                    size_t middle = head + ((tail - head + 1) >> 1); // midlle is the medium or higher medium
                    sort(head, middle - 1);
                    sort(middle, tail);
                    merge(head, middle, tail);
                };

                sort(0, input.size() - 1);
            }
        }

        namespace Partition {

            // Partition input into two ranges input[begin..i] and input[(i+1)..end], such that
            // transform(input[begin..i]) < value <= transform(input[(i+1)..end]).
            // Invariant: given j, divide the input into three ranges input[begin..i],
            // input[(i+1)..(j-1)] and input[j..end] using value,
            // such that transform(input[begin..i]) < value <= transform(input[(i+1)..(j-1)]).
            // Return the index i+1
            // If all elements are less than value, then return index end+1
            // If all elements are greater than or equal to value, then return begin
            template<class T, class C, class Compare = std::less<C>>
            static size_t PartitionByValue(
                vector<T> & input,
                const C & value,
                size_t begin,
                size_t end,
                Compare comp = std::less<C>(),
                function<C(T)> transform = [&](T v)->C { return v; })
            {
                size_t i = begin;
                for (size_t j = begin; j <= end; j++)
                {
                    if (comp(transform(input[j]), value))
                    {
                        if (i++ != j) swap(input[i - 1], input[j]);
                    }
                }
                return i;
            }

        }

        template<class Compare = std::less<>>
        class YoungTableau
        {
            // A Young tableau is an m x n matrix such that the entries of each row are in sorted
            // order from left to right and the entries of each column are in sorted order from
            // top to bottom.
            // A Young tableau is like a heap and can be used to implement a priority queue.

            // comp is a binary function returning a boolean value.
            // If comp(first, second) returns true, then the first input should be
            // to the right or the bottom of the second input.
            // Default comp is std::less, which forms a max heap.

        private:
            static Compare s_comp;

            // Determine whether lhs is lower than rhs
            static bool lower(int lhs, int rhs) { return s_comp(lhs, rhs); }

            // Determine whether lhs is equal to rhs
            static bool equal(int lhs, int rhs) { return !s_comp(lhs, rhs) && !s_comp(rhs, lhs); }

            // Determine whether lhs is higher than rhs
            static bool higher(int lhs, int rhs) { return s_comp(rhs, lhs); }

        public:
            static void PushUp(vector<vector<int>> &tableau, size_t i, size_t j)
            {
                while (true)
                {
                    size_t mi = i;
                    size_t mj = j;
                    int m = tableau[mi][mj];

                    // Check against the upper
                    if (i > 0 && lower(tableau[i - 1][j], m))
                    {
                        mi = i - 1;
                        mj = j;
                        m = tableau[mi][mj];
                    }

                    // Check against the left
                    if (j > 0 && lower(tableau[i][j - 1], m))
                    {
                        mi = i;
                        mj = j - 1;
                        m = tableau[mi][mj];
                    }

                    if (mi == i && mj == j) break;

                    swap(tableau[i][j], tableau[mi][mj]);
                    i = mi;
                    j = mj;
                }
            }

            static void PushDown(vector<vector<int>> &tableau, size_t i, size_t j)
            {
                while (true)
                {
                    size_t mi = i;
                    size_t mj = j;
                    int m = tableau[mi][mj];

                    // Check against the below
                    if (i + 1 < tableau.size() && lower(m, tableau[i + 1][j]))
                    {
                        mi = i + 1;
                        mj = j;
                        m = tableau[mi][mj];
                    }

                    // Check against the right
                    if (j + 1 < tableau[i].size() && lower(m, tableau[i][j + 1]))
                    {
                        mi = i;
                        mj = j + 1;
                        m = tableau[mi][mj];
                    }

                    if (mi == i && mj == j) break;

                    swap(tableau[i][j], tableau[mi][mj]);
                    i = mi;
                    j = mj;
                }
            }

            static void Create(vector<vector<int>> &tableau)
            {
                // Complexity is sum(i + j) for i in [0, m - 1] and j in [0, n - 1],
                // which is O(mn(m+n))
                for (size_t i = 0; i < tableau.size(); i++)
                {
                    for (size_t j = 0; j < tableau[i].size(); j++)
                    {
                        PushUp(tableau, i, j);
                    }
                }
            }

            static void Create2(vector<vector<int>> &tableau)
            {
                // Complecity is m * lg(n) + n * lg(m)

                for (size_t i = 0; i < tableau.size(); i++)
                {
                    sort(tableau[i].begin(), tableau[i].end(), higher);
                }

                for (size_t i = 0; i < tableau[0].size(); i++)
                {
                    Sort::MergeSortColumn(tableau, i, higher);
                }
            }

            static bool Verify(vector<vector<int>> &tableau)
            {
                for (size_t i = 0; i < tableau.size(); i++)
                {
                    for (size_t j = 0; j < tableau[i].size(); j++)
                    {
                        if (j + 1 < tableau[i].size()
                            && lower(tableau[i][j], tableau[i][j + 1]))
                        {
                            return false;
                        }

                        if (i + 1 < tableau.size()
                            && j < tableau[i + 1].size()
                            && lower(tableau[i][j], tableau[i + 1][j]))
                        {
                            return false;
                        }
                    }
                }

                return true;
            }

            static pair<int, int> Search(vector<vector<int>> & tableau, const int & value)
            {
                // Complexit is O(m + n)
                int i = 0;
                int j = tableau[0].size() - 1;

                while (i < (int)tableau.size() && j >= 0)
                {
                    if (lower(value, tableau[i][j])) i++;
                    else if (lower(tableau[i][j], value)) j--;
                    else return make_pair(i, j);
                }

                return make_pair(-1, -1);
            }

            static pair<int, int> Search2(vector<vector<int>> & tableau, const int & value)
            {
                function<pair<int, int>(int, int, int, int)>
                    search = [&](int i0, int j0, int i1, int j1) -> pair<int, int>
                {
                    if (i0 == i1)
                    {
                        int j = Search::BinarySearch(tableau[i0], value, j0, j1, true, higher);
                        if (j != -1) return make_pair(i0, j);
                    }
                    else if (j0 == j1)
                    {
                        int i = Search::BinarySearchColumn(tableau, j0, value, i0, i1, true, higher);
                        if (i != -1) return make_pair(i, j0);
                    }
                    else
                    {
                        int i = (i0 + i1) >> 1;

                        // Find the first j such that value should be to the left of tableau[i][j]
                        int j = Search::FindInsertPoint(tableau[i], value, j0, j1, true, higher);

                        if (j <= j1 && equal(tableau[i][j], value)) return make_pair(i, j);

                        if (j <= j1 && i0 < i)
                        {
                            // search top-right area
                            auto p = search(i0, j, i - 1, j1);
                            if (p.first != -1 && p.second != -1) return p;
                        }

                        if (j0 < j && i < i1)
                        {
                            // search bottom-left area
                            return search(i + 1, j0, i1, j - 1);
                        }
                    }
                    return make_pair(-1, -1);
                };

                return search(0, 0, tableau.size() - 1, tableau[tableau.size() - 1].size() - 1);
            }

            // Count elements are to the top-left area of the input value.
            static unsigned long CountHigherThan(vector<vector<int>> & tableau, const int & value)
            {
                function<unsigned long(size_t, size_t, size_t, size_t)>
                    count = [&](size_t i0, size_t j0, size_t i1, size_t j1) -> unsigned long
                {
                    size_t i = Search::FindInsertPoint(
                        value,
                        i0,
                        i0 + min(i1 - i0, j1 - j0),
                        [&](size_t k)->int { return tableau[k][j0 + k - i0]; },
                        true,
                        higher);
                    size_t j = j0 + i - i0;

                    if (i == i0 && j == j0) return 0;

                    unsigned long c = (i - i0) * (j - j0);

                    if (j <= j1) c += count(i0, j, i - 1, j1);

                    if (i <= i1) c += count(i, j0, i1, j - 1);

                    return c;
                };

                return count(0, 0, tableau.size() - 1, tableau[0].size() - 1);
            }

            // Count elements are to the top-left area of the input value.
            static unsigned long CountHigherThan2(vector<vector<int>> & tableau, const int & value)
            {
                unsigned long c = 0;
                int last = -1;
                for (size_t i = 0; i < tableau.size(); i++)
                {
                    if (last == -1) last = tableau[i].size();
                    if (last == 0) break;
                    last = Search::FindInsertPoint(tableau[i], value, 0, last - 1, true, higher);
                    c += last;
                }
                return c;
            }

            // Count elements are to the top-left area of the input value.
            static unsigned long CountHigherThan3(vector<vector<int>> & tableau, const int & value)
            {
                unsigned long c = 0;
                int rows = tableau.size();
                int cols = tableau[0].size();

                for (int j = 0; j < min(rows, cols); j++)
                {
                    unsigned int t = 0;
                    for (int i = 0; i <= j; i++)
                    {
                        if (lower(value, tableau[i][j - i])) t++;
                    }
                    if (t == 0) return c;
                    else c += t;
                }

                if (rows <= cols)
                {
                    //  +---------+
                    //  | /      /|
                    //  |/      / |
                    //  +---------+
                    for (int j = rows; j < cols; j++)
                    {
                        unsigned int t = 0;
                        for (int i = 0; i < rows; i++)
                        {
                            if (lower(value, tableau[i][j - i])) t++;
                        }
                        if (t == 0) return c;
                        else c += t;
                    }

                    for (int j = cols; j < cols + rows - 1; j++)
                    {
                        unsigned int t = 0;
                        for (int i = j - cols + 1; i < rows; i++)
                        {
                            if (lower(value, tableau[i][j - i])) t++;
                        }
                        if (t == 0) return c;
                        else c += t;
                    }
                }
                else
                {
                    //  +---+
                    //  |  /|
                    //  | / |
                    //  |/ /|
                    //  | / |
                    //  |/  |
                    //  +---+
                    for (int i = cols; i < rows; i++)
                    {
                        unsigned int t = 0;
                        for (int j = 0; j < cols; j++)
                        {
                            if (lower(value, tableau[i - j][j])) t++;
                        }
                        if (t == 0) return c;
                        else c += t;
                    }

                    for (int i = rows; i < rows + cols - 1; i++)
                    {
                        unsigned int t = 0;
                        for (int j = i - rows + 1; j < cols; j++)
                        {
                            if (lower(value, tableau[i - j][j])) t++;
                        }
                        if (t == 0) return c;
                        else c += t;
                    }
                }

                return c;
            }

            // Count elements are to the top-left area of the input value.
            static unsigned long CountHigherThan4(vector<vector<int>> & tableau, const int & value)
            {
                unsigned long c = 0;
                size_t rows = tableau.size();
                size_t cols = tableau[0].size();
                size_t topLefti = 0;
                size_t topLeftj = 0;
                size_t bottomRighti = 0;
                size_t bottomRightj = 0;

                while (topLefti < rows)
                {
                    unsigned int t = 0;
                    for (size_t i = topLefti; i <= bottomRighti; i++)
                    {
                        if (lower(value, tableau[i][topLeftj - i + topLefti])) t++;
                    }
                    if (t == 0) return c;
                    else c += t;
                    topLefti = topLeftj + 1 < cols ? topLefti : topLefti + 1;
                    topLeftj = topLeftj + 1 < cols ? topLeftj + 1 : topLeftj;
                    bottomRightj = bottomRighti + 1 < rows ? bottomRightj : bottomRightj + 1;
                    bottomRighti = bottomRighti + 1 < rows ? bottomRighti + 1 : bottomRighti;
                }

                return c;
            }
            
            // Find the i-th number in it.
            static int SearchByOrder(const vector<vector<int>> &tableau, int i)
            {
                // Option 1: Heap extract-max i times
                // Option 2: Use CountHigherThan with BinarySearch
                return -1;
            }
        };

        template<class Compare> Compare YoungTableau<Compare>::s_comp;

    }
}