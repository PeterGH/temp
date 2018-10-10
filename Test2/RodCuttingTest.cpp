#include "RodCuttingTest.h"


void RodCuttingTest::Init(void)
{
	Add("RodCutting", [&](){
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

		My::RodCutting::ComputeFirstCut(utility, maxUtility, firstCut);

		cout << "Index\tUtility\tMaxUtility\tFirstCut" << endl;
		for (unsigned int i = 0; i < utility.size(); i ++) {
			cout << i << "\t" << utility[i] << "\t" << maxUtility[i] << "\t" << firstCut[i] << endl;
		}

		vector<double> utility2;
		utility2.push_back(1);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(5);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(8);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(9);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(10);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(17);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(17);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(20);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(24);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
		utility2.push_back(30);
		cout << utility2.size() - 1 << ": ";
		My::RodCutting::PrintResult(utility2);
	});
}
