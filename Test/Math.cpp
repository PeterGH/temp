#include "Math.h"
namespace Test {

	
	
	
	
	// Binary tree branch (root-to-leaf path) represents a number with each node as a digit.
	// Sum all branch numbers.
	// 1____2
	//  |___8
	// 12 + 18 = 30
	unsigned long long Math::BinaryTreeSumBranches(BinaryNode<unsigned int> * node)
	{
		if (node == nullptr) return 0;
		stack<BinaryNode<unsigned int> *> path;
		map<BinaryNode<unsigned int> *, unsigned long long> number;
		unsigned long long sum = 0;
		number[node] = node->Value();
		path.push(node);
		while (!path.empty()) {
			node = path.top();
			path.pop();
			if (node->Left() == nullptr && node->Right() == nullptr) {
				sum += number[node];
			}
			if (node->Right() != nullptr) {
				number[node->Right()] = 10 * number[node] + node->Right()->Value();
				path.push(node->Right());
			}
			if (node->Left() != nullptr) {
				number[node->Left()] = 10 * number[node] + node->Left()->Value();
				path.push(node->Left());
			}
		}
		return sum;
	}

	// In a binary tree find a path where the sum of node values is maximized.
	long long Math::BinaryTreeMaxPathSum(BinaryNode<int> * root, vector<BinaryNode<int> *> & path)
	{
		if (root == nullptr) return 0;

		function<void(BinaryNode<int> *, long long &, vector<BinaryNode<int> *> &, long long &, vector<BinaryNode<int> *> &)>
		search = [&](
			BinaryNode<int> * node,
			long long & currentSum,
			vector<BinaryNode<int> *> & currentPath,
			long long & maxSum,
			vector<BinaryNode<int> *> & maxPath)
		{
			currentSum = 0;
			currentPath.clear();
			maxSum = 0;
			maxPath.clear();
			if (node == nullptr) return;

			if (node->Left() == nullptr && node->Right() == nullptr) {
				currentSum = node->Value();
				currentPath.push_back(node);
				maxSum = node->Value();
				maxPath.push_back(node);
				return;
			}

			long long leftSum;
			vector<BinaryNode<int> *> leftPath;
			long long leftMaxSum;
			vector<BinaryNode<int> *> leftMaxPath;
			search(node->Left(), leftSum, leftPath, leftMaxSum, leftMaxPath);

			long long rightSum;
			vector<BinaryNode<int> *> rightPath;
			long long rightMaxSum;
			vector<BinaryNode<int> *> rightMaxPath;
			search(node->Right(), rightSum, rightPath, rightMaxSum, rightMaxPath);

			if (node->Left() != nullptr && node->Right() == nullptr) {
				maxSum = leftMaxSum;
				maxPath.insert(maxPath.begin(), leftMaxPath.begin(), leftMaxPath.end());

				if (leftSum <= 0) {
					currentSum = node->Value();
					currentPath.push_back(node);

					if (node->Value() > maxSum) {
						maxSum = node->Value();
						maxPath.clear();
						maxPath.push_back(node);
					}
				} else {
					currentSum = leftSum + node->Value();
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());

					if (leftSum + node->Value() > maxSum) {
						maxSum = leftSum + node->Value();
						maxPath.clear();
						maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
						maxPath.push_back(node);
					}
				}
			} else if (node->Left() == nullptr && node->Right() != nullptr) {
				maxSum = rightMaxSum;
				maxPath.insert(maxPath.begin(), rightMaxPath.begin(), rightMaxPath.end());

				if (rightSum <= 0) {
					currentSum = node->Value();
					currentPath.push_back(node);

					if (node->Value() > maxSum) {
						maxSum = node->Value();
						maxPath.clear();
						maxPath.push_back(node);
					}
				} else {
					currentSum = node->Value() + rightSum;
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());

					if (node->Value() + rightSum > maxSum) {
						maxSum = node->Value() + rightSum;
						maxPath.clear();
						maxPath.push_back(node);
						maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
					}
				}
			} else {
				if (leftMaxSum >= rightMaxSum) {
					maxSum = leftMaxSum;
					maxPath.insert(maxPath.begin(), leftMaxPath.begin(), leftMaxPath.end());
				} else {
					maxSum = rightMaxSum;
					maxPath.insert(maxPath.begin(), rightMaxPath.begin(), rightMaxPath.end());
				}

				if (leftSum <= 0 && rightSum <= 0) {
					currentSum = node->Value();
					currentPath.push_back(node);

					if (node->Value() > maxSum) {
						maxSum = node->Value();
						maxPath.clear();
						maxPath.push_back(node);
					}
				} else if (leftSum > 0 && rightSum <= 0) {
					currentSum = leftSum + node->Value();
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());

					if (leftSum + node->Value() > maxSum) {
						maxSum = leftSum + node->Value();
						maxPath.clear();
						maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
						maxPath.push_back(node);
					}
				} else if (leftSum <= 0 && rightSum > 0) {
					currentSum = node->Value() + rightSum;
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());

					if (node->Value() + rightSum > maxSum) {
						maxSum = node->Value() + rightSum;
						maxPath.clear();
						maxPath.push_back(node);
						maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
					}
				} else {
					if (leftSum >= rightSum) {
						currentSum = leftSum + node->Value();
						currentPath.push_back(node);
						currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());
					} else {
						currentSum = node->Value() + rightSum;
						currentPath.push_back(node);
						currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());
					}

					if (leftSum + node->Value() + rightSum > maxSum) {
						maxSum = leftSum + node->Value() + rightSum;
						maxPath.clear();
						maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
						maxPath.push_back(node);
						maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
					}
				}
			}
		};

		long long currentSum;
		vector<BinaryNode<int> *> currentPath;
		long long max;
		search(root, currentSum, currentPath, max, path);
		return max;
	}

	//         0
	//    1          2
	//  3   4     5     6
	// 7 8 9 10 11 12 13 14
	// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
	// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
	//
	// 2^(H - 1) <= count <= 2^H - 1
	// There are H bits and the pattern is between:
	// 10000 ... 000
	// 11111 ... 111
	unsigned int Math::Tree::Height(unsigned int count)
	{
		unsigned int h = 0;
		while (count > 0) {
			count = count >> 1;
			h++;
		}
		return h;
	}

	// d-ary
	//                                                  0
	//                   1                              2                    ...          d
	// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
	// (d^2+d+1) (d^2+d+2) ...
	// ......
	// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
	// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]
	//
	// (d^(h-1)-1)/(d-1) < count <= (d^h-1)/(d-1)
	// d^(h-1) - 1 < count * (d-1) <= d^h - 1
	// There are h d-bits and the pattern is between:
	//  1    0    0    ...  0    0    0
	// (d-1)(d-1)(d-1) ... (d-1)(d-1)(d-1)
	unsigned int Math::Tree::Height(unsigned int count, unsigned int d)
	{
		count = count * (d - 1);
		unsigned int h = 0;
		while (count > 0) {
			count = count / d;
			h++;
		}
		return h;
	}
}