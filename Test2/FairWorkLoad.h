#pragma once
namespace My {
	class FairWorkLoad {
	public:
		FairWorkLoad(void) {}
		~FairWorkLoad(void) {}
		static void ComputeSumTable(int * input, int length, int partitions, int * sum);
	};

}

