#pragma once

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>
#include "Algorithm.h"
#include "Log.h"

using namespace std;

namespace Test {
    namespace LeetCode {

        struct ListNode
        {
            int val;
            ListNode *next;
            ListNode(int x) : val(x), next(nullptr) {}
        };

        struct TreeNode
        {
            int val;
            TreeNode *left;
            TreeNode *right;
            TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        };

        struct TreeLinkNode
        {
            TreeLinkNode *left;
            TreeLinkNode *right;
            TreeLinkNode *next;
        };

        struct RandomListNode
        {
            int label;
            RandomListNode *next, *random;
            RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
        };
        
        namespace Helper {

            template<class T>
            static void print(const vector<T> & v)
            {
                cout << "[";
                for (size_t i = 0; i < v.size(); i++)
                {
                    if (i > 0) cout << ", ";
                    cout << v[i];
                }
                cout << "]" << endl;
            }

            template<class T>
            static void print(const vector<vector<T>> & v)
            {
                cout << "[" << endl;
                for (size_t i = 0; i < v.size(); i++)
                {
                    cout << " ";
                    print(v[i]);
                }
                cout << "]" << endl;
            }

            static void Print(TreeNode * node)
            {
                function<void(stringstream *, int, char)>
                    printChar = [&](stringstream * s, int n, char c)
                {
                    if (n > 0) {
                        string chars(n, c);
                        *s << chars;
                    }
                };
                function<void(TreeNode *, unsigned int, int &, int &, vector<stringstream *> &)>
                    toString = [&](
                        TreeNode * n,             // current node to print
                        unsigned int y,           // current node level
                        int & x,                  // x-axis position of root of last printed sub tree
                        int & r,                  // x-axis position of right-most boundary of last printed sub tree
                        vector<stringstream *> & ss // output streams, one per level
                        )
                {
                    if (n == nullptr) return;
                    if (ss.size() <= y) ss.push_back(new stringstream());
                    // print left tree, update x and r accordingly
                    toString(n->left, y + 1, x, r, ss);
                    stringstream * s = ss[y];
                    int l = (int)(s->str().length());
                    if (l < x) printChar(s, x - l, ' ');
                    if (n->left != nullptr && r > x)
                    {
                        *s << '/';
                        printChar(s, r - x - 1, '-');
                    }
                    string nc = to_string(n->val);
                    *s << nc;
                    x = (r + (nc.length() >> 1));
                    r = r + nc.length();
                    int rx = r;
                    int rr = r;
                    toString(n->right, y + 1, rx, rr, ss);
                    if (n->right != nullptr && rx >= r)
                    {
                        printChar(s, rx - r - 1, '-');
                        *s << '\\';
                    }
                    // Update the right most boundary
                    r = rr;
                };
                vector<stringstream *> streams;
                int x = 0;
                int r = 0;
                toString(node, 0, x, r, streams);
                for_each(streams.begin(), streams.end(), [&](stringstream * s)
                {
                    cout << s->str() << endl;
                    delete s;
                });
            }

            static void DeleteTree(TreeNode * node)
            {
                if (node == nullptr) return;
                if (node->left != nullptr)
                {
                    DeleteTree(node->left);
                    node->left = nullptr;
                }
                if (node->right != nullptr)
                {
                    DeleteTree(node->right);
                    node->right = nullptr;
                }
                delete node;
                node = nullptr;
            }
        }

        
        namespace Array {

            

            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            // 88. Merge Sorted Array
            // Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
            // Note:
            // You may assume that nums1 has enough space(size that is greater or equal to m + n)
            // to hold additional elements from nums2. The number of elements initialized in nums1 and nums2
            // are m and n respectively.
            static void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
                vector<int>::iterator it1 = nums1.begin();
                vector<int>::iterator it2 = nums2.begin();
                int i = 0;
                int j = 0;
                while (i < m || j < n) {
                    if (i < m && j < n) {
                        if (*it1 <= *it2) {
                            it1++;
                            i++;
                        }
                        else {
                            it1 = nums1.insert(it1, *it2);
                            it1++;
                            it2 = nums2.erase(it2);
                            j++;
                        }
                    }
                    else if (j < n) {
                        it1 = nums1.insert(it1, *it2);
                        it1++;
                        it2 = nums2.erase(it2);
                        j++;
                    }
                    else {
                        it1++;
                        i++;
                    }
                }
                while (it1 != nums1.end()) it1 = nums1.erase(it1);
            }

            // 89. Gray Code
            // The gray code is a binary numeral system where two successive values differ in only one bit.
            // Given a non-negative integer n representing the total number of bits in the code,
            // print the sequence of gray code. A gray code sequence must begin with 0.
            // For example, given n = 2, return [0, 1, 3, 2]. Its gray code sequence is:
            // 00 - 0
            // 01 - 1
            // 11 - 3
            // 10 - 2
            // Note :
            // For a given n, a gray code sequence is not uniquely defined.
            // For example, [0, 2, 3, 1] is also a valid gray code sequence according to the above definition.
            // For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
            static vector<int> grayCode(int n) {
                vector<int> gray = { 0 };
                int b = 0x1;
                for (int i = 0; i < n; i++) {
                    int m = gray.size();
                    for (int j = m - 1; j >= 0; j--) {
                        int c = gray[j];
                        c |= b;
                        gray.push_back(c);
                    }
                    b = (b << 1);
                }
                return gray;
            }

            // 90. Subsets II
            // Given a collection of integers that might contain duplicates, nums, return all possible subsets.
            // Note: The solution set must not contain duplicate subsets.
            // For example,
            // If nums = [1, 2, 2], a solution is :
            // [
            //   [2],
            //   [1],
            //   [1, 2, 2],
            //   [2, 2],
            //   [1, 2],
            //   []
            // ]
            static vector<vector<int>> subsetsWithDup(vector<int>& nums) {
                vector<vector<int>> result = vector<vector<int>>{ vector<int>{} };
                if (nums.size() == 0) return result;
                sort(nums.begin(), nums.end());
                size_t i = 0;
                while (i < nums.size()) {
                    size_t j = i;
                    while (j + 1 < nums.size() && nums[j] == nums[j + 1]) j++;
                    vector<int> c;
                    size_t n = result.size();
                    for (size_t k = i; k <= j; k++) {
                        c.push_back(nums[k]);
                        for (size_t l = 0; l < n; l++) {
                            vector<int> e(result[l]);
                            e.insert(e.end(), c.begin(), c.end());
                            result.push_back(e);
                        }
                    }
                    i = j + 1;
                }
                return result;
            }

            // 91. Decode Ways
            // A message containing letters from A-Z is being encoded to numbers using the following mapping:
            // 'A' -> 1
            // 'B' -> 2
            // ...
            // 'Z' -> 26
            // Given an encoded message containing digits, determine the total number of ways to decode it.
            // For example,
            // Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
            // The number of ways decoding "12" is 2.
            static int numDecodings(string s) {
                if (s.length() == 0) return 0;
                int n;
                function<int(int)>
                    solve = [&](int i) -> int
                {
                    if (i == s.length()) return 0;
                    if (i == s.length() - 1) {
                        if (s[i] == '0') return 0;
                        else return 1;
                    }
                    switch (s[i]) {
                    case '0':
                        return 0;
                    case '1':
                        if (s[i + 1] == '0') {
                            if (s[i + 2] == '0') return 0;
                            else return solve(i + 2);
                        }
                        else {
                            if (s[i + 2] == '0') return solve(i + 1);
                            else return solve(i + 1) + solve(i + 2);
                        }
                    case '2':
                        if (s[i + 1] == '0') {
                            if (s[i + 2] == '0') return 0;
                            else return solve(i + 2);
                        }
                        else if ('1' <= s[i + 1] && s[i + 1] <= '6') {
                            n = solve(i + 2);
                            if (n == 0) n++;
                            return solve(i + 1) + n;
                        }
                        else {
                            return solve(i + 1);
                        }
                    default:
                        return solve(i + 1);
                    }
                };
                return solve(0);
            }

            // 93. Restore IP Addresses
            // Given a string containing only digits, restore it by returning all possible valid IP address combinations.
            // For example :
            // Given "25525511135",
            // return["255.255.11.135", "255.255.111.35"]. (Order does not matter)
            static vector<string> restoreIpAddresses(string s) {
                vector<string> result;
                function<void(int, int, string &)>
                    solve = [&](int i, int j, string & p)
                {
                    if (i > 4) {
                        if (j == s.length()) {
                            p.pop_back();
                            result.push_back(p);
                        }
                        return;
                    }
                    if (j == s.length()) return;
                    string p1(p);
                    solve(i + 1, j + 1, p1.append(1, s[j]).append(1, '.'));
                    if (j + 1 == s.length() || s[j] == '0') return;
                    string p2(p);
                    solve(i + 1, j + 2, p2.append(s.substr(j, 2)).append(1, '.'));
                    if (j + 2 == s.length()) return;
                    int c = s[j] - '0';
                    c = 10 * c + s[j + 1] - '0';
                    c = 10 * c + s[j + 2] - '0';
                    if (c <= 255) {
                        string p3(p);
                        solve(i + 1, j + 3, p3.append(s.substr(j, 3)).append(1, '.'));
                    }
                };
                string prefix;
                solve(1, 0, prefix);
                return result;
            }

            // 118. Pascal's Triangle
            // Given numRows, generate the first numRows of Pascal's triangle.
            // For example, given numRows = 5,
            // Return
            // [
            //      [1],
            //     [1, 1],
            //    [1, 2, 1],
            //   [1, 3, 3, 1],
            //  [1, 4, 6, 4, 1]
            // ]
            static vector<vector<int>> generate(int numRows) {
                vector<vector<int>> result;
                if (numRows <= 0) return result;
                vector<int> row;
                for (int i = 0; i < numRows; i++) {
                    row.push_back(1);
                    for (int j = row.size() - 2; j > 0; j--) {
                        row[j] += row[j - 1];
                    }
                    result.push_back(row);
                    row = vector<int>(row);
                }
                return result;
            }

            // 119. Pascal's Triangle II
            // Given an index k, return the kth row of the Pascal's triangle.
            // For example, given k = 3,
            // Return[1, 3, 3, 1].
            // Note:
            // Could you optimize your algorithm to use only O(k) extra space ?
            static vector<int> getRow(int rowIndex) {
                vector<int> row;
                for (int k = 0; k <= rowIndex; k++) {
                    row.push_back(1);
                    for (int i = row.size() - 2; i > 0; i--) {
                        row[i] += row[i - 1];
                    }
                }
                return row;
            }

            // 120. Triangle
            // Given a triangle, find the minimum path sum from top to bottom.
            // Each step you may move to adjacent numbers on the row below.
            // For example, given the following triangle
            // [
            //     [2],
            //    [3, 4],
            //   [6, 5, 7],
            //  [4, 1, 8, 3]
            // ]
            // The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
            // Note:
            // Bonus point if you are able to do this using only O(n) extra space,
            // where n is the total number of rows in the triangle.
            static int minimumTotal(vector<vector<int>>& triangle) {
                vector<int> row(triangle[0]);
                for (size_t i = 1; i < triangle.size(); i++) {
                    size_t n = triangle[i].size();
                    row.push_back(row[n - 2] + triangle[i][n - 1]);
                    for (int j = n - 2; j > 0; j--) {
                        row[j] = triangle[i][j] + min(row[j - 1], row[j]);
                    }
                    row[0] += triangle[i][0];
                }
                int min = row[0];
                for (size_t i = 1; i < row.size(); i++) {
                    if (row[i] < min) min = row[i];
                }
                return min;
            }

            // 121. Best Time to Buy and Sell Stock
            // Say you have an array for which the i-th element is the price of a given stock on day i.
            // If you were only permitted to complete at most one transaction(ie, buy one and sell one share
            // of the stock), design an algorithm to find the maximum profit.
            // Example 1:
            // Input: [7, 1, 5, 3, 6, 4]
            // Output : 5
            // max.difference = 6 - 1 = 5 (not 7 - 1 = 6, as selling price needs to be larger than buying price)
            // Example 2 :
            // Input : [7, 6, 4, 3, 1]
            // Output : 0
            // In this case, no transaction is done, i.e.max profit = 0.
            static int maxProfit(vector<int>& prices) {
                if (prices.empty()) return 0;
                int min = prices[0];
                int profit = 0;
                for (size_t i = 1; i < prices.size(); i++) {
                    if (prices[i] - min > profit) {
                        profit = prices[i] - min;
                    }
                    else if (prices[i] < min) {
                        min = prices[i];
                    }
                }
                return profit;
            }

            // 122. Best Time to Buy and Sell Stock II
            // Say you have an array for which the ith element is the price of a given
            // stock on day i. Design an algorithm to find the maximum profit.
            // You may complete as many transactions as you like (ie, buy one and sell
            // one share of the stock multiple times). However, you may not engage in
            // multiple transactions at the same time (ie, you must sell the stock
            // before you buy again).
            static int maxProfit2(vector<int>& prices) {
                if (prices.empty()) return 0;
                int profit = 0;
                for (size_t i = 1; i < prices.size(); i++) {
                    if (prices[i] > prices[i - 1]) {
                        profit += (prices[i] - prices[i - 1]);
                    }
                }
                return profit;
            }

            // 125. Valid Palindrome
            // Given a string, determine if it is a palindrome, considering only alphanumeric
            // characters and ignoring cases.
            // For example,
            // "A man, a plan, a canal: Panama" is a palindrome.
            // "race a car" is not a palindrome.
            // Note:
            // Have you consider that the string might be empty?
            // This is a good question to ask during an interview.
            // For the purpose of this problem, we define empty string as valid palindrome.
            static bool isPalindrome(string s) {
                function<bool(char)>
                    isDigit = [&](char c) -> bool
                {
                    return '0' <= c && c <= '9';
                };
                function<bool(char)>
                    isLower = [&](char c) -> bool
                {
                    return 'a' <= c && c <= 'z';
                };
                function<bool(char)>
                    isUpper = [&](char c) -> bool
                {
                    return 'A' <= c && c <= 'Z';
                };
                int i = 0;
                int j = s.size() - 1;
                while (i < j) {
                    char a = s[i];
                    if (!isDigit(a) && !isLower(a) && !isUpper(a)) {
                        i++;
                        continue;
                    }
                    char b = s[j];
                    if (!isDigit(b) && !isLower(b) && !isUpper(b)) {
                        j--;
                        continue;
                    }
                    if (isDigit(a) != isDigit(b)) return false;
                    if (isDigit(a) && a != b) return false;
                    if (isLower(a) && a - 'a' != b - 'a' && a - 'a' != b - 'A') return false;
                    if (isUpper(a) && a - 'A' != b - 'a' && a - 'A' != b - 'A') return false;
                    i++;
                    j--;
                }
                return true;
            }

            // 162. Find Peak Element
            // A peak element is an element that is greater than its neighbors.
            // Given an input array where num[i] != num[i + 1], find a peak element
            // and return its index.
            // The array may contain multiple peaks, in that case return the index
            // to any one of the peaks is fine.
            // You may imagine that num[-1] = num[n] = negative infinity.
            // For example, in array[1, 2, 3, 1], 3 is a peak element and your function
            // should return the index number 2.
            // Note: Your solution should be in logarithmic complexity.
            static int findPeakElement(vector<int>& nums) {
                int l = 0;
                int h = nums.size() - 1;
                int m;
                while (l <= h) {
                    m = l + ((h - l) >> 1);
                    if (m == h) {
                        return m;
                    }
                    else if (l == m) {
                        if (nums[m] <= nums[m + 1]) {
                            l = m + 1;
                        }
                        else {
                            return m;
                        }
                    }
                    else {
                        if (nums[m - 1] < nums[m] && nums[m] > nums[m + 1]) {
                            return m;
                        }
                        else if (nums[m - 1] <= nums[m + 1]) {
                            l = m + 1;
                        }
                        else {
                            h = m - 1;
                        }
                    }
                }
            }

            // 169. Majority Element
            // Given an array of size n, find the majority element. The majority
            // element is the element that appears more than ⌊ n/2 ⌋ times.
            // You may assume that the array is non-empty and the majority element
            // always exist in the array.
            static int majorityElement(vector<int>& nums) {
                map<int, int> m;
                for (size_t i = 0; i < nums.size(); i++) {
                    if (m.find(nums[i]) == m.end()) {
                        m[nums[i]] = 1;
                    }
                    else {
                        m[nums[i]]++;
                    }
                    if (m[nums[i]] > (int)nums.size() / 2) {
                        return nums[i];
                    }
                }
            }

            // 189. Rotate Array
            // Rotate an array of n elements to the right by k steps.
            // For example, with n = 7 and k = 3, the array[1, 2, 3, 4, 5, 6, 7]
            // is rotated to[5, 6, 7, 1, 2, 3, 4].
            // Note: Try to come up as many solutions as you can, there are at least
            // 3 different ways to solve this problem.
            // Hint: Could you do it in-place with O(1) extra space?
            static void rotate(vector<int>& nums, int k) {
                if (nums.empty()) return;
                k %= nums.size();
                if (k == 0) return;
                function<void(int, int)>
                    swapRange = [&](int i, int j) {
                    while (i < j) {
                        swap(nums[i++], nums[j--]);
                    }
                };
                swapRange(0, nums.size() - 1);
                swapRange(0, k - 1);
                swapRange(k, nums.size() - 1);
            }
            // This one works only if n and k are co-prime
            static void rotate2(vector<int>& nums, int k) {
                if (nums.empty()) return;
                k %= nums.size();
                if (k == 0) return;
                size_t i = 0;
                do {
                    i = (i + k) % nums.size();
                    swap(nums[0], nums[i]);
                } while (i != 0);
            }

            // 198. House Robber
            // You are a professional robber planning to rob houses along a street.
            // Each house has a certain amount of money stashed, the only constraint
            // stopping you from robbing each of them is that adjacent houses have
            // security system connected and it will automatically contact the police
            // if two adjacent houses were broken into on the same night.
            // Given a list of non-negative integers representing the amount of money
            // of each house, determine the maximum amount of money you can rob tonight
            // without alerting the police.
            static int rob(vector<int>& nums) {
                int a = 0;
                int b = 0;
                int c;
                for (size_t i = 0; i < nums.size(); i++) {
                    c = max(a + nums[i], b);
                    a = b;
                    b = c;
                }
                return b;
            }
        }

        namespace Grid {
            // 36. Valid Sudoku
            // Determine if a Sudoku is valid, according to: Sudoku Puzzles
            // The Rules. The Sudoku board could be partially filled, where empty
            // cells are filled with the character '.'.
            // A partially filled sudoku which is valid.
            // Note: A valid Sudoku board (partially filled) is not necessarily
            // solvable. Only the filled cells need to be validated.
            static bool isValidSudoku(vector<vector<char>>& board)
            {
                map<size_t, set<char>> rows;
                map<size_t, set<char>> cols;
                map<size_t, set<char>> grids;
                for (size_t i = 0; i < board.size(); i++)
                {
                    if (rows.find(i) == rows.end()) rows[i] = set<char>{};
                    for (size_t j = 0; j < board[i].size(); j++)
                    {
                        if (i == 0 && cols.find(j) == cols.end()) cols[j] = set<char>();
                        if (i % 3 == 0 && j % 3 == 0 && grids.find(i * 3 + j) == grids.end()) {
                            grids[i * 3 + j] = set<char>{};
                        }
                        if (board[i][j] != '.') { // A real check may be against '0'-'9'
                            if (rows[i].find(board[i][j]) != rows[i].end()) return false;
                            rows[i].insert(board[i][j]);
                            if (cols[j].find(board[i][j]) != cols[j].end()) return false;
                            cols[j].insert(board[i][j]);
                            auto k = (i / 3) * 3 + (j / 3);
                            if (grids[k].find(board[i][j]) != grids[k].end()) return false;
                            grids[k].insert(board[i][j]);
                        }
                    }
                }
                return true;
            }

            // 48. Rotate Image
            // You are given an n x n 2D matrix representing an image.
            // Rotate the image by 90 degrees(clockwise).
            // 0 1        3 0
            // 3 2        2 1
            static void rotate(vector<vector<int>>& matrix) {
                int d = matrix.size();
                for (int i = 0; i < d - 1; i++) {
                    for (int j = 0; j < d - i - 1; j++) {
                        swap(matrix[i][j], matrix[d - j - 1][d - i - 1]);
                    }
                }
                for (int i = 0; i < (d >> 1); i++) {
                    for (int j = 0; j < d; j++) {
                        swap(matrix[i][j], matrix[d - i - 1][j]);
                    }
                }
            }

            
            // 63. Unique Paths II
            // Follow up for "Unique Paths":
            // Now consider if some obstacles are added to the grids.How many unique paths would there be ?
            // An obstacle and empty space is marked as 1 and 0 respectively in the grid.
            // For example,
            // There is one obstacle in the middle of a 3x3 grid as illustrated below.
            // [
            //   [0, 0, 0],
            //   [0, 1, 0],
            //   [0, 0, 0]
            // ]
            // The total number of unique paths is 2.
            // Note: m and n will be at most 100.
            static int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
                int m = obstacleGrid.size();
                int n = obstacleGrid[0].size();
                if (m == 0 || n == 0) return 0;
                vector<vector<int>> grid(obstacleGrid);
                grid[m - 1][n - 1] = (obstacleGrid[m - 1][n - 1] == 0) ? 1 : 0;
                for (int j = n - 2; j >= 0; j--) {
                    grid[m - 1][j] = (obstacleGrid[m - 1][j] == 0) ? grid[m - 1][j + 1] : 0;
                }
                for (int i = m - 2; i >= 0; i--) {
                    grid[i][n - 1] = (obstacleGrid[i][n - 1] == 0) ? grid[i + 1][n - 1] : 0;
                    for (int j = n - 2; j >= 0; j--) {
                        grid[i][j] = (obstacleGrid[i][j] == 0) ? (grid[i + 1][j] + grid[i][j + 1]) : 0;
                    }
                }
                return grid[0][0];
            }

            // 73. Set Matrix Zeroes
            // Given a m x n matrix, if an element is 0, set its entire row and
            // column to 0. Do it in place.
            static void setZeroes(vector<vector<int>>& matrix) {
                if (matrix.size() == 0 || matrix[0].size() == 0) return;
                size_t m = matrix.size();
                size_t n = matrix[0].size();
                bool zeroFirstColumn = false;
                bool zeroFirstRow = false;
                for (size_t i = 0; i < m; i++) {
                    for (size_t j = 0; j < n; j++) {
                        if (matrix[i][j] == 0) {
                            if (i == 0) zeroFirstRow = true;
                            if (j == 0) zeroFirstColumn = true;
                            matrix[i][0] = 0;
                            matrix[0][j] = 0;
                        }
                    }
                }
                for (size_t i = 1; i < m; i++) {
                    if (matrix[i][0] == 0) {
                        for (size_t j = 1; j < n; j++) {
                            matrix[i][j] = 0;
                        }
                    }
                }
                for (size_t j = 1; j < n; j++) {
                    if (matrix[0][j] == 0) {
                        for (size_t i = 1; i < m; i++) {
                            matrix[i][j] = 0;
                        }
                    }
                }
                if (zeroFirstColumn) {
                    for (size_t i = 1; i < m; i++) {
                        matrix[i][0] = 0;
                    }
                }
                if (zeroFirstRow) {
                    for (size_t j = 1; j < n; j++) {
                        matrix[0][j] = 0;
                    }
                }
            }

            // 130. Surrounded Regions
            // Given a 2D board containing 'X' and 'O' (the letter O), capture all
            // regions surrounded by 'X'. A region is captured by flipping all 'O's
            // into 'X's in that surrounded region.
            // For example,
            //    X X X X
            //    X O O X
            //    X X O X
            //    X O X X
            // After running your function, the board should be :
            //    X X X X
            //    X X X X
            //    X X X X
            //    X O X X
            static void solve(vector<vector<char>>& board) {
                size_t m = board.size();
                if (m == 0) return;
                size_t n = board[0].size();
                if (n == 0) return;
                function<void(size_t, size_t)>
                    mark = [&](size_t x, size_t y)
                {
                    if (board[x][y] != 'O') return;
                    board[x][y] = 'Y';
                    if (0 < x) mark(x - 1, y);
                    if (y < n - 1) mark(x, y + 1);
                    if (x < m - 1) mark(x + 1, y);
                    if (0 < y) mark(x, y - 1);
                };
                for (size_t i = 0; i < n; i++) {
                    if (board[0][i] == 'O') mark(0, i);
                    if (m > 1 && board[m - 1][i] == 'O') mark(m - 1, i);
                }
                for (size_t i = 0; i < m; i++) {
                    if (board[i][0] == 'O') mark(i, 0);
                    if (n > 1 && board[i][n - 1] == 'O') mark(i, n - 1);
                }
                for (size_t i = 0; i < m; i++) {
                    for (size_t j = 0; j < n; j++) {
                        if (board[i][j] == 'O') {
                            board[i][j] = 'X';
                        }
                        else if (board[i][j] == 'Y') {
                            board[i][j] = 'O';
                        }
                    }
                }
            }

            // 200. Number of Islands
            // Given a 2d grid map of '1's (land) and '0's (water), count the number
            // of islands. An island is surrounded by water and is formed by connecting
            // adjacent lands horizontally or vertically. You may assume all four
            // edges of the grid are all surrounded by water.
            // Example 1:
            //  11110
            //  11010
            //  11000
            //  00000
            // Answer: 1
            // Example 2:
            //  11000
            //  11000
            //  00100
            //  00011
            // Answer: 3
            static int numIslands(vector<vector<char>>& grid) {
                int m = grid.size();
                if (m == 0) return 0;
                int n = grid[0].size();
                if (n == 0) return 0;
                function<void(int, int)>
                    visit = [&](int i, int j) {
                    if (grid[i][j] == '1') {
                        grid[i][j] = '2';
                        if (i > 0) visit(i - 1, j);
                        if (j < n - 1) visit(i, j + 1);
                        if (i < m - 1) visit(i + 1, j);
                        if (j > 0) visit(i, j - 1);
                    }
                };
                int c = 0;
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        if (grid[i][j] == '1') {
                            c++;
                            visit(i, j);
                        }
                    }
                }
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        if (grid[i][j] != '0') {
                            grid[i][j] = '1';
                        }
                    }
                }
                return c;
            }
        }

        
        // 131. Palindrome Partitioning
        // Given a string s, partition s such that every substring of the partition is a palindrome.
        // Return all possible palindrome partitioning of s.
        // For example, given s = "aab",
        // Return
        // [
        //  ["aa", "b"],
        //  ["a", "a", "b"]
        // ]
        static vector<vector<string>> partition(string s) {
            vector<vector<string>> result;
            if (s.empty()) return result;
            function<bool(size_t, size_t)>
                isPalindrome = [&](size_t i, size_t j) -> bool
            {
                while (i < j) {
                    if (s[i++] != s[j--]) return false;
                }
                return true;
            };
            function<void(size_t, vector<string> &)>
                solve = [&](size_t i, vector<string> & p)
            {
                if (i == s.length()) {
                    result.push_back(p);
                    return;
                }
                for (size_t j = i; j < s.length(); j++) {
                    if (isPalindrome(i, j)) {
                        vector<string> p2(p);
                        p2.push_back(s.substr(i, j - i + 1));
                        solve(j + 1, p2);
                    }
                }
            };
            vector<string> r;
            solve(0, r);
            return result;
        }

        // 133. Clone Graph
        // Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
        // OJ's undirected graph serialization:
        // Nodes are labeled uniquely.
        // We use # as a separator for each node, and, as a separator for node label and each neighbor of the node.
        // As an example, consider the serialized graph{ 0,1,2#1,2#2,2 }.
        // The graph has a total of three nodes, and therefore contains three parts as separated by #.
        // First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
        // Second node is labeled as 1. Connect node 1 to node 2.
        // Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self - cycle.
        // Visually, the graph looks like the following :
        //    1
        //   /  \
        //  /    \
        // 0 -- - 2
        //       / \
        //       \_/
        struct UndirectedGraphNode {
            int label;
            vector<UndirectedGraphNode *> neighbors;
            UndirectedGraphNode(int x) : label(x) {};
        };
        static UndirectedGraphNode *cloneGraph(UndirectedGraphNode * node) {
            map<int, UndirectedGraphNode *> cloned;
            function<UndirectedGraphNode * (UndirectedGraphNode *)>
                clone = [&](UndirectedGraphNode * n) -> UndirectedGraphNode *
            {
                if (node == nullptr) return nullptr;
                if (cloned.find(n->label) != cloned.end()) return cloned[n->label];
                UndirectedGraphNode * copy = new UndirectedGraphNode(n->label);
                cloned[n->label] = copy;
                for (size_t i = 0; i < n->neighbors.size(); i++) {
                    int label = n->neighbors[i]->label;
                    if (cloned.find(label) == cloned.end()) {
                        cloned[label] = clone(n->neighbors[i]);
                    }
                    copy->neighbors.push_back(cloned[label]);
                }
                return copy;
            };
            return clone(node);
        }

        // 134. Gas Station
        // There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
        // You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station
        // i to its next station(i + 1).You begin the journey with an empty tank at one of the gas stations.
        // Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.
        // Note:
        // The solution is guaranteed to be unique.
        static int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
            size_t s = 0;
            while (s < gas.size()) {
                size_t i = s;
                int t = 0;
                size_t j;
                while (t >= 0 && (i - s) < gas.size()) {
                    j = (i++) % gas.size();
                    t += (gas[j] - cost[j]);
                }
                if (t >= 0) return s;
                s = i;
            }
            return -1;
        }

        // 136. Single Number
        // Given an array of integers, every element appears twice except for one. Find that single one.
        // Note:
        // Your algorithm should have a linear runtime complexity.Could you implement it without using extra memory?
        static int singleNumber(vector<int>& nums) {
            int n = 0;
            for_each(nums.begin(), nums.end(), [&](int e) {
                n ^= e;
            });
            return n;
        }

        // 137. Single Number II
        // Given an array of integers, every element appears three times except for one,
        // which appears exactly once. Find that single one.
        // Note:
        // Your algorithm should have a linear runtime complexity.
        // Could you implement it without using extra memory?
        static int singleNumber2(vector<int>& nums) {

        }

        // 138. Copy List with Random Pointer
        // A linked list is given such that each node contains an additional random pointer
        // which could point to any node in the list or null.
        // Return a deep copy of the list.
        static RandomListNode *copyRandomList(RandomListNode *head) {
            map<RandomListNode *, RandomListNode *> copied;
            function<RandomListNode * (RandomListNode *)>
                copy = [&](RandomListNode * node) -> RandomListNode *
            {
                if (node == nullptr) return nullptr;
                RandomListNode * c = new RandomListNode(node->label);
                copied[node] = c;
                if (copied.find(node->next) == copied.end()) {
                    copied[node->next] = copy(node->next);
                }
                c->next = copied[node->next];
                if (copied.find(node->random) == copied.end()) {
                    copied[node->random] = copy(node->random);
                }
                c->random = copied[node->random];
                return c;
            };
            return copy(head);
        }

        // 139. Word Break
        // Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
        // determine if s can be segmented into a space-separated sequence of one or more dictionary words.
        // You may assume the dictionary does not contain duplicate words.
        // For example, given
        // s = "leetcode",
        // dict = ["leet", "code"].
        // Return true because "leetcode" can be segmented as "leet code".
        // Note: Each word in the dictionary can be used more than once.
        // UPDATE(2017 / 1 / 4) :
        // The wordDict parameter had been changed to a list of strings(instead of a set of strings).
        // Please reload the code definition to get the latest changes.
        static bool wordBreak(string s, vector<string>& wordDict) {
            if (wordDict.empty()) return false;
            size_t minLength = wordDict[0].size();
            size_t maxLength = wordDict[0].size();
            for (size_t i = 1; i < wordDict.size(); i++) {
                if (wordDict[i].size() < minLength) minLength = wordDict[i].size();
                if (wordDict[i].size() > maxLength) maxLength = wordDict[i].size();
            }
            map<size_t, bool> breakable;
            function<bool(size_t)>
                solve = [&](size_t i) -> bool
            {
                if (breakable.find(i) != breakable.end()) return breakable[i];
                breakable[i] = false;
                if (i == s.size()) {
                    breakable[i] = true;
                }
                else {
                    for (size_t j = minLength; j <= min(maxLength, s.size() - i); j++) {
                        auto it = find(wordDict.begin(), wordDict.end(), s.substr(i, j));
                        if (it != wordDict.end()) {
                            if (breakable.find(i + j) == breakable.end()) {
                                breakable[i + j] = solve(i + j);
                            }
                            if (breakable[i + j]) {
                                breakable[i] = true;
                                break;
                            }
                        }
                    }
                }
                return breakable[i];
            };
            return solve(0);
        }

        // 150. Evaluate Reverse Polish Notation
        // Evaluate the value of an arithmetic expression in Reverse Polish
        // Notation.
        // Valid operators are + , -, *, /. Each operand may be an integer or
        // another expression.
        // Some examples :
        // ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
        // ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
        static int evalRPN(vector<string>& tokens) {
            int n1;
            int n2;
            stack<int> nums;
            function<void(int &, int &)>
                pop = [&](int & m1, int & m2) {
                m2 = nums.top();
                nums.pop();
                m1 = nums.top();
                nums.pop();
            };
            for (size_t i = 0; i < tokens.size(); i++) {
                if (tokens[i].compare("+") == 0) {
                    pop(n1, n2);
                    nums.push(n1 + n2);
                }
                else if (tokens[i].compare("-") == 0) {
                    pop(n1, n2);
                    nums.push(n1 - n2);
                }
                else if (tokens[i].compare("*") == 0) {
                    pop(n1, n2);
                    nums.push(n1 * n2);
                }
                else if (tokens[i].compare("/") == 0) {
                    pop(n1, n2);
                    nums.push(n1 / n2);
                }
                else {
                    nums.push(atoi(tokens[i].c_str()));
                }
            }
            return nums.top();
        }

        // 152. Maximum Product Subarray
        // Find the contiguous subarray within an array (containing at least
        // one number) which has the largest product.
        // For example, given the array[2, 3, -2, 4],
        // the contiguous subarray[2, 3] has the largest product = 6.
        static int maxProduct(vector<int>& nums) {
            long long maxProd = LLONG_MIN;
            vector<long long> product(nums.begin(), nums.end());
            for (size_t l = 1; l <= nums.size(); l++) {
                for (size_t i = 0; i <= nums.size() - l; i++) {
                    if (l > 1) {
                        product[i] *= nums[i + l - 1];
                    }
                    maxProd = max(product[i], maxProd);
                }
            }
            return (int)maxProd;
        }
        // 
        static int maxProduct2(vector<int>& nums) {
            long long maxNegative = LLONG_MIN;
            long long maxProd = LLONG_MIN;
            long long prod = 1;
            for (size_t i = 0; i < nums.size(); i++) {
                prod *= nums[i];
                if (prod < 0) {
                    if (maxNegative == LLONG_MIN) {
                        maxProd = max(maxProd, prod);
                    }
                    else {
                        maxProd = max(maxProd, prod / maxNegative);
                    }
                    maxNegative = max(maxNegative, prod);
                }
                else if (prod > 0) {
                    maxProd = max(maxProd, prod);
                }
                else {
                    maxProd = max(maxProd, prod);
                    maxNegative = LLONG_MIN;
                    prod = 1;
                }
            }
            return (int)maxProd;
        }

        // 153. Find Minimum in Rotated Sorted Array
        // Suppose an array sorted in ascending order is rotated at some
        // pivot unknown to you beforehand.
        // (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
        // Find the minimum element.
        // You may assume no duplicate exists in the array.
        static int findMin(vector<int>& nums) {
            int l = 0;
            int h = nums.size() - 1;
            int m;
            while (l <= h) {
                m = l + ((h - l) >> 1);
                if (nums[l] < nums[m]) {
                    if (nums[m] < nums[h]) {
                        h = m - 1;
                    }
                    else {
                        l = m + 1;
                    }
                }
                else if (nums[l] > nums[m]) {
                    h = m;
                }
                else {
                    if (nums[m] < nums[h]) {
                        h = m;
                    }
                    else if (nums[m] > nums[h]) {
                        l = m + 1;
                    }
                    else {
                        return nums[m];
                    }
                }
            }
        }

        namespace String {

            // 28. Implement strStr()
            // Returns the index of the first occurrence of needle in haystack,
            // or -1 if needle is not part of haystack.
            static int strStr(string haystack, string needle)
            {
                if (needle.empty()) return 0;
                size_t i = 0;
                while (i + needle.size() <= haystack.size()) {
                    while (i + needle.size() <= haystack.size()
                        && haystack[i] != needle[0]) {
                        i++;
                    }
                    if (i + needle.size() > haystack.size()) break;
                    size_t j = 1;
                    while (j < needle.size() && haystack[i + j] == needle[j]) j++;
                    if (j == needle.size()) return i;
                    i++;
                }
                return -1;
            }

            // 38. Count and Say
            // The count-and-say sequence is the sequence of integers beginning
            // as follows:
            // 1, 11, 21, 1211, 111221, ...
            // 1 is read off as "one 1" or 11.
            // 11 is read off as "two 1s" or 21.
            // 21 is read off as "one 2, then one 1" or 1211.
            // Given an integer n, generate the nth sequence.
            // Note: The sequence of integers will be represented as a string.
            static string countAndSay(int n)
            {
                if (n <= 0) return string();
                string s = "1";
                for (int i = 2; i <= n; i++)
                {
                    ostringstream oss;
                    size_t j = 0;
                    size_t c = 1;
                    while (j < s.size())
                    {
                        while (j + 1 < s.size() && s[j] == s[j + 1])
                        {
                            j++;
                            c++;
                        }
                        oss << c << s[j];
                        j++;
                        c = 1;
                    }
                    s = oss.str();
                }
                return s;
            }

            // 43. Multiply Strings
            // Given two non-negative integers num1 and num2 represented as
            // strings, return the product of num1 and num2.
            // Note:
            // The length of both num1 and num2 is < 110.
            // Both num1 and num2 contains only digits 0 - 9.
            // Both num1 and num2 does not contain any leading zero.
            // You must not use any built-in BigInteger library or convert the
            // inputs to integer directly.
            static string multiply(string num1, string num2) {
                if (num1.length() == 1 && num1[0] == '0') return string("0");
                if (num2.length() == 1 && num2[0] == '0') return string("0");
                function<int(char)> toDigit = [&](char c)
                {
                    return c - '0';
                };
                function<char(int)> toChar = [&](int i)
                {
                    return i + '0';
                };
                function<string(string, char)> multiplyDigit = [&](string str, char ch)
                {
                    string result;
                    int i = str.length() - 1;
                    int c = 0;
                    int m;
                    while (0 <= i) {
                        m = c + toDigit(str[i--]) * toDigit(ch);
                        c = m / 10;
                        result.insert(result.begin(), toChar(m % 10));
                    }
                    if (c > 0) {
                        result.insert(result.begin(), toChar(c));
                    }
                    return result;
                };
                function<string(string, string)> sum = [&](string str1, string str2)
                {
                    string result;
                    int i = str1.length() - 1;
                    int j = str2.length() - 1;
                    int c = 0;
                    int m;
                    while (0 <= i || 0 <= j)
                    {
                        if (0 <= i && 0 <= j) {
                            m = toDigit(str1[i--]) + toDigit(str2[j--]);
                        }
                        else if (0 <= i) {
                            m = toDigit(str1[i--]);
                        }
                        else {
                            m = toDigit(str2[j--]);
                        }
                        m += c;
                        c = m / 10;
                        result.insert(result.begin(), toChar(m % 10));
                    }
                    if (c > 0) {
                        result.insert(result.begin(), toChar(c));
                    }
                    return result;
                };
                string result = "0";
                char c;
                int i = num2.length() - 1;
                while (0 <= i) {
                    c = num2[i--];
                    if (c != '0') {
                        result = sum(result, multiplyDigit(num1, c));
                    }
                    num1.append(1, '0');
                }
                return result;
            }

            // 49. Group Anagrams
            // Given an array of strings, group anagrams together.
            // For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
            // Return :
            // [
            //   ["ate", "eat", "tea"],
            //   ["nat", "tan"],
            //   ["bat"]
            // ]
            static vector<vector<string>> groupAnagrams(vector<string>& strs)
            {
                vector<vector<string>> result = vector<vector<string>>{};
                map<string, vector<string>> m = map<string, vector<string>>{};
                for_each(strs.begin(), strs.end(), [&](string & s)
                {
                    string k(s);
                    sort(k.begin(), k.end());
                    if (m.find(k) == m.end()) m[k] = vector<string>{};
                    m[k].push_back(s);
                });
                for (map<string, vector<string>>::iterator it = m.begin(); it != m.end(); it++)
                {
                    result.push_back(it->second);
                }
                return result;
            }

            // 127. Word Ladder
            // Given two words (beginWord and endWord), and a dictionary's word list,
            // find the length of shortest transformation sequence from beginWord to endWord, such that:
            // Only one letter can be changed at a time.
            // Each transformed word must exist in the word list. 
            // Note that beginWord is not a transformed word.
            // For example,
            // Given:
            // beginWord = "hit"
            // endWord = "cog"
            // wordList = ["hot", "dot", "dog", "lot", "log", "cog"]
            // As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
            // return its length 5.
            // Note :
            // Return 0 if there is no such transformation sequence.
            // All words have the same length.
            // All words contain only lowercase alphabetic characters.
            // You may assume no duplicates in the word list.
            // You may assume beginWord and endWord are non - empty and are not the same.
            // UPDATE(2017 / 1 / 20) :
            // The wordList parameter had been changed to a list of strings(instead of a set of strings).
            // Please reload the code definition to get the latest changes
            static int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
                function<int(bool, string, vector<string> &)>
                    search = [&](bool transformed, string word, vector<string> & list) -> int
                {
                    vector<string> list2(list);
                    auto it = find(list2.begin(), list2.end(), word);
                    if (it == list2.end()) {
                        if (transformed) return 0;
                    }
                    else {
                        list2.erase(it);
                    }
                    if (word == endWord) return 1;
                    int min = INT_MAX;
                    for (size_t i = 0; i < word.length(); i++) {
                        string word2(word);
                        for (char j = 0; j < 26; j++) {
                            if (word[i] != 'a' + j) {
                                word2[i] = 'a' + j;
                                int m = search(true, word2, list2);
                                if (m > 0 && m < min) {
                                    min = m;
                                }
                            }
                        }
                    }
                    if (min != INT_MAX) return min + 1;
                    else return 0;
                };
                return search(false, beginWord, wordList);
            }


            // 151. Reverse Words in a String
            // Given an input string, reverse the string word by word.
            // For example,
            // Given s = "the sky is blue",
            // return "blue is sky the".
            // Update(2015-02-12):
            // For C programmers: Try to solve it in-place in O(1) space.
            // Clarification:
            // What constitutes a word?
            // A sequence of non-space characters constitutes a word.
            // Could the input string contain leading or trailing spaces?
            // Yes. However, your reversed string should not contain leading or
            // trailing spaces.
            // How about multiple spaces between two words?
            // Reduce them to a single space in the reversed string.
            static void reverseWords(string &s) {
                if (s.length() == 0) return;
                int i = -1;
                size_t j = 0;
                while (j < s.length() && s[j] == ' ') j++;
                if (j == s.length()) {
                    s.resize(0);
                    return;
                }
                while (j < s.length()) {
                    if (s[j] != ' ' || s[j - 1] != ' ') {
                        i++;
                        if (i < (int)j) s[i] = s[j];
                    }
                    j++;
                }
                if (0 <= i && s[i] == ' ') i--;
                s.resize(i + 1);
                function<void(int, int)>
                    reverse = [&](int b, int e) {
                    while (b < e) {
                        swap(s[b++], s[e--]);
                    }
                };
                reverse(0, s.length() - 1);
                i = 0;
                j = 0;
                while (j <= s.length()) {
                    if (j == s.length() || s[j] == ' ') {
                        reverse(i, j - 1);
                        i = j + 1;
                    }
                    j++;
                }
            }

            // 165. Compare Version Numbers
            // Compare two version numbers version1 and version2.
            // If version1 > version2 return 1, if version1 < version2 return -1,
            // otherwise return 0.
            // You may assume that the version strings are non-empty and contain only
            // digits and the . character.
            // The . character does not represent a decimal point and is used to
            // separate number sequences. For instance, 2.5 is not "two and a half"
            // or "half way to version three", it is the fifth second-level
            // revision of the second first-level revision.
            // Here is an example of version numbers ordering:
            // 0.1 < 1.1 < 1.2 < 13.37
            static int compareVersion(string version1, string version2) {
                function<int(const string &, size_t &)>
                    version = [&](const string & str, size_t & i) -> int {
                    int val = 0;
                    while (i < str.size() && str[i] == '.') i++;
                    if (i >= str.size()) return val;
                    size_t j = str.find_first_of('.', i);
                    if (j == string::npos) {
                        val = atoi(str.substr(i).c_str());
                        i = str.size();
                    }
                    else {
                        val = atoi(str.substr(i, j - i).c_str());
                        i = j;
                    }
                    return val;
                };
                size_t i1 = 0;
                size_t i2 = 0;
                int v1;
                int v2;
                while (i1 < version1.size() || i2 < version2.size()) {
                    v1 = version(version1, i1);
                    v2 = version(version2, i2);
                    if (v1 < v2) return -1;
                    else if (v1 > v2) return 1;
                }
                return 0;
            }

            // 187. Repeated DNA Sequences
            // All DNA is composed of a series of nucleotides abbreviated as A, C, G,
            // and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes
            // useful to identify repeated sequences within the DNA.
            // Write a function to find all the 10-letter-long sequences(substrings)
            // that occur more than once in a DNA molecule.
            // For example,
            // Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
            // Return: ["AAAAACCCCC", "CCCCCAAAAA"].
            static vector<string> findRepeatedDnaSequences(string s) {

            }
        }

        namespace Numeric {

            // 29. Divide Two Integers
            // Divide two integers without using multiplication, division and mod
            // operator. If it is overflow, return MAX_INT.
            static int divide(int dividend, int divisor)
            {
                if (divisor == 0 || dividend == INT_MIN && divisor == -1) {
                    return INT_MAX;
                }
                bool negative = false;
                // use long in case of overflow when fliping the sign
                long longDividend = (long)dividend;
                long longDivisor = (long)divisor;
                if (longDividend < 0) {
                    longDividend = -longDividend;
                    if (longDivisor < 0) longDivisor = -longDivisor;
                    else negative = true;
                }
                else if (longDivisor < 0) {
                    longDivisor = -longDivisor;
                    negative = true;
                }
                int quotient = 0;
                // use long in case of overflow when left shift by 1
                long d = longDivisor;
                int m = 1;
                while (longDividend >= longDivisor) {
                    if (d <= longDividend && longDividend < d << 1) {
                        quotient += m;
                        longDividend -= d;
                    }
                    else if (longDividend < d) {
                        d = d >> 1;
                        m = m >> 1;
                    }
                    else { // d << 1 <= longDividend
                        d = d << 1;
                        m = m << 1;
                    }
                }
                return negative ? -quotient : quotient;
            }

            // 50. Pow(x, n)
            static double myPow(double x, int n) {
                long long n1 = n; // Use long long to avoid overflow when flip the sign.
                bool inverse = false;
                if (n1 < 0) {
                    inverse = true;
                    n1 = -n1;
                }
                long long d; // Use long long to avoid overflow when left-shift the bits.
                double y;
                double z = 1;
                while (n1 > 0) {
                    d = 1;
                    y = x;
                    while ((d << 1) <= n1) {
                        y *= y;
                        d = d << 1;
                    }
                    z *= y;
                    n1 -= d;
                }
                return inverse ? 1 / z : z;
            }

            // 69. Sqrt(x)
            // Implement int sqrt(int x).
            // Compute and return the square root of x.
            static int mySqrt(int x) {
                long long l = 0;
                long long r = x;
                long long m; // Use long long to avoid overflow of m * m.
                while (l <= r) {
                    m = l + ((r - l) >> 1);
                    long long low = m * m;
                    long long high = (m + 1) * (m + 1);
                    if (low <= x && x < high) {
                        break;
                    }
                    else if (x < low) {
                        r = m - 1;
                    }
                    else {
                        l = m + 1;
                    }
                }
                return (int)m;
            }

            // 166. Fraction to Recurring Decimal
            // Given two integers representing the numerator and denominator of a
            // fraction, return the fraction in string format.
            // If the fractional part is repeating, enclose the repeating part in
            // parentheses.
            // For example,
            // Given numerator = 1, denominator = 2, return "0.5".
            // Given numerator = 2, denominator = 1, return "2".
            // Given numerator = 2, denominator = 3, return "0.(6)".
            static string fractionToDecimal(int numerator, int denominator) {
                // Suffix tree to find repeating parts?
            }

            // 168. Excel Sheet Column Title
            // Given a positive integer, return its corresponding column title as
            // appear in an Excel sheet.
            // For example :
            // 1 -> A
            // 2 -> B
            // 3 -> C
            //   ...
            // 26 -> Z
            // 27 -> AA
            // 28 -> AB
            static string convertToTitle(int n) {
                string e;
                while (n > 0) {
                    int r = n % 26;
                    n = (n - r) / 26;
                    if (r == 0) {
                        r = 26;
                        n--;
                    }
                    e.insert(e.begin(), 'A' + r - 1);
                }
                return e;
            }

            // 171. Excel Sheet Column Number
            // Related to question Excel Sheet Column Title
            // Given a column title as appear in an Excel sheet, return its
            // corresponding column number.
            // For example :
            // A -> 1
            // B -> 2
            // C -> 3
            //   ...
            // Z -> 26
            // AA -> 27
            // AB -> 28
            static int titleToNumber(string s) {
                int n = 0;
                for (size_t i = 0; i < s.length(); i++) {
                    n *= 26;
                    n += (s[i] - 'A' + 1);
                }
                return n;
            }

            // 172. Factorial Trailing Zeroes
            // Given an integer n, return the number of trailing zeroes in n!.
            // Note: Your solution should be in logarithmic time complexity.
            static int trailingZeroes(int n) {
                // n! = 1 * 2 * 3 * 4 * 5 * ... * 10 * ... * 15 * ... * n
                //    = 2^x * 5^y * z
                // Usually x >= y. So just need to count occurrence of 5.
                int c = 0;
                while (n >= 5) {
                    n /= 5;
                    c += n;
                }
                return c;
            }

            // 179. Largest Number
            // Given a list of non negative integers, arrange them such that they
            // form the largest number.
            // For example, given [3, 30, 34, 5, 9], the largest formed number is
            // 9534330.
            // Note: The result may be very large, so you need to return a string
            // instead of an integer.
            static string largestNumber(vector<int>& nums) {
                vector<string> strs;
                strs.resize(nums.size());
                transform(nums.begin(), nums.end(), strs.begin(), [&](int i) {
                    ostringstream oss;
                    oss << i;
                    return oss.str();
                });
                sort(strs.begin(), strs.end(),
                    [&](const string & str1, const string & str2) {
                    string str12(str1);
                    str12.append(str2);
                    string str21(str2);
                    str21.append(str1);
                    return str12.compare(str21) > 0;
                });
                string result;
                if (strs[0] == "0") {
                    result = "0";
                }
                else {
                    for_each(strs.begin(), strs.end(), [&](const string & str) {
                        result.append(str);
                    });
                }
                return result;
            }

            // 190. Reverse Bits
            // Reverse bits of a given 32 bits unsigned integer.
            // For example, given input 43261596 (represented in binary as
            // 00000010100101000001111010011100), return 964176192 (represented
            // in binary as 00111001011110000010100101000000).
            // Follow up: If this function is called many times, how would you
            // optimize it?
            static uint32_t reverseBits(uint32_t n) {
                n = (n & 0x55555555) << 1 | (n & 0xaaaaaaaa) >> 1;
                n = (n & 0x33333333) << 2 | (n & 0xcccccccc) >> 2;
                n = (n & 0x0f0f0f0f) << 4 | (n & 0xf0f0f0f0) >> 4;
                n = (n & 0x00ff00ff) << 8 | (n & 0xff00ff00) >> 8;
                n = (n & 0x0000ffff) << 16 | (n & 0xffff0000) >> 16;
                return n;
            }

            // 191. Number of 1 Bits
            // Write a function that takes an unsigned integer and returns the
            // number of ’1' bits it has (also known as the Hamming weight).
            // For example, the 32-bit integer ’11' has binary representation
            // 00000000000000000000000000001011, so the function should return 3.
            static int hammingWeight(uint32_t n) {
                int h = 0;
                while (n != 0) {
                    n &= (n - 1);
                    h++;
                }
                return h;
            }

            // 201. Bitwise AND of Numbers Range
            // Given a range [m, n] where 0 <= m <= n <= 2147483647, return the
            // bitwise AND of all numbers in this range, inclusive.
            // For example, given the range[5, 7], you should return 4.
            static int rangeBitwiseAnd(int m, int n) {
                int x = 0;
                while (m != n) {
                    m >>= 1;
                    n >>= 1;
                    x++;
                }
                return m << x;
            }

            // 202. Happy Number
            // Write an algorithm to determine if a number is "happy".
            // A happy number is a number defined by the following process: Starting
            // with any positive integer, replace the number by the sum of the squares
            // of its digits, and repeat the process until the number equals 1 (where
            // it will stay), or it loops endlessly in a cycle which does not include
            // 1. Those numbers for which this process ends in 1 are happy numbers.
            // Example: 19 is a happy number
            //  1^2 + 9^2 = 82
            //  8^2 + 2^2 = 68
            //  6^2 + 8^2 = 100
            //  1^2 + 0^2 + 0^2 = 1
            static bool isHappy(int n) {
                int x = n;
                cout << n;
                do {
                    int y = 0;
                    while (x > 0) {
                        int r = x % 10;
                        y += (r * r);
                        x /= 10;
                    }
                    x = y;
                    cout << ", " << x;
                } while (x != n && x != 1);
                return x == 1;
            }
        }
        namespace SingleLinkList {

            // 61. Rotate List
            // Given a list, rotate the list to the right by k places, where k is
            // non-negative. For example :
            // Given 1->2->3->4->5->NULL and k = 2,
            // return 4->5->1->2->3->NULL.
            static ListNode* rotateRight(ListNode* head, int k) {
                if (head == nullptr) return head;
                ListNode * tail = head;
                int i = 1;
                while (tail->next != nullptr) {
                    i++;
                    tail = tail->next;
                }
                k %= i;
                if (k == 0) return head;
                int j = i - k;
                ListNode * p = head;
                while (j > 1) {
                    p = p->next;
                    j--;
                }
                tail->next = head;
                head = p->next;
                p->next = nullptr;
                return head;
            }

            // 82. Remove Duplicates from Sorted List II
            // Given a sorted linked list, delete all nodes that have duplicate numbers,
            // leaving only distinct numbers from the original list.
            // For example,
            // Given 1->2->3->3->4->4->5, return 1->2->5.
            // Given 1->1->1->2->3, return 2->3.
            static ListNode* deleteDuplicates2(ListNode* head) {
                ListNode * prev = nullptr;
                ListNode * p = head;
                ListNode * next = nullptr;
                while (p != nullptr) {
                    if (p->next != nullptr && p->val == p->next->val) {
                        int v = p->val;
                        while (p != nullptr && p->val == v) {
                            next = p->next;
                            delete p;
                            p = next;
                        }
                        if (prev == nullptr) {
                            head = p;
                        }
                        else {
                            prev->next = p;
                        }
                    }
                    else {
                        if (prev == nullptr) {
                            head = p;
                        }
                        else {
                            prev->next = p;
                        }
                        prev = p;
                        p = p->next;
                    }
                }
                return head;
            }

            // 83. Remove Duplicates from Sorted List
            // Given a sorted linked list, delete all duplicates such that each element appear only once.
            // For example,
            // Given 1->1->2, return 1->2.
            // Given 1->1->2->3->3, return 1->2->3.
            static ListNode* deleteDuplicates(ListNode* head) {
                ListNode * p = head;
                while (p != nullptr) {
                    if (p->next != nullptr && p->val == p->next->val) {
                        ListNode * n = p->next;
                        p->next = n->next;
                        delete n;
                    }
                    else {
                        p = p->next;
                    }
                }
                return head;
            }

            // 86. Partition List
            // Given a linked list and a value x, partition it such that all nodes less than x
            // come before nodes greater than or equal to x.
            // You should preserve the original relative order of the nodes in each of the two partitions.
            // For example,
            // Given 1->4->3->2->5->2 and x = 3,
            // return 1->2->2->4->3->5.
            static ListNode* partition(ListNode* head, int x) {
                if (head == nullptr) return head;
                ListNode * prev = nullptr;
                ListNode * p = head;
                if (p->val < x) {
                    prev = p;
                }
                while (p->next != nullptr) {
                    if (p->next->val < x) {
                        if (prev == p) {
                            prev = p->next;
                            p = p->next;
                        }
                        else {
                            ListNode * next = p->next;
                            p->next = next->next;
                            if (prev == nullptr) {
                                next->next = head;
                                head = next;
                                prev = next;
                            }
                            else {
                                next->next = prev->next;
                                prev->next = next;
                                prev = next;
                            }
                        }
                    }
                    else {
                        p = p->next;
                    }
                }
                return head;
            }

            // 92. Reverse Linked List II
            // Reverse a linked list from position m to n. Do it in-place and in one-pass.
            // For example :
            // Given 1->2->3->4->5->NULL, m = 2 and n = 4,
            // return 1->4->3->2->5->NULL.
            // Note :
            // Given m, n satisfy the following condition :
            // 1 �� m �� n �� length of list.
            static ListNode* reverseBetween(ListNode* head, int m, int n) {
                if (head == nullptr) return nullptr;
                ListNode * pm_prev = nullptr;
                ListNode * pm = nullptr;
                int i;
                if (m == 1) {
                    pm = head;
                }
                else {
                    pm_prev = head;
                    i = 1;
                    while (i < m - 1 && pm_prev->next != nullptr) {
                        pm_prev = pm_prev->next;
                        i++;
                    }
                    if (i < m - 1) return head;
                    pm = pm_prev->next;
                }
                ListNode * pn = pm;
                i = m;
                while (i < n && pn->next != nullptr) {
                    pn = pn->next;
                    i++;
                }
                ListNode * pn_next = pn->next;
                ListNode * prev = pn_next;
                ListNode * curr = pm;
                ListNode * next = pm->next;
                while (curr != pn) {
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                    next = curr->next;
                }
                curr->next = prev;
                if (pm_prev == nullptr) {
                    head = pn;
                }
                else {
                    pm_prev->next = pn;
                }
                return head;
            }
            // static ListNode* reverseBetween_2(ListNode* head, int m, int n) {
            // Should just reverse each node while searching for pn
            // }

            namespace Cycle {
                // 141. Linked List Cycle
                // Given a linked list, determine if it has a cycle in it.
                // Follow up: Can you solve it without using extra space?
                static bool hasCycle(ListNode *head) {
                    if (head == nullptr) return false;
                    ListNode * p1 = head;
                    ListNode * p2 = head;
                    while (p2 != nullptr && p2->next != nullptr) {
                        p1 = p1->next;
                        p2 = p2->next->next;
                        if (p1 == p2) return true;
                    }
                    return false;
                }

                // 142. Linked List Cycle II
                // Given a linked list, return the node where the cycle begins.
                // If there is no cycle, return null.
                // Note: Do not modify the linked list.
                // Follow up: Can you solve it without using extra space?
                static ListNode *detectCycle(ListNode *head) {
                    ListNode * p1 = head;
                    ListNode * p2 = head;
                    while (p2 != nullptr && p2->next != nullptr) {
                        p1 = p1->next;
                        p2 = p2->next->next;
                        if (p1 == p2) break;
                    }
                    if (p2 == nullptr || p2->next == nullptr) return nullptr;
                    p1 = head;
                    while (p1 != p2) {
                        p1 = p1->next;
                        p2 = p2->next;
                    }
                    return p1;
                }
            }
            // 143. Reorder List
            // Given a singly linked list L: L0->L1->...->Ln-1->Ln,
            // reorder it to : L0->Ln->L1->Ln-1->L2->Ln-2->...
            // You must do this in-place without altering the nodes' values.
            // For example,
            // Given{ 1,2,3,4 }, reorder it to{ 1,4,2,3 }.
            static void reorderList(ListNode* head) {
                if (head == nullptr) return;
                ListNode * first = head;
                ListNode * second = head;
                while (second != nullptr && second->next != nullptr) {
                    first = first->next;
                    second = second->next->next;
                }
                ListNode * tail = first;
                ListNode * head2 = tail->next;
                tail->next = nullptr;
                if (head2 == nullptr) return;
                ListNode * prev = nullptr;
                ListNode * middle = head2;
                ListNode * next = middle->next;
                while (next != nullptr) {
                    middle->next = prev;
                    prev = middle;
                    middle = next;
                    next = middle->next;
                }
                middle->next = prev;
                head2 = middle;
                first = head;
                while (head2 != nullptr) {
                    second = head2;
                    head2 = second->next;
                    second->next = first->next;
                    first->next = second;
                    first = second->next;
                }
            }

            // 147. Insertion Sort List
            // Sort a linked list using insertion sort.
            static ListNode* insertionSortList(ListNode* head) {
                if (head == nullptr || head->next == nullptr) return head;
                ListNode * p = head;
                while (p->next != nullptr) {
                    if (p->val <= p->next->val) {
                        p = p->next;
                    }
                    else {
                        ListNode * q = p->next;
                        p->next = q->next;
                        q->next = nullptr;
                        if (q->val < head->val) {
                            q->next = head;
                            head = q;
                        }
                        else {
                            ListNode * s = head;
                            while (s != p
                                && s->next != nullptr
                                && s->next->val <= q->val) {
                                s = s->next;
                            }
                            q->next = s->next;
                            s->next = q;
                        }
                    }
                }
                return head;
            }

            // 148. Sort List
            // Sort a linked list in O(nlogn) time using constant space complexity.
            static ListNode* sortList(ListNode* head) {
                if (head == nullptr || head->next == nullptr) return head;
                function<ListNode * (ListNode *, ListNode *)>
                    merge = [&](ListNode * l1, ListNode * l2) -> ListNode * {
                    if (l1 == nullptr) return l2;
                    if (l2 == nullptr) return l1;
                    ListNode * h = nullptr;
                    if (l1->val <= l2->val) {
                        h = l1;
                        l1 = l1->next;
                    }
                    else {
                        h = l2;
                        l2 = l2->next;
                    }
                    ListNode * p = h;
                    while (l1 != nullptr && l2 != nullptr) {
                        if (l1->val <= l2->val) {
                            p->next = l1;
                            l1 = l1->next;
                        }
                        else {
                            p->next = l2;
                            l2 = l2->next;
                        }
                        p = p->next;
                    }
                    p->next = l1 == nullptr ? l2 : l1;
                    return h;
                };
                function<ListNode * (ListNode *)>
                    sort = [&](ListNode * h) -> ListNode * {
                    if (h == nullptr || h->next == nullptr) return h;
                    ListNode * p = h;
                    ListNode * q = h->next;
                    while (q != nullptr && q->next != nullptr) {
                        p = p->next;
                        q = q->next->next;
                    }
                    q = p->next;
                    p->next = nullptr;
                    p = sort(h);
                    q = sort(q);
                    p = merge(p, q);
                    return p;
                };
                return sort(head);
            }

            // 160. Intersection of Two Linked Lists
            // Write a program to find the node at which the intersection of two
            // singly linked lists begins.
            // For example, the following two linked lists :
            // A:        a1 -> a2
            //                   \
            //                    >
            //                     c1 -> c2 -> c3
            //                    >
            //                   /
            // B : b1 -> b2 -> b3
            // begin to intersect at node c1.
            // Notes :
            // If the two linked lists have no intersection at all, return null.
            // The linked lists must retain their original structure after the
            // function returns.
            // You may assume there are no cycles anywhere in the entire linked
            // structure.
            // Your code should preferably run in O(n) time and use only O(1) memory.
            static ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
                function<int(ListNode *)>
                    getLength = [&](ListNode * h) -> int {
                    int i = 0;
                    while (h != nullptr) {
                        i++;
                        h = h->next;
                    }
                    return i;
                };
                function<ListNode * (ListNode *, int)>
                    advance = [&](ListNode * h, int n) -> ListNode * {
                    while (n > 0) {
                        h = h->next;
                        n--;
                    }
                    return h;
                };
                int la = getLength(headA);
                int lb = getLength(headB);
                ListNode * pa = headA;
                ListNode * pb = headB;
                if (la > lb) pa = advance(pa, la - lb);
                else pb = advance(pb, lb - la);
                while (pa != pb) {
                    pa = pa->next;
                    pb = pb->next;
                }
                return pa;
            }
            static ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB) {
                ListNode * pa = headA;
                ListNode * pb = headB;
                while (pa != nullptr && pb != nullptr && pa != pb) {
                    pa = pa->next;
                    pb = pb->next;
                    if (pa == pb) break;
                    if (pa == nullptr) pa = headB;
                    if (pb == nullptr) pb = headA;
                }
                return pa == pb ? pa : nullptr;
            }
        }

        namespace BinaryTree {
            //
            // Binary Tree
            //

            // 94. Binary Tree Inorder Traversal
            // Given a binary tree, return the inorder traversal of its nodes'
            // values.
            // For example :
            // Given binary tree[1, null, 2, 3],
            //   1
            //    \
            //     2
            //    /
            //   3
            // return[1, 3, 2].
            // Note: Recursive solution is trivial, could you do it iteratively?
            static vector<int> inorderTraversal(TreeNode* root) {
                stack<TreeNode *> path;
                TreeNode * node = root;
                vector<int> result;
                while (!path.empty() || node != nullptr) {
                    if (node != nullptr) {
                        path.push(node);
                        node = node->left;
                    }
                    else {
                        node = path.top();
                        path.pop();
                        result.push_back(node->val);
                        node = node->right;
                    }
                }
                return result;
            }
            static vector<int> inorderTraversal_2(TreeNode* root) {
                if (root == nullptr) return vector<int>{};
                stack<TreeNode *> path;
                TreeNode * lastVisited = nullptr;
                path.push(root);
                TreeNode * node;
                vector<int> result;
                while (!path.empty()) {
                    node = path.top();
                    if (node->right != nullptr && node->right == lastVisited) {
                        path.pop();
                        lastVisited = node;
                    }
                    else if (node->left != nullptr && node->left != lastVisited) {
                        path.push(node->left);
                        lastVisited = node;
                    }
                    else {
                        result.push_back(node->val);
                        lastVisited = node;
                        if (node->right != nullptr) {
                            path.push(node->right);
                        }
                        else {
                            path.pop();
                        }
                    }
                }
                return result;
            }

            // 95. Unique Binary Search Trees II
            // Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.
            // For example,
            // Given n = 3, your program should return all 5 unique BST's shown below.
            //  1         3     3      2      1
            //   \       /     /      / \      \
            //    3     2     1      1   3      2
            //   /     /       \                 \
            //  2     1         2                 3
            static vector<TreeNode*> generateTrees(int n) {
                if (n <= 0) return vector<TreeNode *>{};
                function<vector<vector<int>>(int, int)>
                    generateSerializations = [&](int i, int j) -> vector<vector<int>>
                {
                    vector<vector<int>> serializations;
                    if (i > j) {
                        serializations.push_back(vector<int> { 0 });
                    }
                    else {
                        for (int k = i; k <= j; k++) {
                            vector<vector<int>> leftSerializations = generateSerializations(i, k - 1);
                            vector<vector<int>> rightSerializations = generateSerializations(k + 1, j);
                            for (size_t l = 0; l < leftSerializations.size(); l++) {
                                for (size_t r = 0; r < rightSerializations.size(); r++) {
                                    vector<int> serialization = { k };
                                    serialization.insert(serialization.end(), leftSerializations[l].begin(), leftSerializations[l].end());
                                    serialization.insert(serialization.end(), rightSerializations[r].begin(), rightSerializations[r].end());
                                    serializations.push_back(serialization);
                                }
                            }
                        }
                    }
                    return serializations;
                };
                function<TreeNode *(size_t & i, vector<int> &)>
                    generateTree = [&](size_t & i, vector<int> & serialization) -> TreeNode *
                {
                    if (i >= serialization.size()) return nullptr;
                    if (serialization[i] == 0) {
                        i++;
                        return nullptr;
                    }
                    TreeNode * node = new TreeNode(serialization[i++]);
                    node->left = generateTree(i, serialization);
                    node->right = generateTree(i, serialization);
                    return node;
                };
                vector<vector<int>> serializations = generateSerializations(1, n);
                vector<TreeNode *> trees;
                for (size_t i = 0; i < serializations.size(); i++) {
                    size_t j = 0;
                    trees.push_back(generateTree(j, serializations[i]));
                }
                return trees;
            }
            // incomplete
            static vector<TreeNode*> generateTrees_2(int n) {
                if (n <= 0) return vector<TreeNode *>{};
                function<vector<TreeNode *>(int, int)>
                    solve = [&](int i, int j) -> vector<TreeNode *>
                {
                    if (i > j) {
                        return vector<TreeNode *>{ nullptr };
                    }
                    if (i == j) {
                        return vector<TreeNode *>{ new TreeNode(i) };
                    }
                    for (int k = i; k <= j; k++) {
                        vector<TreeNode *> leftChildren = solve(i, k - 1);
                        vector<TreeNode *> rightChildren = solve(k + 1, j);
                    }
                };
                return vector<TreeNode *>{};
            }

            // 96. Unique Binary Search Trees
            // Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
            // For example,
            // Given n = 3, there are a total of 5 unique BST's.
            // 1         3     3      2      1
            //  \       /     /      / \      \
            //   3     2     1      1   3      2
            //  /     /       \                 \
            // 2     1         2                 3
            static int numTrees(int n) {
                if (n <= 0) return 0;
                map<pair<int, int>, int> solved;
                function<int(int, int)>
                    count = [&](int i, int j) -> int
                {
                    if (i >= j) return 1;
                    pair<int, int> p = make_pair(i, j);
                    if (solved.find(p) != solved.end()) return solved[p];
                    int c = 0;
                    for (int k = i; k <= j; k++) {
                        c += (count(i, k - 1) * count(k + 1, j));
                    }
                    solved[p] = c;
                    return c;
                };
                return count(1, n);
            }

            // 98. Validate Binary Search Tree
            // Given a binary tree, determine if it is a valid binary search tree (BST).
            // Assume a BST is defined as follows :
            // The left subtree of a node contains only nodes with keys less than the node's key.
            // The right subtree of a node contains only nodes with keys greater than the node's key.
            // Both the left and right subtrees must also be binary search trees.
            // Example 1 :
            //   2
            //  / \
            // 1   3
            // Binary tree[2, 1, 3], return true.
            // Example 2:
            //   1
            //  / \
            // 2   3
            // Binary tree[1, 2, 3], return false.
            static bool isValidBST(TreeNode* root) {
                stack<TreeNode *> path;
                TreeNode * node = root;
                TreeNode * prev = nullptr;
                while (!path.empty() || node != nullptr) {
                    if (node != nullptr) {
                        path.push(node);
                        node = node->left;
                    }
                    else {
                        node = path.top();
                        path.pop();
                        if (prev != nullptr && prev->val >= node->val) return false;
                        prev = node;
                        node = node->right;
                    }
                }
                return true;
            }

            // 100. Same Tree
            // Given two binary trees, write a function to check if they are equal or not.
            // Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
            static bool isSameTree(TreeNode* p, TreeNode* q) {
                function<bool(TreeNode *, TreeNode *)>
                    isSame = [&](TreeNode * node1, TreeNode * node2) -> bool
                {
                    if (node1 == nullptr && node2 == nullptr) return true;
                    if (node1 == nullptr || node2 == nullptr) return false;
                    if (node1->val != node2->val) return false;
                    if (!isSame(node1->left, node2->left)) return false;
                    return isSame(node1->right, node2->right);
                };
                return isSame(p, q);
            }

            // 101. Symmetric Tree
            // Given a binary tree, check whether it is a mirror of itself(ie, symmetric around its center).
            // For example, this binary tree[1, 2, 2, 3, 4, 4, 3] is symmetric :
            //     1
            //    / \
            //   2   2
            //  / \ / \
            // 3  4 4  3
            // But the following[1, 2, 2, null, 3, null, 3] is not:
            //   1
            //  / \
            // 2   2
            //  \   \
            //   3   3
            // Note:
            // Bonus points if you could solve it both recursively and iteratively.
            static bool isSymmetric(TreeNode* root) {
                function<bool(TreeNode *, TreeNode *)>
                    isSame = [&](TreeNode * node1, TreeNode * node2) -> bool
                {
                    if (node1 == nullptr && node2 == nullptr) return true;
                    if (node1 == nullptr || node2 == nullptr) return false;
                    if (node1->val != node2->val) return false;
                    if (!isSame(node1->left, node2->right)) return false;
                    return isSame(node1->right, node2->left);
                };
                return isSame(root, root);
            }
            static bool isSymmetric_2(TreeNode* root) {
                deque<TreeNode *> deq;
                deq.push_front(root);
                deq.push_back(root);
                TreeNode * node1;
                TreeNode * node2;
                while (!deq.empty()) {
                    node1 = deq.front();
                    deq.pop_front();
                    node2 = deq.back();
                    deq.pop_back();
                    if (node1 == nullptr && node2 == nullptr) continue;
                    if (node1 == nullptr || node2 == nullptr) return false;
                    if (node1->val != node2->val) return false;
                    deq.push_front(node1->right);
                    deq.push_front(node1->left);
                    deq.push_back(node2->left);
                    deq.push_back(node2->right);
                }
                return true;
            }

            // 102. Binary Tree Level Order Traversal
            // Given a binary tree, return the level order traversal of its nodes'
            // values.
            // (ie, from left to right, level by level).
            // For example :
            // Given binary tree[3, 9, 20, null, null, 15, 7],
            //   3
            //  / \
            // 9  20
            //    / \
            //  15   7
            // return its level order traversal as :
            // [
            //  [3],
            //  [9, 20],
            //  [15, 7]
            // ]
            static vector<vector<int>> levelOrder(TreeNode* root) {
                vector<vector<int>> result;
                if (root == nullptr) return result;
                queue<TreeNode *> q[2];
                q[0].push(root);
                int level = 0;
                while (!q[0].empty() || !q[1].empty()) {
                    int currentLevel = level % 2;
                    int nextLevel = (level + 1) % 2;
                    vector<int> v;
                    TreeNode * node;
                    while (!q[currentLevel].empty()) {
                        node = q[currentLevel].front();
                        q[currentLevel].pop();
                        v.push_back(node->val);
                        if (node->left != nullptr) q[nextLevel].push(node->left);
                        if (node->right != nullptr) q[nextLevel].push(node->right);
                    }
                    result.push_back(v);
                    level++;
                }
                return result;
            }

            // 103. Binary Tree Zigzag Level Order Traversal
            // Given a binary tree, return the zigzag level order traversal of its nodes' values.
            // (ie, from left to right, then right to left for the next level and alternate between).
            // For example :
            // Given binary tree [3, 9, 20, null, null, 15, 7],
            //   3
            //  / \
            // 9  20
            //    / \
            //  15   7
            // return its zigzag level order traversal as :
            // [
            //  [3],
            //  [20, 9],
            //  [15, 7]
            // ]
            static vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
                vector<vector<int>> result;
                if (root == nullptr) return result;
                deque<TreeNode *> q[2];
                int level = 0;
                bool leftToRight = true;
                q[0].push_back(root);
                while (!q[0].empty() || !q[1].empty()) {
                    int currentLevel = level % 2;
                    int nextLevel = (level + 1) % 2;
                    vector<int> v;
                    TreeNode * node;
                    if (leftToRight) {
                        while (!q[currentLevel].empty()) {
                            node = q[currentLevel].front();
                            q[currentLevel].pop_front();
                            v.push_back(node->val);
                            if (node->left != nullptr) q[nextLevel].push_back(node->left);
                            if (node->right != nullptr) q[nextLevel].push_back(node->right);
                        }
                    }
                    else {
                        while (!q[currentLevel].empty()) {
                            node = q[currentLevel].back();
                            q[currentLevel].pop_back();
                            v.push_back(node->val);
                            if (node->right != nullptr) q[nextLevel].push_front(node->right);
                            if (node->left != nullptr) q[nextLevel].push_front(node->left);
                        }
                    }
                    result.push_back(v);
                    level++;
                    leftToRight = !leftToRight;
                }
                return result;
            }

            // 104. Maximum Depth of Binary Tree
            // Given a binary tree, find its maximum depth.
            // The maximum depth is the number of nodes along the longest path
            // from the root node down to the farthest leaf node.
            static int maxDepth(TreeNode* root) {
                function<int(TreeNode *)>
                    depth = [&](TreeNode * node) -> int
                {
                    if (node == nullptr) return 0;
                    if (node->left == nullptr && node->right == nullptr) return 1;
                    return 1 + max(depth(node->left), depth(node->right));
                };
                return depth(root);
            }
            // This is wrong
            static int maxDepth_2(TreeNode* root) {
                if (root == nullptr) return 0;
                stack<TreeNode *> path;
                path.push(root);
                TreeNode * node;
                int depth = 1;
                int maxDepth = 0;
                while (!path.empty()) {
                    if (depth > maxDepth) {
                        maxDepth = depth;
                    }
                    node = path.top();
                    path.pop();
                    if (node->right == nullptr && node->left == nullptr) {
                        depth--;
                    }
                    else {
                        depth++;
                        if (node->right != nullptr) path.push(node->right);
                        if (node->left != nullptr) path.push(node->left);
                    }
                }
                return maxDepth;
            }

            // 105. Construct Binary Tree from Preorder and Inorder Traversal
            // Given preorder and inorder traversal of a tree, construct the binary tree.
            // Note: You may assume that duplicates do not exist in the tree.
            static TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
                function<TreeNode * (int, int, int, int)>
                    build = [&](int i1, int i2, int j1, int j2) -> TreeNode *
                {
                    if (i1 > i2) return nullptr;
                    TreeNode * node = new TreeNode(preorder[i1]);
                    int k;
                    for (k = j1; k <= j2; k++) {
                        if (preorder[i1] == inorder[k]) break;
                    }
                    if (k <= j2) {
                        node->left = build(i1 + 1, i1 + k - j1, j1, k - 1);
                        node->right = build(i1 + k - j1 + 1, i2, k + 1, j2);
                    }
                    return node;
                };
                return build(0, preorder.size() - 1, 0, inorder.size() - 1);
            }

            // 106. Construct Binary Tree from Inorder and Postorder Traversal
            // Given inorder and postorder traversal of a tree, construct the binary tree.
            // Note: You may assume that duplicates do not exist in the tree.
            static TreeNode* buildTreeInOrderPostOrder(vector<int>& inorder, vector<int>& postorder) {
                function<TreeNode * (int, int, int, int)>
                    build = [&](int i1, int i2, int j1, int j2) -> TreeNode *
                {
                    if (j1 > j2) return nullptr;
                    TreeNode * node = new TreeNode(postorder[j2]);
                    int k;
                    for (k = i1; k <= i2; k++) {
                        if (inorder[k] == postorder[j2]) break;
                    }
                    if (k <= i2) {
                        node->left = build(i1, k - 1, j1, j2 - i2 + k - 1);
                        node->right = build(k + 1, i2, j2 - i2 + k, j2 - 1);
                    }
                    return node;
                };
                return build(0, inorder.size() - 1, 0, postorder.size() - 1);
            }

            // 107. Binary Tree Level Order Traversal II
            // Given a binary tree, return the bottom-up level order traversal of its nodes' values.
            // (ie, from left to right, level by level from leaf to root).
            // For example :
            // Given binary tree[3, 9, 20, null, null, 15, 7],
            //   3
            //  / \
            // 9  20
            //    / \
            //  15   7
            // return its bottom - up level order traversal as :
            // [
            //   [15, 7],
            //   [9, 20],
            //   [3]
            // ]
            static vector<vector<int>> levelOrderBottom(TreeNode* root) {
                vector<vector<int>> result;
                if (root == nullptr) return result;
                queue<TreeNode *> q[2];
                q[0].push(root);
                int level = 0;
                TreeNode * node;
                while (!q[0].empty() || !q[1].empty()) {
                    int currentLevel = level % 2;
                    int nextLevel = (level + 1) % 2;
                    vector<int> v;
                    while (!q[currentLevel].empty()) {
                        node = q[currentLevel].front();
                        q[currentLevel].pop();
                        v.push_back(node->val);
                        if (node->left != nullptr) q[nextLevel].push(node->left);
                        if (node->right != nullptr) q[nextLevel].push(node->right);
                    }
                    result.insert(result.begin(), v);
                    level++;
                }
                return result;
            }

            // 108. Convert Sorted Array to Binary Search Tree
            // Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
            static TreeNode* sortedArrayToBST(vector<int>& nums) {
                function<TreeNode * (int, int)>
                    build = [&](int i, int j) -> TreeNode *
                {
                    if (i > j) return nullptr;
                    int k = i + ((j - i) >> 1);
                    TreeNode * node = new TreeNode(nums[k]);
                    node->left = build(i, k - 1);
                    node->right = build(k + 1, j);
                    return node;
                };
                return build(0, nums.size() - 1);
            }

            // 109. Convert Sorted List to Binary Search Tree
            // Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
            static TreeNode* sortedListToBST(ListNode* head) {
                if (head == nullptr) return nullptr;
                if (head->next == nullptr) return new TreeNode(head->val);
                function<TreeNode * (ListNode *, ListNode *)>
                    build = [&](ListNode * b, ListNode * e) -> TreeNode *
                {
                    if (b == nullptr || e == nullptr) return nullptr;
                    TreeNode * node;
                    if (b == e) {
                        node = new TreeNode(b->val);
                    }
                    else if (b->next == e) {
                        node = new TreeNode(b->val);
                        node->right = new TreeNode(e->val);
                    }
                    else {
                        ListNode * p = b;
                        ListNode * q = p->next->next;
                        while (q != e && q->next != e) {
                            p = p->next;
                            q = q->next;
                            q = q->next;
                        }
                        node = new TreeNode(p->next->val);
                        node->left = build(b, p);
                        node->right = build(p->next->next, e);
                    }
                    return node;
                };
                ListNode * p = head;
                ListNode * q = p->next;
                while (q->next != nullptr && q->next->next != nullptr) {
                    p = p->next;
                    q = q->next;
                    q = q->next;
                }
                TreeNode * node = new TreeNode(p->next->val);
                node->left = build(head, p);
                node->right = build(p->next->next, q->next == nullptr ? q : q->next);
                return node;
            }

            // 110. Balanced Binary Tree
            // Given a binary tree, determine if it is height-balanced.
            // For this problem, a height-balanced binary tree is defined as a binary tree
            // in which the depth of the two subtrees of every node never differ by more than 1.
            static bool isBalanced(TreeNode* root) {
                function<bool(TreeNode *, int &)>
                    solve = [&](TreeNode * node, int & depth) -> bool
                {
                    if (node == nullptr) {
                        depth = 0;
                        return true;
                    }
                    int leftDepth;
                    if (!solve(node->left, leftDepth)) return false;
                    int rightDepth;
                    if (!solve(node->right, rightDepth)) return false;
                    if (abs(leftDepth - rightDepth) > 1) return false;
                    depth = 1 + max(leftDepth, rightDepth);
                    return true;
                };
                int depth;
                return solve(root, depth);
            }

            // 111. Minimum Depth of Binary Tree
            // Given a binary tree, find its minimum depth.
            // The minimum depth is the number of nodes along the shortest path
            // from the root node down to the nearest leaf node.
            static int minDepth(TreeNode* root) {
                function<int(TreeNode *, int)>
                    solve = [&](TreeNode * node, int depth) -> int
                {
                    if (node == nullptr) return depth;
                    depth++;
                    if (node->left == nullptr) return solve(node->right, depth);
                    else if (node->right == nullptr) return solve(node->left, depth);
                    else return min(solve(node->left, depth), solve(node->right, depth));
                };
                return solve(root, 0);
            }

            // 112. Path Sum
            // Given a binary tree and a sum, determine if the tree has a root-to-leaf path
            // such that adding up all the values along the path equals the given sum.
            // For example :
            // Given the below binary tree and sum = 22,
            //       5
            //      / \
            //     4   8
            //    /   / \
            //   11  13  4
            //  / \       \
            // 7    2      1
            // return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
            static bool hasPathSum(TreeNode* root, int sum) {
                function<bool(TreeNode *, int)>
                    solve = [&](TreeNode * node, int parentSum) -> bool
                {
                    if (node == nullptr) return false;
                    parentSum += node->val;
                    if (node->left == nullptr && node->right == nullptr) return parentSum == sum;
                    return (node->left != nullptr && solve(node->left, parentSum))
                        || (node->right != nullptr && solve(node->right, parentSum));
                };
                return solve(root, 0);
            }

            // 113. Path Sum II
            // Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
            // For example :
            // Given the below binary tree and sum = 22,
            //       5
            //      / \
            //     4   8
            //    /   / \
            //   11  13  4
            //  /  \    / \
            // 7    2  5   1
            // return
            // [
            //  [5, 4, 11, 2],
            //  [5, 8, 4, 5]
            // ]
            static vector<vector<int>> pathSum(TreeNode* root, int sum) {
                vector<vector<int>> result;
                function<void(TreeNode *, int, vector<int> &)>
                    solve = [&](TreeNode * node, int parentSum, vector<int> & parents)
                {
                    if (node == nullptr) return;
                    parentSum += node->val;
                    parents.push_back(node->val);
                    if (node->left == nullptr && node->right == nullptr) {
                        if (parentSum == sum) {
                            result.push_back(parents);
                        }
                    }
                    else {
                        if (node->left != nullptr) {
                            vector<int> v(parents);
                            solve(node->left, parentSum, v);
                        }
                        if (node->right != nullptr) {
                            vector<int> v(parents);
                            solve(node->right, parentSum, v);
                        }
                    }
                };
                vector<int> c;
                solve(root, 0, c);
                return result;
            }

            // 114. Flatten Binary Tree to Linked List
            // Given a binary tree, flatten it to a linked list in-place.
            // For example,
            // Given
            //     1
            //    / \
            //   2   5
            //  / \   \
            // 3   4   6
            // The flattened tree should look like :
            // 1
            //  \
            //   2
            //    \
            //     3
            //      \
            //       4
            //        \
            //         5
            //          \
            //           6
            static void flatten(TreeNode* root) {
                function<TreeNode *(TreeNode *)>
                    solve = [&](TreeNode * node) -> TreeNode *
                {
                    if (node == nullptr) return nullptr;
                    if (node->left == nullptr && node->right == nullptr) {
                        return node;
                    }
                    TreeNode * leftTail = solve(node->left);
                    TreeNode * rightTail = solve(node->right);
                    if (leftTail != nullptr) {
                        leftTail->right = node->right;
                        node->right = node->left;
                        node->left = nullptr;
                    }
                    return rightTail == nullptr ? leftTail : rightTail;
                };
                solve(root);
            }

            // 116. Populating Next Right Pointers in Each Node
            // Given a binary tree
            // Populate each next pointer to point to its next right node.
            // If there is no next right node, the next pointer should be set to NULL.
            // Initially, all next pointers are set to NULL.
            // Note:
            // You may only use constant extra space.
            // You may assume that it is a perfect binary tree (ie, all leaves are at the same level,
            // and every parent has two children).
            // For example,
            // Given the following perfect binary tree,
            //      1
            //    /   \
            //   2     3
            //  / \   / \
            // 4   5 6   7
            // After calling your function, the tree should look like :
            //      1->NULL
            //    /   \
            //   2 ->  3->NULL
            //  / \   / \
            // 4-> 5->6->7->NULL
            static void connect(TreeLinkNode *root) {
                TreeLinkNode * leftMost = root;
                while (leftMost != nullptr && leftMost->left != nullptr) {
                    TreeLinkNode * node = leftMost;
                    leftMost = leftMost->left;
                    TreeLinkNode * left = nullptr;
                    while (node != nullptr) {
                        if (left != nullptr) {
                            left->next = node->left;
                        }
                        node->left->next = node->right;
                        left = node->right;
                        node = node->next;
                    }
                }
            }

            // 117. Populating Next Right Pointers in Each Node II
            // Follow up for problem "Populating Next Right Pointers in Each Node".
            // What if the given tree could be any binary tree ? Would your previous solution still work ?
            // Note :
            // You may only use constant extra space.
            // For example,
            // Given the following binary tree,
            //     1
            //    / \
            //   2    3
            //  / \    \
            // 4   5    7
            // After calling your function, the tree should look like :
            //     1->NULL
            //    / \
            //   2 -> 3->NULL
            //  / \    \
            // 4-> 5 -> 7->NULL
            static void connect2(TreeLinkNode *root) {
                TreeLinkNode * leftMost = root;
                while (leftMost != nullptr) {
                    TreeLinkNode * node = leftMost;
                    leftMost = nullptr;
                    TreeLinkNode * left = nullptr;
                    while (node != nullptr) {
                        if (node->left != nullptr) {
                            if (leftMost == nullptr) {
                                leftMost = node->left;
                            }
                            if (left != nullptr) {
                                left->next = node->left;
                            }
                            left = node->left;
                        }
                        if (node->right != nullptr) {
                            if (leftMost == nullptr) {
                                leftMost = node->right;
                            }
                            if (left != nullptr) {
                                left->next = node->right;
                            }
                            left = node->right;
                        }
                        node = node->next;
                    }
                }
            }

            // 129. Sum Root to Leaf Numbers
            // Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
            // An example is the root-to-leaf path 1->2->3 which represents the number 123.
            // Find the total sum of all root-to-leaf numbers.
            // For example,
            //   1
            //  / \
                // 2   3
        // The root-to-leaf path 1->2 represents the number 12.
        // The root-to-leaf path 1->3 represents the number 13.
        // Return the sum = 12 + 13 = 25.
            static int sumNumbers(TreeNode* root) {
                function<void(TreeNode *, int, int &)>
                    sum = [&](TreeNode * node, int pathSum, int & totalSum)
                {
                    if (node == nullptr) return;
                    pathSum = pathSum * 10 + node->val;
                    if (node->left == nullptr && node->right == nullptr) {
                        totalSum += pathSum;
                        return;
                    }
                    if (node->left != nullptr) sum(node->left, pathSum, totalSum);
                    if (node->right != nullptr) sum(node->right, pathSum, totalSum);
                };
                int total = 0;
                sum(root, 0, total);
                return total;
            }

            // 144. Binary Tree Preorder Traversal
            // Given a binary tree, return the preorder traversal of its nodes' values.
            // For example :
            // Given binary tree{ 1,#,2,3 },
            //  1
            //   \
            //    2
            //   /
            //  3
            // return[1, 2, 3].
            // Note: Recursive solution is trivial, could you do it iteratively?
            static vector<int> preorderTraversal(TreeNode* root) {
                vector<int> result;
                if (root == nullptr) return result;
                stack<TreeNode *> stack;
                stack.push(root);
                TreeNode * node;
                while (!stack.empty()) {
                    node = stack.top();
                    stack.pop();
                    result.push_back(node->val);
                    if (node->right != nullptr) stack.push(node->right);
                    if (node->left != nullptr) stack.push(node->left);
                }
                return result;
            }

            // 145. Binary Tree Postorder Traversal
            // Given a binary tree, return the postorder traversal of its nodes' values.
            // For example :
            // Given binary tree{ 1,#,2,3 },
            //  1
            //   \
            //    2
            //   /
            //  3
            // return[3, 2, 1].
            // Note: Recursive solution is trivial, could you do it iteratively ?
            static vector<int> postorderTraversal(TreeNode* root) {
                vector<int> result;
                if (root == nullptr) return result;
                stack<TreeNode *> stack;
                TreeNode * lastVisited = nullptr;
                TreeNode * node = root;
                while (!stack.empty() || node != nullptr) {
                    if (node != nullptr) {
                        stack.push(node);
                        lastVisited = node;
                        node = node->left;
                    }
                    else {
                        TreeNode * top = stack.top();
                        if (top->right != nullptr && lastVisited != top->right) {
                            node = top->right;
                        }
                        else {
                            stack.pop();
                            result.push_back(top->val);
                            lastVisited = top;
                        }
                    }
                }
                return result;
            }

            // 173. Binary Search Tree Iterator
            // Implement an iterator over a binary search tree (BST).
            // Your iterator will be initialized with the root node of a BST.
            // Calling next() will return the next smallest number in the BST.
            // Note: next() and hasNext() should run in average O(1) time and
            // uses O(h) memory, where h is the height of the tree.
            class BSTIterator {
            private:
                stack<TreeNode *> _stack;
                TreeNode * _node;
            public:
                BSTIterator(TreeNode *root) {
                    _node = root;
                }

                /** @return whether we have a next smallest number */
                bool hasNext() {
                    return !_stack.empty() || _node != nullptr;
                }

                /** @return the next smallest number */
                int next() {
                    int val;
                    while (hasNext()) {
                        if (_node != nullptr) {
                            _stack.push(_node);
                            _node = _node->left;
                        }
                        else {
                            _node = _stack.top();
                            _stack.pop();
                            val = _node->val;
                            _node = _node->right;
                            break;
                        }
                    }
                    return val;
                }
            };

            // 199. Binary Tree Right Side View
            // Given a binary tree, imagine yourself standing on the right side of it,
            // return the values of the nodes you can see ordered from top to bottom.
            // For example :
            // Given the following binary tree,
            //   1      <---
            //  / \
            // 2   3    <---
            //  \   \
            //   5   4  <---
            // You should return[1, 3, 4].
            static vector<int> rightSideView(TreeNode* root) {
                vector<int> result;
                if (root == nullptr) return result;
                queue<TreeNode *> q[2];
                q[0].push(root);
                int level = 0;
                int current = 0;
                int next = 0;
                TreeNode * p;
                while (!q[0].empty() || !q[1].empty()) {
                    current = level % 2;
                    next = (level + 1) % 2;
                    p = q[current].front();
                    result.push_back(p->val);
                    while (!q[current].empty()) {
                        p = q[current].front();
                        q[current].pop();
                        if (p->right != nullptr) {
                            q[next].push(p->right);
                        }
                        if (p->left != nullptr) {
                            q[next].push(p->left);
                        }
                    }
                    level++;
                }
                return result;
            }
        }
    }
}
