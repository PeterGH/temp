#include "Test.h"

void LeetCodeTest::Init(void)
{
    
    

    
    
    
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