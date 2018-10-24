#include "Test.h"

void LeetCodeTest::Init(void)
{
    
    Add("26. Remove Duplicates", [&]() {
        auto check = [&](vector<int> & v)
        {
            Logger() << v;
            set<int> s;
            for (size_t i = 0; i < v.size(); i++)
            {
                s.insert(v[i]);
            }
            size_t len = LeetCode::Array::removeDuplicates(v);
            Logger() << v;
            ASSERT1(len == s.size());
            for (size_t i = 0; i < len; i++)
            {
                ASSERT1(v[i] == *s.begin());
                s.erase(s.begin());
            }
        };
        {
            vector<int> v = { 0, 1, 2, 3, 4, 5 };
            check(v);
        }
        {
            vector<int> v = { 0, 0, 0 };
            check(v);
        }
        {
            for (int i = 0; i < 20; i++) {
                vector<int> input = Util::RandomVector(Util::RandomInt(50, 1), 10, -10);
                sort(input.begin(), input.end());
                int length = (int)input.size();
                Logger().WriteInformation("Run %d: %d elements\n", i, length);
                check(input);
            }
        }
    });

    Add("27. Remove Element", [&]() {
        auto check = [&](vector<int> & v, int e)
        {
            Logger() << v << "Removing " << e << endl;
            vector<int> s;
            for (size_t i = 0; i < v.size(); i++)
            {
                if (v[i] != e) s.push_back(v[i]);
            }
            vector<int> v2 = Util::Duplicate(v); 
            
            size_t len = LeetCode::Array::removeElementStable(v, e);
            Logger() << v << "Length " << len << endl;
            size_t len2 = LeetCode::Array::removeElementUnstable(v2, e);
            Logger() << v2 << "Length " << len2 << endl;
            ASSERT1(len == s.size());
            ASSERT1(len2 == s.size());

            sort(v.begin(), v.begin() + len);
            sort(v2.begin(), v2.begin() + len2);
            sort(s.begin(), s.end());
            for (size_t i = 0; i < len; i++)
            {
                ASSERT1(v[i] == s[i]);
                ASSERT1(v2[i] == s[i]);
            }
        };
        {
            vector<int> v = { 0, 1, 2, 3, 4, 5 };
            check(v, 0);
        }
        {
            vector<int> v = { 0, 0, 0 };
            check(v, 0);
        }
        for (int i = 0; i < 20; i++) {
            vector<int> input = Util::RandomVector(Util::RandomInt(50, 1), 10, -10);
            int length = (int)input.size();
            Logger().WriteInformation("Run %d: %d elements\n", i, length);
            check(input, Util::RandomInt(10, -10));
        }
    });


    
    Add("34. Search Range", [&]() {
        auto check = [&](vector<int> & v, int e) {
            Logger() << v;
            Logger() << "Range " << e << ": ";
            vector<int> p = LeetCode::Array::searchRange(v, e);
            vector<int> p2 = LeetCode::Array::searchRange2(v, e);
            Logger() << "[" << p[0] << ", " << p[1] << "], [" << p2[0] << ", " << p2[1] << "]" << endl;
            ASSERT1(p[0] == p2[0]);
            ASSERT1(p[1] == p2[1]);
            if (p[0] > 0) ASSERT1(v[p[0] - 1] < v[p[0]]);
            if (0 <= p[1] && p[1] < (int)v.size() - 1) ASSERT1(v[p[1]] < v[p[1] + 1]);
        };
        {
            vector<int> v = { 0 };
            check(v, 0);
            check(v, 1);
        }
        {
            vector<int> v = { 1, 1 };
            check(v, 1);
            check(v, 2);
        }
        {
            vector<int> v = { 2, 3 };
            check(v, 1);
            check(v, 2);
            check(v, 3);
            check(v, 4);
        }
        for (int i = 0; i < 100; i++) {
            vector<int> input = Util::RandomVector(Util::RandomInt(100, 1), 5, -5);
            sort(input.begin(), input.end());
            check(input, Util::RandomInt(6, -6));
        }
    });

    Add("39. Combination Sum", [&]() {
        auto check = [&](vector<int>& v, int t) {
            Logger() << v << "Target " << t << endl;
            auto v1 = Util::Duplicate(v);
            auto v2 = Util::Duplicate(v);
            auto v3 = Util::Duplicate(v);
            auto c1 = LeetCode::Combination::combinationSumReuse(v1, t);
            auto c2 = LeetCode::Combination::combinationSumReuse2(v2, t);
            auto c3 = LeetCode::Combination::combinationSumReuse3(v3, t);
            Util::SortGrid(c1);
            Util::SortGrid(c2);
            Util::SortGrid(c3);
            Logger() << c1;
            ASSERT1(c1.size() == c2.size());
            ASSERT1(c1.size() == c3.size());
            for (size_t i = 0; i < c1.size(); i++)
            {
                ASSERT1(c1[i].size() == c2[i].size());
                ASSERT1(c1[i].size() == c3[i].size());
                for (size_t j = 0; j < c1[i].size(); j++)
                {
                    ASSERT1(c1[i][j] == c2[i][j]);
                    ASSERT1(c1[i][j] == c3[i][j]);
                }
            }
        };
        for (int i = 0; i < 20; i++) {
            vector<int> input = Util::IncreasingVector(Util::RandomInt(10, 1), 2);
            Util::Shuffle(input);
            int t = 0;
            int c = 1 + (input.size() >> 2);
            for (int j = 0; j < c; j++)
            {
                t += input[Util::RandomInt(input.size() - 1)];
            }
            check(input, t);
        }
    });

    Add("49. Group Anagrams", [&]() {
        vector<string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
        vector<vector<string>> result = LeetCode::String::groupAnagrams(strs);
    });

    Add("50. Pow(x, n)", [&]() {
        auto test = [&](double x, int n) -> double {
            double p = LeetCode::Numeric::myPow(x, n);
            Logger() << "pow(" << x << ", " << n << ") = " << p << "\n";
            return p;
        };
        
        test(0.00001, 2147483647);
    });

    Add("53. Max Subarray", [&]() {
        auto check = [&](vector<int> & a, int el, int er, int es) -> void {
            Logger() << a;
            int sum = LeetCode::Array::maxSubArray(a);
            int l2, r2;
            int sum2 = LeetCode::Array::maxSubArray2(a, l2, r2);
            Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
            int l3, r3;
            int sum3 = LeetCode::Array::maxSubArray3(a, l3, r3);
            Logger().WriteInformation("a[%d..%d] = %d\n", l3, r3, sum3);
            ASSERT1(es == sum);
            ASSERT1(el == l2);
            ASSERT1(er == r2);
            ASSERT1(es == sum2);
            ASSERT1(el == l3);
            ASSERT1(er == r3);
            ASSERT1(es == sum3);
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
                Logger() << input;
                int sum = LeetCode::Array::maxSubArray(input);
                int l2, r2;
                int sum2 = LeetCode::Array::maxSubArray2(input, l2, r2);
                Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
                int l3, r3;
                int sum3 = LeetCode::Array::maxSubArray3(input, l3, r3);
                Logger().WriteInformation("a[%d..%d] = %d\n", l3, r3, sum3);
                ASSERT1(l2 == l3);
                ASSERT1(r2 == r3);
                ASSERT1(sum == sum2);
                ASSERT1(sum == sum3);
            }
        }
        {
            for (int i = 0; i < 1000; i++) {
                vector<int> input;
                int length = 1 + (rand() % 100);
                for (int j = 0; j < length; j++) {
                    input.push_back(rand() % 20 - 10);
                }
                Logger() << input;
                int sum = LeetCode::Array::maxSubArray(input);
                int l2, r2;
                int sum2 = LeetCode::Array::maxSubArray2(input, l2, r2);
                Logger().WriteInformation("a[%d..%d] = %d\n", l2, r2, sum2);
                int l3, r3;
                int sum3 = LeetCode::Array::maxSubArray3(input, l3, r3);
                Logger().WriteInformation("a[%d..%d] = %d\n", l3, r3, sum3);
                ASSERT1(l2 == l3);
                ASSERT1(r2 == r3);
                ASSERT1(sum == sum2);
                ASSERT1(sum == sum3);
            }
        }
    });

    Add("54. Spiral Matrix", [&]() {
        auto check = [&](vector<vector<int>> m) {
            Logger() << m;
            vector<int> o = LeetCode::Grid::spiralOrder(m);
            vector<int> o2 = LeetCode::Grid::spiralOrder2(m);
            Logger() << o << o2;
            ASSERT1(o.size() == o2.size());
            for (size_t i = 0; i < o.size(); i++) {
                ASSERT1(o[i] == i);
                ASSERT1(o2[i] == i);
            }
        };
        {
            vector<vector<int>> m = {
                { 0 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1, 2 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0 },
                { 1 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0 },
                { 1 },
                { 2 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1 },
                { 3, 2 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1, 2 },
                { 5, 4, 3 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1 },
                { 5, 2 },
                { 4, 3 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1, 2 },
                { 7, 8, 3 },
                { 6, 5, 4 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1,  2,  3 },
                { 9, 10, 11, 4 },
                { 8, 7,  6,  5 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0, 1,  2 },
                { 9, 10, 3 },
                { 8, 11, 4 },
                { 7, 6,  5 }
            };
            check(m);
        }
        {
            vector<vector<int>> m = {
                { 0,  1,  2,  3 },
                { 11, 12, 13, 4 },
                { 10, 15, 14, 5 },
                { 9,  8,  7,  6 }
            };
            check(m);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                vector<vector<int>> m = Util::RandomMatrix(Util::RandomInt(50, 1), Util::RandomInt(50, 1));
                Logger() << m;
                vector<int> o = LeetCode::Grid::spiralOrder(m);
                vector<int> o2 = LeetCode::Grid::spiralOrder2(m);
                ASSERT1(o.size() == o2.size());
                for (size_t j = 0; j < o.size(); j++)
                {
                    ASSERT1(o[j] == o2[j]);
                };
            }
        }
    });

    Add("55. Jump Game", [&]() {
        auto check = [&](vector<int> a) {
            Logger() << a;
            bool c = LeetCode::Array::canJump(a);
            bool c2 = LeetCode::Array::canJump2(a);
            Logger().WriteInformation("Can %sjump\n", c ? "" : "not ");
            Logger().WriteInformation("Can %sjump\n", c2 ? "" : "not ");
            ASSERT1(c == c2);
        };
        {
            vector<int> a = { 0, 1 };
            check(a);
        }
        {
            vector<int> a = { 2, 3, 1, 1, 4 };
            check(a);
        }
        {
            vector<int> a = { 3, 2, 1, 0, 4 };
            check(a);
        }
        {
            for (int i = 0; i < 100; i++)
            {
                vector<int> a = Util::RandomVector(Util::RandomInt(100, 1), 10);
                check(a);
            }
        }
    });

    Add("63. Unique Paths II", [&]() {
        auto test = [&](vector<vector<int>> & grid, int expected) {
            int count = LeetCode::Grid::uniquePathsWithObstacles(grid);
            Logger() << "Unique paths: " << count << "\n";
            ASSERT1(count == expected);
        };

        vector<vector<int>> grid = { { 0, 0}, { 0, 0} };
        test(grid, 2);
    });

    Add("69. Sqrt(x)", [&]() {
        auto test = [&](int x, int expected) {
            int actual = LeetCode::Numeric::mySqrt(x);
            Logger() << "sqrt(" << x << ") = " << actual << "\n";
            ASSERT1(actual == expected);
        };
        test(2147395599, 46339);
    });

    Add("73. Set Matrix Zeroes", [&]() {
        auto test = [&](vector<vector<int>> & matrix) {
            LeetCode::Grid::setZeroes(matrix);
        };

        vector<vector<int>> m = { {0, 1} };
        test(m);
    });

    Add("95. Unique Binary Search Trees II", [&]() {
        auto test = [&](int n) {
            vector<LeetCode::TreeNode *> trees = LeetCode::BinaryTree::generateTrees(n);
            for (size_t i = 0; i < trees.size(); i++) {
                Logger() << "Tree " << i << "\n";
                LeetCode::Helper::Print(trees[i]);
                LeetCode::Helper::DeleteTree(trees[i]);
            }
        };
        test(3);
    });

    Add("114. Flatten Binary Tree to Linked List", [&]() {
        auto test = [&](LeetCode::TreeNode * node) {
            LeetCode::Helper::Print(node);
            LeetCode::BinaryTree::flatten(node);
            LeetCode::Helper::Print(node);
            LeetCode::Helper::DeleteTree(node);
        };
        {
            LeetCode::TreeNode * node = new LeetCode::TreeNode(1);
            node->left = new LeetCode::TreeNode(2);
            node->left->right = new LeetCode::TreeNode(3);
            test(node);
        }
    });

    Add("127. Word Ladder", [&]() {
        auto test = [&](string beginWord, string endWord, vector<string> wordList, int expect) {
            int actual = LeetCode::String::ladderLength(beginWord, endWord, wordList);
            Logger() << actual << ", " << expect << "\n";
            ASSERT1(actual == expect);
        };

        test("a", "c", vector<string> { "a", "b", "c" }, 2);
        test("hit", "cog", vector<string> {"hot", "dot", "dog", "lot", "log", "cog"}, 5);
        test("qa", "sq", vector<string> {"si", "go", "se", "cm", "so", "ph", "mt", "db", "mb", "sb", "kr", "ln", "tm", "le", "av", "sm", "ar" }, 0);
    });

    Add("130. Surrounded Regions", [&]() {
        auto test = [&](vector<vector<char>> & board) {
            LeetCode::Helper::print(board);
            LeetCode::Grid::solve(board);
            LeetCode::Helper::print(board);
        };
        {
            vector<vector<char>> board(1, vector<char>(100, 'O'));
            test(board);
        }
        {
            vector<vector<char>> board = {
                { 'X', 'X', 'X', 'X' },
                { 'X', 'O', 'O', 'X' },
                { 'X', 'X', 'O', 'X' },
                { 'X', 'O', 'X', 'X' }
            };
            test(board);
        }
    });

    Add("139. Word Break", [&]() {
        auto test = [&](string s, vector<string> & dict, bool expect){
            bool actual = LeetCode::wordBreak(s, dict);
            ASSERT1(actual == expect);
        };
        test("leetcode", vector<string>{"leet", "code"}, true);
    });

    Add("145. Binary Tree Postorder Traversal", [&]() {
        auto test = [&](LeetCode::TreeNode * node, const vector<int> & expect) {
            LeetCode::Helper::Print(node);
            vector<int> actual = LeetCode::BinaryTree::postorderTraversal(node);
            LeetCode::Helper::DeleteTree(node);
            LeetCode::Helper::print(expect);
            LeetCode::Helper::print(actual);
        };

        {
            LeetCode::TreeNode * node = new LeetCode::TreeNode(1);
            test(node, vector<int>{1});
        }
    });

    Add("151. Reverse Words in a String", [&]() {
        auto test = [&](string & str, const string & expect) {
            Logger() << str << endl; 
            LeetCode::String::reverseWords(str);
            Logger() << str << endl;
            Logger() << expect << endl;
            ASSERT1(str.compare(expect) == 0);
        };
        test(string("a"), "a");
    });

    Add("179. Largest Number", [&]() {
        auto test = [&](vector<int> & nums, const string & expect) {
            string actual = LeetCode::Numeric::largestNumber(nums);
            Logger() << actual << ", " << expect << endl;
            ASSERT1(actual.compare(expect) == 0);
        };
        test(vector<int> { 1 }, "1");
    });

    Add("199. Binary Tree Right Side View", [&]() {
        auto test = [&](LeetCode::TreeNode * root, const vector<int> & expect) {
            vector<int> actual = LeetCode::BinaryTree::rightSideView(root);
            LeetCode::Helper::print(actual);
            LeetCode::Helper::print(expect);
        };
        {
            LeetCode::TreeNode n(1);
            test(&n, vector<int> { 1 });
        }
    });

    Add("202. Happy Number", [&]() {
        auto test = [&](int n, bool expect) {
            bool actual = LeetCode::Numeric::isHappy(n);
            ASSERT1(actual == expect);
        };
        test(2, false);
    });
}