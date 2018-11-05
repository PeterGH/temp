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