#pragma once

namespace My {
	class __declspec(dllexport) MatrixChain {
	public:
		MatrixChain(void) {}
		~MatrixChain(void) {}
		static void ComputeCostTable(int * dimension, int count, int * cost, int * split);
	};
}

