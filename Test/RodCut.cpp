#include "RodCut.h"
namespace Test {

	// Indices:
	//   i = 0   1   2   3   ... i   ... n
	// Utilities:
	//   u = u_0 u_1 u_2 u_3 ... u_i ... u_n
	// Max utilities:
	//   m = m_0 m_1 m_2 m_3 ... m_i ... m_n
	//   m_0 = u_0
	//   m_1 = max((u_0 + m_0), u_1)
	//   m_2 = max((u_0 + m_1), (u_1 + m_0), u_2)
	//   ...
	//   m_i = max((u_0 + m_(i-1)), (u_1 + m_(i-2)), (u_2 + m_(i-3)), ... (u_(i-1) + m_0), u_i)
	void RodCut::ComputeFirstCut(const vector<double> & utility, vector<double> & maxUtility, vector<int> & firstCut)
	{
		if (utility.size() == 0) return;

		maxUtility[0] = utility[0];
		firstCut[0] = 0;

		for (unsigned int i = 1; i < utility.size(); i ++) {
			maxUtility[i] = -1;
			for (unsigned int j = 0; j < i; j ++) {
				double current = utility[j] + maxUtility[i - j - 1];
				if (maxUtility[i] < current) {
					maxUtility[i] = current;
					firstCut[i] = j;
				}
			}

			if (maxUtility[i] < utility[i]) {
				maxUtility[i] = utility[i];
				firstCut[i] = i;
			}
		}
	}

	// i = 0   1   2   3   ... i   ... n
	// f = f_0 f_1 f_2 f_3 ... f_i ... f_n
	// index          cut    left
	// n              f_n    n - f_n - 1
	// n - f_n - 1
	void RodCut::PrintResult(const vector<double> & utility)
	{
		int i = (int)utility.size();
		if (i == 0) return;

		vector<double> maxUtility(i);
		vector<int> firstCut(i);

		ComputeFirstCut(utility, maxUtility, firstCut);

		i--;
		cout << utility[i] << ": " << maxUtility[i] << " = ";
		while (i >= 0) {
			int j = firstCut[i];
			cout << "utility[" << j << "]";
			i = i - firstCut[i] - 1;
			if (i >= 0) cout << " + ";
		}

		cout << endl;
	}


}