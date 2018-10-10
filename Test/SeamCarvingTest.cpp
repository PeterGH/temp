#include "SeamCarvingTest.h"

void SeamCarvingTest::Init(void)
{
	Add("1", [&](){
		Matrix<int> input(1, 1);
		input(0, 0) = 2;
		Matrix<int> seams(1, 1);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 2);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 1);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 0);
	});

	Add("2", [&](){
		Matrix<int> input(1, 2);
		input(0, 0) = 2;
		input(0, 1) = 2;
		Matrix<int> seams(1, 2);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 2);
		ASSERT1(seams(0, 1) == 2);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 1);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 0);
	});

	Add("3", [&](){
		Matrix<int> input(1, 2);
		input(0, 0) = 1;
		input(0, 1) = 2;
		Matrix<int> seams(1, 2);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 1);
		ASSERT1(seams(0, 1) == 2);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 1);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 0);
	});

	Add("4", [&](){
		Matrix<int> input(1, 2);
		input(0, 0) = 2;
		input(0, 1) = 1;
		Matrix<int> seams(1, 2);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 2);
		ASSERT1(seams(0, 1) == 1);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 1);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 1);
	});

	Add("5", [&](){
		Matrix<int> input(2, 1);
		input(0, 0) = 2;
		input(1, 0) = 2;
		Matrix<int> seams(2, 1);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 2);
		ASSERT1(seams(1, 0) == 4);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 2);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 0);
		ASSERT1(seam[1].first == 1);
		ASSERT1(seam[1].second == 0);
	});

	Add("6", [&](){
		Matrix<int> input(2, 2);
		input(0, 0) = 0;
		input(0, 1) = 2;
		input(1, 0) = 0;
		input(1, 1) = 2;
		Matrix<int> seams(2, 2);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 0);
		ASSERT1(seams(0, 1) == 2);
		ASSERT1(seams(1, 0) == 0);
		ASSERT1(seams(1, 1) == 2);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 2);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 0);
		ASSERT1(seam[1].first == 1);
		ASSERT1(seam[1].second == 0);
	});

	Add("7", [&](){
		Matrix<int> input(2, 2);
		input(0, 0) = 2;
		input(0, 1) = 0;
		input(1, 0) = 2;
		input(1, 1) = 0;
		Matrix<int> seams(2, 2);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 2);
		ASSERT1(seams(0, 1) == 0);
		ASSERT1(seams(1, 0) == 2);
		ASSERT1(seams(1, 1) == 0);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 2);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 1);
		ASSERT1(seam[1].first == 1);
		ASSERT1(seam[1].second == 1);
	});

	Add("8", [&](){
		Matrix<int> input(2, 2);
		input(0, 0) = 0;
		input(0, 1) = 2;
		input(1, 0) = 2;
		input(1, 1) = 0;
		Matrix<int> seams(2, 2);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 0);
		ASSERT1(seams(0, 1) == 2);
		ASSERT1(seams(1, 0) == 2);
		ASSERT1(seams(1, 1) == 0);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 2);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 0);
		ASSERT1(seam[1].first == 1);
		ASSERT1(seam[1].second == 1);
	});

	Add("9", [&](){
		Matrix<int> input(2, 2);
		input(0, 0) = 2;
		input(0, 1) = 0;
		input(1, 0) = 0;
		input(1, 1) = 2;
		Matrix<int> seams(2, 2);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		ASSERT1(seams(0, 0) == 2);
		ASSERT1(seams(0, 1) == 0);
		ASSERT1(seams(1, 0) == 0);
		ASSERT1(seams(1, 1) == 2);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 2);
		ASSERT1(seam[0].first == 0);
		ASSERT1(seam[0].second == 1);
		ASSERT1(seam[1].first == 1);
		ASSERT1(seam[1].second == 0);
	});

	Add("10", [&](){
		Matrix<int> input(10, 10);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				input(i, j) = i * 10 + j;
			}
		}

		Matrix<int> seams(10, 10);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		Logger().Print(seams);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 10);
		for (int j = 0; j < 10; j++) {
			cout << j << "\t(" << seam[j].first << ", " << seam[j].second << ")" << endl;
			ASSERT1(seam[j].first == j);
			ASSERT1(seam[j].second == 0);
		}
	});

	Add("11", [&](){
		Matrix<int> input(10, 10);
		int v = 100;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				input(i, j) = v--;
			}
		}

		Matrix<int> seams(10, 10);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		Logger().Print(seams);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 10);
		for (int j = 0; j < 10; j++) {
			cout << j << "\t(" << seam[j].first << ", " << seam[j].second << ")" << endl;
			ASSERT1(seam[j].first == j);
			ASSERT1(seam[j].second == 9);
		}
	});

	Add("12", [&](){
		Matrix<int> input(10, 10);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				input(i, j) = Test::Random::Next();
			}
		}

		Matrix<int> seams(10, 10);
		Test::SeamCarving<int>::ComputeSeams(input, seams);
		Logger().Print(seams);
		vector<pair<size_t, size_t>> seam;
		Test::SeamCarving<int>::MinSeam(input, seam);
		ASSERT1(seam.size() == 10);
		for (int j = 0; j < 10; j++) {
			cout << j << "\t(" << seam[j].first << ", " << seam[j].second << ")" << endl;
		}
	});
}