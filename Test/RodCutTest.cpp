#include "RodCutTest.h"

void RodCutTest::Init(void)
{
	Add("ComputeFirstCut", [&](){
		vector<double> utility;
		utility.push_back(1);
		utility.push_back(5);
		utility.push_back(8);
		utility.push_back(9);
		utility.push_back(10);
		utility.push_back(17);
		utility.push_back(17);
		utility.push_back(20);
		utility.push_back(24);
		utility.push_back(30);

		for (unsigned int i = 0; i < utility.size(); i ++) {
			cout << utility[i] << " ";
		}

		cout << endl;

		vector<double> maxUtility(utility.size());
		vector<int> firstCut(utility.size());

		Test::RodCut::ComputeFirstCut(utility, maxUtility, firstCut);

		cout << "Index\tUtility\tMaxUtility\tFirstCut" << endl;
		for (unsigned int i = 0; i < utility.size(); i ++) {
			cout << i << "\t" << utility[i] << "\t" << maxUtility[i] << "\t" << firstCut[i] << endl;
		}
	});

	Add("PrintResult", [&](){
		vector<double> utility;
		utility.push_back(1);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(5);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(8);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(9);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(10);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(17);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(17);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(20);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(24);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
		utility.push_back(30);
		cout << utility.size() - 1 << ": ";
		Test::RodCut::PrintResult(utility);
	});
}